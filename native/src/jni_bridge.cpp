#include "jni_util.h"

using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// NpcArray — Lifecycle
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_NpcArray_nativeCreateFromHandle(JNIEnv* env, jclass, jlong handle) {
    return handle;
}

JNIEXPORT void JNICALL
Java_libnpc_NpcArray_nativeClose(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    if (handle != 0) {
        freeHandle(handle);
        jfieldID fid = getNativePtrFieldID(env, obj);
        if (fid) env->SetLongField(obj, fid, 0);
    }
}

JNIEXPORT jboolean JNICALL
Java_libnpc_NpcArray_nativeIsClosed(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    return (handle == 0) ? JNI_TRUE : JNI_FALSE;
}

// ═══════════════════════════════════════════════════════════════════
// NpcArray — Metadata accessors
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jint JNICALL
Java_libnpc_NpcArray_nativeNdim(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "ndim");
    auto* arr = unwrapArray(handle);
    return arr ? arr->ndim() : 0;
}

JNIEXPORT jint JNICALL
Java_libnpc_NpcArray_nativeSize(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "size");
    auto* arr = unwrapArray(handle);
    return arr ? arr->size() : 0;
}

JNIEXPORT jintArray JNICALL
Java_libnpc_NpcArray_nativeShape(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "shape");
    auto* arr = unwrapArray(handle);
    if (!arr || arr->is_null()) return env->NewIntArray(0);
    int ndim = arr->ndim();
    const int* sh = arr->shape();
    jintArray result = env->NewIntArray(ndim);
    if (ndim > 0 && sh) {
        std::vector<jint> buf(sh, sh + ndim);
        env->SetIntArrayRegion(result, 0, ndim, buf.data());
    }
    return result;
}

JNIEXPORT jint JNICALL
Java_libnpc_NpcArray_nativeShapeAxis(JNIEnv* env, jobject obj, jint axis) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "shape");
    auto* arr = unwrapArray(handle);
    if (!arr || arr->is_null()) return 0;
    int ndim = arr->ndim();
    const int* sh = arr->shape();
    int a = (axis < 0) ? ndim + axis : axis;
    if (a < 0 || a >= ndim) return 0;
    return sh ? sh[a] : 0;
}

JNIEXPORT jintArray JNICALL
Java_libnpc_NpcArray_nativeStrides(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "strides");
    auto* arr = unwrapArray(handle);
    if (!arr || arr->is_null()) return env->NewIntArray(0);
    int ndim = arr->ndim();
    const int* st = arr->strides();
    jintArray result = env->NewIntArray(ndim);
    if (ndim > 0 && st) {
        std::vector<jint> buf(st, st + ndim);
        env->SetIntArrayRegion(result, 0, ndim, buf.data());
    }
    return result;
}

JNIEXPORT jint JNICALL
Java_libnpc_NpcArray_nativeDtype(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "dtype");
    auto* arr = unwrapArray(handle);
    return arr ? static_cast<jint>(arr->dtype()) : -1;
}

JNIEXPORT jboolean JNICALL
Java_libnpc_NpcArray_nativeIsView(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "isView");
    auto* arr = unwrapArray(handle);
    return arr ? (arr->is_view() ? JNI_TRUE : JNI_FALSE) : JNI_FALSE;
}

// ═══════════════════════════════════════════════════════════════════
// NpcArray — Element access (double)
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jdouble JNICALL
Java_libnpc_NpcArray_nativeGetDouble(JNIEnv* env, jobject obj, jintArray jindices) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "getDouble");
    auto* arr = unwrapArray(handle);
    if (!arr) return 0.0;

    auto indices = jintArrayToVector(env, jindices);
    if (static_cast<int>(indices.size()) == 0 || arr->ndim() == 0) {
        return static_cast<double>(arr->scalar<double>());
    }
    if (static_cast<int>(indices.size()) == 1 && arr->ndim() == 1) {
        return (*arr)[indices[0]];
    }
    // Use raw get_item for multi-dim access
    void* p = ::get_item(arr->get(), const_cast<int*>(indices.data()));
    return p ? *static_cast<double*>(p) : 0.0;
}

JNIEXPORT void JNICALL
Java_libnpc_NpcArray_nativeSetDouble(JNIEnv* env, jobject obj, jintArray jindices, jdouble value) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "setDouble");
    auto* arr = unwrapArray(handle);
    if (!arr) return;

    auto indices = jintArrayToVector(env, jindices);
    if (arr->ndim() == 0) return;
    if (static_cast<int>(indices.size()) == 1 && arr->ndim() == 1) {
        (*arr)[indices[0]] = value;
        return;
    }
    void* p = ::get_item(arr->get(), const_cast<int*>(indices.data()));
    if (p) *static_cast<double*>(p) = value;
}

JNIEXPORT jdouble JNICALL
Java_libnpc_NpcArray_nativeGetDouble1D(JNIEnv* env, jobject obj, jint index) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "getDouble");
    auto* arr = unwrapArray(handle);
    if (!arr) return 0.0;
    return (*arr)[index];
}

JNIEXPORT void JNICALL
Java_libnpc_NpcArray_nativeSetDouble1D(JNIEnv* env, jobject obj, jint index, jdouble value) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "setDouble");
    auto* arr = unwrapArray(handle);
    if (!arr) return;
    (*arr)[index] = value;
}

