#pragma once

#include <jni.h>
#include <npc/npc.hpp>
#include <memory>
#include <vector>
#include <string>
#include <cstring>

// ── Type conversions: Java → C++ ──────────────────────────────────

inline std::vector<int> jintArrayToVector(JNIEnv* env, jintArray arr) {
    if (!arr) return {};
    jsize len = env->GetArrayLength(arr);
    std::vector<int> vec(len);
    jint* elems = env->GetIntArrayElements(arr, nullptr);
    for (jsize i = 0; i < len; ++i) vec[i] = static_cast<int>(elems[i]);
    env->ReleaseIntArrayElements(arr, elems, JNI_ABORT);
    return vec;
}

inline std::vector<double> jdoubleArrayToVector(JNIEnv* env, jdoubleArray arr) {
    if (!arr) return {};
    jsize len = env->GetArrayLength(arr);
    std::vector<double> vec(len);
    jdouble* elems = env->GetDoubleArrayElements(arr, nullptr);
    for (jsize i = 0; i < len; ++i) vec[i] = elems[i];
    env->ReleaseDoubleArrayElements(arr, elems, JNI_ABORT);
    return vec;
}

inline std::vector<long> jlongArrayToVector(JNIEnv* env, jlongArray arr) {
    if (!arr) return {};
    jsize len = env->GetArrayLength(arr);
    std::vector<long> vec(len);
    jlong* elems = env->GetLongArrayElements(arr, nullptr);
    for (jsize i = 0; i < len; ++i) vec[i] = elems[i];
    env->ReleaseLongArrayElements(arr, elems, JNI_ABORT);
    return vec;
}

inline std::string jstringToString(JNIEnv* env, jstring str) {
    if (!str) return {};
    const char* chars = env->GetStringUTFChars(str, nullptr);
    std::string result(chars);
    env->ReleaseStringUTFChars(str, chars);
    return result;
}

// ── Type conversions: C++ → Java ──────────────────────────────────

inline jintArray vectorToJintArray(JNIEnv* env, const std::vector<int>& vec) {
    jintArray result = env->NewIntArray(static_cast<jsize>(vec.size()));
    env->SetIntArrayRegion(result, 0, static_cast<jsize>(vec.size()), vec.data());
    return result;
}

inline jdoubleArray vectorToJdoubleArray(JNIEnv* env, const std::vector<double>& vec) {
    jdoubleArray result = env->NewDoubleArray(static_cast<jsize>(vec.size()));
    env->SetDoubleArrayRegion(result, 0, static_cast<jsize>(vec.size()), vec.data());
    return result;
}

inline jlongArray vectorToJlongArray(JNIEnv* env, const std::vector<long>& vec) {
    jlongArray result = env->NewLongArray(static_cast<jsize>(vec.size()));
    env->SetLongArrayRegion(result, 0, static_cast<jsize>(vec.size()), vec.data());
    return result;
}

// ── Native handle management ──────────────────────────────────────

// We store a pointer to a heap-allocated std::unique_ptr<npc::Array>.
// This double indirection lets Java hold an opaque jlong while the
// unique_ptr handles RAII cleanup.

using ArrayHandle = std::unique_ptr<npc::Array>;

inline jlong wrapArray(std::unique_ptr<npc::Array> arr) {
    if (!arr || arr->is_null()) return 0;
    auto* handle = new ArrayHandle(std::move(arr));
    return reinterpret_cast<jlong>(handle);
}

inline npc::Array* unwrapArray(jlong handle) {
    if (handle == 0) return nullptr;
    auto* h = reinterpret_cast<ArrayHandle*>(handle);
    return h->get();
}

inline void freeHandle(jlong handle) {
    if (handle == 0) return;
    delete reinterpret_cast<ArrayHandle*>(handle);
}

// Create a Java NpcArray object from a native handle.
// Returns the jfieldID cache approach via a helper function.
inline jobject createNpcArrayObject(JNIEnv* env, jlong handle) {
    jclass cls = env->FindClass("libnpc/NpcArray");
    if (!cls) return nullptr;
    jmethodID ctor = env->GetMethodID(cls, "<init>", "(J)V");
    if (!ctor) return nullptr;
    return env->NewObject(cls, ctor, handle);
}

// ── Exception helpers ─────────────────────────────────────────────

inline void throwNpcException(JNIEnv* env, const char* msg) {
    jclass cls = env->FindClass("java/lang/RuntimeException");
    if (cls) env->ThrowNew(cls, msg);
}

inline void checkNotNull(JNIEnv* env, jlong handle, const char* func) {
    if (handle == 0) {
        char buf[256];
        snprintf(buf, sizeof(buf), "%s: NpcArray is closed or null", func);
        throwNpcException(env, buf);
    }
}

// ── Get native handle from Java NpcArray ──────────────────────────

inline jlong getNativeHandle(JNIEnv* env, jobject npcArray) {
    jclass cls = env->GetObjectClass(npcArray);
    jfieldID fid = env->GetFieldID(cls, "nativePtr", "J");
    if (!fid) return 0;
    return env->GetLongField(npcArray, fid);
}

// ── Helper: convert Java NpcArray[] to vector of npc::Array* ─────

inline std::vector<npc::Array*> toArrayVec(JNIEnv* env, jobjectArray arr) {
    std::vector<npc::Array*> result;
    if (!arr) return result;
    jsize len = env->GetArrayLength(arr);
    result.reserve(len);
    for (jsize i = 0; i < len; ++i) {
        jobject elem = env->GetObjectArrayElement(arr, i);
        result.push_back(unwrapArray(getNativeHandle(env, elem)));
        env->DeleteLocalRef(elem);
    }
    return result;
}

// ── Get field IDs cache ───────────────────────────────────────────

// Field IDs for NpcArray.nativePtr (cached for performance)
inline jfieldID getNativePtrFieldID(JNIEnv* env, jobject obj) {
    static jfieldID fid = nullptr;
    if (!fid) {
        jclass cls = env->GetObjectClass(obj);
        fid = env->GetFieldID(cls, "nativePtr", "J");
    }
    return fid;
}
