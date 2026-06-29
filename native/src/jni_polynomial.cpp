#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Polynomial creation from roots
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePoly(JNIEnv* env, jclass, jlong rootsHandle) {
    try {
        auto* roots = unwrapArray(rootsHandle);
        checkNotNull(env, rootsHandle, "poly");
        return wrapArray(std::make_unique<npc::Array>(npc::poly(*roots)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Roots of a polynomial
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRoots(JNIEnv* env, jclass, jlong pHandle) {
    try {
        auto* p = unwrapArray(pHandle);
        checkNotNull(env, pHandle, "roots");
        return wrapArray(std::make_unique<npc::Array>(npc::roots(*p)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Polynomial arithmetic
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePolyadd(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "polyadd");
        checkNotNull(env, bHandle, "polyadd");
        return wrapArray(std::make_unique<npc::Array>(npc::polyadd(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePolysub(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "polysub");
        checkNotNull(env, bHandle, "polysub");
        return wrapArray(std::make_unique<npc::Array>(npc::polysub(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePolymul(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "polymul");
        checkNotNull(env, bHandle, "polymul");
        return wrapArray(std::make_unique<npc::Array>(npc::polymul(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Polynomial division — returns [quotient, remainder]
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativePolydiv(JNIEnv* env, jclass, jlong uHandle, jlong vHandle) {
    try {
        auto* u = unwrapArray(uHandle);
        auto* v = unwrapArray(vHandle);
        checkNotNull(env, uHandle, "polydiv");
        checkNotNull(env, vHandle, "polydiv");

        auto result = npc::polydiv(*u, *v);

        jclass npcArrayCls = env->FindClass("libnpc/NpcArray");
        jobjectArray arr = env->NewObjectArray(2, npcArrayCls, nullptr);

        jobject qObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.first))));
        jobject rObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.second))));

        env->SetObjectArrayElement(arr, 0, qObj);
        env->SetObjectArrayElement(arr, 1, rObj);

        env->DeleteLocalRef(qObj);
        env->DeleteLocalRef(rObj);

        return arr;
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Polynomial derivative
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePolyder(JNIEnv* env, jclass, jlong pHandle, jint m) {
    try {
        auto* p = unwrapArray(pHandle);
        checkNotNull(env, pHandle, "polyder");
        return wrapArray(std::make_unique<npc::Array>(npc::polyder(*p, static_cast<int>(m))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Polynomial integral
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePolyint(JNIEnv* env, jclass, jlong pHandle, jint m) {
    try {
        auto* p = unwrapArray(pHandle);
        checkNotNull(env, pHandle, "polyint");
        return wrapArray(std::make_unique<npc::Array>(npc::polyint(*p, static_cast<int>(m))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Polynomial evaluation
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePolyval(JNIEnv* env, jclass, jlong pHandle, jlong xHandle) {
    try {
        auto* p = unwrapArray(pHandle);
        auto* x = unwrapArray(xHandle);
        checkNotNull(env, pHandle, "polyval");
        checkNotNull(env, xHandle, "polyval");
        return wrapArray(std::make_unique<npc::Array>(npc::polyval(*p, *x)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Least-squares polynomial fit
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePolyfit(JNIEnv* env, jclass, jlong xHandle, jlong yHandle, jint deg) {
    try {
        auto* x = unwrapArray(xHandle);
        auto* y = unwrapArray(yHandle);
        checkNotNull(env, xHandle, "polyfit");
        checkNotNull(env, yHandle, "polyfit");
        return wrapArray(std::make_unique<npc::Array>(npc::polyfit(*x, *y, static_cast<int>(deg))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

} // extern "C"
