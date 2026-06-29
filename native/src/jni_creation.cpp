#include "jni_util.h"
using namespace npc;

extern "C" {

// Each function follows this pattern:
// - Unwrap input handles via unwrapArray()
// - Call npc:: factory function (or the underlying C function)
// - Wrap result via wrapArray(std::make_unique<npc::Array>(...))
// - Return jlong (0 for failure)

// ═══════════════════════════════════════════════════════════════════
// Creation functions
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeZeros(JNIEnv* env, jclass, jintArray shape, jint dtypeOrdinal) {
    try {
        auto shape_vec = jintArrayToVector(env, shape);
        auto arr = std::make_unique<npc::Array>(
            ::zeros(shape_vec.data(), static_cast<int>(shape_vec.size()),
                    static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal))));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeZeros: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeOnes(JNIEnv* env, jclass, jintArray shape, jint dtypeOrdinal) {
    try {
        auto shape_vec = jintArrayToVector(env, shape);
        auto arr = std::make_unique<npc::Array>(
            ::ones(shape_vec.data(), static_cast<int>(shape_vec.size()),
                   static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal))));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeOnes: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFull(JNIEnv* env, jclass, jintArray shape, jdouble value, jint dtypeOrdinal) {
    try {
        auto shape_vec = jintArrayToVector(env, shape);
        double v = value;
        auto arr = std::make_unique<npc::Array>(
            ::full(shape_vec.data(), static_cast<int>(shape_vec.size()),
                   static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal)), &v));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeFull: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeEmpty(JNIEnv* env, jclass, jintArray shape, jint dtypeOrdinal) {
    try {
        auto shape_vec = jintArrayToVector(env, shape);
        auto arr = std::make_unique<npc::Array>(
            ::empty(shape_vec.data(), static_cast<int>(shape_vec.size()),
                    static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal))));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeEmpty: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArange(JNIEnv* env, jclass, jdouble start, jdouble stop, jdouble step, jint dtypeOrdinal) {
    try {
        auto arr = std::make_unique<npc::Array>(
            ::arange(start, stop, step,
                     static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal))));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeArange: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLinspace(JNIEnv* env, jclass, jdouble start, jdouble stop, jint num, jboolean endpoint) {
    try {
        if (num <= 0) return 0;
        auto arr = std::make_unique<npc::Array>(
            npc::linspace(start, stop, num, endpoint == JNI_TRUE));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeLinspace: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogspace(JNIEnv* env, jclass, jdouble start, jdouble stop, jint num, jdouble base, jboolean endpoint) {
    try {
        auto arr = std::make_unique<npc::Array>(
            ::logspace(start, stop, num, base, endpoint == JNI_TRUE ? 1 : 0));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeLogspace: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGeomspace(JNIEnv* env, jclass, jdouble start, jdouble stop, jint num, jboolean endpoint) {
    try {
        auto arr = std::make_unique<npc::Array>(
            ::geomspace(start, stop, num, endpoint == JNI_TRUE ? 1 : 0));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeGeomspace: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeEye(JNIEnv* env, jclass, jint N, jint M, jint k, jint dtypeOrdinal) {
    try {
        auto arr = std::make_unique<npc::Array>(
            ::eye(N, M, k, static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal))));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeEye: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIdentity(JNIEnv* env, jclass, jint N, jint dtypeOrdinal) {
    try {
        auto arr = std::make_unique<npc::Array>(
            ::identity(N, static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal))));
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeIdentity: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCopy(JNIEnv* env, jclass, jlong aHandle) {
    try {
        checkNotNull(env, aHandle, "copy");
        auto* arr = unwrapArray(aHandle);
        if (!arr) return 0;
        auto result = std::make_unique<npc::Array>(npc::copy(*arr));
        return wrapArray(std::move(result));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeCopy: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAstype(JNIEnv* env, jclass, jlong aHandle, jint dtypeOrdinal) {
    try {
        checkNotNull(env, aHandle, "astype");
        auto* arr = unwrapArray(aHandle);
        if (!arr) return 0;
        auto result = std::make_unique<npc::Array>(
            npc::astype(*arr, static_cast<npc::DType>(dtypeOrdinal)));
        return wrapArray(std::move(result));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeAstype: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArray1D(JNIEnv* env, jclass, jdoubleArray data) {
    try {
        auto vec = jdoubleArrayToVector(env, data);
        int shape[] = {static_cast<int>(vec.size())};
        auto raw = ::empty(shape, 1, FLOAT64);
        if (raw && !vec.empty()) {
            double* dst = static_cast<double*>(raw->data);
            for (size_t i = 0; i < vec.size(); ++i) {
                dst[i] = vec[i];
            }
        }
        auto arr = std::make_unique<npc::Array>(raw);
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeArray1D: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArray2D(JNIEnv* env, jclass, jobjectArray data) {
    try {
        if (!data) return 0;

        jsize rows = env->GetArrayLength(data);
        if (rows == 0) return 0;

        // First pass: determine max column count
        jsize cols = 0;
        for (jsize r = 0; r < rows; ++r) {
            jdoubleArray row = static_cast<jdoubleArray>(env->GetObjectArrayElement(data, r));
            jsize rowLen = env->GetArrayLength(row);
            if (rowLen > cols) cols = rowLen;
            env->DeleteLocalRef(row);
        }

        if (cols == 0) return 0;

        // Second pass: collect data with zero-padding
        std::vector<double> flat;
        flat.reserve(rows * cols);

        for (jsize r = 0; r < rows; ++r) {
            jdoubleArray row = static_cast<jdoubleArray>(env->GetObjectArrayElement(data, r));
            jsize rowLen = env->GetArrayLength(row);
            jdouble* elems = env->GetDoubleArrayElements(row, nullptr);
            for (jsize c = 0; c < rowLen; ++c) {
                flat.push_back(static_cast<double>(elems[c]));
            }
            for (jsize c = rowLen; c < cols; ++c) {
                flat.push_back(0.0);
            }
            env->ReleaseDoubleArrayElements(row, elems, JNI_ABORT);
            env->DeleteLocalRef(row);
        }

        int shape[] = {static_cast<int>(rows), static_cast<int>(cols)};
        auto raw = ::empty(shape, 2, FLOAT64);
        if (raw) {
            double* dst = static_cast<double*>(raw->data);
            for (size_t i = 0; i < flat.size(); ++i) {
                dst[i] = flat[i];
            }
        }
        auto arr = std::make_unique<npc::Array>(raw);
        return wrapArray(std::move(arr));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeArray2D: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFullLike(JNIEnv* env, jclass, jlong aHandle, jdouble value, jint dtypeOrdinal) {
    try {
        checkNotNull(env, aHandle, "fullLike");
        auto* arr = unwrapArray(aHandle);
        if (!arr) return 0;

        auto result_shape = arr->shape_vec();
        double v = value;
        auto result = std::make_unique<npc::Array>(
            ::full_like(arr->get(), &v, static_cast<DataType>(static_cast<npc::DType>(dtypeOrdinal))));
        return wrapArray(std::move(result));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nativeFullLike: unknown error");
        return 0;
    }
}

} // extern "C"
