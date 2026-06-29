#include "jni_util.h"
using namespace npc;

extern "C" {

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativePlace(JNIEnv* env, jobject arrObj, jlong maskHandle, jlong valsHandle) {
    jlong handle = getNativeHandle(env, arrObj);
    auto* arr = unwrapArray(handle);
    auto* mask = unwrapArray(maskHandle);
    auto* vals = unwrapArray(valsHandle);
    if (!arr || !mask || !vals) { throwNpcException(env, "place: null input"); return -1; }
    return ::place(arr->get(), mask->get(), vals->get());
}

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativePut(JNIEnv* env, jobject arrObj, jlong indicesHandle, jlong valuesHandle, jstring jmode) {
    jlong handle = getNativeHandle(env, arrObj);
    auto* arr = unwrapArray(handle);
    auto* indices = unwrapArray(indicesHandle);
    auto* values = unwrapArray(valuesHandle);
    if (!arr || !indices || !values) { throwNpcException(env, "put: null input"); return -1; }
    std::string mode = jstringToString(env, jmode);
    return ::put(arr->get(), indices->get(), values->get(), mode.c_str());
}

JNIEXPORT void JNICALL
Java_libnpc_Npc_nativePutmask(JNIEnv* env, jobject arrObj, jlong maskHandle, jlong valuesHandle) {
    jlong handle = getNativeHandle(env, arrObj);
    auto* arr = unwrapArray(handle);
    auto* mask = unwrapArray(maskHandle);
    auto* values = unwrapArray(valuesHandle);
    if (!arr || !mask || !values) { throwNpcException(env, "putmask: null input"); return; }
    ::putmask(arr->get(), mask->get(), values->get());
}

JNIEXPORT void JNICALL
Java_libnpc_Npc_nativeFillDiagonal(JNIEnv* env, jobject arrObj, jdouble val) {
    jlong handle = getNativeHandle(env, arrObj);
    auto* arr = unwrapArray(handle);
    if (!arr) { throwNpcException(env, "fillDiagonal: null input"); return; }
    double v = static_cast<double>(val);
    ::fill_diagonal(arr->get(), &v);
}

JNIEXPORT void JNICALL
Java_libnpc_Npc_nativeSwapRows(JNIEnv* env, jobject arrObj, jint row1, jint row2) {
    jlong handle = getNativeHandle(env, arrObj);
    auto* arr = unwrapArray(handle);
    if (!arr) { throwNpcException(env, "swapRows: null input"); return; }
    npc::swap_rows(*arr, row1, row2);
}

JNIEXPORT void JNICALL
Java_libnpc_Npc_nativeSwapCols(JNIEnv* env, jobject arrObj, jint col1, jint col2) {
    jlong handle = getNativeHandle(env, arrObj);
    auto* arr = unwrapArray(handle);
    if (!arr) { throwNpcException(env, "swapCols: null input"); return; }
    npc::swap_cols(*arr, col1, col2);
}

} // extern "C"
