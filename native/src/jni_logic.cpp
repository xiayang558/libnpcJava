#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Binary logic — each takes jlong aHandle, jlong bHandle, returns jlong
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogicalAnd(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "logical_and");
        checkNotNull(env, bHandle, "logical_and");
        return wrapArray(std::make_unique<npc::Array>(npc::logical_and(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogicalOr(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "logical_or");
        checkNotNull(env, bHandle, "logical_or");
        return wrapArray(std::make_unique<npc::Array>(npc::logical_or(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogicalXor(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "logical_xor");
        checkNotNull(env, bHandle, "logical_xor");
        return wrapArray(std::make_unique<npc::Array>(npc::logical_xor(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogicalNot(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "logical_not");
        return wrapArray(std::make_unique<npc::Array>(npc::logical_not(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBitwiseAnd(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "bitwise_and");
        checkNotNull(env, bHandle, "bitwise_and");
        return wrapArray(std::make_unique<npc::Array>(npc::bitwise_and(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBitwiseOr(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "bitwise_or");
        checkNotNull(env, bHandle, "bitwise_or");
        return wrapArray(std::make_unique<npc::Array>(npc::bitwise_or(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBitwiseXor(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "bitwise_xor");
        checkNotNull(env, bHandle, "bitwise_xor");
        return wrapArray(std::make_unique<npc::Array>(npc::bitwise_xor(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBitwiseNot(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "bitwise_not");
        return wrapArray(std::make_unique<npc::Array>(npc::bitwise_not(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeInvert(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "invert");
        return wrapArray(std::make_unique<npc::Array>(npc::invert(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}


} // extern "C"
