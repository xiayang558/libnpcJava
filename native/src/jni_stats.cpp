#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Npc — Aggregation (axis + keepdims)
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSum(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "sum");
        auto result = npc::sum(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMean(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "mean");
        auto result = npc::mean(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMin(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "min");
        auto result = npc::min(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMax(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "max");
        auto result = npc::max(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeProd(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "prod");
        auto result = npc::prod(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeStddev(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "stddev");
        auto result = npc::stddev(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeVar(JNIEnv* env, jclass, jlong aHandle, jint axis, jint ddof, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "var");
        auto result = npc::var(*a, static_cast<int>(axis), static_cast<int>(ddof), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMedian(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "median");
        auto result = npc::median(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePercentile(JNIEnv* env, jclass, jlong aHandle, jlong qHandle, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* q = unwrapArray(qHandle);
        checkNotNull(env, aHandle, "percentile");
        checkNotNull(env, qHandle, "percentile");
        auto result = npc::percentile(*a, *q, static_cast<int>(axis));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeQuantile(JNIEnv* env, jclass, jlong aHandle, jlong qHandle, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* q = unwrapArray(qHandle);
        checkNotNull(env, aHandle, "quantile");
        checkNotNull(env, qHandle, "quantile");
        auto result = npc::quantile(*a, *q, static_cast<int>(axis));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArgmax(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "argmax");
        auto result = npc::argmax(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArgmin(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "argmin");
        auto result = npc::argmin(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCountNonzero(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "count_nonzero");
        auto result = npc::count_nonzero(*a, static_cast<int>(axis));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePtp(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "ptp");
        auto result = npc::ptp(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAll(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "all");
        auto result = npc::all(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAny(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "any");
        auto result = npc::any(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Npc — Cumulative operations
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCumsum(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "cumsum");
        auto result = npc::cumsum(*a, static_cast<int>(axis));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCumprod(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "cumprod");
        auto result = npc::cumprod(*a, static_cast<int>(axis));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Npc — Other stats
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeWhere(JNIEnv* env, jclass, jlong condHandle, jlong xHandle, jlong yHandle) {
    try {
        auto* cond = unwrapArray(condHandle);
        auto* x = unwrapArray(xHandle);
        auto* y = unwrapArray(yHandle);
        checkNotNull(env, condHandle, "where");
        checkNotNull(env, xHandle, "where");
        checkNotNull(env, yHandle, "where");
        auto result = npc::where(*cond, *x, *y);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAverage_w(JNIEnv* env, jclass, jlong aHandle, jlong wHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* w = unwrapArray(wHandle);
        checkNotNull(env, aHandle, "average");
        checkNotNull(env, wHandle, "average");
        auto result = npc::average(*a, *w, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAverage(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "average");
        auto result = npc::average(*a, static_cast<int>(axis), keepdims == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCov(JNIEnv* env, jclass, jlong aHandle, jboolean rowvar, jint ddof, jint dtypeOrdinal) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "cov");
        auto result = npc::cov(*a, rowvar == JNI_TRUE,
                               static_cast<int>(ddof),
                               static_cast<npc::DType>(dtypeOrdinal));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCorrcoef(JNIEnv* env, jclass, jlong aHandle, jboolean rowvar) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "corrcoef");
        auto result = npc::corrcoef(*a, rowvar == JNI_TRUE);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCorrelate(JNIEnv* env, jclass, jlong aHandle, jlong vHandle, jstring modeStr) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* v = unwrapArray(vHandle);
        checkNotNull(env, aHandle, "correlate");
        checkNotNull(env, vHandle, "correlate");
        std::string mode = jstringToString(env, modeStr);
        auto result = npc::correlate(*a, *v, mode.c_str());
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrapz_dx(JNIEnv* env, jclass, jlong aHandle, jdouble dx, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "trapz");
        auto result = npc::trapz(*a, static_cast<double>(dx), static_cast<int>(axis));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrapz_x(JNIEnv* env, jclass, jlong aHandle, jlong xHandle, jdouble dx, jint axis) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* x = unwrapArray(xHandle);
        checkNotNull(env, aHandle, "trapz");
        checkNotNull(env, xHandle, "trapz");
        auto result = npc::trapz(*a, *x, static_cast<double>(dx), static_cast<int>(axis));
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

} // extern "C"
