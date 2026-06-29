#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// 1-D linear interpolation
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeInterp(JNIEnv* env, jclass, jlong arrHandle, jlong xpHandle,
                              jlong fpHandle, jlong leftHandle, jlong rightHandle) {
    try {
        auto* arr = unwrapArray(arrHandle);
        auto* xp = unwrapArray(xpHandle);
        auto* fp = unwrapArray(fpHandle);
        checkNotNull(env, arrHandle, "interp");
        checkNotNull(env, xpHandle, "interp");
        checkNotNull(env, fpHandle, "interp");

        npc::Array left = (leftHandle != 0) ? npc::Array(*unwrapArray(leftHandle))
                                            : npc::Array();
        npc::Array right = (rightHandle != 0) ? npc::Array(*unwrapArray(rightHandle))
                                              : npc::Array();

        return wrapArray(std::make_unique<npc::Array>(
            npc::interp(*arr, *xp, *fp, left, right)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// n-th difference along axis
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDiff(JNIEnv* env, jclass, jlong aHandle, jint n, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "diff");
        return wrapArray(std::make_unique<npc::Array>(
            npc::diff(*a, static_cast<int>(n), static_cast<int>(axis))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Differences between adjacent elements (ediff1d)
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeEdiff1d(JNIEnv* env, jclass, jlong yHandle,
                               jlong toBeginHandle, jlong toEndHandle) {
    try {
        auto* y = unwrapArray(yHandle);
        checkNotNull(env, yHandle, "ediff1d");

        npc::Array to_begin = (toBeginHandle != 0) ? npc::Array(*unwrapArray(toBeginHandle))
                                                   : npc::Array();
        npc::Array to_end = (toEndHandle != 0) ? npc::Array(*unwrapArray(toEndHandle))
                                               : npc::Array();

        return wrapArray(std::make_unique<npc::Array>(
            npc::ediff1d(*y, to_begin, to_end)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// N-D gradient — returns NpcArray[]
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativeGradient(JNIEnv* env, jclass cls,
                                jlong aHandle, jlong spacingHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "gradient");

        std::vector<npc::Array> result;
        if (spacingHandle != 0) {
            auto* spacing = unwrapArray(spacingHandle);
            result = npc::gradient(*a, *spacing);
        } else {
            result = npc::gradient(*a);
        }

        jclass npcArrayCls = env->FindClass("libnpc/NpcArray");
        jobjectArray arr = env->NewObjectArray(
            static_cast<jsize>(result.size()), npcArrayCls, nullptr);

        for (size_t i = 0; i < result.size(); ++i) {
            jobject elem = createNpcArrayObject(env,
                wrapArray(std::make_unique<npc::Array>(std::move(result[i]))));
            env->SetObjectArrayElement(arr, static_cast<jsize>(i), elem);
            env->DeleteLocalRef(elem);
        }

        return arr;
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

} // extern "C"
