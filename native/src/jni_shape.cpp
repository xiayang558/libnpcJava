#include "jni_util.h"
using namespace npc;

extern "C" {

// ── Helpers ───────────────────────────────────────────────────────

// Call raw C shape function that takes (data*, ndim)
#define SHAPE_FN(JavaName, CFunc) \
JNIEXPORT jlong JNICALL \
Java_libnpc_Npc_native##JavaName(JNIEnv* env, jclass, jlong aHandle, jintArray jshape) { \
    auto* a = unwrapArray(aHandle); \
    if (!a) { throwNpcException(env, #JavaName ": null input"); return 0; } \
    auto sh = jintArrayToVector(env, jshape); \
    ::Array* raw = ::CFunc(a->get(), sh.data(), static_cast<int>(sh.size())); \
    if (!raw) { throwNpcException(env, #JavaName " failed"); return 0; } \
    return wrapArray(std::make_unique<npc::Array>(raw)); \
}

SHAPE_FN(Reshape, reshape)
SHAPE_FN(Resize, resize)
SHAPE_FN(BroadcastTo, broadcast_to)
SHAPE_FN(Tile, tile)
#undef SHAPE_FN

// ── Simple unary shape ops ────────────────────────────────────────

#define UNARY_SHAPE(JavaName, CppExpr) \
JNIEXPORT jlong JNICALL \
Java_libnpc_Npc_native##JavaName(JNIEnv* env, jclass, jlong aHandle) { \
    auto* a = unwrapArray(aHandle); \
    if (!a) { throwNpcException(env, #JavaName ": null input"); return 0; } \
    auto result = CppExpr; \
    return wrapArray(std::make_unique<npc::Array>(std::move(result))); \
}

UNARY_SHAPE(Transpose, npc::transpose(*a))
UNARY_SHAPE(Flatten, npc::flatten(*a))
UNARY_SHAPE(Fliplr, npc::fliplr(*a))
UNARY_SHAPE(Flipud, npc::flipud(*a))
UNARY_SHAPE(Atleast1d, npc::atleast_1d(*a))
UNARY_SHAPE(Atleast2d, npc::atleast_2d(*a))
UNARY_SHAPE(Atleast3d, npc::atleast_3d(*a))
#undef UNARY_SHAPE

// ── Ravel (with string order) ─────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRavel(JNIEnv* env, jclass, jlong aHandle, jstring jorder) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "ravel: null input"); return 0; }
    std::string order = jstringToString(env, jorder);
    auto result = npc::ravel(*a, order.c_str());
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

// ── Squeeze / ExpandDims ──────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSqueeze(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "squeeze: null input"); return 0; }
    auto result = npc::squeeze(*a, axis);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeExpandDims(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "expandDims: null input"); return 0; }
    auto result = npc::expand_dims(*a, axis);
    return wrapArray(std::make_unique<npc::Array>(std::move(result)));
}

// ── Concatenate / Append ──────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeConcatenate(JNIEnv* env, jclass, jlong aHandle, jlong bHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* b = unwrapArray(bHandle);
    if (!a || !b) { throwNpcException(env, "concatenate: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::concatenate(*a, *b, axis))));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAppend(JNIEnv* env, jclass, jlong aHandle, jlong vHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* v = unwrapArray(vHandle);
    if (!a || !v) { throwNpcException(env, "append: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::append(*a, *v, axis))));
}

// ── Stack functions ───────────────────────────────────────────────

static std::vector<npc::Array> toNpcArrayVec(JNIEnv* env, jobjectArray arrays) {
    std::vector<npc::Array> vec;
    jsize n = env->GetArrayLength(arrays);
    for (jsize i = 0; i < n; ++i) {
        jobject elem = env->GetObjectArrayElement(arrays, i);
        auto* a = unwrapArray(getNativeHandle(env, elem));
        if (a) vec.push_back(*a);
        env->DeleteLocalRef(elem);
    }
    return vec;
}

#define STACK_FN(JavaName, CppCall) \
JNIEXPORT jlong JNICALL \
Java_libnpc_Npc_native##JavaName(JNIEnv* env, jclass, jobjectArray arrays, jint _dummy) { \
    auto vec = toNpcArrayVec(env, arrays); \
    if (vec.empty()) { throwNpcException(env, #JavaName ": empty input"); return 0; } \
    auto result = CppCall; \
    return wrapArray(std::make_unique<npc::Array>(std::move(result))); \
}

STACK_FN(Stack, npc::stack(vec, _dummy))

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeHstack(JNIEnv* env, jclass, jobjectArray arrays) {
    auto vec = toNpcArrayVec(env, arrays);
    if (vec.empty()) { throwNpcException(env, "hstack: empty input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::hstack(vec))));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeVstack(JNIEnv* env, jclass, jobjectArray arrays) {
    auto vec = toNpcArrayVec(env, arrays);
    if (vec.empty()) { throwNpcException(env, "vstack: empty input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::vstack(vec))));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDstack(JNIEnv* env, jclass, jobjectArray arrays) {
    auto vec = toNpcArrayVec(env, arrays);
    if (vec.empty()) { throwNpcException(env, "dstack: empty input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::dstack(vec))));
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeColumnStack(JNIEnv* env, jclass, jobjectArray arrays) {
    auto vec = toNpcArrayVec(env, arrays);
    if (vec.empty()) { throwNpcException(env, "columnStack: empty input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::column_stack(vec))));
}

#undef STACK_FN

// ── Split functions ───────────────────────────────────────────────

#define SPLIT_FN(JavaName, CppCall) \
JNIEXPORT jobjectArray JNICALL \
Java_libnpc_Npc_native##JavaName(JNIEnv* env, jclass, jlong aHandle, jlong idxHandle) { \
    auto* a = unwrapArray(aHandle); auto* idx = unwrapArray(idxHandle); \
    if (!a || !idx) { throwNpcException(env, #JavaName ": null input"); return nullptr; } \
    auto result = CppCall; \
    jclass arrCls = env->FindClass("libnpc/NpcArray"); \
    jobjectArray out = env->NewObjectArray(static_cast<jsize>(result.size()), arrCls, nullptr); \
    for (size_t i = 0; i < result.size(); ++i) \
        env->SetObjectArrayElement(out, i, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(std::move(result[i]))))); \
    return out; \
}

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativeSplit(JNIEnv* env, jclass, jlong aHandle, jlong idxHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* idx = unwrapArray(idxHandle);
    if (!a || !idx) { throwNpcException(env, "split: null input"); return nullptr; }
    auto result = npc::split(*a, *idx, axis);
    jclass arrCls = env->FindClass("libnpc/NpcArray");
    jobjectArray out = env->NewObjectArray(static_cast<jsize>(result.size()), arrCls, nullptr);
    for (size_t i = 0; i < result.size(); ++i)
        env->SetObjectArrayElement(out, i, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(std::move(result[i])))));
    return out;
}

SPLIT_FN(Hsplit, npc::hsplit(*a, *idx))
SPLIT_FN(Vsplit, npc::vsplit(*a, *idx))
SPLIT_FN(Dsplit, npc::dsplit(*a, *idx))
#undef SPLIT_FN

// ── Flip / Rot90 / Roll ───────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFlip(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "flip: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::flip(*a, axis))));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRot90(JNIEnv* env, jclass, jlong aHandle, jint k, jint axis1, jint axis2) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "rot90: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::rot90(*a, k, axis1, axis2))));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRoll(JNIEnv* env, jclass, jlong aHandle, jint shift, jint axis) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "roll: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::roll(*a, shift, axis))));
}

// ── Repeat / Moveaxis / Rollaxis / Swapaxes ───────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRepeat(JNIEnv* env, jclass, jlong aHandle, jlong rHandle, jint axis) {
    auto* a = unwrapArray(aHandle); auto* r = unwrapArray(rHandle);
    if (!a || !r) { throwNpcException(env, "repeat: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::repeat(*a, *r, axis))));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMoveaxis(JNIEnv* env, jclass, jlong aHandle, jint src, jint dst) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "moveaxis: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::moveaxis(*a, src, dst))));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRollaxis(JNIEnv* env, jclass, jlong aHandle, jint axis, jint start) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "rollaxis: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::rollaxis(*a, axis, start))));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSwapaxes(JNIEnv* env, jclass, jlong aHandle, jint axis1, jint axis2) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "swapaxes: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::swapaxes(*a, axis1, axis2))));
}

// ── Pad ───────────────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePad(JNIEnv* env, jclass, jlong aHandle, jlong pwHandle, jstring jmode, jdouble cv) {
    auto* a = unwrapArray(aHandle); auto* pw = unwrapArray(pwHandle);
    if (!a || !pw) { throwNpcException(env, "pad: null input"); return 0; }
    std::string mode = jstringToString(env, jmode);
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::pad(*a, *pw, mode.c_str(), cv))));
}

// ── Meshgrid ──────────────────────────────────────────────────────

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativeMeshgrid(JNIEnv* env, jclass, jobjectArray arrays, jstring jindexing) {
    auto vec = toNpcArrayVec(env, arrays);
    if (vec.empty()) { throwNpcException(env, "meshgrid: empty input"); return nullptr; }
    std::string indexing = jstringToString(env, jindexing);
    auto result = npc::meshgrid(vec, indexing.c_str());
    jclass arrCls = env->FindClass("libnpc/NpcArray");
    jobjectArray out = env->NewObjectArray(static_cast<jsize>(result.size()), arrCls, nullptr);
    for (size_t i = 0; i < result.size(); ++i)
        env->SetObjectArrayElement(out, i, createNpcArrayObject(env, wrapArray(std::make_unique<npc::Array>(std::move(result[i])))));
    return out;
}

// ── Diagonal operations ───────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDiag(JNIEnv* env, jclass, jlong aHandle, jint k) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "diag: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::diag(*a, k))));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDiagflat(JNIEnv* env, jclass, jlong aHandle, jint k) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "diagflat: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::diagflat(*a, k))));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDiagonal(JNIEnv* env, jclass, jlong aHandle, jint offset, jint axis1, jint axis2) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "diagonal: null input"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(std::move(npc::diagonal(*a, offset, axis1, axis2))));
}

// ── Tril / Triu ───────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTril(JNIEnv* env, jclass, jlong aHandle, jint k) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "tril: null input"); return 0; }
    ::Array* raw = ::tril(a->get(), k);
    if (!raw) { throwNpcException(env, "tril failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTriu(JNIEnv* env, jclass, jlong aHandle, jint k) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "triu: null input"); return 0; }
    ::Array* raw = ::triu(a->get(), k);
    if (!raw) { throwNpcException(env, "triu failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}

// ── broadcast_arrays ──────────────────────────────────────────────

JNIEXPORT jobjectArray JNICALL
Java_libnpc_Npc_nativeBroadcastArrays(JNIEnv* env, jclass, jobjectArray jarrays) {
    auto vec = toArrayVec(env, jarrays);
    std::vector<::Array*> rawPtrs;
    for (auto* a : vec) rawPtrs.push_back(a ? a->get() : nullptr);
    if (rawPtrs.empty()) { throwNpcException(env, "broadcastArrays: empty input"); return nullptr; }
    int out_ndim = 0;
    int* out_shape = nullptr;
    ::Array** result = ::broadcast_arrays(rawPtrs.data(), static_cast<int>(rawPtrs.size()),
                                            &out_ndim, &out_shape);
    if (!result) { throwNpcException(env, "broadcastArrays failed"); return nullptr; }
    jclass arrCls = env->FindClass("libnpc/NpcArray");
    int n = static_cast<int>(rawPtrs.size());
    jobjectArray out = env->NewObjectArray(n, arrCls, nullptr);
    for (int i = 0; i < n; ++i) {
        if (result[i]) {
            env->SetObjectArrayElement(out, i, createNpcArrayObject(env,
                wrapArray(std::make_unique<npc::Array>(result[i]))));
        }
    }
    free(result);
    if (out_shape) free(out_shape);
    return out;
}

} // extern "C"
