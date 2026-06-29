#include "jni_util.h"
using namespace npc;

extern "C" {

// Helper: convert jintArray shape to (data*, ndim) pair for C functions
#define SHAPE(shv) \
    int _nd = static_cast<int>((shv).size()); \
    int* _sp = (shv).empty() ? nullptr : (shv).data()

// Call C function, wrap as npc::Array, return jlong
#define JNI_RAND(CFunc, ...) \
    do { \
        ::Array* raw = ::CFunc(__VA_ARGS__); \
        if (!raw) { throwNpcException(env, #CFunc " failed"); return 0; } \
        return wrapArray(std::make_unique<npc::Array>(raw)); \
    } while(0)

// ── Seeding ───────────────────────────────────────────────────────
JNIEXPORT void JNICALL
Java_libnpc_Npc_nativeRandomSeed(JNIEnv*, jclass, jlong seed) { ::random_seed(seed); }
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRandomUint64(JNIEnv*, jclass) { return static_cast<jlong>(::random_uint64()); }
JNIEXPORT jdouble JNICALL
Java_libnpc_Npc_nativeRandomDouble(JNIEnv*, jclass) { return ::random_double(); }

// ── Uniform ───────────────────────────────────────────────────────
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRandomSample(JNIEnv* env, jclass, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_sample, _sp, _nd); } catch(...) { throwNpcException(env,"randomSample failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRand(JNIEnv* env, jclass, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_rand, _sp, _nd); } catch(...) { throwNpcException(env,"rand failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRandint(JNIEnv* env, jclass, jint low, jint high, jintArray jsh, jint dtypeOrdinal) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_randint, low, high, _sp, _nd, static_cast<DataType>(dtypeOrdinal)); }
    catch(...) { throwNpcException(env,"randint failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeUniform(JNIEnv* env, jclass, jdouble low, jdouble high, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_uniform, low, high, _sp, _nd); }
    catch(...) { throwNpcException(env,"uniform failed"); return 0; }
}

// ── Normal ────────────────────────────────────────────────────────
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeStandardNormal(JNIEnv* env, jclass, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_standard_normal, _sp, _nd); } catch(...) { throwNpcException(env,"standardNormal failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRandn(JNIEnv* env, jclass, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_randn, _sp, _nd); } catch(...) { throwNpcException(env,"randn failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNormal(JNIEnv* env, jclass, jdouble loc, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_normal, loc, scale, _sp, _nd); } catch(...) { throwNpcException(env,"normal failed"); return 0; }
}

// ── Exponential ───────────────────────────────────────────────────
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeStandardExponential(JNIEnv* env, jclass, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_standard_exponential, _sp, _nd); } catch(...) { throwNpcException(env,"standardExponential failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeExponential(JNIEnv* env, jclass, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_exponential, scale, _sp, _nd); } catch(...) { throwNpcException(env,"exponential failed"); return 0; }
}

// ── Gamma family ──────────────────────────────────────────────────
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeStandardGamma(JNIEnv* env, jclass, jdouble shape, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_standard_gamma, shape, _sp, _nd); } catch(...) { throwNpcException(env,"standardGamma failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGamma(JNIEnv* env, jclass, jdouble shape, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_gamma, shape, scale, _sp, _nd); } catch(...) { throwNpcException(env,"gamma failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeChisquare(JNIEnv* env, jclass, jdouble df, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_chisquare, df, _sp, _nd); } catch(...) { throwNpcException(env,"chisquare failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBeta(JNIEnv* env, jclass, jdouble a, jdouble b, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_beta, a, b, _sp, _nd); } catch(...) { throwNpcException(env,"beta failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeStandardT(JNIEnv* env, jclass, jdouble df, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_standard_t, df, _sp, _nd); } catch(...) { throwNpcException(env,"standardT failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeF(JNIEnv* env, jclass, jdouble dfn, jdouble dfd, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_f, dfn, dfd, _sp, _nd); } catch(...) { throwNpcException(env,"F failed"); return 0; }
}

// ── Continuous distributions ──────────────────────────────────────
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLaplace(JNIEnv* env, jclass, jdouble loc, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_laplace, loc, scale, _sp, _nd); } catch(...) { throwNpcException(env,"laplace failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogistic(JNIEnv* env, jclass, jdouble loc, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_logistic, loc, scale, _sp, _nd); } catch(...) { throwNpcException(env,"logistic failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLognormal(JNIEnv* env, jclass, jdouble mean, jdouble sigma, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_lognormal, mean, sigma, _sp, _nd); } catch(...) { throwNpcException(env,"lognormal failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePareto(JNIEnv* env, jclass, jdouble a, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_pareto, a, _sp, _nd); } catch(...) { throwNpcException(env,"pareto failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePowerDist(JNIEnv* env, jclass, jdouble a, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_power, a, _sp, _nd); } catch(...) { throwNpcException(env,"powerDist failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRayleigh(JNIEnv* env, jclass, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_rayleigh, scale, _sp, _nd); } catch(...) { throwNpcException(env,"rayleigh failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeWeibull(JNIEnv* env, jclass, jdouble a, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_weibull, a, _sp, _nd); } catch(...) { throwNpcException(env,"weibull failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeStandardCauchy(JNIEnv* env, jclass, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_standard_cauchy, _sp, _nd); } catch(...) { throwNpcException(env,"standardCauchy failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGumbel(JNIEnv* env, jclass, jdouble loc, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_gumbel, loc, scale, _sp, _nd); } catch(...) { throwNpcException(env,"gumbel failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeTriangular(JNIEnv* env, jclass, jdouble left, jdouble mode, jdouble right, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_triangular, left, mode, right, _sp, _nd); } catch(...) { throwNpcException(env,"triangular failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeVonmises(JNIEnv* env, jclass, jdouble mu, jdouble kappa, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_vonmises, mu, kappa, _sp, _nd); } catch(...) { throwNpcException(env,"vonmises failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeWald(JNIEnv* env, jclass, jdouble mean, jdouble scale, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_wald, mean, scale, _sp, _nd); } catch(...) { throwNpcException(env,"wald failed"); return 0; }
}

// ── Discrete distributions ────────────────────────────────────────
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeGeometric(JNIEnv* env, jclass, jdouble p, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_geometric, p, _sp, _nd); } catch(...) { throwNpcException(env,"geometric failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePoisson(JNIEnv* env, jclass, jdouble lam, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_poisson, lam, _sp, _nd); } catch(...) { throwNpcException(env,"poisson failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeBinomial(JNIEnv* env, jclass, jint n, jdouble p, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_binomial, n, p, _sp, _nd); } catch(...) { throwNpcException(env,"binomial failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeNegativeBinomial(JNIEnv* env, jclass, jint n, jdouble p, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_negative_binomial, n, p, _sp, _nd); } catch(...) { throwNpcException(env,"negativeBinomial failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeHypergeometric(JNIEnv* env, jclass, jint ngood, jint nbad, jint nsample, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_hypergeometric, ngood, nbad, nsample, _sp, _nd); } catch(...) { throwNpcException(env,"hypergeometric failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeZipf(JNIEnv* env, jclass, jdouble a, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_zipf, a, _sp, _nd); } catch(...) { throwNpcException(env,"zipf failed"); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeLogseries(JNIEnv* env, jclass, jdouble p, jintArray jsh) {
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_logseries, p, _sp, _nd); } catch(...) { throwNpcException(env,"logseries failed"); return 0; }
}

// ── Sampling ──────────────────────────────────────────────────────
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativePermutation(JNIEnv* env, jclass, jlong aHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "permutation: null input"); return 0; }
    try { auto r = npc::permutation(*a); return wrapArray(std::make_unique<npc::Array>(std::move(r))); }
    catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}
JNIEXPORT void JNICALL
Java_libnpc_Npc_nativeShuffle(JNIEnv* env, jobject obj) {
    jlong handle = getNativeHandle(env, obj);
    auto* a = unwrapArray(handle);
    if (!a) { throwNpcException(env, "shuffle: null input"); return; }
    npc::shuffle(*a);
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeChoice(JNIEnv* env, jclass, jlong aHandle, jint size, jboolean replace, jlong pHandle) {
    auto* a = unwrapArray(aHandle);
    if (!a) { throwNpcException(env, "choice: null input"); return 0; }
    npc::Array p;
    if (pHandle != 0) { auto* pp = unwrapArray(pHandle); if (pp) p = *pp; }
    try { auto r = npc::choice(*a, size, replace, p); return wrapArray(std::make_unique<npc::Array>(std::move(r))); }
    catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMultinomial(JNIEnv* env, jclass, jint n, jlong pvalsHandle, jintArray jsh) {
    auto* pvals = unwrapArray(pvalsHandle);
    if (!pvals) { throwNpcException(env, "multinomial: null pvals"); return 0; }
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    try { JNI_RAND(random_multinomial, n, pvals->get(), _sp, _nd); }
    catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeMultivariateNormal(JNIEnv* env, jclass, jlong meanHandle, jlong covHandle, jintArray jsh) {
    auto* mean = unwrapArray(meanHandle);
    auto* cov = unwrapArray(covHandle);
    if (!mean || !cov) { throwNpcException(env, "multivariateNormal: null input"); return 0; }
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    ::Array* raw = ::random_multivariate_normal(mean->get(), cov->get(), _sp, _nd);
    if (!raw) { throwNpcException(env, "multivariateNormal failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeDirichlet(JNIEnv* env, jclass, jlong alphaHandle, jintArray jsh) {
    auto* alpha = unwrapArray(alphaHandle);
    if (!alpha) { throwNpcException(env, "dirichlet: null input"); return 0; }
    auto sh = jintArrayToVector(env, jsh); SHAPE(sh);
    ::Array* raw = ::random_dirichlet(alpha->get(), _sp, _nd);
    if (!raw) { throwNpcException(env, "dirichlet failed"); return 0; }
    return wrapArray(std::make_unique<npc::Array>(raw));
}
JNIEXPORT jlong JNICALL
Java_libnpc_Npc_nativeRandomBytes(JNIEnv* env, jclass, jint n) {
    try { auto r = npc::random_bytes(n); return wrapArray(std::make_unique<npc::Array>(std::move(r))); }
    catch (const std::exception& e) { throwNpcException(env, e.what()); return 0; }
}

#undef JNI_RAND
#undef SHAPE

} // extern "C"
