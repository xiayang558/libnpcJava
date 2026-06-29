#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// NaN-aware statistics
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanmax(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanmax");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanmax(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanmax: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanmin(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanmin");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanmin(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanmin: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanmean(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanmean");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanmean(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanmean: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanmedian(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanmedian");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanmedian(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanmedian: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNansum(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nansum");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nansum(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nansum: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanprod(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanprod");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanprod(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanprod: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanstd(JNIEnv* env, jclass, jlong aHandle, jint axis, jboolean keepdims) {
    try {
        checkNotNull(env, aHandle, "nanstd");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanstd(*a, axis, keepdims);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanstd: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanvar(JNIEnv* env, jclass, jlong aHandle, jint axis, jint ddof, jboolean keepdims) {
    try {
        checkNotNull(env, aHandle, "nanvar");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanvar(*a, axis, ddof, keepdims);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanvar: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanpercentile(JNIEnv* env, jclass, jlong aHandle, jlong qHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanpercentile");
        checkNotNull(env, qHandle, "nanpercentile");
        auto* a = unwrapArray(aHandle);
        auto* q = unwrapArray(qHandle);
        auto result = npc::nanpercentile(*a, *q, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanpercentile: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanquantile(JNIEnv* env, jclass, jlong aHandle, jlong qHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanquantile");
        checkNotNull(env, qHandle, "nanquantile");
        auto* a = unwrapArray(aHandle);
        auto* q = unwrapArray(qHandle);
        auto result = npc::nanquantile(*a, *q, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanquantile: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNancumsum(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nancumsum");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nancumsum(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nancumsum: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNancumprod(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nancumprod");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nancumprod(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nancumprod: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanargmax(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanargmax");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanargmax(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanargmax: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanargmin(JNIEnv* env, jclass, jlong aHandle, jint axis) {
    try {
        checkNotNull(env, aHandle, "nanargmin");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nanargmin(*a, axis);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanargmin: unknown error");
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// NaN detection
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIsnan(JNIEnv* env, jclass, jlong aHandle) {
    try {
        checkNotNull(env, aHandle, "isnan");
        auto* a = unwrapArray(aHandle);
        auto result = npc::isnan(*a);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "isnan: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIsinf(JNIEnv* env, jclass, jlong aHandle) {
    try {
        checkNotNull(env, aHandle, "isinf");
        auto* a = unwrapArray(aHandle);
        auto result = npc::isinf(*a);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "isinf: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeIsfinite(JNIEnv* env, jclass, jlong aHandle) {
    try {
        checkNotNull(env, aHandle, "isfinite");
        auto* a = unwrapArray(aHandle);
        auto result = npc::isfinite(*a);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "isfinite: unknown error");
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNanToNum(JNIEnv* env, jclass, jlong aHandle) {
    try {
        checkNotNull(env, aHandle, "nanToNum");
        auto* a = unwrapArray(aHandle);
        auto result = npc::nan_to_num(*a);
        return wrapArray(std::make_unique<npc::Array>(std::move(result)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    } catch (...) {
        throwNpcException(env, "nanToNum: unknown error");
        return 0;
    }
}

} // extern "C"
