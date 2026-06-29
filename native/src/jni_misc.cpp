#include "jni_util.h"
using namespace npc;

extern "C" {

// ── Clip ──────────────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeClip_arr(JNIEnv* env, jclass, jlong aHandle, jlong loHandle, jlong hiHandle) {
    auto* a = unwrapArray(aHandle);
    auto* lo = unwrapArray(loHandle);
    auto* hi = unwrapArray(hiHandle);
    if (!a || !lo || !hi) { throwNpcException(env, "clip: null input"); return 0; }
    try {
        auto result = npc::clip(*a, *lo, *hi);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeClip_scalar(JNIEnv* env, jclass, jlong aHandle, jdouble lo, jdouble hi) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "clip: null input"); return 0; }
    try {
        auto result = a->clip(lo, hi);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

// ── Basic ops ─────────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeConjTranspose(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "conjTranspose: null input"); return 0; }
    auto result = npc::conj_transpose(*a);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeConvolve(JNIEnv* env, jclass, jlong aHandle, jlong vHandle) {
    auto* a = unwrapArray(aHandle); auto* v = unwrapArray(vHandle);
    if (!a || !v) { throwNpcException(env, "convolve: null input"); return 0; }
    auto result = npc::convolve(*a, *v);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrimZeros(JNIEnv* env, jclass, jlong aHandle, jstring jtrim) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "trimZeros: null input"); return 0; }
    std::string trim = jstringToString(env, jtrim);
    auto result = npc::trim_zeros(*a, trim.c_str());
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTake(JNIEnv* env, jclass, jlong aHandle, jlong indicesHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* idx = unwrapArray(indicesHandle);
    if (!a || !idx) { throwNpcException(env, "take: null input"); return 0; }
    auto result = npc::take(*a, *idx, axis);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTakeAlongAxis(JNIEnv* env, jclass, jlong aHandle, jlong indicesHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* idx = unwrapArray(indicesHandle);
    if (!a || !idx) { throwNpcException(env, "takeAlongAxis: null input"); return 0; }
    ::Array* raw = ::take_along_axis(a->get(), idx->get(), axis);
    if (!raw) { throwNpcException(env, "takeAlongAxis: failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCompress(JNIEnv* env, jclass, jlong condHandle, jlong aHandle, jint axis) {
    auto* cond = unwrapArray(condHandle); auto* a = unwrapArray(aHandle);
    if (!cond || !a) { throwNpcException(env, "compress: null input"); return 0; }
    auto result = npc::compress(*cond, *a, axis);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeChoose(JNIEnv* env, jclass, jlong aHandle, jobjectArray choices, jint mode) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "choose: null input"); return 0; }
    auto choicesVec = toArrayVec(env, choices);
    std::vector<::Array*> rawPtrs;
    for (auto* c : choicesVec) rawPtrs.push_back(c ? c->get() : nullptr);
    if (rawPtrs.empty()) { throwNpcException(env, "choose: empty choices"); return 0; }
    ::Array* raw = ::choose(a->get(), static_cast<int>(rawPtrs.size()), rawPtrs.data(), mode);
    if (!raw) { throwNpcException(env, "choose: failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFlatnonzero(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "flatnonzero: null input"); return 0; }
    auto result = npc::flatnonzero(*a);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeExtract(JNIEnv* env, jclass, jlong condHandle, jlong aHandle) {
    auto* cond = unwrapArray(condHandle); auto* a = unwrapArray(aHandle);
    if (!cond || !a) { throwNpcException(env, "extract: null input"); return 0; }
    auto result = npc::extract(*cond, *a);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDelete(JNIEnv* env, jclass, jlong aHandle, jlong objHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* obj = unwrapArray(objHandle);
    if (!a || !obj) { throwNpcException(env, "delete: null input"); return 0; }
    ::Array* raw = ::npc_delete(a->get(), obj->get(), axis);
    if (!raw) { throwNpcException(env, "delete: failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeInsert(JNIEnv* env, jclass, jlong aHandle, jlong objHandle, jlong valuesHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* obj = unwrapArray(objHandle); auto* vals = unwrapArray(valuesHandle);
    if (!a || !obj || !vals) { throwNpcException(env, "insert: null input"); return 0; }
    ::Array* raw = ::insert(a->get(), obj->get(), vals->get(), axis);
    if (!raw) { throwNpcException(env, "insert: failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBincount_w(JNIEnv* env, jclass, jlong aHandle, jlong weightsHandle, jint minlength) {
    auto* a = unwrapArray(aHandle); auto* w = unwrapArray(weightsHandle);
    if (!a || !w) { throwNpcException(env, "bincount: null input"); return 0; }
    auto result = npc::bincount(*a, *w, minlength);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBincount(JNIEnv* env, jclass, jlong aHandle, jint minlength) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "bincount: null input"); return 0; }
    auto result = npc::bincount(*a, minlength);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

// ── frexp / modf ──────────────────────────────────────────────────

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativeFrexp(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "frexp: null input"); return nullptr; }
    ::Array *mant = nullptr, *exp_ = nullptr;
    int ret = ::npc_frexp(a->get(), &mant, &exp_);
    if (ret != 0 || !mant || !exp_) { throwNpcException(env, "frexp: failed"); return nullptr; }
    jclass arrCls = env->FindClass("libnpc/NpcArray");
    jobjectArray out = env->NewObjectArray(2, arrCls, nullptr);
    env->SetObjectArrayElement(out, 0, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(mant))));
    env->SetObjectArrayElement(out, 1, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(exp_))));
    return out;
}

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativeModf(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "modf: null input"); return nullptr; }
    ::Array *frac = nullptr, *integ = nullptr;
    int ret = ::modf_arr(a->get(), &frac, &integ);
    if (ret != 0 || !frac || !integ) { throwNpcException(env, "modf: failed"); return nullptr; }
    jclass arrCls = env->FindClass("libnpc/NpcArray");
    jobjectArray out = env->NewObjectArray(2, arrCls, nullptr);
    env->SetObjectArrayElement(out, 0, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(frac))));
    env->SetObjectArrayElement(out, 1, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(integ))));
    return out;
}

