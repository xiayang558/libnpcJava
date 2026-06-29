#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Simple linear algebra — each returns jlong
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDot(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "dot");
        checkNotNull(env, bHandle, "dot");
        return wrapArray(std::make_unique<npc::Array>(npc::dot(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMatmul(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "matmul");
        checkNotNull(env, bHandle, "matmul");
        return wrapArray(std::make_unique<npc::Array>(npc::matmul(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeVdot(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "vdot");
        checkNotNull(env, bHandle, "vdot");
        return wrapArray(std::make_unique<npc::Array>(npc::vdot(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeInner(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "inner");
        checkNotNull(env, bHandle, "inner");
        return wrapArray(std::make_unique<npc::Array>(npc::inner(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeOuter(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "outer");
        checkNotNull(env, bHandle, "outer");
        return wrapArray(std::make_unique<npc::Array>(npc::outer(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCross(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "cross");
        checkNotNull(env, bHandle, "cross");
        return wrapArray(std::make_unique<npc::Array>(npc::cross(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeKron(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "kron");
        checkNotNull(env, bHandle, "kron");
        return wrapArray(std::make_unique<npc::Array>(npc::kron(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Tensordot ──────────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTensordot_1axes(JNIEnv* env, jclass, jlong aHandle, jlong bHandle,
                                      jlong axesAHandle, jlong axesBHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        auto* axes_a = unwrapArray(axesAHandle);
        auto* axes_b = unwrapArray(axesBHandle);
        checkNotNull(env, aHandle, "tensordot");
        checkNotNull(env, bHandle, "tensordot");
        checkNotNull(env, axesAHandle, "tensordot");
        checkNotNull(env, axesBHandle, "tensordot");
        return wrapArray(std::make_unique<npc::Array>(npc::tensordot(*a, *b, *axes_a, *axes_b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTensordot_1int(JNIEnv* env, jclass, jlong aHandle, jlong bHandle,
                                     jint axes) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "tensordot");
        checkNotNull(env, bHandle, "tensordot");
        return wrapArray(std::make_unique<npc::Array>(npc::tensordot(*a, *b, static_cast<int>(axes))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Matrix properties ──────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeInv(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "inv");
        return wrapArray(std::make_unique<npc::Array>(npc::inv(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePinv(JNIEnv* env, jclass, jlong aHandle, jdouble rcond) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "pinv");
        return wrapArray(std::make_unique<npc::Array>(npc::pinv(*a, static_cast<double>(rcond))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDet(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "det");
        return wrapArray(std::make_unique<npc::Array>(npc::det(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrace(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "trace");
        return wrapArray(std::make_unique<npc::Array>(npc::trace(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Cholesky ───────────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCholesky(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "cholesky");
        return wrapArray(std::make_unique<npc::Array>(npc::cholesky(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Decompositions — each returns a jobject (Java result class)
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeSvd(JNIEnv* env, jclass, jlong aHandle, jboolean fullMatrices) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "svd");
        auto result = npc::svd(*a, fullMatrices);
        jclass svdCls = env->FindClass("libnpc/SvdResult");
        jmethodID ctor = env->GetMethodID(svdCls, "<init>",
            "(Llibnpc/NpcArray;Llibnpc/NpcArray;Llibnpc/NpcArray;)V");
        jobject uObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.U))));
        jobject sObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.s))));
        jobject vtObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.Vt))));
        return env->NewObject(svdCls, ctor, uObj, sObj, vtObj);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeQr(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "qr");
        auto result = npc::qr(*a);
        jclass cls = env->FindClass("libnpc/QrResult");
        jmethodID ctor = env->GetMethodID(cls, "<init>",
            "(Llibnpc/NpcArray;Llibnpc/NpcArray;)V");
        jobject qObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.Q))));
        jobject rObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.R))));
        return env->NewObject(cls, ctor, qObj, rObj);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeLu(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "lu");
        auto result = npc::lu(*a);
        jclass cls = env->FindClass("libnpc/LuResult");
        jmethodID ctor = env->GetMethodID(cls, "<init>",
            "(Llibnpc/NpcArray;Llibnpc/NpcArray;Llibnpc/NpcArray;)V");
        jobject pObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.P))));
        jobject lObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.L))));
        jobject uObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.U))));
        return env->NewObject(cls, ctor, pObj, lObj, uObj);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

JNIEXPORT jobject JNICALL
Java_libnpc_Npc_nativeEig(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "eig");
        auto result = npc::eig(*a);
        jclass cls = env->FindClass("libnpc/EigResult");
        jmethodID ctor = env->GetMethodID(cls, "<init>",
            "(Llibnpc/NpcArray;Llibnpc/NpcArray;)V");
        jobject eigenvalsObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.eigenvalues))));
        jobject eigenvecsObj = createNpcArrayObject(env,
            wrapArray(std::make_unique<npc::Array>(std::move(result.eigenvectors))));
        return env->NewObject(cls, ctor, eigenvalsObj, eigenvecsObj);
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return nullptr;
    }
}

} // extern "C"
