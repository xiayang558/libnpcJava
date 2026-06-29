#include "jni_util.h"
using namespace npc;

extern "C" {

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeReadtxt(JNIEnv* env, jclass, jstring jfilename, jstring jdelimiter,
                               jchar comment, jint skiplines, jint maxRows, jint ndmin,
                               jboolean unpack, jint dtypeOrdinal) {
    std::string filename = jstringToString(env, jfilename);
    std::string delimiter = jstringToString(env, jdelimiter);
    try {
        auto result = npc::readtxt(filename.c_str(), delimiter.c_str(), static_cast<char>(comment),
            skiplines, maxRows, ndmin, unpack == JNI_TRUE,
            static_cast<npc::DType>(dtypeOrdinal));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGenfromtxt(JNIEnv* env, jclass, jstring jfilename,
                                  jstring jdelimiter, jint skipHeader) {
    std::string filename = jstringToString(env, jfilename);
    std::string delimiter = jstringToString(env, jdelimiter);
    try {
        auto result = npc::genfromtxt(filename.c_str(), delimiter.c_str(), skipHeader);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativeSavetxt(JNIEnv* env, jclass, jstring jfilename, jlong aHandle,
                               jstring jfmt, jstring jdelimiter, jstring jnewline,
                               jstring jheader, jstring jfooter, jstring jcomments) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "savetxt: null input"); return -1; }
    std::string filename = jstringToString(env, jfilename);
    std::string fmt = jstringToString(env, jfmt);
    std::string delimiter = jstringToString(env, jdelimiter);
    std::string newline = jstringToString(env, jnewline);
    const char* header = jheader ? env->GetStringUTFChars(jheader, nullptr) : nullptr;
    const char* footer = jfooter ? env->GetStringUTFChars(jfooter, nullptr) : nullptr;
    std::string comments = jstringToString(env, jcomments);
    try {
        int ret = ::savetxt(filename.c_str(), a->get(), fmt.c_str(), delimiter.c_str(),
            newline.c_str(), header, footer, comments.c_str());
        if (header) env->ReleaseStringUTFChars(jheader, header);
        if (footer) env->ReleaseStringUTFChars(jfooter, footer);
        return ret;
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return -1; }
}

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativeSaveNpy(JNIEnv* env, jclass, jstring jfilename, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "saveNpy: null input"); return -1; }
    std::string filename = jstringToString(env, jfilename);
    try {
        return npc::save_npy(filename, *a);
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return -1; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLoadNpy(JNIEnv* env, jclass, jstring jfilename) {
    std::string filename = jstringToString(env, jfilename);
    try {
        auto result = npc::load_npy(filename);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativeSavez(JNIEnv* env, jclass, jstring jfilename, jobjectArray arrays) {
    std::string filename = jstringToString(env, jfilename);
    try {
        jsize n = env->GetArrayLength(arrays);
        std::vector<npc::Array> vec;
        for (jsize i = 0; i < n; ++i) {
            jobject elem = env->GetObjectArrayElement(arrays, i);
            auto* arr = unwrapArray(getNativeHandle(env, elem));
            if (arr) vec.push_back(*arr);
            env->DeleteLocalRef(elem);
        }
        return npc::savez(filename.c_str(), vec);
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return -1; }
}

} // extern "C"
