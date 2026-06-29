#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Npc — Comparison operators
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeEqual(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        return wrapArray(std::make_unique<npc::Array>(npc::equal(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNotEqual(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        return wrapArray(std::make_unique<npc::Array>(npc::not_equal(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGreater(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        return wrapArray(std::make_unique<npc::Array>(npc::greater(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGreaterEqual(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        return wrapArray(std::make_unique<npc::Array>(npc::greater_equal(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLess(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        return wrapArray(std::make_unique<npc::Array>(npc::less(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLessEqual(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        return wrapArray(std::make_unique<npc::Array>(npc::less_equal(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIsclose(JNIEnv* env, jclass, jlong aHandle, jlong bHandle,
                               jdouble rtol, jdouble atol, jboolean equalNan) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        return wrapArray(std::make_unique<npc::Array>(
            npc::isclose(*a, *b, rtol, atol, equalNan == JNI_TRUE)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

} // extern "C"
