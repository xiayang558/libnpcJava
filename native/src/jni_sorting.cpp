#include "jni_util.h"
using namespace npc;

extern "C" {

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSort(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "sort: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::sort(*a))));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMsort(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "msort: null input"); return 0; }
    ::Array* raw = ::msort(a->get());
    if (!raw) { throwNpcException(env, "msort failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArgsort(JNIEnv* env, jclass, jlong aHandle, jint axis, jstring jkind) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "argsort: null input"); return 0; }
    std::string kind = jstringToString(env, jkind);
    ::Array* raw = ::argsort(a->get(), axis, kind.c_str());
    if (!raw) { throwNpcException(env, "argsort failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArgpartition(JNIEnv* env, jclass, jlong aHandle, jint kth, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "argpartition: null input"); return 0; }
    ::Array* raw = ::argpartition(a->get(), kth, axis);
    if (!raw) { throwNpcException(env, "argpartition failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePartition(JNIEnv* env, jclass, jlong aHandle, jint kth, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "partition: null input"); return 0; }
    ::Array* raw = ::partition(a->get(), kth, axis);
    if (!raw) { throwNpcException(env, "partition failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeUnwrap(JNIEnv* env, jclass, jlong aHandle, jdouble discont, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "unwrap: null input"); return 0; }
    ::Array* raw = ::unwrap(a->get(), discont, axis);
    if (!raw) { throwNpcException(env, "unwrap failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

} // extern "C"
