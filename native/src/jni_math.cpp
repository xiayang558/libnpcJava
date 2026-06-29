#include "jni_util.h"
using namespace npc;

extern "C" {

// ═══════════════════════════════════════════════════════════════════
// Unary math — each takes jlong aHandle, returns jlong
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAbs(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "abs");
        return wrapArray(std::make_unique<npc::Array>(npc::abs(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSqrt(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "sqrt");
        return wrapArray(std::make_unique<npc::Array>(npc::sqrt(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeExp(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "exp");
        return wrapArray(std::make_unique<npc::Array>(npc::exp(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLog(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "log");
        return wrapArray(std::make_unique<npc::Array>(npc::log(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLog10(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "log10");
        return wrapArray(std::make_unique<npc::Array>(npc::log10(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLog2(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "log2");
        return wrapArray(std::make_unique<npc::Array>(npc::log2(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Trigonometry ──────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSin(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "sin");
        return wrapArray(std::make_unique<npc::Array>(npc::sin(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCos(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "cos");
        return wrapArray(std::make_unique<npc::Array>(npc::cos(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTan(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "tan");
        return wrapArray(std::make_unique<npc::Array>(npc::tan(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSinh(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "sinh");
        return wrapArray(std::make_unique<npc::Array>(npc::sinh(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCosh(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "cosh");
        return wrapArray(std::make_unique<npc::Array>(npc::cosh(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTanh(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "tanh");
        return wrapArray(std::make_unique<npc::Array>(npc::tanh(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Inverse trigonometry ──────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArcsin(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "arcsin");
        return wrapArray(std::make_unique<npc::Array>(npc::arcsin(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArccos(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "arccos");
        return wrapArray(std::make_unique<npc::Array>(npc::arccos(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArctan(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "arctan");
        return wrapArray(std::make_unique<npc::Array>(npc::arctan(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArcsinh(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "arcsinh");
        return wrapArray(std::make_unique<npc::Array>(npc::arcsinh(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArccosh(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "arccosh");
        return wrapArray(std::make_unique<npc::Array>(npc::arccosh(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArctanh(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "arctanh");
        return wrapArray(std::make_unique<npc::Array>(npc::arctanh(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Angle conversion ──────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDeg2rad(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "deg2rad");
        return wrapArray(std::make_unique<npc::Array>(npc::deg2rad(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRad2deg(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "rad2deg");
        return wrapArray(std::make_unique<npc::Array>(npc::rad2deg(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDegrees(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "degrees");
        return wrapArray(std::make_unique<npc::Array>(npc::degrees(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRadians(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "radians");
        return wrapArray(std::make_unique<npc::Array>(npc::radians(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Rounding ──────────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFloor(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "floor");
        return wrapArray(std::make_unique<npc::Array>(npc::floor(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCeil(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "ceil");
        return wrapArray(std::make_unique<npc::Array>(npc::ceil(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRint(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "rint");
        return wrapArray(std::make_unique<npc::Array>(npc::rint(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrunc(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "trunc");
        return wrapArray(std::make_unique<npc::Array>(npc::trunc(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFix(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "fix");
        return wrapArray(std::make_unique<npc::Array>(npc::fix(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAround(JNIEnv* env, jclass, jlong aHandle, jint decimals) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "around");
        return wrapArray(std::make_unique<npc::Array>(npc::around(*a, static_cast<int>(decimals))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Sign / special ────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSign(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "sign");
        return wrapArray(std::make_unique<npc::Array>(npc::sign(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSinc(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "sinc");
        return wrapArray(std::make_unique<npc::Array>(npc::sinc(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFabs(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "fabs");
        return wrapArray(std::make_unique<npc::Array>(npc::fabs(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAbsolute(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "absolute");
        return wrapArray(std::make_unique<npc::Array>(npc::absolute(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeReciprocal(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "reciprocal");
        return wrapArray(std::make_unique<npc::Array>(npc::reciprocal(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePositive(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "positive");
        return wrapArray(std::make_unique<npc::Array>(npc::positive(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNegative(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "negative");
        return wrapArray(std::make_unique<npc::Array>(npc::negative(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCbrt(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "cbrt");
        return wrapArray(std::make_unique<npc::Array>(npc::cbrt(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSquare(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "square");
        return wrapArray(std::make_unique<npc::Array>(npc::square(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Heaviside step function ───────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeHeaviside(JNIEnv* env, jclass, jlong aHandle, jdouble h) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "heaviside");
        return wrapArray(std::make_unique<npc::Array>(npc::heaviside(*a, static_cast<double>(h))));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Bessel function ───────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeI0(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "i0");
        return wrapArray(std::make_unique<npc::Array>(npc::i0(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Complex number parts ──────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeReal(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "real");
        return wrapArray(std::make_unique<npc::Array>(npc::real(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeImag(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "imag");
        return wrapArray(std::make_unique<npc::Array>(npc::imag(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Phase angle (complex) ─────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAngle(JNIEnv* env, jclass, jlong aHandle, jboolean deg) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "angle");
        return wrapArray(std::make_unique<npc::Array>(npc::angle(*a, deg == JNI_TRUE)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ── Float spacing ─────────────────────────────────────────────────

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSpacing(JNIEnv* env, jclass, jlong aHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "spacing");
        return wrapArray(std::make_unique<npc::Array>(npc::spacing(*a)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Binary math — each takes jlong aHandle, jlong bHandle, returns jlong
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAdd(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "add");
        checkNotNull(env, bHandle, "add");
        return wrapArray(std::make_unique<npc::Array>(::add(a->get(), b->get())));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSubtract(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "subtract");
        checkNotNull(env, bHandle, "subtract");
        return wrapArray(std::make_unique<npc::Array>(::subtract(a->get(), b->get())));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMultiply(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "multiply");
        checkNotNull(env, bHandle, "multiply");
        return wrapArray(std::make_unique<npc::Array>(::multiply(a->get(), b->get())));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDivide(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "divide");
        checkNotNull(env, bHandle, "divide");
        return wrapArray(std::make_unique<npc::Array>(::divide(a->get(), b->get())));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTrueDivide(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "true_divide");
        checkNotNull(env, bHandle, "true_divide");
        return wrapArray(std::make_unique<npc::Array>(::true_divide(a->get(), b->get())));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePower(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "power");
        checkNotNull(env, bHandle, "power");
        return wrapArray(std::make_unique<npc::Array>(npc::power(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeHypot(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "hypot");
        checkNotNull(env, bHandle, "hypot");
        return wrapArray(std::make_unique<npc::Array>(npc::hypot(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogaddexp(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "logaddexp");
        checkNotNull(env, bHandle, "logaddexp");
        return wrapArray(std::make_unique<npc::Array>(npc::logaddexp(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogaddexp2(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "logaddexp2");
        checkNotNull(env, bHandle, "logaddexp2");
        return wrapArray(std::make_unique<npc::Array>(npc::logaddexp2(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeArctan2(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "arctan2");
        checkNotNull(env, bHandle, "arctan2");
        return wrapArray(std::make_unique<npc::Array>(npc::arctan2(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeCopysign(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "copysign");
        checkNotNull(env, bHandle, "copysign");
        return wrapArray(std::make_unique<npc::Array>(npc::copysign(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNextafter(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "nextafter");
        checkNotNull(env, bHandle, "nextafter");
        return wrapArray(std::make_unique<npc::Array>(npc::nextafter(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMod(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "mod");
        checkNotNull(env, bHandle, "mod");
        return wrapArray(std::make_unique<npc::Array>(npc::mod(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeFmod(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "fmod");
        checkNotNull(env, bHandle, "fmod");
        return wrapArray(std::make_unique<npc::Array>(npc::fmod(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMaximum(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "maximum");
        checkNotNull(env, bHandle, "maximum");
        return wrapArray(std::make_unique<npc::Array>(npc::maximum(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMinimum(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "minimum");
        checkNotNull(env, bHandle, "minimum");
        return wrapArray(std::make_unique<npc::Array>(npc::minimum(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLdexp(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "ldexp");
        checkNotNull(env, bHandle, "ldexp");
        return wrapArray(std::make_unique<npc::Array>(npc::ldexp(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGcd(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "gcd");
        checkNotNull(env, bHandle, "gcd");
        return wrapArray(std::make_unique<npc::Array>(npc::gcd(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLcm(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "lcm");
        checkNotNull(env, bHandle, "lcm");
        return wrapArray(std::make_unique<npc::Array>(npc::lcm(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLeftShift(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "left_shift");
        checkNotNull(env, bHandle, "left_shift");
        return wrapArray(std::make_unique<npc::Array>(npc::left_shift(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRightShift(JNIEnv* env, jclass, jlong aHandle, jlong bHandle) {
    try {
        auto* a = unwrapArray(aHandle);
        auto* b = unwrapArray(bHandle);
        checkNotNull(env, aHandle, "right_shift");
        checkNotNull(env, bHandle, "right_shift");
        return wrapArray(std::make_unique<npc::Array>(npc::right_shift(*a, *b)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

// ═══════════════════════════════════════════════════════════════════
// Scalar math — each takes jlong aHandle, jdouble scalar, returns jlong
// ═══════════════════════════════════════════════════════════════════

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeAddScalar(JNIEnv* env, jclass, jlong aHandle, jdouble scalar) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "add_scalar");
        double s = static_cast<double>(scalar);
        return wrapArray(std::make_unique<npc::Array>(::add_scalar(a->get(), &s)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSubtractScalar(JNIEnv* env, jclass, jlong aHandle, jdouble scalar) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "subtract_scalar");
        // a - s = a + (-s)
        double neg = -static_cast<double>(scalar);
        return wrapArray(std::make_unique<npc::Array>(::add_scalar(a->get(), &neg)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMultiplyScalar(JNIEnv* env, jclass, jlong aHandle, jdouble scalar) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "multiply_scalar");
        double s = static_cast<double>(scalar);
        return wrapArray(std::make_unique<npc::Array>(::multiply_scalar(a->get(), &s)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDivideScalar(JNIEnv* env, jclass, jlong aHandle, jdouble scalar) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "divide_scalar");
        // a / s = a * (1/s)
        double inv = 1.0 / static_cast<double>(scalar);
        return wrapArray(std::make_unique<npc::Array>(::multiply_scalar(a->get(), &inv)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeSubtractFromScalar(JNIEnv* env, jclass, jlong aHandle, jdouble scalar) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "subtract_from_scalar");
        // s - a = -(a + (-s))
        double neg = -static_cast<double>(scalar);
        auto temp = std::make_unique<npc::Array>(::add_scalar(a->get(), &neg));
        // negate: multiply by -1
        double neg_one = -1.0;
        return wrapArray(std::make_unique<npc::Array>(::multiply_scalar(temp->get(), &neg_one)));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDivideFromScalar(JNIEnv* env, jclass, jlong aHandle, jdouble scalar) {
    try {
        auto* a = unwrapArray(aHandle);
        checkNotNull(env, aHandle, "divide_from_scalar");
        // s / a — create a copy, then fill with scalar / a[i]
        double s = static_cast<double>(scalar);
        auto result = std::make_unique<npc::Array>(npc::copy(*a));
        for (int i = 0; i < result->size(); ++i) {
            (*result)[i] = s / (*result)[i];
        }
        return wrapArray(std::move(result));
    } catch (const std::exception& e) {
        throwNpcException(env, e.what());
        return 0;
    }
}

} // extern "C"