// ── ix_ ───────────────────────────────────────────────────────────

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativeIx(JNIEnv* env, jclass, jobjectArray arrays) {
    jsize n = env->GetArrayLength(arrays);
    std::vector<::Array*> rawPtrs(n, nullptr);
    for (jsize i = 0; i < n; ++i) {
        jobject elem = env->GetObjectArrayElement(arrays, i);
        auto* a = unwrapArray(getNativeHandle(env, elem));
        if (a) rawPtrs[i] = a->get();
        env->DeleteLocalRef(elem);
    }
    ::Array** out = nullptr;
    int ret = ::ix_(rawPtrs.data(), static_cast<int>(n), &out);
    if (ret != 0 || !out) { throwNpcException(env, "ix_: failed"); return nullptr; }
    jclass arrCls = env->FindClass("libnpc/NpcArray");
    jobjectArray jout = env->NewObjectArray(n, arrCls, nullptr);
    for (jsize i = 0; i < n; ++i) {
        if (out[i]) {
            env->SetObjectArrayElement(jout, i, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(out[i]))));
        }
    }
    free(out);
    return jout;
}

// ── frombuffer ────────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFrombuffer(JNIEnv* env, jclass, jbyteArray buffer, jint dtypeOrdinal, jint count, jint offset) {
    if (!buffer) { throwNpcException(env, "frombuffer: null buffer"); return 0; }
    jbyte* bytes = env->GetByteArrayElements(buffer, nullptr);
    ::Array* raw = ::frombuffer(bytes, static_cast<DataType>(dtypeOrdinal), count, static_cast<size_t>(offset));
    env->ReleaseByteArrayElements(buffer, bytes, JNI_ABORT);
    if (!raw) { throwNpcException(env, "frombuffer: failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

// ── ndim ──────────────────────────────────────────────────────────

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativeNdim(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    return a ? npc::ndim(*a) : 0;
}

// ── Parallel config & buffer size ─────────────────────────────────

JNIEXPORT void JNICALL
Java_libnpc_Npc_nativeSetParallelConfig(JNIEnv*, jclass, jint numThreads, jboolean enable) {
    ::set_parallel_config(numThreads, enable);
}

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativeGetBufsize(JNIEnv*, jclass) {
    return ::getbufsize();
}

JNIEXPORT void JNICALL
Java_libnpc_Npc_nativeSetBufsize(JNIEnv*, jclass, jint size) {
    ::setbufsize(size);
}

// ── Vandermonde / Triangular / Block ──────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeVander(JNIEnv* env, jclass, jlong xHandle, jint N, jint increasing) {
    auto* x = unwrapArray(xHandle);
    if (!x) { throwNpcException(env, "vander: null input"); return 0; }
    ::Array* raw = ::vander(x->get(), N, increasing);
    if (!raw) { throwNpcException(env, "vander failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTri(JNIEnv* env, jclass, jint N, jint M, jint k, jint dtypeOrdinal) {
    ::Array* raw = ::tri(N, M, k, static_cast<DataType>(dtypeOrdinal));
    if (!raw) { throwNpcException(env, "tri failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrilIndices(JNIEnv* env, jclass, jint n, jint k, jint m) {
    ::Array* raw = ::tril_indices(n, k, m);
    if (!raw) { throwNpcException(env, "tril_indices failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrilIndicesFrom(JNIEnv* env, jclass, jlong aHandle, jint k) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "tril_indices_from: null input"); return 0; }
    ::Array* raw = ::tril_indices_from(a->get(), k);
    if (!raw) { throwNpcException(env, "tril_indices_from failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTriuIndices(JNIEnv* env, jclass, jint n, jint k, jint m) {
    ::Array* raw = ::triu_indices(n, k, m);
    if (!raw) { throwNpcException(env, "triu_indices failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTriuIndicesFrom(JNIEnv* env, jclass, jlong aHandle, jint k) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "triu_indices_from: null input"); return 0; }
    ::Array* raw = ::triu_indices_from(a->get(), k);
    if (!raw) { throwNpcException(env, "triu_indices_from failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBlock(JNIEnv* env, jclass, jobjectArray jblocks, jint rows, jint cols) {
    auto vec = toArrayVec(env, jblocks);
    std::vector<::Array*> rawPtrs;
    for (auto* a : vec) rawPtrs.push_back(a ? a->get() : nullptr);
    if (rawPtrs.empty()) { throwNpcException(env, "block: empty input"); return 0; }
    ::Array* raw = ::block(rawPtrs.data(), rows, cols);
    if (!raw) { throwNpcException(env, "block failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBmat(JNIEnv* env, jclass, jobjectArray jblocks, jint rows, jint cols) {
    auto vec = toArrayVec(env, jblocks);
    std::vector<::Array*> rawPtrs;
    for (auto* a : vec) rawPtrs.push_back(a ? a->get() : nullptr);
    if (rawPtrs.empty()) { throwNpcException(env, "bmat: empty input"); return 0; }
    ::Array* raw = ::bmat(rawPtrs.data(), rows, cols);
    if (!raw) { throwNpcException(env, "bmat failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

// ── Einsum path / Utility ─────────────────────────────────────────

JNIEXPORT jstring JNICALL
Java_libnpc_Npc_einsumPath(JNIEnv* env, jclass, jstring jsubscripts, jobjectArray joperands) {
    std::string subscripts = jstringToString(env, jsubscripts);
    auto vec = toArrayVec(env, joperands);
    std::vector<npc::Array> copies;
    for (auto* a : vec) { if (a) copies.push_back(*a); }
    auto [path, info] = npc::einsum_path(subscripts.c_str(), copies, "greedy");
    return env->NewStringUTF(info.c_str());
}

JNIEXPORT jint JNICALL
Java_libnpc_Npc_nativeAsize(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "asize: null input"); return 0; }
    return ::asize(a->get(), axis);
}

JNIEXPORT jstring JNICALL
Java_libnpc_Npc_typenameStr(JNIEnv* env, jclass, jstring jtypechar) {
    const char* tc = env->GetStringUTFChars(jtypechar, nullptr);
    const char* name = ::np_typename(tc);
    jstring result = env->NewStringUTF(name ? name : "unknown");
    env->ReleaseStringUTFChars(jtypechar, tc);
    return result;
}

// ── Parallel config / create_array / mod_scalar ───────────────────

JNIEXPORT jintArray JNICALL
Java_libnpc_Npc_nativeGetParallelConfig(JNIEnv* env, jclass) {
    ::ParallelConfig* cfg = ::get_parallel_config();
    jintArray result = env->NewIntArray(2);
    if (cfg) {
        jint buf[2] = {cfg->num_threads, cfg->enable_parallel};
        env->SetIntArrayRegion(result, 0, 2, buf);
    }
    return result;
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCreateArray(JNIEnv* env, jclass, jintArray jshape, jint dtypeOrdinal) {
    auto shape = jintArrayToVector(env, jshape);
    ::Array* raw = ::create_array(shape.data(), static_cast<int>(shape.size()),
                                   static_cast<DataType>(dtypeOrdinal));
    if (!raw) { throwNpcException(env, "create_array failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeModScalar(JNIEnv* env, jclass, jlong aHandle, jdouble scalar) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "modScalar: null input"); return 0; }
    double v = static_cast<double>(scalar);
    ::Array* raw = ::mod_scalar(a->get(), &v);
    if (!raw) { throwNpcException(env, "mod_scalar failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

} // extern "C"