// ═══════════════════════════════════════════════════════════════════
// NpcArray — Scalar / conversion
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jdouble JNICALL
Java_libnpc_NpcArray_nativeScalarDouble(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "scalarDouble");
    auto* arr = unwrapArray(handle);
    return arr ? arr->scalar<double>() : 0.0;
}

JNIEXPORT jlong JNICALL
Java_libnpc_NpcArray_nativeScalarLong(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "scalarLong");
    auto* arr = unwrapArray(handle);
    return arr ? static_cast<jlong>(arr->scalar<int64_t>()) : 0;
}

JNIEXPORT jint JNICALL
Java_libnpc_NpcArray_nativeScalarInt(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "scalarInt");
    auto* arr = unwrapArray(handle);
    return arr ? static_cast<jint>(arr->scalar<int32_t>()) : 0;
}

JNIEXPORT jboolean JNICALL
Java_libnpc_NpcArray_nativeScalarBoolean(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "scalarBoolean");
    auto* arr = unwrapArray(handle);
    return arr ? (arr->scalar<bool>() ? JNI_TRUE : JNI_FALSE) : JNI_FALSE;
}

// ═══════════════════════════════════════════════════════════════════
// NpcArray — Bulk data extraction
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jdoubleArray JNICALL
Java_libnpc_NpcArray_nativeToDoubleArray(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "toDoubleArray");
    auto* arr = unwrapArray(handle);
    if (!arr) return env->NewDoubleArray(0);

    int n = arr->size();
    jdoubleArray result = env->NewDoubleArray(n);
    DType dt = arr->dtype();
    jdouble* buf = new jdouble[n];

    if (dt == DType::Float64) {
        const double* src = arr->data<double>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jdouble>(src[i]);
    } else if (dt == DType::Float32) {
        const float* src = arr->data<float>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jdouble>(src[i]);
    } else if (dt == DType::Int32) {
        const int32_t* src = arr->data<int32_t>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jdouble>(src[i]);
    } else if (dt == DType::Int64) {
        const int64_t* src = arr->data<int64_t>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jdouble>(src[i]);
    } else {
        for (int i = 0; i < n; ++i) buf[i] = 0.0;
    }
    env->SetDoubleArrayRegion(result, 0, n, buf);
    delete[] buf;
    return result;
}

JNIEXPORT jlongArray JNICALL
Java_libnpc_NpcArray_nativeToLongArray(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "toLongArray");
    auto* arr = unwrapArray(handle);
    if (!arr) return env->NewLongArray(0);

    int n = arr->size();
    jlongArray result = env->NewLongArray(n);
    jlong* buf = new jlong[n];
    DType dt = arr->dtype();

    if (dt == DType::Int64) {
        const int64_t* src = arr->data<int64_t>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jlong>(src[i]);
    } else if (dt == DType::Float64) {
        const double* src = arr->data<double>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jlong>(src[i]);
    } else if (dt == DType::Int32) {
        const int32_t* src = arr->data<int32_t>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jlong>(src[i]);
    } else {
        for (int i = 0; i < n; ++i) buf[i] = 0;
    }
    env->SetLongArrayRegion(result, 0, n, buf);
    delete[] buf;
    return result;
}

JNIEXPORT jintArray JNICALL
Java_libnpc_NpcArray_nativeToIntArray(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "toIntArray");
    auto* arr = unwrapArray(handle);
    if (!arr) return env->NewIntArray(0);

    int n = arr->size();
    jintArray result = env->NewIntArray(n);
    jint* buf = new jint[n];
    DType dt = arr->dtype();

    if (dt == DType::Int32) {
        const int32_t* src = arr->data<int32_t>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jint>(src[i]);
    } else if (dt == DType::Float64) {
        const double* src = arr->data<double>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jint>(src[i]);
    } else if (dt == DType::Int64) {
        const int64_t* src = arr->data<int64_t>();
        for (int i = 0; i < n; ++i) buf[i] = static_cast<jint>(src[i]);
    } else {
        for (int i = 0; i < n; ++i) buf[i] = 0;
    }
    env->SetIntArrayRegion(result, 0, n, buf);
    delete[] buf;
    return result;
}

// ═══════════════════════════════════════════════════════════════════
// NpcArray — Print / info
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT void JNICALL
Java_libnpc_NpcArray_nativePrint(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "print");
    auto* arr = unwrapArray(handle);
    if (arr) arr->print();
}

JNIEXPORT void JNICALL
Java_libnpc_NpcArray_nativeInfo(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    checkNotNull(env, handle, "info");
    auto* arr = unwrapArray(handle);
    if (arr) arr->info();
}

JNIEXPORT jstring JNICALL
Java_libnpc_NpcArray_nativeToString(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    if (handle == 0) return env->NewStringUTF("NpcArray(closed)");
    auto* arr = unwrapArray(handle);
    if (!arr || arr->is_null()) return env->NewStringUTF("NpcArray(null)");
    std::ostringstream oss;
    oss << *arr;
    return env->NewStringUTF(oss.str().c_str());
}

// ═══════════════════════════════════════════════════════════════════
// Npc — version
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jstring JNICALL
Java_libnpc_Npc_nativeVersion(JNIEnv* env, jclass) {
    return env->NewStringUTF("1.0.0");
}

} // extern "C"
