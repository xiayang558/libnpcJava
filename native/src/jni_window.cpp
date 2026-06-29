#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Window functions — each takes a size M and returns a 1-D window array
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBartlett(JNIEnv* env, jclass, jint M) {
    try {
        return wrapArray(std::make_unique<npc::Array>(npc::bartlett(static_cast<int>(M))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBlackman(JNIEnv* env, jclass, jint M) {
    try {
        return wrapArray(std::make_unique<npc::Array>(npc::blackman(static_cast<int>(M))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeKaiser(JNIEnv* env, jclass, jint M, jdouble beta) {
    try {
        return wrapArray(std::make_unique<npc::Array>(
            npc::kaiser(static_cast<int>(M), static_cast<double>(beta))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeHanning(JNIEnv* env, jclass, jint M) {
    try {
        return wrapArray(std::make_unique<npc::Array>(npc::hanning(static_cast<int>(M))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeHamming(JNIEnv* env, jclass, jint M) {
    try {
        return wrapArray(std::make_unique<npc::Array>(npc::hamming(static_cast<int>(M))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

} // extern "C"
