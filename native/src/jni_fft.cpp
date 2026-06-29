#include "jni_util.h"
using namespace npc;

extern "C" {

#define UNARY_FFT(JavaName, CppCall) \
JNIEXPORT jlong JNICALL \
Java_libnpc_Npc_native##JavaName(JNIEnv* env, jclass, jlong aHandle) { \
    auto* a = unwrapArray(aHandle); \
    if (!a) { throwNpcException(env, #JavaName ": null input"); return 0; } \
    try { \
        auto result = CppCall; \
        return wrapArray(std::make_unique<npc::Array>(std::move(result))); \
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; } \
}

UNARY_FFT(Fft, npc::fft(*a))
UNARY_FFT(Ifft, npc::ifft(*a))
UNARY_FFT(Rfft, npc::rfft(*a))
UNARY_FFT(Rfft2, npc::rfft2(*a))
UNARY_FFT(Rfftn, npc::rfftn(*a))
UNARY_FFT(Fft2, npc::fft2(*a))
UNARY_FFT(Ifft2, npc::ifft2(*a))
UNARY_FFT(Fftn, npc::fftn(*a))
UNARY_FFT(Ifftn, npc::ifftn(*a))
UNARY_FFT(Fftshift, npc::fftshift(*a))
UNARY_FFT(Ifftshift, npc::ifftshift(*a))
#undef UNARY_FFT

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeHfft(JNIEnv* env, jclass, jlong aHandle, jint n) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "hfft: null input"); return 0; }
    try {
        auto result = npc::hfft(*a, n);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIhfft(JNIEnv* env, jclass, jlong aHandle, jint n) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "ihfft: null input"); return 0; }
    try {
        auto result = npc::ihfft(*a, n);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIrfft(JNIEnv* env, jclass, jlong aHandle, jint n) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "irfft: null input"); return 0; }
    try {
        auto result = npc::irfft(*a, n);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIrfft2(JNIEnv* env, jclass, jlong aHandle, jintArray js) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "irfft2: null input"); return 0; }
    auto sv = jintArrayToVector(env, js);
    try {
        auto result = npc::irfft2(*a, std::array<int, 2>{{sv[0], sv[1]}});
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIrfftn(JNIEnv* env, jclass, jlong aHandle, jintArray js) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "irfftn: null input"); return 0; }
    auto sv = jintArrayToVector(env, js);
    try {
        // Call C function directly since irfftn takes initializer_list
        ::Array* raw = ::irfftn(a->get(), sv.data());
        if (!raw) { throwNpcException(env, "irfftn: failed"); return 0; }
        return wrapArray(std::make_unique<npc::Array>(raw));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFftfreq(JNIEnv* env, jclass, jint n, jdouble d) {
    try {
        auto result = npc::fftfreq(n, d);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRfftfreq(JNIEnv* env, jclass, jint n, jdouble d) {
    try {
        auto result = npc::rfftfreq(n, d);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

} // extern "C"
