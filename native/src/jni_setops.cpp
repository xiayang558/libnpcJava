#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Unique — returns a libnpc/UniqueResult Java object
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeUnique(JNIEnv* env, jclass, jlong aHandle,
                              jboolean returnIndex, jboolean returnInverse,
                              jboolean returnCounts) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "unique");
        auto result = npc::unique(*a, returnIndex == JNI_TRUE,
                                  returnInverse == JNI_TRUE,
                                  returnCounts == JNI_TRUE);
        jclass cls = env->FindClass("libnpc/UniqueResult");
        jmethodID ctor = env->GetMethodID(cls, "<init>",
            "(Llibnpc/NpcArray;Llibnpc/NpcArray;Llibnpc/NpcArray;Llibnpc/NpcArray;)V");
        jobject valuesObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.values))));
        jobject indicesObj = result.indices.is_null() ? nullptr : createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.indices))));
        jobject inverseObj = result.inverse.is_null() ? nullptr : createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.inverse))));
        jobject countsObj = result.counts.is_null() ? nullptr : createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.counts))));
        return env->NewObject(cls, ctor, valuesObj, indicesObj, inverseObj, countsObj);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Other set operations — each returns jlong
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIntersect1d(JNIEnv* env, jclass, jlong aHandle, jlong bHandle,
                                   jboolean assumeUnique) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "intersect1d");
        checkNotNull(env, bHandle, "intersect1d");
        return wrapArray(std::make_unique<npc::Array>(
            npc::intersect1d(*a, *b, assumeUnique == JNI_TRUE)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSetdiff1d(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "setdiff1d");
        checkNotNull(env, bHandle, "setdiff1d");
        return wrapArray(std::make_unique<npc::Array>(npc::setdiff1d(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSearchsorted(JNIEnv* env, jclass, jlong aHandle,
                                    jlong vHandle, jstring side) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* v = unwrapArray(vHandle);
        checkNotNull(env, aHandle, "searchsorted");
        checkNotNull(env, vHandle, "searchsorted");
        std::string sideStr = jstringToString(env, side);
        return wrapArray(std::make_unique<npc::Array>(
            npc::searchsorted(*a, *v, sideStr.c_str())));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDigitize(JNIEnv* env, jclass, jlong aHandle,
                                jlong binsHandle, jboolean right) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* bins = unwrapArray(binsHandle);
        checkNotNull(env, aHandle, "digitize");
        checkNotNull(env, binsHandle, "digitize");
        return wrapArray(std::make_unique<npc::Array>(
            npc::digitize(*a, *bins, right == JNI_TRUE)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArgwhere(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "argwhere");
        return wrapArray(std::make_unique<npc::Array>(npc::argwhere(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

} // extern "C"
