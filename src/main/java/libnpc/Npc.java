package libnpc;

import libnpc.io.ReadtxtBuilder;
import libnpc.io.SavetxtBuilder;

/**
 * Static utility class with all factory functions, mathematical operations,
 * and computational methods for {@link NpcArray}.
 *
 * <p>Mirrors NumPy's {@code np.} namespace. All methods are static and
 * produce or consume {@link NpcArray} objects.</p>
 *
 * <p>For common operations, use instance methods on {@link NpcArray} directly
 * (e.g. {@code arr.sum()} instead of {@code Npc.sum(arr)}).</p>
 *
 * <h3>Module Overview</h3>
 * <ul>
 *   <li><b>Creation</b> — zeros, ones, full, empty, arange, linspace, eye, …</li>
 *   <li><b>Math</b> — abs, sqrt, exp, log, sin, cos, add, multiply, …</li>
 *   <li><b>Statistics</b> — sum, mean, min, max, stddev, var, median, …</li>
 *   <li><b>Linear Algebra</b> — dot, matmul, inv, svd, qr, lu, eig, …</li>
 *   <li><b>FFT</b> — fft, ifft, rfft, fft2, fftshift, fftfreq, …</li>
 *   <li><b>Random</b> — rand, randn, uniform, normal, exponential, …</li>
 *   <li><b>Shape</b> — reshape, transpose, concatenate, stack, split, …</li>
 *   <li><b>… and more</b></li>
 * </ul>
 *
 * @version 1.0.0
 */
public final class Npc {

    static {
        NativeLib.ensureLoaded();
    }

    private Npc() {}

    // ═══════════════════════════════════════════════════════════
    // Metadata
    // ═══════════════════════════════════════════════════════════

    /** Library version string. */
    public static native String nativeVersion();

    /** Returns the library version string. */
    public static String version() { return nativeVersion(); }

    // ═══════════════════════════════════════════════════════════
    // Array Creation
    // ═══════════════════════════════════════════════════════════

    /** Create an array of zeros with default Float64 dtype. */
    public static NpcArray zeros(int... shape) {
        return new NpcArray(nativeZeros(shape, DType.FLOAT64.ordinal()));
    }
    /** Create an array of zeros with specified dtype. */
    public static NpcArray zeros(DType dtype, int... shape) {
        return new NpcArray(nativeZeros(shape, dtype.ordinal()));
    }
    /** Create an array of ones with default Float64 dtype. */
    public static NpcArray ones(int... shape) {
        return new NpcArray(nativeOnes(shape, DType.FLOAT64.ordinal()));
    }
    /** Create an array of ones with specified dtype. */
    public static NpcArray ones(DType dtype, int... shape) {
        return new NpcArray(nativeOnes(shape, dtype.ordinal()));
    }
    /** Create an array filled with a constant value. */
    public static NpcArray full(int[] shape, double value) {
        return new NpcArray(nativeFull(shape, value, DType.FLOAT64.ordinal()));
    }
    /** Create an array filled with a constant value, with specified dtype. */
    public static NpcArray full(int[] shape, double value, DType dtype) {
        return new NpcArray(nativeFull(shape, value, dtype.ordinal()));
    }
    /** Create an uninitialized array. */
    public static NpcArray empty(int... shape) {
        return new NpcArray(nativeEmpty(shape, DType.FLOAT64.ordinal()));
    }
    /** Create an uninitialized array with specified dtype. */
    public static NpcArray empty(DType dtype, int... shape) {
        return new NpcArray(nativeEmpty(shape, dtype.ordinal()));
    }
    /** Evenly spaced values in [start, stop) with step. Like numpy.arange. */
    public static NpcArray arange(double start, double stop, double step) {
        return new NpcArray(nativeArange(start, stop, step, DType.FLOAT64.ordinal()));
    }
    /** arange with default step=1.0. */
    public static NpcArray arange(double start, double stop) {
        return arange(start, stop, 1.0);
    }
    /** arange with specified dtype. */
    public static NpcArray arange(double start, double stop, double step, DType dtype) {
        return new NpcArray(nativeArange(start, stop, step, dtype.ordinal()));
    }
    /** Evenly spaced numbers over interval. Like numpy.linspace. */
    public static NpcArray linspace(double start, double stop, int num) {
        return new NpcArray(nativeLinspace(start, stop, num, true));
    }
    /** linspace with endpoint control. */
    public static NpcArray linspace(double start, double stop, int num, boolean endpoint) {
        return new NpcArray(nativeLinspace(start, stop, num, endpoint));
    }
    /** Logarithmically spaced numbers. Like numpy.logspace. */
    public static NpcArray logspace(double start, double stop, int num) {
        return new NpcArray(nativeLogspace(start, stop, num, 10.0, true));
    }
    /** logspace with base and endpoint. */
    public static NpcArray logspace(double start, double stop, int num, double base, boolean endpoint) {
        return new NpcArray(nativeLogspace(start, stop, num, base, endpoint));
    }
    /** Geometrically spaced numbers. Like numpy.geomspace. */
    public static NpcArray geomspace(double start, double stop, int num) {
        return new NpcArray(nativeGeomspace(start, stop, num, true));
    }
    /** geomspace with endpoint control. */
    public static NpcArray geomspace(double start, double stop, int num, boolean endpoint) {
        return new NpcArray(nativeGeomspace(start, stop, num, endpoint));
    }
    /** Identity-like matrix with optional offset. Like numpy.eye. */
    public static NpcArray eye(int N) {
        return new NpcArray(nativeEye(N, -1, 0, DType.FLOAT64.ordinal()));
    }
    /** eye with M columns. */
    public static NpcArray eye(int N, int M) {
        return new NpcArray(nativeEye(N, M, 0, DType.FLOAT64.ordinal()));
    }
    /** eye with M and diagonal offset k. */
    public static NpcArray eye(int N, int M, int k) {
        return new NpcArray(nativeEye(N, M, k, DType.FLOAT64.ordinal()));
    }
    /** eye with full parameters. */
    public static NpcArray eye(int N, int M, int k, DType dtype) {
        return new NpcArray(nativeEye(N, M, k, dtype.ordinal()));
    }
    /** N×N identity matrix. Like numpy.identity. */
    public static NpcArray identity(int N) {
        return new NpcArray(nativeIdentity(N, DType.FLOAT64.ordinal()));
    }
    /** identity with specified dtype. */
    public static NpcArray identity(int N, DType dtype) {
        return new NpcArray(nativeIdentity(N, dtype.ordinal()));
    }
    /** Create like another array, filled with a value. */
    public static NpcArray fullLike(NpcArray arr, double value) {
        return new NpcArray(nativeFullLike(arr.nativePtr, value, DType.FLOAT64.ordinal()));
    }
    /** fullLike with specified dtype. */
    public static NpcArray fullLike(NpcArray arr, double value, DType dtype) {
        return new NpcArray(nativeFullLike(arr.nativePtr, value, dtype.ordinal()));
    }

    /** Create 1-D array from double[]. */
    public static NpcArray array(double[] data) {
        return new NpcArray(nativeArray1D(data));
    }
    /** Create 2-D array from double[][]. */
    public static NpcArray array(double[][] data) {
        return new NpcArray(nativeArray2D(data));
    }
    /** Create 1-D array from int[]. */
    public static NpcArray array(int[] data) {
        double[] d = new double[data.length];
        for (int i = 0; i < data.length; i++) d[i] = data[i];
        return new NpcArray(nativeArray1D(d));
    }

    // ═══════════════════════════════════════════════════════════
    // Copy / Type Conversion
    // ═══════════════════════════════════════════════════════════

    /** Deep copy of an array. */
    public static NpcArray copy(NpcArray arr) {
        return new NpcArray(nativeCopy(arr.nativePtr));
    }
    /** Cast array to a different data type. */
    public static NpcArray astype(NpcArray arr, DType dtype) {
        return new NpcArray(nativeAstype(arr.nativePtr, dtype.ordinal()));
    }

    // ═══════════════════════════════════════════════════════════
    // Arithmetic Operators (binary)
    // ═══════════════════════════════════════════════════════════

    /** Element-wise addition. */
    public static NpcArray add(NpcArray a, NpcArray b) {
        return new NpcArray(nativeAdd(a.nativePtr, b.nativePtr));
    }
    /** Element-wise addition with scalar. */
    public static NpcArray add(NpcArray a, double scalar) {
        return new NpcArray(nativeAddScalar(a.nativePtr, scalar));
    }
    /** Element-wise subtraction. */
    public static NpcArray subtract(NpcArray a, NpcArray b) {
        return new NpcArray(nativeSubtract(a.nativePtr, b.nativePtr));
    }
    /** Element-wise subtraction with scalar. */
    public static NpcArray subtract(NpcArray a, double scalar) {
        return new NpcArray(nativeSubtractScalar(a.nativePtr, scalar));
    }
    /** Scalar minus array. */
    public static NpcArray subtract(double scalar, NpcArray a) {
        return new NpcArray(nativeSubtractFromScalar(a.nativePtr, scalar));
    }
    /** Element-wise multiplication. */
    public static NpcArray multiply(NpcArray a, NpcArray b) {
        return new NpcArray(nativeMultiply(a.nativePtr, b.nativePtr));
    }
    /** Element-wise multiplication with scalar. */
    public static NpcArray multiply(NpcArray a, double scalar) {
        return new NpcArray(nativeMultiplyScalar(a.nativePtr, scalar));
    }
    /** Element-wise division. */
    public static NpcArray divide(NpcArray a, NpcArray b) {
        return new NpcArray(nativeDivide(a.nativePtr, b.nativePtr));
    }
    /** Element-wise division with scalar. */
    public static NpcArray divide(NpcArray a, double scalar) {
        return new NpcArray(nativeDivideScalar(a.nativePtr, scalar));
    }
    /** Scalar divided by array. */
    public static NpcArray divide(double scalar, NpcArray a) {
        return new NpcArray(nativeDivideFromScalar(a.nativePtr, scalar));
    }
    /** Forced floating-point division. Like numpy.true_divide. */
    public static NpcArray trueDivide(NpcArray a, NpcArray b) {
        return new NpcArray(nativeTrueDivide(a.nativePtr, b.nativePtr));
    }
    /** Element-wise power. */
    public static NpcArray power(NpcArray a, NpcArray b) {
        return new NpcArray(nativePower(a.nativePtr, b.nativePtr));
    }
    /** Element-wise hypot. sqrt(x² + y²). */
    public static NpcArray hypot(NpcArray x, NpcArray y) {
        return new NpcArray(nativeHypot(x.nativePtr, y.nativePtr));
    }
    /** log(exp(a) + exp(b)), avoiding overflow. */
    public static NpcArray logaddexp(NpcArray a, NpcArray b) {
        return new NpcArray(nativeLogaddexp(a.nativePtr, b.nativePtr));
    }
    /** log2(2**a + 2**b), avoiding overflow. */
    public static NpcArray logaddexp2(NpcArray a, NpcArray b) {
        return new NpcArray(nativeLogaddexp2(a.nativePtr, b.nativePtr));
    }
    /** Element-wise arctan2. */
    public static NpcArray arctan2(NpcArray y, NpcArray x) {
        return new NpcArray(nativeArctan2(y.nativePtr, x.nativePtr));
    }
    /** Copy sign from x2 to x1. */
    public static NpcArray copysign(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeCopysign(x1.nativePtr, x2.nativePtr));
    }
    /** Next representable value. */
    public static NpcArray nextafter(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeNextafter(x1.nativePtr, x2.nativePtr));
    }
    /** Element-wise modulo. Like numpy.mod. */
    public static NpcArray mod(NpcArray a, NpcArray b) {
        return new NpcArray(nativeMod(a.nativePtr, b.nativePtr));
    }
    /** Element-wise floating-point modulo. Like numpy.fmod. */
    public static NpcArray fmod(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeFmod(x1.nativePtr, x2.nativePtr));
    }
    /** Element-wise maximum. Like numpy.maximum. */
    public static NpcArray maximum(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeMaximum(x1.nativePtr, x2.nativePtr));
    }
    /** Element-wise minimum. Like numpy.minimum. */
    public static NpcArray minimum(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeMinimum(x1.nativePtr, x2.nativePtr));
    }
    /** Load exponent. */
    public static NpcArray ldexp(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeLdexp(x1.nativePtr, x2.nativePtr));
    }
    /** Greatest common divisor. */
    public static NpcArray gcd(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeGcd(x1.nativePtr, x2.nativePtr));
    }
    /** Least common multiple. */
    public static NpcArray lcm(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeLcm(x1.nativePtr, x2.nativePtr));
    }
    /** Bitwise left shift. */
    public static NpcArray leftShift(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeLeftShift(x1.nativePtr, x2.nativePtr));
    }
    /** Bitwise right shift. */
    public static NpcArray rightShift(NpcArray x1, NpcArray x2) {
        return new NpcArray(nativeRightShift(x1.nativePtr, x2.nativePtr));
    }

    // ═══════════════════════════════════════════════════════════
    // Unary Math Functions
    // ═══════════════════════════════════════════════════════════

    /** Element-wise absolute value. */
    public static NpcArray abs(NpcArray a) { return new NpcArray(nativeAbs(a.nativePtr)); }
    /** Element-wise square root. */
    public static NpcArray sqrt(NpcArray a) { return new NpcArray(nativeSqrt(a.nativePtr)); }
    /** Element-wise exponential (e^x). */
    public static NpcArray exp(NpcArray a) { return new NpcArray(nativeExp(a.nativePtr)); }
    /** Element-wise natural logarithm. */
    public static NpcArray log(NpcArray a) { return new NpcArray(nativeLog(a.nativePtr)); }
    /** Element-wise base-10 logarithm. */
    public static NpcArray log10(NpcArray a) { return new NpcArray(nativeLog10(a.nativePtr)); }
    /** Element-wise base-2 logarithm. */
    public static NpcArray log2(NpcArray a) { return new NpcArray(nativeLog2(a.nativePtr)); }
    /** Element-wise sine. */
    public static NpcArray sin(NpcArray a) { return new NpcArray(nativeSin(a.nativePtr)); }
    /** Element-wise cosine. */
    public static NpcArray cos(NpcArray a) { return new NpcArray(nativeCos(a.nativePtr)); }
    /** Element-wise tangent. */
    public static NpcArray tan(NpcArray a) { return new NpcArray(nativeTan(a.nativePtr)); }
    /** Element-wise hyperbolic sine. */
    public static NpcArray sinh(NpcArray a) { return new NpcArray(nativeSinh(a.nativePtr)); }
    /** Element-wise hyperbolic cosine. */
    public static NpcArray cosh(NpcArray a) { return new NpcArray(nativeCosh(a.nativePtr)); }
    /** Element-wise hyperbolic tangent. */
    public static NpcArray tanh(NpcArray a) { return new NpcArray(nativeTanh(a.nativePtr)); }
    /** Element-wise inverse sine. */
    public static NpcArray arcsin(NpcArray a) { return new NpcArray(nativeArcsin(a.nativePtr)); }
    /** Element-wise inverse cosine. */
    public static NpcArray arccos(NpcArray a) { return new NpcArray(nativeArccos(a.nativePtr)); }
    /** Element-wise inverse tangent. */
    public static NpcArray arctan(NpcArray a) { return new NpcArray(nativeArctan(a.nativePtr)); }
    /** Element-wise inverse hyperbolic sine. */
    public static NpcArray arcsinh(NpcArray a) { return new NpcArray(nativeArcsinh(a.nativePtr)); }
    /** Element-wise inverse hyperbolic cosine. */
    public static NpcArray arccosh(NpcArray a) { return new NpcArray(nativeArccosh(a.nativePtr)); }
    /** Element-wise inverse hyperbolic tangent. */
    public static NpcArray arctanh(NpcArray a) { return new NpcArray(nativeArctanh(a.nativePtr)); }
    /** Convert degrees to radians. */
    public static NpcArray deg2rad(NpcArray a) { return new NpcArray(nativeDeg2rad(a.nativePtr)); }
    /** Convert radians to degrees. */
    public static NpcArray rad2deg(NpcArray a) { return new NpcArray(nativeRad2deg(a.nativePtr)); }
    /** Convert radians to degrees (alias). */
    public static NpcArray degrees(NpcArray a) { return new NpcArray(nativeDegrees(a.nativePtr)); }
    /** Convert degrees to radians (alias). */
    public static NpcArray radians(NpcArray a) { return new NpcArray(nativeRadians(a.nativePtr)); }
    /** Element-wise floor (round down). */
    public static NpcArray floor(NpcArray a) { return new NpcArray(nativeFloor(a.nativePtr)); }
    /** Element-wise ceil (round up). */
    public static NpcArray ceil(NpcArray a) { return new NpcArray(nativeCeil(a.nativePtr)); }
    /** Round to nearest integer, ties to even. */
    public static NpcArray rint(NpcArray a) { return new NpcArray(nativeRint(a.nativePtr)); }
    /** Truncate toward zero. */
    public static NpcArray trunc(NpcArray a) { return new NpcArray(nativeTrunc(a.nativePtr)); }
    /** Round toward zero. */
    public static NpcArray fix(NpcArray a) { return new NpcArray(nativeFix(a.nativePtr)); }
    /** Round to given number of decimals. */
    public static NpcArray around(NpcArray a, int decimals) { return new NpcArray(nativeAround(a.nativePtr, decimals)); }
    /** Element-wise sign (-1, 0, +1). */
    public static NpcArray sign(NpcArray a) { return new NpcArray(nativeSign(a.nativePtr)); }
    /** sinc(x) = sin(πx)/(πx). */
    public static NpcArray sinc(NpcArray a) { return new NpcArray(nativeSinc(a.nativePtr)); }
    /** Element-wise absolute value (float). Like numpy.fabs. */
    public static NpcArray fabs(NpcArray a) { return new NpcArray(nativeFabs(a.nativePtr)); }
    /** Element-wise absolute value (alias). Like numpy.absolute. */
    public static NpcArray absolute(NpcArray a) { return new NpcArray(nativeAbsolute(a.nativePtr)); }
    /** Element-wise reciprocal (1/x). */
    public static NpcArray reciprocal(NpcArray a) { return new NpcArray(nativeReciprocal(a.nativePtr)); }
    /** Element-wise unary plus (+x). */
    public static NpcArray positive(NpcArray a) { return new NpcArray(nativePositive(a.nativePtr)); }
    /** Element-wise negation (-x). */
    public static NpcArray negative(NpcArray a) { return new NpcArray(nativeNegative(a.nativePtr)); }
    /** Element-wise cube root. */
    public static NpcArray cbrt(NpcArray a) { return new NpcArray(nativeCbrt(a.nativePtr)); }
    /** Element-wise square (x²). */
    public static NpcArray square(NpcArray a) { return new NpcArray(nativeSquare(a.nativePtr)); }
    /** Heaviside step function. */
    public static NpcArray heaviside(NpcArray x, double h) { return new NpcArray(nativeHeaviside(x.nativePtr, h)); }
    /** Modified Bessel function of the first kind, order 0. */
    public static NpcArray i0(NpcArray a) { return new NpcArray(nativeI0(a.nativePtr)); }
    /** Real part of complex numbers. */
    public static NpcArray real(NpcArray a) { return new NpcArray(nativeReal(a.nativePtr)); }
    /** Imaginary part of complex numbers. */
    public static NpcArray imag(NpcArray a) { return new NpcArray(nativeImag(a.nativePtr)); }
    /** Angle of complex numbers. */
    public static NpcArray angle(NpcArray z) { return new NpcArray(nativeAngle(z.nativePtr, false)); }
    /** Angle in degrees if deg=true. */
    public static NpcArray angle(NpcArray z, boolean deg) { return new NpcArray(nativeAngle(z.nativePtr, deg)); }
    /** Spacing between floating-point values. */
    public static NpcArray spacing(NpcArray a) { return new NpcArray(nativeSpacing(a.nativePtr)); }

    // ═══════════════════════════════════════════════════════════
    // Comparison
    // ═══════════════════════════════════════════════════════════

    /** Element-wise equality. Returns BOOL array. */
    public static NpcArray equal(NpcArray a, NpcArray b) { return new NpcArray(nativeEqual(a.nativePtr, b.nativePtr)); }
    /** Element-wise inequality. */
    public static NpcArray notEqual(NpcArray a, NpcArray b) { return new NpcArray(nativeNotEqual(a.nativePtr, b.nativePtr)); }
    /** Element-wise greater-than. */
    public static NpcArray greater(NpcArray a, NpcArray b) { return new NpcArray(nativeGreater(a.nativePtr, b.nativePtr)); }
    /** Element-wise greater-or-equal. */
    public static NpcArray greaterEqual(NpcArray a, NpcArray b) { return new NpcArray(nativeGreaterEqual(a.nativePtr, b.nativePtr)); }
    /** Element-wise less-than. */
    public static NpcArray less(NpcArray a, NpcArray b) { return new NpcArray(nativeLess(a.nativePtr, b.nativePtr)); }
    /** Element-wise less-or-equal. */
    public static NpcArray lessEqual(NpcArray a, NpcArray b) { return new NpcArray(nativeLessEqual(a.nativePtr, b.nativePtr)); }
    /** Approximate equality with default tolerances. */
    public static NpcArray isclose(NpcArray a, NpcArray b) {
        return new NpcArray(nativeIsclose(a.nativePtr, b.nativePtr, 1e-5, 1e-8, false));
    }
    /** isclose with custom tolerances. */
    public static NpcArray isclose(NpcArray a, NpcArray b, double rtol, double atol) {
        return new NpcArray(nativeIsclose(a.nativePtr, b.nativePtr, rtol, atol, false));
    }
    /** isclose with equal_nan option. */
    public static NpcArray isclose(NpcArray a, NpcArray b, double rtol, double atol, boolean equalNan) {
        return new NpcArray(nativeIsclose(a.nativePtr, b.nativePtr, rtol, atol, equalNan));
    }

    // ═══════════════════════════════════════════════════════════
    // Logical / Bitwise
    // ═══════════════════════════════════════════════════════════

    public static NpcArray logicalAnd(NpcArray a, NpcArray b) { return new NpcArray(nativeLogicalAnd(a.nativePtr, b.nativePtr)); }
    public static NpcArray logicalOr(NpcArray a, NpcArray b) { return new NpcArray(nativeLogicalOr(a.nativePtr, b.nativePtr)); }
    public static NpcArray logicalXor(NpcArray a, NpcArray b) { return new NpcArray(nativeLogicalXor(a.nativePtr, b.nativePtr)); }
    public static NpcArray logicalNot(NpcArray a) { return new NpcArray(nativeLogicalNot(a.nativePtr)); }
    public static NpcArray bitwiseAnd(NpcArray a, NpcArray b) { return new NpcArray(nativeBitwiseAnd(a.nativePtr, b.nativePtr)); }
    public static NpcArray bitwiseOr(NpcArray a, NpcArray b) { return new NpcArray(nativeBitwiseOr(a.nativePtr, b.nativePtr)); }
    public static NpcArray bitwiseXor(NpcArray a, NpcArray b) { return new NpcArray(nativeBitwiseXor(a.nativePtr, b.nativePtr)); }
    public static NpcArray bitwiseNot(NpcArray a) { return new NpcArray(nativeBitwiseNot(a.nativePtr)); }
    public static NpcArray invert(NpcArray a) { return new NpcArray(nativeInvert(a.nativePtr)); }

    // ═══════════════════════════════════════════════════════════
    // Statistics / Aggregation
    // ═══════════════════════════════════════════════════════════

    public static NpcArray sum(NpcArray a) { return new NpcArray(nativeSum(a.nativePtr, -1, false)); }
    public static NpcArray sum(NpcArray a, int axis) { return new NpcArray(nativeSum(a.nativePtr, axis, false)); }
    public static NpcArray sum(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeSum(a.nativePtr, axis, keepdims)); }
    public static NpcArray mean(NpcArray a) { return new NpcArray(nativeMean(a.nativePtr, -1, false)); }
    public static NpcArray mean(NpcArray a, int axis) { return new NpcArray(nativeMean(a.nativePtr, axis, false)); }
    public static NpcArray mean(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeMean(a.nativePtr, axis, keepdims)); }
    public static NpcArray min(NpcArray a) { return new NpcArray(nativeMin(a.nativePtr, -1, false)); }
    public static NpcArray min(NpcArray a, int axis) { return new NpcArray(nativeMin(a.nativePtr, axis, false)); }
    public static NpcArray min(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeMin(a.nativePtr, axis, keepdims)); }
    public static NpcArray max(NpcArray a) { return new NpcArray(nativeMax(a.nativePtr, -1, false)); }
    public static NpcArray max(NpcArray a, int axis) { return new NpcArray(nativeMax(a.nativePtr, axis, false)); }
    public static NpcArray max(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeMax(a.nativePtr, axis, keepdims)); }
    public static NpcArray prod(NpcArray a) { return new NpcArray(nativeProd(a.nativePtr, -1, false)); }
    public static NpcArray prod(NpcArray a, int axis) { return new NpcArray(nativeProd(a.nativePtr, axis, false)); }
    public static NpcArray prod(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeProd(a.nativePtr, axis, keepdims)); }
    public static NpcArray stddev(NpcArray a) { return new NpcArray(nativeStddev(a.nativePtr, -1, false)); }
    public static NpcArray stddev(NpcArray a, int axis) { return new NpcArray(nativeStddev(a.nativePtr, axis, false)); }
    public static NpcArray stddev(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeStddev(a.nativePtr, axis, keepdims)); }
    public static NpcArray var(NpcArray a) { return new NpcArray(nativeVar(a.nativePtr, -1, 0, false)); }
    public static NpcArray var(NpcArray a, int axis) { return new NpcArray(nativeVar(a.nativePtr, axis, 0, false)); }
    public static NpcArray var(NpcArray a, int axis, int ddof) { return new NpcArray(nativeVar(a.nativePtr, axis, ddof, false)); }
    public static NpcArray var(NpcArray a, int axis, int ddof, boolean keepdims) { return new NpcArray(nativeVar(a.nativePtr, axis, ddof, keepdims)); }
    public static NpcArray median(NpcArray a) { return new NpcArray(nativeMedian(a.nativePtr, -1, false)); }
    public static NpcArray median(NpcArray a, int axis) { return new NpcArray(nativeMedian(a.nativePtr, axis, false)); }
    public static NpcArray median(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeMedian(a.nativePtr, axis, keepdims)); }
    public static NpcArray percentile(NpcArray a, NpcArray q, int axis) { return new NpcArray(nativePercentile(a.nativePtr, q.nativePtr, axis)); }
    public static NpcArray quantile(NpcArray a, NpcArray q, int axis) { return new NpcArray(nativeQuantile(a.nativePtr, q.nativePtr, axis)); }
    public static NpcArray cumsum(NpcArray a) { return new NpcArray(nativeCumsum(a.nativePtr, -1)); }
    public static NpcArray cumsum(NpcArray a, int axis) { return new NpcArray(nativeCumsum(a.nativePtr, axis)); }
    public static NpcArray cumprod(NpcArray a) { return new NpcArray(nativeCumprod(a.nativePtr, -1)); }
    public static NpcArray cumprod(NpcArray a, int axis) { return new NpcArray(nativeCumprod(a.nativePtr, axis)); }
    public static NpcArray argmax(NpcArray a) { return new NpcArray(nativeArgmax(a.nativePtr, -1, false)); }
    public static NpcArray argmax(NpcArray a, int axis) { return new NpcArray(nativeArgmax(a.nativePtr, axis, false)); }
    public static NpcArray argmax(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeArgmax(a.nativePtr, axis, keepdims)); }
    public static NpcArray argmin(NpcArray a) { return new NpcArray(nativeArgmin(a.nativePtr, -1, false)); }
    public static NpcArray argmin(NpcArray a, int axis) { return new NpcArray(nativeArgmin(a.nativePtr, axis, false)); }
    public static NpcArray argmin(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeArgmin(a.nativePtr, axis, keepdims)); }
    public static NpcArray countNonzero(NpcArray a) { return new NpcArray(nativeCountNonzero(a.nativePtr, -1)); }
    public static NpcArray countNonzero(NpcArray a, int axis) { return new NpcArray(nativeCountNonzero(a.nativePtr, axis)); }
    public static NpcArray ptp(NpcArray a) { return new NpcArray(nativePtp(a.nativePtr, -1, false)); }
    public static NpcArray ptp(NpcArray a, int axis) { return new NpcArray(nativePtp(a.nativePtr, axis, false)); }
    public static NpcArray ptp(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativePtp(a.nativePtr, axis, keepdims)); }
    public static NpcArray all(NpcArray a) { return new NpcArray(nativeAll(a.nativePtr, -1, false)); }
    public static NpcArray all(NpcArray a, int axis) { return new NpcArray(nativeAll(a.nativePtr, axis, false)); }
    public static NpcArray all(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeAll(a.nativePtr, axis, keepdims)); }
    public static NpcArray any(NpcArray a) { return new NpcArray(nativeAny(a.nativePtr, -1, false)); }
    public static NpcArray any(NpcArray a, int axis) { return new NpcArray(nativeAny(a.nativePtr, axis, false)); }
    public static NpcArray any(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeAny(a.nativePtr, axis, keepdims)); }
    /** Conditional selection: where condition is true, take x, else y. Like numpy.where. */
    public static NpcArray where(NpcArray condition, NpcArray x, NpcArray y) {
        return new NpcArray(nativeWhere(condition.nativePtr, x.nativePtr, y.nativePtr));
    }
    /** Weighted average. */
    public static NpcArray average(NpcArray a) { return new NpcArray(nativeAverage(a.nativePtr, -1, false)); }
    /** Weighted average with weights and optional axis/keepdims. */
    public static NpcArray average(NpcArray a, NpcArray weights) {
        return new NpcArray(nativeAverage_w(a.nativePtr, weights.nativePtr, -1, false));
    }
    public static NpcArray average(NpcArray a, NpcArray weights, int axis, boolean keepdims) {
        return new NpcArray(nativeAverage_w(a.nativePtr, weights.nativePtr, axis, keepdims));
    }
    /** Covariance matrix. */
    public static NpcArray cov(NpcArray m) { return new NpcArray(nativeCov(m.nativePtr, true, 0, DType.FLOAT64.ordinal())); }
    public static NpcArray cov(NpcArray m, boolean rowvar) { return new NpcArray(nativeCov(m.nativePtr, rowvar, 0, DType.FLOAT64.ordinal())); }
    public static NpcArray cov(NpcArray m, boolean rowvar, int ddof) { return new NpcArray(nativeCov(m.nativePtr, rowvar, ddof, DType.FLOAT64.ordinal())); }
    public static NpcArray cov(NpcArray m, boolean rowvar, int ddof, DType dtype) { return new NpcArray(nativeCov(m.nativePtr, rowvar, ddof, dtype.ordinal())); }
    /** Pearson correlation coefficient matrix. */
    public static NpcArray corrcoef(NpcArray m) { return new NpcArray(nativeCorrcoef(m.nativePtr, true)); }
    public static NpcArray corrcoef(NpcArray m, boolean rowvar) { return new NpcArray(nativeCorrcoef(m.nativePtr, rowvar)); }
    /** Cross-correlation. */
    public static NpcArray correlate(NpcArray a, NpcArray v) { return new NpcArray(nativeCorrelate(a.nativePtr, v.nativePtr, "valid")); }
    public static NpcArray correlate(NpcArray a, NpcArray v, String mode) { return new NpcArray(nativeCorrelate(a.nativePtr, v.nativePtr, mode)); }
    /** Trapezoidal integration. */
    public static NpcArray trapz(NpcArray y) { return new NpcArray(nativeTrapz_dx(y.nativePtr, 1.0, -1)); }
    public static NpcArray trapz(NpcArray y, double dx) { return new NpcArray(nativeTrapz_dx(y.nativePtr, dx, -1)); }
    public static NpcArray trapz(NpcArray y, double dx, int axis) { return new NpcArray(nativeTrapz_dx(y.nativePtr, dx, axis)); }
    public static NpcArray trapz(NpcArray y, NpcArray x, double dx, int axis) { return new NpcArray(nativeTrapz_x(y.nativePtr, x.nativePtr, dx, axis)); }

    // ═══════════════════════════════════════════════════════════
    // NaN-aware Statistics
    // ═══════════════════════════════════════════════════════════

    public static NpcArray nanmax(NpcArray a) { return new NpcArray(nativeNanmax(a.nativePtr, -1)); }
    public static NpcArray nanmax(NpcArray a, int axis) { return new NpcArray(nativeNanmax(a.nativePtr, axis)); }
    public static NpcArray nanmin(NpcArray a) { return new NpcArray(nativeNanmin(a.nativePtr, -1)); }
    public static NpcArray nanmin(NpcArray a, int axis) { return new NpcArray(nativeNanmin(a.nativePtr, axis)); }
    public static NpcArray nanmean(NpcArray a) { return new NpcArray(nativeNanmean(a.nativePtr, -1)); }
    public static NpcArray nanmean(NpcArray a, int axis) { return new NpcArray(nativeNanmean(a.nativePtr, axis)); }
    public static NpcArray nanmedian(NpcArray a) { return new NpcArray(nativeNanmedian(a.nativePtr, -1)); }
    public static NpcArray nanmedian(NpcArray a, int axis) { return new NpcArray(nativeNanmedian(a.nativePtr, axis)); }
    public static NpcArray nansum(NpcArray a) { return new NpcArray(nativeNansum(a.nativePtr, -1)); }
    public static NpcArray nansum(NpcArray a, int axis) { return new NpcArray(nativeNansum(a.nativePtr, axis)); }
    public static NpcArray nanprod(NpcArray a) { return new NpcArray(nativeNanprod(a.nativePtr, -1)); }
    public static NpcArray nanprod(NpcArray a, int axis) { return new NpcArray(nativeNanprod(a.nativePtr, axis)); }
    public static NpcArray nanstd(NpcArray a, int axis, boolean keepdims) { return new NpcArray(nativeNanstd(a.nativePtr, axis, keepdims)); }
    public static NpcArray nanvar(NpcArray a, int axis, int ddof, boolean keepdims) { return new NpcArray(nativeNanvar(a.nativePtr, axis, ddof, keepdims)); }
    public static NpcArray nanpercentile(NpcArray a, NpcArray q, int axis) { return new NpcArray(nativeNanpercentile(a.nativePtr, q.nativePtr, axis)); }
    public static NpcArray nanquantile(NpcArray a, NpcArray q, int axis) { return new NpcArray(nativeNanquantile(a.nativePtr, q.nativePtr, axis)); }
    public static NpcArray nancumsum(NpcArray a, int axis) { return new NpcArray(nativeNancumsum(a.nativePtr, axis)); }
    public static NpcArray nancumprod(NpcArray a, int axis) { return new NpcArray(nativeNancumprod(a.nativePtr, axis)); }
    public static NpcArray nanargmax(NpcArray a, int axis) { return new NpcArray(nativeNanargmax(a.nativePtr, axis)); }
    public static NpcArray nanargmin(NpcArray a, int axis) { return new NpcArray(nativeNanargmin(a.nativePtr, axis)); }
    /** Test each element for NaN. */
    public static NpcArray isnan(NpcArray a) { return new NpcArray(nativeIsnan(a.nativePtr)); }
    /** Test each element for infinity. */
    public static NpcArray isinf(NpcArray a) { return new NpcArray(nativeIsinf(a.nativePtr)); }
    /** Test each element for finiteness. */
    public static NpcArray isfinite(NpcArray a) { return new NpcArray(nativeIsfinite(a.nativePtr)); }
    /** Replace NaN and infinity with finite values. */
    public static NpcArray nanToNum(NpcArray a) { return new NpcArray(nativeNanToNum(a.nativePtr)); }

    // ═══════════════════════════════════════════════════════════
    // Linear Algebra
    // ═══════════════════════════════════════════════════════════

    public static NpcArray dot(NpcArray a, NpcArray b) { return new NpcArray(nativeDot(a.nativePtr, b.nativePtr)); }
    public static NpcArray matmul(NpcArray a, NpcArray b) { return new NpcArray(nativeMatmul(a.nativePtr, b.nativePtr)); }
    /** Conjugate inner product. Flatten then dot. */
    public static NpcArray vdot(NpcArray a, NpcArray b) { return new NpcArray(nativeVdot(a.nativePtr, b.nativePtr)); }
    /** Inner product. */
    public static NpcArray inner(NpcArray a, NpcArray b) { return new NpcArray(nativeInner(a.nativePtr, b.nativePtr)); }
    /** Outer product. */
    public static NpcArray outer(NpcArray a, NpcArray b) { return new NpcArray(nativeOuter(a.nativePtr, b.nativePtr)); }
    /** Cross product. */
    public static NpcArray cross(NpcArray a, NpcArray b) { return new NpcArray(nativeCross(a.nativePtr, b.nativePtr)); }
    /** Kronecker product. */
    public static NpcArray kron(NpcArray a, NpcArray b) { return new NpcArray(nativeKron(a.nativePtr, b.nativePtr)); }
    /** Tensor dot product with axes specified as arrays. */
    public static NpcArray tensordot(NpcArray a, NpcArray b, NpcArray axesA, NpcArray axesB) {
        return new NpcArray(nativeTensordot_axes(a.nativePtr, b.nativePtr, axesA.nativePtr, axesB.nativePtr));
    }
    /** Tensor dot product with integer axes. */
    public static NpcArray tensordot(NpcArray a, NpcArray b, int axes) {
        return new NpcArray(nativeTensordot_int(a.nativePtr, b.nativePtr, axes));
    }
    /** Matrix inverse (2-D square). */
    public static NpcArray inv(NpcArray a) { return new NpcArray(nativeInv(a.nativePtr)); }
    /** Moore-Penrose pseudo-inverse. */
    public static NpcArray pinv(NpcArray a) { return new NpcArray(nativePinv(a.nativePtr, 1e-15)); }
    public static NpcArray pinv(NpcArray a, double rcond) { return new NpcArray(nativePinv(a.nativePtr, rcond)); }
    /** Determinant. */
    public static NpcArray det(NpcArray a) { return new NpcArray(nativeDet(a.nativePtr)); }
    /** Trace (sum of diagonal). */
    public static NpcArray trace(NpcArray a) { return new NpcArray(nativeTrace(a.nativePtr)); }
    /** Cholesky decomposition. */
    public static NpcArray cholesky(NpcArray a) { return new NpcArray(nativeCholesky(a.nativePtr)); }
    /** Singular Value Decomposition. */
    public static native SvdResult nativeSvd(long aHandle, boolean fullMatrices);
    /** SVD with full matrices. */
    public static SvdResult svd(NpcArray a) { return nativeSvd(a.nativePtr, true); }
    /** SVD with full_matrices option. */
    public static SvdResult svd(NpcArray a, boolean fullMatrices) { return nativeSvd(a.nativePtr, fullMatrices); }
    /** QR decomposition. */
    public static native QrResult nativeQr(long aHandle);
    public static QrResult qr(NpcArray a) { return nativeQr(a.nativePtr); }
    /** LU decomposition. */
    public static native LuResult nativeLu(long aHandle);
    public static LuResult lu(NpcArray a) { return nativeLu(a.nativePtr); }
    /** Eigenvalue decomposition. */
    public static native EigResult nativeEig(long aHandle);
    public static EigResult eig(NpcArray a) { return nativeEig(a.nativePtr); }

    // ═══════════════════════════════════════════════════════════
    // FFT
    // ═══════════════════════════════════════════════════════════

    public static NpcArray fft(NpcArray a) { return new NpcArray(nativeFft(a.nativePtr)); }
    public static NpcArray ifft(NpcArray a) { return new NpcArray(nativeIfft(a.nativePtr)); }
    public static NpcArray rfft(NpcArray a) { return new NpcArray(nativeRfft(a.nativePtr)); }
    public static NpcArray rfft2(NpcArray a) { return new NpcArray(nativeRfft2(a.nativePtr)); }
    public static NpcArray rfftn(NpcArray a) { return new NpcArray(nativeRfftn(a.nativePtr)); }
    public static NpcArray hfft(NpcArray a, int n) { return new NpcArray(nativeHfft(a.nativePtr, n)); }
    public static NpcArray ihfft(NpcArray a, int n) { return new NpcArray(nativeIhfft(a.nativePtr, n)); }
    public static NpcArray irfft(NpcArray a) { return new NpcArray(nativeIrfft(a.nativePtr, -1)); }
    public static NpcArray irfft(NpcArray a, int n) { return new NpcArray(nativeIrfft(a.nativePtr, n)); }
    public static NpcArray irfft2(NpcArray a, int[] s) { return new NpcArray(nativeIrfft2(a.nativePtr, s)); }
    public static NpcArray irfftn(NpcArray a, int[] s) { return new NpcArray(nativeIrfftn(a.nativePtr, s)); }
    public static NpcArray fft2(NpcArray a) { return new NpcArray(nativeFft2(a.nativePtr)); }
    public static NpcArray ifft2(NpcArray a) { return new NpcArray(nativeIfft2(a.nativePtr)); }
    public static NpcArray fftn(NpcArray a) { return new NpcArray(nativeFftn(a.nativePtr)); }
    public static NpcArray ifftn(NpcArray a) { return new NpcArray(nativeIfftn(a.nativePtr)); }
    public static NpcArray fftshift(NpcArray a) { return new NpcArray(nativeFftshift(a.nativePtr)); }
    public static NpcArray ifftshift(NpcArray a) { return new NpcArray(nativeIfftshift(a.nativePtr)); }
    public static NpcArray fftfreq(int n) { return new NpcArray(nativeFftfreq(n, 1.0)); }
    public static NpcArray fftfreq(int n, double d) { return new NpcArray(nativeFftfreq(n, d)); }
    public static NpcArray rfftfreq(int n) { return new NpcArray(nativeRfftfreq(n, 1.0)); }
    public static NpcArray rfftfreq(int n, double d) { return new NpcArray(nativeRfftfreq(n, d)); }

    // ═══════════════════════════════════════════════════════════
    // Random Number Generation
    // ═══════════════════════════════════════════════════════════

    public static native void nativeRandomSeed(long seed);
    public static native long nativeRandomUint64();
    public static native double nativeRandomDouble();

    /** Seed the random number generator. */
    public static void randomSeed(long seed) { nativeRandomSeed(seed); }
    /** Get a random 64-bit unsigned integer. */
    public static long randomUint64() { return nativeRandomUint64(); }
    /** Get a random double in [0, 1). */
    public static double randomDouble() { return nativeRandomDouble(); }

    /** Uniform random samples in [0, 1). */
    public static NpcArray randomSample(int... shape) { return new NpcArray(nativeRandomSample(shape)); }
    /** Uniform random in [0, 1) (alias). */
    public static NpcArray rand(int... shape) { return new NpcArray(nativeRand(shape)); }
    /** Random integers in [low, high). */
    public static NpcArray randint(int low, int high, int... shape) { return new NpcArray(nativeRandint(low, high, shape, DType.INT64.ordinal())); }
    public static NpcArray randint(int low, int high, DType dtype, int... shape) { return new NpcArray(nativeRandint(low, high, shape, dtype.ordinal())); }
    /** Uniform distribution in [low, high). */
    public static NpcArray uniform(double low, double high, int... shape) { return new NpcArray(nativeUniform(low, high, shape)); }
    /** Standard normal (μ=0, σ=1). */
    public static NpcArray standardNormal(int... shape) { return new NpcArray(nativeStandardNormal(shape)); }
    /** Standard normal (alias). */
    public static NpcArray randn(int... shape) { return new NpcArray(nativeRandn(shape)); }
    /** Normal distribution N(loc, scale). */
    public static NpcArray normal(double loc, double scale, int... shape) { return new NpcArray(nativeNormal(loc, scale, shape)); }
    /** Standard exponential (scale=1). */
    public static NpcArray standardExponential(int... shape) { return new NpcArray(nativeStandardExponential(shape)); }
    /** Exponential distribution. */
    public static NpcArray exponential(double scale, int... shape) { return new NpcArray(nativeExponential(scale, shape)); }
    /** Standard gamma distribution. */
    public static NpcArray standardGamma(double shape, int... outShape) { return new NpcArray(nativeStandardGamma(shape, outShape)); }
    /** Gamma distribution. */
    public static NpcArray gamma(double shape, double scale, int... outShape) { return new NpcArray(nativeGamma(shape, scale, outShape)); }
    /** Chi-square distribution. */
    public static NpcArray chisquare(double df, int... shape) { return new NpcArray(nativeChisquare(df, shape)); }
    /** Beta distribution. */
    public static NpcArray beta(double a, double b, int... shape) { return new NpcArray(nativeBeta(a, b, shape)); }
    /** Student's t distribution. */
    public static NpcArray standardT(double df, int... shape) { return new NpcArray(nativeStandardT(df, shape)); }
    /** F distribution. */
    public static NpcArray f(double dfn, double dfd, int... shape) { return new NpcArray(nativeF(dfn, dfd, shape)); }
    /** Laplace distribution. */
    public static NpcArray laplace(double loc, double scale, int... shape) { return new NpcArray(nativeLaplace(loc, scale, shape)); }
    /** Logistic distribution. */
    public static NpcArray logistic(double loc, double scale, int... shape) { return new NpcArray(nativeLogistic(loc, scale, shape)); }
    /** Log-normal distribution. */
    public static NpcArray lognormal(double mean, double sigma, int... shape) { return new NpcArray(nativeLognormal(mean, sigma, shape)); }
    /** Pareto distribution. */
    public static NpcArray pareto(double a, int... shape) { return new NpcArray(nativePareto(a, shape)); }
    /** Power distribution. */
    public static NpcArray powerDist(double a, int... shape) { return new NpcArray(nativePowerDist(a, shape)); }
    /** Rayleigh distribution. */
    public static NpcArray rayleigh(double scale, int... shape) { return new NpcArray(nativeRayleigh(scale, shape)); }
    /** Weibull distribution. */
    public static NpcArray weibull(double a, int... shape) { return new NpcArray(nativeWeibull(a, shape)); }
    /** Standard Cauchy distribution. */
    public static NpcArray standardCauchy(int... shape) { return new NpcArray(nativeStandardCauchy(shape)); }
    /** Gumbel distribution. */
    public static NpcArray gumbel(double loc, double scale, int... shape) { return new NpcArray(nativeGumbel(loc, scale, shape)); }
    /** Triangular distribution. */
    public static NpcArray triangular(double left, double mode, double right, int... shape) { return new NpcArray(nativeTriangular(left, mode, right, shape)); }
    /** Von Mises distribution. */
    public static NpcArray vonmises(double mu, double kappa, int... shape) { return new NpcArray(nativeVonmises(mu, kappa, shape)); }
    /** Wald (inverse Gaussian) distribution. */
    public static NpcArray wald(double mean, double scale, int... shape) { return new NpcArray(nativeWald(mean, scale, shape)); }

    /** Geometric distribution. */
    public static NpcArray geometric(double p, int... shape) { return new NpcArray(nativeGeometric(p, shape)); }
    /** Poisson distribution. */
    public static NpcArray poisson(double lam, int... shape) { return new NpcArray(nativePoisson(lam, shape)); }
    /** Binomial distribution. */
    public static NpcArray binomial(int n, double p, int... shape) { return new NpcArray(nativeBinomial(n, p, shape)); }
    /** Negative binomial distribution. */
    public static NpcArray negativeBinomial(int n, double p, int... shape) { return new NpcArray(nativeNegativeBinomial(n, p, shape)); }
    /** Hypergeometric distribution. */
    public static NpcArray hypergeometric(int ngood, int nbad, int nsample, int... shape) { return new NpcArray(nativeHypergeometric(ngood, nbad, nsample, shape)); }
    /** Zipf distribution. */
    public static NpcArray zipf(double a, int... shape) { return new NpcArray(nativeZipf(a, shape)); }
    /** Logarithmic series distribution. */
    public static NpcArray logseries(double p, int... shape) { return new NpcArray(nativeLogseries(p, shape)); }

    /** Random permutation of an array. */
    public static NpcArray permutation(NpcArray x) { return new NpcArray(nativePermutation(x.nativePtr)); }
    /** In-place shuffle. */
    public static void shuffle(NpcArray x) { nativeShuffle(x); }
    /** Random choice from array. */
    public static NpcArray choice(NpcArray a, int size) { return new NpcArray(nativeChoice(a.nativePtr, size, true, 0)); }
    public static NpcArray choice(NpcArray a, int size, boolean replace) { return new NpcArray(nativeChoice(a.nativePtr, size, replace, 0)); }
    public static NpcArray choice(NpcArray a, int size, boolean replace, NpcArray p) { return new NpcArray(nativeChoice(a.nativePtr, size, replace, p != null ? p.nativePtr : 0)); }
    /** Multinomial distribution. */
    public static NpcArray multinomial(int n, NpcArray pvals, int... shape) { return new NpcArray(nativeMultinomial(n, pvals.nativePtr, shape)); }
    /** Multivariate normal distribution. */
    public static NpcArray multivariateNormal(NpcArray mean, NpcArray cov, int... shape) { return new NpcArray(nativeMultivariateNormal(mean.nativePtr, cov.nativePtr, shape)); }
    /** Dirichlet distribution. */
    public static NpcArray dirichlet(NpcArray alpha, int... shape) { return new NpcArray(nativeDirichlet(alpha.nativePtr, shape)); }
    /** Random bytes. */
    public static NpcArray randomBytes(int n) { return new NpcArray(nativeRandomBytes(n)); }

    // ═══════════════════════════════════════════════════════════
    // Polynomial
    // ═══════════════════════════════════════════════════════════

    /** Polynomial from roots. */
    public static NpcArray poly(NpcArray roots) { return new NpcArray(nativePoly(roots.nativePtr)); }
    /** Roots of polynomial. */
    public static NpcArray roots(NpcArray p) { return new NpcArray(nativeRoots(p.nativePtr)); }
    public static NpcArray polyadd(NpcArray a, NpcArray b) { return new NpcArray(nativePolyadd(a.nativePtr, b.nativePtr)); }
    public static NpcArray polysub(NpcArray a, NpcArray b) { return new NpcArray(nativePolysub(a.nativePtr, b.nativePtr)); }
    public static NpcArray polymul(NpcArray a, NpcArray b) { return new NpcArray(nativePolymul(a.nativePtr, b.nativePtr)); }
    /** Polynomial division. Returns [quotient, remainder]. */
    public static native NpcArray[] nativePolydiv(long uHandle, long vHandle);
    public static NpcArray[] polydiv(NpcArray u, NpcArray v) { return nativePolydiv(u.nativePtr, v.nativePtr); }
    public static NpcArray polyder(NpcArray p) { return new NpcArray(nativePolyder(p.nativePtr, 1)); }
    public static NpcArray polyder(NpcArray p, int m) { return new NpcArray(nativePolyder(p.nativePtr, m)); }
    public static NpcArray polyint(NpcArray p) { return new NpcArray(nativePolyint(p.nativePtr, 1)); }
    public static NpcArray polyint(NpcArray p, int m) { return new NpcArray(nativePolyint(p.nativePtr, m)); }
    public static NpcArray polyval(NpcArray p, NpcArray x) { return new NpcArray(nativePolyval(p.nativePtr, x.nativePtr)); }
    /** Least-squares polynomial fit. */
    public static NpcArray polyfit(NpcArray x, NpcArray y, int deg) { return new NpcArray(nativePolyfit(x.nativePtr, y.nativePtr, deg)); }

    // ═══════════════════════════════════════════════════════════
    // Shape Manipulation
    // ═══════════════════════════════════════════════════════════

    public static NpcArray reshape(NpcArray a, int... shape) { return new NpcArray(nativeReshape(a.nativePtr, shape)); }
    public static NpcArray resize(NpcArray a, int... shape) { return new NpcArray(nativeResize(a.nativePtr, shape)); }
    public static NpcArray transpose(NpcArray a) { return new NpcArray(nativeTranspose(a.nativePtr)); }
    public static NpcArray flatten(NpcArray a) { return new NpcArray(nativeFlatten(a.nativePtr)); }
    public static NpcArray ravel(NpcArray a) { return new NpcArray(nativeRavel(a.nativePtr, "C")); }
    public static NpcArray ravel(NpcArray a, String order) { return new NpcArray(nativeRavel(a.nativePtr, order)); }
    public static NpcArray squeeze(NpcArray a) { return new NpcArray(nativeSqueeze(a.nativePtr, -1)); }
    public static NpcArray squeeze(NpcArray a, int axis) { return new NpcArray(nativeSqueeze(a.nativePtr, axis)); }
    public static NpcArray expandDims(NpcArray a, int axis) { return new NpcArray(nativeExpandDims(a.nativePtr, axis)); }
    public static NpcArray concatenate(NpcArray a, NpcArray b) { return new NpcArray(nativeConcatenate(a.nativePtr, b.nativePtr, 0)); }
    public static NpcArray concatenate(NpcArray a, NpcArray b, int axis) { return new NpcArray(nativeConcatenate(a.nativePtr, b.nativePtr, axis)); }
    public static NpcArray append(NpcArray a, NpcArray values, int axis) { return new NpcArray(nativeAppend(a.nativePtr, values.nativePtr, axis)); }
    /** Stack arrays along a new axis. */
    public static native NpcArray nativeStack(NpcArray[] arrays, int axis);
    public static NpcArray stack(NpcArray[] arrays) { return nativeStack(arrays, 0); }
    public static NpcArray stack(NpcArray[] arrays, int axis) { return nativeStack(arrays, axis); }
    public static native NpcArray nativeHstack(NpcArray[] arrays);
    public static NpcArray hstack(NpcArray[] arrays) { return nativeHstack(arrays); }
    public static native NpcArray nativeVstack(NpcArray[] arrays);
    public static NpcArray vstack(NpcArray[] arrays) { return nativeVstack(arrays); }
    public static native NpcArray nativeDstack(NpcArray[] arrays);
    public static NpcArray dstack(NpcArray[] arrays) { return nativeDstack(arrays); }
    public static native NpcArray nativeColumnStack(NpcArray[] arrays);
    public static NpcArray columnStack(NpcArray[] arrays) { return nativeColumnStack(arrays); }
    /** Split array. */
    public static native NpcArray[] nativeSplit(long aHandle, long indicesHandle, int axis);
    public static NpcArray[] split(NpcArray ary, NpcArray indicesOrSections) { return nativeSplit(ary.nativePtr, indicesOrSections.nativePtr, 0); }
    public static NpcArray[] split(NpcArray ary, NpcArray indicesOrSections, int axis) { return nativeSplit(ary.nativePtr, indicesOrSections.nativePtr, axis); }
    public static native NpcArray[] nativeHsplit(long aHandle, long indicesHandle);
    public static NpcArray[] hsplit(NpcArray ary, NpcArray indicesOrSections) { return nativeHsplit(ary.nativePtr, indicesOrSections.nativePtr); }
    public static native NpcArray[] nativeVsplit(long aHandle, long indicesHandle);
    public static NpcArray[] vsplit(NpcArray ary, NpcArray indicesOrSections) { return nativeVsplit(ary.nativePtr, indicesOrSections.nativePtr); }
    public static native NpcArray[] nativeDsplit(long aHandle, long indicesHandle);
    public static NpcArray[] dsplit(NpcArray ary, NpcArray indicesOrSections) { return nativeDsplit(ary.nativePtr, indicesOrSections.nativePtr); }

    public static NpcArray flip(NpcArray a) { return new NpcArray(nativeFlip(a.nativePtr, -1)); }
    public static NpcArray flip(NpcArray a, int axis) { return new NpcArray(nativeFlip(a.nativePtr, axis)); }
    public static NpcArray fliplr(NpcArray a) { return new NpcArray(nativeFliplr(a.nativePtr)); }
    public static NpcArray flipud(NpcArray a) { return new NpcArray(nativeFlipud(a.nativePtr)); }
    public static NpcArray rot90(NpcArray m) { return new NpcArray(nativeRot90(m.nativePtr, 1, 0, 1)); }
    public static NpcArray rot90(NpcArray m, int k, int axis1, int axis2) { return new NpcArray(nativeRot90(m.nativePtr, k, axis1, axis2)); }
    public static NpcArray roll(NpcArray a, int shift) { return new NpcArray(nativeRoll(a.nativePtr, shift, -1)); }
    public static NpcArray roll(NpcArray a, int shift, int axis) { return new NpcArray(nativeRoll(a.nativePtr, shift, axis)); }
    public static NpcArray broadcastTo(NpcArray a, int... shape) { return new NpcArray(nativeBroadcastTo(a.nativePtr, shape)); }
    public static NpcArray tile(NpcArray a, int... reps) { return new NpcArray(nativeTile(a.nativePtr, reps)); }
    public static NpcArray repeat(NpcArray a, NpcArray repeats, int axis) { return new NpcArray(nativeRepeat(a.nativePtr, repeats.nativePtr, axis)); }
    public static NpcArray moveaxis(NpcArray a, int source, int destination) { return new NpcArray(nativeMoveaxis(a.nativePtr, source, destination)); }
    public static NpcArray rollaxis(NpcArray a, int axis, int start) { return new NpcArray(nativeRollaxis(a.nativePtr, axis, start)); }
    public static NpcArray swapaxes(NpcArray a, int axis1, int axis2) { return new NpcArray(nativeSwapaxes(a.nativePtr, axis1, axis2)); }
    public static NpcArray atleast1d(NpcArray a) { return new NpcArray(nativeAtleast1d(a.nativePtr)); }
    public static NpcArray atleast2d(NpcArray a) { return new NpcArray(nativeAtleast2d(a.nativePtr)); }
    public static NpcArray atleast3d(NpcArray a) { return new NpcArray(nativeAtleast3d(a.nativePtr)); }
    /** Pad array. */
    public static NpcArray pad(NpcArray a, NpcArray padWidth) { return new NpcArray(nativePad(a.nativePtr, padWidth.nativePtr, "constant", 0.0)); }
    public static NpcArray pad(NpcArray a, NpcArray padWidth, String mode, double constantValue) { return new NpcArray(nativePad(a.nativePtr, padWidth.nativePtr, mode, constantValue)); }
    /** Meshgrid. */
    public static native NpcArray[] nativeMeshgrid(NpcArray[] arrays, String indexing);
    public static NpcArray[] meshgrid(NpcArray[] arrays) { return nativeMeshgrid(arrays, "xy"); }
    public static NpcArray[] meshgrid(NpcArray[] arrays, String indexing) { return nativeMeshgrid(arrays, indexing); }

    // ═══════════════════════════════════════════════════════════
    // Diagonal operations
    // ═══════════════════════════════════════════════════════════

    public static NpcArray diag(NpcArray v) { return new NpcArray(nativeDiag(v.nativePtr, 0)); }
    public static NpcArray diag(NpcArray v, int k) { return new NpcArray(nativeDiag(v.nativePtr, k)); }
    public static NpcArray diagflat(NpcArray a) { return new NpcArray(nativeDiagflat(a.nativePtr, 0)); }
    public static NpcArray diagflat(NpcArray a, int k) { return new NpcArray(nativeDiagflat(a.nativePtr, k)); }
    public static NpcArray diagonal(NpcArray a, int offset, int axis1, int axis2) { return new NpcArray(nativeDiagonal(a.nativePtr, offset, axis1, axis2)); }
    /** Lower triangle. */
    public static NpcArray tril(NpcArray m) { return new NpcArray(nativeTril(m.nativePtr, 0)); }
    public static NpcArray tril(NpcArray m, int k) { return new NpcArray(nativeTril(m.nativePtr, k)); }
    /** Upper triangle. */
    public static NpcArray triu(NpcArray m) { return new NpcArray(nativeTriu(m.nativePtr, 0)); }
    public static NpcArray triu(NpcArray m, int k) { return new NpcArray(nativeTriu(m.nativePtr, k)); }

    // ═══════════════════════════════════════════════════════════
    // Sorting
    // ═══════════════════════════════════════════════════════════

    public static NpcArray sort(NpcArray a) { return new NpcArray(nativeSort(a.nativePtr)); }
    public static NpcArray argsort(NpcArray arr) { return new NpcArray(nativeArgsort(arr.nativePtr, -1, "quicksort")); }
    public static NpcArray argsort(NpcArray arr, int axis) { return new NpcArray(nativeArgsort(arr.nativePtr, axis, "quicksort")); }
    public static NpcArray argsort(NpcArray arr, int axis, String kind) { return new NpcArray(nativeArgsort(arr.nativePtr, axis, kind)); }
    public static NpcArray argpartition(NpcArray arr, int kth) { return new NpcArray(nativeArgpartition(arr.nativePtr, kth, -1)); }
    public static NpcArray argpartition(NpcArray arr, int kth, int axis) { return new NpcArray(nativeArgpartition(arr.nativePtr, kth, axis)); }
    public static NpcArray partition(NpcArray arr, int kth, int axis) { return new NpcArray(nativePartition(arr.nativePtr, kth, axis)); }
    /** Sort along first axis. Alias for sort. */
    public static NpcArray msort(NpcArray a) { return new NpcArray(nativeMsort(a.nativePtr)); }
    /** Phase unwrapping. */
    public static NpcArray unwrap(NpcArray arr) { return new NpcArray(nativeUnwrap(arr.nativePtr, Math.PI, -1)); }
    public static NpcArray unwrap(NpcArray arr, double discont, int axis) { return new NpcArray(nativeUnwrap(arr.nativePtr, discont, axis)); }

    // ═══════════════════════════════════════════════════════════
    // Set Operations
    // ═══════════════════════════════════════════════════════════

    public static native UniqueResult nativeUnique(long aHandle, boolean returnIndex, boolean returnInverse, boolean returnCounts);
    public static UniqueResult unique(NpcArray arr) { return nativeUnique(arr.nativePtr, false, false, false); }
    public static UniqueResult unique(NpcArray arr, boolean returnIndex, boolean returnInverse, boolean returnCounts) { return nativeUnique(arr.nativePtr, returnIndex, returnInverse, returnCounts); }
    public static NpcArray intersect1d(NpcArray a, NpcArray b) { return new NpcArray(nativeIntersect1d(a.nativePtr, b.nativePtr, false)); }
    public static NpcArray intersect1d(NpcArray a, NpcArray b, boolean assumeUnique) { return new NpcArray(nativeIntersect1d(a.nativePtr, b.nativePtr, assumeUnique)); }
    public static NpcArray setdiff1d(NpcArray a, NpcArray b) { return new NpcArray(nativeSetdiff1d(a.nativePtr, b.nativePtr)); }
    public static NpcArray searchsorted(NpcArray a, NpcArray v) { return new NpcArray(nativeSearchsorted(a.nativePtr, v.nativePtr, "left")); }
    public static NpcArray searchsorted(NpcArray a, NpcArray v, String side) { return new NpcArray(nativeSearchsorted(a.nativePtr, v.nativePtr, side)); }
    public static NpcArray digitize(NpcArray arr, NpcArray bins, boolean right) { return new NpcArray(nativeDigitize(arr.nativePtr, bins.nativePtr, right)); }
    public static NpcArray argwhere(NpcArray arr) { return new NpcArray(nativeArgwhere(arr.nativePtr)); }

    // ═══════════════════════════════════════════════════════════
    // Interpolation / Difference
    // ═══════════════════════════════════════════════════════════

    /** 1-D linear interpolation. */
    public static NpcArray interp(NpcArray arr, NpcArray xp, NpcArray fp) {
        return new NpcArray(nativeInterp(arr.nativePtr, xp.nativePtr, fp.nativePtr, 0, 0));
    }
    public static NpcArray interp(NpcArray arr, NpcArray xp, NpcArray fp, NpcArray left, NpcArray right) {
        return new NpcArray(nativeInterp(arr.nativePtr, xp.nativePtr, fp.nativePtr,
                left != null ? left.nativePtr : 0, right != null ? right.nativePtr : 0));
    }
    /** n-th difference along axis. */
    public static NpcArray diff(NpcArray arr) { return new NpcArray(nativeDiff(arr.nativePtr, 1, -1)); }
    public static NpcArray diff(NpcArray arr, int n, int axis) { return new NpcArray(nativeDiff(arr.nativePtr, n, axis)); }
    /** Differences between adjacent elements. */
    public static NpcArray ediff1d(NpcArray y) { return new NpcArray(nativeEdiff1d(y.nativePtr, 0, 0)); }
    public static NpcArray ediff1d(NpcArray y, NpcArray toBegin, NpcArray toEnd) {
        return new NpcArray(nativeEdiff1d(y.nativePtr,
                toBegin != null ? toBegin.nativePtr : 0, toEnd != null ? toEnd.nativePtr : 0));
    }
    /** N-D gradient. */
    public static native NpcArray[] nativeGradient(long aHandle, long spacingHandle);
    public static NpcArray[] gradient(NpcArray arr) { return nativeGradient(arr.nativePtr, 0); }
    public static NpcArray[] gradient(NpcArray arr, NpcArray spacing) { return nativeGradient(arr.nativePtr, spacing != null ? spacing.nativePtr : 0); }

    // ═══════════════════════════════════════════════════════════
    // Window Functions
    // ═══════════════════════════════════════════════════════════

    public static NpcArray bartlett(int M) { return new NpcArray(nativeBartlett(M)); }
    public static NpcArray blackman(int M) { return new NpcArray(nativeBlackman(M)); }
    public static NpcArray kaiser(int M, double beta) { return new NpcArray(nativeKaiser(M, beta)); }
    public static NpcArray hanning(int M) { return new NpcArray(nativeHanning(M)); }
    public static NpcArray hamming(int M) { return new NpcArray(nativeHamming(M)); }

    // ═══════════════════════════════════════════════════════════
    // Histogram
    // ═══════════════════════════════════════════════════════════

    public static native HistogramResult nativeHistogram(long xHandle, int bins, boolean density);
    public static HistogramResult histogram(NpcArray x, int bins) { return nativeHistogram(x.nativePtr, bins, false); }
    public static HistogramResult histogram(NpcArray x, int bins, boolean density) { return nativeHistogram(x.nativePtr, bins, density); }
    public static native Histogram2DResult nativeHistogram2d(long xHandle, long yHandle, int binsX, int binsY, long rangeXHandle, long rangeYHandle, boolean density);
    public static Histogram2DResult histogram2d(NpcArray x, NpcArray y, int binsX, int binsY) {
        return nativeHistogram2d(x.nativePtr, y.nativePtr, binsX, binsY, 0, 0, false);
    }
    public static Histogram2DResult histogram2d(NpcArray x, NpcArray y, int binsX, int binsY,
                                                  NpcArray rangeX, NpcArray rangeY, boolean density) {
        return nativeHistogram2d(x.nativePtr, y.nativePtr, binsX, binsY,
                rangeX != null ? rangeX.nativePtr : 0, rangeY != null ? rangeY.nativePtr : 0, density);
    }
    public static native HistogramDDResult nativeHistogramdd(long sampleHandle, long binsHandle, long rangeHandle, boolean density);
    public static HistogramDDResult histogramdd(NpcArray sample, NpcArray bins) {
        return nativeHistogramdd(sample.nativePtr, bins.nativePtr, 0, false);
    }
    public static HistogramDDResult histogramdd(NpcArray sample, NpcArray bins, NpcArray range, boolean density) {
        return nativeHistogramdd(sample.nativePtr, bins.nativePtr, range != null ? range.nativePtr : 0, density);
    }

    // ═══════════════════════════════════════════════════════════
    // I/O
    // ═══════════════════════════════════════════════════════════

    /** Read a text file into an array. */
    public static NpcArray readtxt(String filename) {
        return new NpcArray(nativeReadtxt(filename, " ", '#', 0, -1, 0, false, DType.FLOAT64.ordinal()));
    }
    /** readtxt with full options. */
    public static NpcArray readtxt(String filename, String delimiter, char comment, int skiplines,
                                    int maxRows, int ndmin, boolean unpack, DType dtype) {
        return new NpcArray(nativeReadtxt(filename, delimiter, comment, skiplines, maxRows, ndmin, unpack, dtype.ordinal()));
    }
    /** Create a fluent builder for readtxt. */
    public static ReadtxtBuilder readtxtBuilder(String filename) {
        return new ReadtxtBuilder(filename);
    }
    /** Read a CSV-like file. */
    public static NpcArray genfromtxt(String filename) {
        return new NpcArray(nativeGenfromtxt(filename, ",", 0));
    }
    public static NpcArray genfromtxt(String filename, String delimiter, int skipHeader) {
        return new NpcArray(nativeGenfromtxt(filename, delimiter, skipHeader));
    }
    /** Save array as text file with default format. */
    public static void savetxt(String filename, NpcArray arr) {
        nativeSavetxt(filename, arr.nativePtr, "%g", " ", "\n", null, null, "# ");
    }
    /** Save array as text file with full options. */
    public static void savetxt(String filename, NpcArray arr, String fmt, String delimiter,
                                String newline, String header, String footer, String comments) {
        nativeSavetxt(filename, arr.nativePtr, fmt, delimiter, newline, header, footer, comments);
    }
    /** Create a fluent builder for savetxt. */
    public static SavetxtBuilder savetxtBuilder(String filename, NpcArray arr) {
        return new SavetxtBuilder(filename, arr);
    }
    /** Save array as .npy binary file. */
    public static void saveNpy(String filename, NpcArray arr) {
        nativeSaveNpy(filename, arr.nativePtr);
    }
    /** Load array from .npy binary file. */
    public static NpcArray loadNpy(String filename) {
        return new NpcArray(nativeLoadNpy(filename));
    }
    /** Save multiple arrays as .npz archive. */
    public static void savez(String filename, NpcArray... arrays) {
        nativeSavez(filename, arrays);
    }

    // ═══════════════════════════════════════════════════════════
    // In-Place Mutation
    // ═══════════════════════════════════════════════════════════

    /** Place values at mask positions. In-place. */
    public static int place(NpcArray arr, NpcArray mask, NpcArray vals) { return nativePlace(arr, mask.nativePtr, vals.nativePtr); }
    /** Put values at specified indices. In-place. */
    public static int put(NpcArray arr, NpcArray indices, NpcArray values) { return nativePut(arr, indices.nativePtr, values.nativePtr, "raise"); }
    public static int put(NpcArray arr, NpcArray indices, NpcArray values, String mode) { return nativePut(arr, indices.nativePtr, values.nativePtr, mode); }
    /** Put values at mask positions. In-place. */
    public static void putmask(NpcArray arr, NpcArray mask, NpcArray values) { nativePutmask(arr, mask.nativePtr, values.nativePtr); }
    /** In-place fill diagonal. */
    public static void fillDiagonal(NpcArray arr, double val) { nativeFillDiagonal(arr, val); }

    /** Swap two rows in-place. */
    public static void swapRows(NpcArray arr, int row1, int row2) { nativeSwapRows(arr, row1, row2); }
    /** Swap two columns in-place. */
    public static void swapCols(NpcArray arr, int col1, int col2) { nativeSwapCols(arr, col1, col2); }

    // ═══════════════════════════════════════════════════════════
    // Miscellaneous
    // ═══════════════════════════════════════════════════════════

    /** Clip values to [lo, hi] range. */
    public static NpcArray clip(NpcArray arr, NpcArray lo, NpcArray hi) { return new NpcArray(nativeClip_arr(arr.nativePtr, lo.nativePtr, hi.nativePtr)); }
    public static NpcArray clip(NpcArray arr, double lo, double hi) { return new NpcArray(nativeClip_scalar(arr.nativePtr, lo, hi)); }
    /** Conjugate (Hermitian) transpose. */
    public static NpcArray conjTranspose(NpcArray a) { return new NpcArray(nativeConjTranspose(a.nativePtr)); }
    /** Convolution. */
    public static NpcArray convolve(NpcArray a, NpcArray v) { return new NpcArray(nativeConvolve(a.nativePtr, v.nativePtr)); }
    /** Trim leading/trailing zeros. */
    public static NpcArray trimZeros(NpcArray arr) { return new NpcArray(nativeTrimZeros(arr.nativePtr, "fb")); }
    public static NpcArray trimZeros(NpcArray arr, String trim) { return new NpcArray(nativeTrimZeros(arr.nativePtr, trim)); }
    /** Take elements along axis. */
    public static NpcArray take(NpcArray a, NpcArray indices, int axis) { return new NpcArray(nativeTake(a.nativePtr, indices.nativePtr, axis)); }
    /** Take along axis (advanced). */
    public static NpcArray takeAlongAxis(NpcArray a, NpcArray indices, int axis) { return new NpcArray(nativeTakeAlongAxis(a.nativePtr, indices.nativePtr, axis)); }
    /** Compress array based on condition. */
    public static NpcArray compress(NpcArray condition, NpcArray a, int axis) { return new NpcArray(nativeCompress(condition.nativePtr, a.nativePtr, axis)); }
    /** Choose from choices based on index array. */
    public static native NpcArray nativeChoose(long aHandle, NpcArray[] choices, int mode);
    public static NpcArray choose(NpcArray a, NpcArray[] choices, int mode) { return nativeChoose(a.nativePtr, choices, mode); }
    /** Flat non-zero indices. */
    public static NpcArray flatnonzero(NpcArray a) { return new NpcArray(nativeFlatnonzero(a.nativePtr)); }
    /** Extract elements matching condition. */
    public static NpcArray extract(NpcArray condition, NpcArray arr) { return new NpcArray(nativeExtract(condition.nativePtr, arr.nativePtr)); }
    /** Delete sub-arrays along axis. */
    public static NpcArray delete(NpcArray arr, NpcArray obj, int axis) { return new NpcArray(nativeDelete(arr.nativePtr, obj.nativePtr, axis)); }
    /** Insert values along axis. */
    public static NpcArray insert(NpcArray arr, NpcArray obj, NpcArray values, int axis) { return new NpcArray(nativeInsert(arr.nativePtr, obj.nativePtr, values.nativePtr, axis)); }
    /** Bincount with optional weights. */
    public static NpcArray bincount(NpcArray a) { return new NpcArray(nativeBincount(a.nativePtr, 0)); }
    public static NpcArray bincount(NpcArray a, int minlength) { return new NpcArray(nativeBincount(a.nativePtr, minlength)); }
    public static NpcArray bincount(NpcArray a, NpcArray weights, int minlength) { return new NpcArray(nativeBincount_w(a.nativePtr, weights.nativePtr, minlength)); }
    /** Float decomposition: returns [mantissa, exponent]. */
    public static native NpcArray[] nativeFrexp(long aHandle);
    public static NpcArray[] frexp(NpcArray arr) { return nativeFrexp(arr.nativePtr); }
    /** Float decomposition: returns [fractional, integral]. */
    public static native NpcArray[] nativeModf(long aHandle);
    public static NpcArray[] modf(NpcArray arr) { return nativeModf(arr.nativePtr); }
    /** Open grid indices. Like numpy.ix_. */
    public static native NpcArray[] nativeIx(NpcArray[] arrays);
    public static NpcArray[] ix(NpcArray... arrays) { return nativeIx(arrays); }
    /** Create array from byte buffer. */
    public static NpcArray frombuffer(byte[] buffer, DType dtype, int count) { return new NpcArray(nativeFrombuffer(buffer, dtype.ordinal(), count, 0)); }
    public static NpcArray frombuffer(byte[] buffer, DType dtype, int count, int offset) { return new NpcArray(nativeFrombuffer(buffer, dtype.ordinal(), count, offset)); }
    /** Number of dimensions. */
    public static int ndim(NpcArray a) { return nativeNdim(a.nativePtr); }

    // ═══════════════════════════════════════════════════════════
    // Vandermonde / Triangular / Block
    // ═══════════════════════════════════════════════════════════

    /** Vandermonde matrix. Like numpy.vander. */
    public static NpcArray vander(NpcArray x, int N) { return new NpcArray(nativeVander(x.nativePtr, N, 0)); }
    /** Vandermonde matrix with increasing order option. */
    public static NpcArray vander(NpcArray x, int N, boolean increasing) { return new NpcArray(nativeVander(x.nativePtr, N, increasing ? 1 : 0)); }
    /** Lower triangular matrix of ones. Like numpy.tri. */
    public static NpcArray tri(int N, int M, int k, DType dtype) { return new NpcArray(nativeTri(N, M, k, dtype.ordinal())); }
    /** Lower triangular indices. Like numpy.tril_indices. */
    public static NpcArray trilIndices(int n) { return new NpcArray(nativeTrilIndices(n, 0, -1)); }
    public static NpcArray trilIndices(int n, int k) { return new NpcArray(nativeTrilIndices(n, k, -1)); }
    public static NpcArray trilIndices(int n, int k, int m) { return new NpcArray(nativeTrilIndices(n, k, m)); }
    /** Lower triangular indices from array. Like numpy.tril_indices_from. */
    public static NpcArray trilIndicesFrom(NpcArray arr) { return new NpcArray(nativeTrilIndicesFrom(arr.nativePtr, 0)); }
    public static NpcArray trilIndicesFrom(NpcArray arr, int k) { return new NpcArray(nativeTrilIndicesFrom(arr.nativePtr, k)); }
    /** Upper triangular indices. Like numpy.triu_indices. */
    public static NpcArray triuIndices(int n) { return new NpcArray(nativeTriuIndices(n, 0, -1)); }
    public static NpcArray triuIndices(int n, int k) { return new NpcArray(nativeTriuIndices(n, k, -1)); }
    public static NpcArray triuIndices(int n, int k, int m) { return new NpcArray(nativeTriuIndices(n, k, m)); }
    /** Upper triangular indices from array. Like numpy.triu_indices_from. */
    public static NpcArray triuIndicesFrom(NpcArray arr) { return new NpcArray(nativeTriuIndicesFrom(arr.nativePtr, 0)); }
    public static NpcArray triuIndicesFrom(NpcArray arr, int k) { return new NpcArray(nativeTriuIndicesFrom(arr.nativePtr, k)); }
    /** Build block matrix. Like numpy.block. */
    public static NpcArray block(NpcArray[] blocks, int rows, int cols) { return new NpcArray(nativeBlock(blocks, rows, cols)); }
    /** Build matrix from blocks. Like numpy.bmat. */
    public static NpcArray bmat(NpcArray[] blocks, int rows, int cols) { return new NpcArray(nativeBmat(blocks, rows, cols)); }

    // ═══════════════════════════════════════════════════════════
    // Einsum path / Utility
    // ═══════════════════════════════════════════════════════════

    /** Einstein summation optimal contraction path. Like numpy.einsum_path. */
    public static native String einsumPath(String subscripts, NpcArray[] operands);
    /** Return total elements or axis length. Like numpy.size. */
    public static int asize(NpcArray a) { return nativeAsize(a.nativePtr, -1); }
    /** asize along axis. */
    public static int asize(NpcArray a, int axis) { return nativeAsize(a.nativePtr, axis); }
    /** Type character to readable name. Like numpy.typename. */
    public static native String typenameStr(String typechar);

    // ═══════════════════════════════════════════════════════════
    // Advanced
    // ═══════════════════════════════════════════════════════════

    /** Get current parallel computation config. Returns [numThreads, enableParallel]. */
    public static int[] getParallelConfig() { return nativeGetParallelConfig(); }
    /** Broadcast multiple arrays to a common shape. Like numpy.broadcast_arrays. */
    public static NpcArray[] broadcastArrays(NpcArray[] arrays) { return nativeBroadcastArrays(arrays); }
    /** Create raw array with given shape and dtype. */
    public static NpcArray createArray(int[] shape, DType dtype) { return new NpcArray(nativeCreateArray(shape, dtype.ordinal())); }
    /** Scalar modulo (dividend array, scalar divisor). Like numpy.mod. */
    public static NpcArray modScalar(NpcArray arr, double scalar) { return new NpcArray(nativeModScalar(arr.nativePtr, scalar)); }
    /** Stack arrays row-wise. Equivalent to vstack. Like numpy.row_stack. */
    public static NpcArray rowStack(NpcArray[] arrays) { return nativeVstack(arrays); }
    /** Einstein summation. */
    public static native NpcArray nativeEinsum(String subscripts, NpcArray[] operands);
    public static NpcArray einsum(String subscripts, NpcArray... operands) { return nativeEinsum(subscripts, operands); }
    /** Set parallel computation config. */
    public static native void nativeSetParallelConfig(int numThreads, boolean enable);
    public static void setParallelConfig(int numThreads, boolean enableParallel) { nativeSetParallelConfig(numThreads, enableParallel); }
    /** Get I/O buffer size. */
    public static native int nativeGetBufsize();
    public static int getBufsize() { return nativeGetBufsize(); }
    /** Set I/O buffer size. */
    public static native void nativeSetBufsize(int size);
    public static void setBufsize(int size) { nativeSetBufsize(size); }

    // ═══════════════════════════════════════════════════════════
    // All native method declarations
    // ═══════════════════════════════════════════════════════════

    // Creation
    private static native long nativeZeros(int[] shape, int dtypeOrdinal);
    private static native long nativeOnes(int[] shape, int dtypeOrdinal);
    private static native long nativeFull(int[] shape, double value, int dtypeOrdinal);
    private static native long nativeEmpty(int[] shape, int dtypeOrdinal);
    private static native long nativeArange(double start, double stop, double step, int dtypeOrdinal);
    private static native long nativeLinspace(double start, double stop, int num, boolean endpoint);
    private static native long nativeLogspace(double start, double stop, int num, double base, boolean endpoint);
    private static native long nativeGeomspace(double start, double stop, int num, boolean endpoint);
    private static native long nativeEye(int N, int M, int k, int dtypeOrdinal);
    private static native long nativeIdentity(int N, int dtypeOrdinal);
    private static native long nativeFullLike(long aHandle, double value, int dtypeOrdinal);
    private static native long nativeArray1D(double[] data);
    private static native long nativeArray2D(double[][] data);
    private static native long nativeCopy(long aHandle);
    private static native long nativeAstype(long aHandle, int dtypeOrdinal);

    // Arithmetic
    private static native long nativeAdd(long aHandle, long bHandle);
    private static native long nativeSubtract(long aHandle, long bHandle);
    private static native long nativeMultiply(long aHandle, long bHandle);
    private static native long nativeDivide(long aHandle, long bHandle);
    private static native long nativeTrueDivide(long aHandle, long bHandle);
    private static native long nativePower(long aHandle, long bHandle);
    private static native long nativeHypot(long aHandle, long bHandle);
    private static native long nativeLogaddexp(long aHandle, long bHandle);
    private static native long nativeLogaddexp2(long aHandle, long bHandle);
    private static native long nativeArctan2(long aHandle, long bHandle);
    private static native long nativeCopysign(long aHandle, long bHandle);
    private static native long nativeNextafter(long aHandle, long bHandle);
    private static native long nativeMod(long aHandle, long bHandle);
    private static native long nativeFmod(long aHandle, long bHandle);
    private static native long nativeMaximum(long aHandle, long bHandle);
    private static native long nativeMinimum(long aHandle, long bHandle);
    private static native long nativeLdexp(long aHandle, long bHandle);
    private static native long nativeGcd(long aHandle, long bHandle);
    private static native long nativeLcm(long aHandle, long bHandle);
    private static native long nativeLeftShift(long aHandle, long bHandle);
    private static native long nativeRightShift(long aHandle, long bHandle);
    // Scalar arithmetic
    private static native long nativeAddScalar(long aHandle, double scalar);
    private static native long nativeSubtractScalar(long aHandle, double scalar);
    private static native long nativeMultiplyScalar(long aHandle, double scalar);
    private static native long nativeDivideScalar(long aHandle, double scalar);
    private static native long nativeSubtractFromScalar(long aHandle, double scalar);
    private static native long nativeDivideFromScalar(long aHandle, double scalar);

    // Unary math
    private static native long nativeAbs(long aHandle);
    private static native long nativeSqrt(long aHandle);
    private static native long nativeExp(long aHandle);
    private static native long nativeLog(long aHandle);
    private static native long nativeLog10(long aHandle);
    private static native long nativeLog2(long aHandle);
    private static native long nativeSin(long aHandle);
    private static native long nativeCos(long aHandle);
    private static native long nativeTan(long aHandle);
    private static native long nativeSinh(long aHandle);
    private static native long nativeCosh(long aHandle);
    private static native long nativeTanh(long aHandle);
    private static native long nativeArcsin(long aHandle);
    private static native long nativeArccos(long aHandle);
    private static native long nativeArctan(long aHandle);
    private static native long nativeArcsinh(long aHandle);
    private static native long nativeArccosh(long aHandle);
    private static native long nativeArctanh(long aHandle);
    private static native long nativeDeg2rad(long aHandle);
    private static native long nativeRad2deg(long aHandle);
    private static native long nativeDegrees(long aHandle);
    private static native long nativeRadians(long aHandle);
    private static native long nativeFloor(long aHandle);
    private static native long nativeCeil(long aHandle);
    private static native long nativeRint(long aHandle);
    private static native long nativeTrunc(long aHandle);
    private static native long nativeFix(long aHandle);
    private static native long nativeAround(long aHandle, int decimals);
    private static native long nativeSign(long aHandle);
    private static native long nativeSinc(long aHandle);
    private static native long nativeFabs(long aHandle);
    private static native long nativeAbsolute(long aHandle);
    private static native long nativeReciprocal(long aHandle);
    private static native long nativePositive(long aHandle);
    private static native long nativeNegative(long aHandle);
    private static native long nativeCbrt(long aHandle);
    private static native long nativeSquare(long aHandle);
    private static native long nativeHeaviside(long aHandle, double h);
    private static native long nativeI0(long aHandle);
    private static native long nativeReal(long aHandle);
    private static native long nativeImag(long aHandle);
    private static native long nativeAngle(long aHandle, boolean deg);
    private static native long nativeSpacing(long aHandle);

    // Comparison
    private static native long nativeEqual(long aHandle, long bHandle);
    private static native long nativeNotEqual(long aHandle, long bHandle);
    private static native long nativeGreater(long aHandle, long bHandle);
    private static native long nativeGreaterEqual(long aHandle, long bHandle);
    private static native long nativeLess(long aHandle, long bHandle);
    private static native long nativeLessEqual(long aHandle, long bHandle);
    private static native long nativeIsclose(long aHandle, long bHandle, double rtol, double atol, boolean equalNan);

    // Logical
    private static native long nativeLogicalAnd(long aHandle, long bHandle);
    private static native long nativeLogicalOr(long aHandle, long bHandle);
    private static native long nativeLogicalXor(long aHandle, long bHandle);
    private static native long nativeLogicalNot(long aHandle);
    private static native long nativeBitwiseAnd(long aHandle, long bHandle);
    private static native long nativeBitwiseOr(long aHandle, long bHandle);
    private static native long nativeBitwiseXor(long aHandle, long bHandle);
    private static native long nativeBitwiseNot(long aHandle);
    private static native long nativeInvert(long aHandle);

    // Statistics
    private static native long nativeSum(long aHandle, int axis, boolean keepdims);
    private static native long nativeMean(long aHandle, int axis, boolean keepdims);
    private static native long nativeMin(long aHandle, int axis, boolean keepdims);
    private static native long nativeMax(long aHandle, int axis, boolean keepdims);
    private static native long nativeProd(long aHandle, int axis, boolean keepdims);
    private static native long nativeStddev(long aHandle, int axis, boolean keepdims);
    private static native long nativeVar(long aHandle, int axis, int ddof, boolean keepdims);
    private static native long nativeMedian(long aHandle, int axis, boolean keepdims);
    private static native long nativePercentile(long aHandle, long qHandle, int axis);
    private static native long nativeQuantile(long aHandle, long qHandle, int axis);
    private static native long nativeCumsum(long aHandle, int axis);
    private static native long nativeCumprod(long aHandle, int axis);
    private static native long nativeArgmax(long aHandle, int axis, boolean keepdims);
    private static native long nativeArgmin(long aHandle, int axis, boolean keepdims);
    private static native long nativeCountNonzero(long aHandle, int axis);
    private static native long nativePtp(long aHandle, int axis, boolean keepdims);
    private static native long nativeAll(long aHandle, int axis, boolean keepdims);
    private static native long nativeAny(long aHandle, int axis, boolean keepdims);
    private static native long nativeWhere(long condHandle, long xHandle, long yHandle);
    private static native long nativeAverage_w(long aHandle, long wHandle, int axis, boolean keepdims);
    private static native long nativeAverage(long aHandle, int axis, boolean keepdims);
    private static native long nativeCov(long aHandle, boolean rowvar, int ddof, int dtypeOrdinal);
    private static native long nativeCorrcoef(long aHandle, boolean rowvar);
    private static native long nativeCorrelate(long aHandle, long vHandle, String mode);
    private static native long nativeTrapz_dx(long aHandle, double dx, int axis);
    private static native long nativeTrapz_x(long aHandle, long xHandle, double dx, int axis);

    // NaN statistics
    private static native long nativeNanmax(long aHandle, int axis);
    private static native long nativeNanmin(long aHandle, int axis);
    private static native long nativeNanmean(long aHandle, int axis);
    private static native long nativeNanmedian(long aHandle, int axis);
    private static native long nativeNansum(long aHandle, int axis);
    private static native long nativeNanprod(long aHandle, int axis);
    private static native long nativeNanstd(long aHandle, int axis, boolean keepdims);
    private static native long nativeNanvar(long aHandle, int axis, int ddof, boolean keepdims);
    private static native long nativeNanpercentile(long aHandle, long qHandle, int axis);
    private static native long nativeNanquantile(long aHandle, long qHandle, int axis);
    private static native long nativeNancumsum(long aHandle, int axis);
    private static native long nativeNancumprod(long aHandle, int axis);
    private static native long nativeNanargmax(long aHandle, int axis);
    private static native long nativeNanargmin(long aHandle, int axis);
    private static native long nativeIsnan(long aHandle);
    private static native long nativeIsinf(long aHandle);
    private static native long nativeIsfinite(long aHandle);
    private static native long nativeNanToNum(long aHandle);

    // Linear algebra
    private static native long nativeDot(long aHandle, long bHandle);
    private static native long nativeMatmul(long aHandle, long bHandle);
    private static native long nativeVdot(long aHandle, long bHandle);
    private static native long nativeInner(long aHandle, long bHandle);
    private static native long nativeOuter(long aHandle, long bHandle);
    private static native long nativeCross(long aHandle, long bHandle);
    private static native long nativeKron(long aHandle, long bHandle);
    private static native long nativeTensordot_axes(long aHandle, long bHandle, long axesAHandle, long axesBHandle);
    private static native long nativeTensordot_int(long aHandle, long bHandle, int axes);
    private static native long nativeInv(long aHandle);
    private static native long nativePinv(long aHandle, double rcond);
    private static native long nativeDet(long aHandle);
    private static native long nativeTrace(long aHandle);
    private static native long nativeCholesky(long aHandle);

    // FFT
    private static native long nativeFft(long aHandle);
    private static native long nativeIfft(long aHandle);
    private static native long nativeRfft(long aHandle);
    private static native long nativeRfft2(long aHandle);
    private static native long nativeRfftn(long aHandle);
    private static native long nativeHfft(long aHandle, int n);
    private static native long nativeIhfft(long aHandle, int n);
    private static native long nativeIrfft(long aHandle, int n);
    private static native long nativeIrfft2(long aHandle, int[] s);
    private static native long nativeIrfftn(long aHandle, int[] s);
    private static native long nativeFft2(long aHandle);
    private static native long nativeIfft2(long aHandle);
    private static native long nativeFftn(long aHandle);
    private static native long nativeIfftn(long aHandle);
    private static native long nativeFftshift(long aHandle);
    private static native long nativeIfftshift(long aHandle);
    private static native long nativeFftfreq(int n, double d);
    private static native long nativeRfftfreq(int n, double d);

    // Random
    private static native long nativeRandomSample(int[] shape);
    private static native long nativeRand(int[] shape);
    private static native long nativeRandint(int low, int high, int[] shape, int dtypeOrdinal);
    private static native long nativeUniform(double low, double high, int[] shape);
    private static native long nativeStandardNormal(int[] shape);
    private static native long nativeRandn(int[] shape);
    private static native long nativeNormal(double loc, double scale, int[] shape);
    private static native long nativeStandardExponential(int[] shape);
    private static native long nativeExponential(double scale, int[] shape);
    private static native long nativeStandardGamma(double shape, int[] outShape);
    private static native long nativeGamma(double shape, double scale, int[] outShape);
    private static native long nativeChisquare(double df, int[] shape);
    private static native long nativeBeta(double a, double b, int[] shape);
    private static native long nativeStandardT(double df, int[] shape);
    private static native long nativeF(double dfn, double dfd, int[] shape);
    private static native long nativeLaplace(double loc, double scale, int[] shape);
    private static native long nativeLogistic(double loc, double scale, int[] shape);
    private static native long nativeLognormal(double mean, double sigma, int[] shape);
    private static native long nativePareto(double a, int[] shape);
    private static native long nativePowerDist(double a, int[] shape);
    private static native long nativeRayleigh(double scale, int[] shape);
    private static native long nativeWeibull(double a, int[] shape);
    private static native long nativeStandardCauchy(int[] shape);
    private static native long nativeGumbel(double loc, double scale, int[] shape);
    private static native long nativeTriangular(double left, double mode, double right, int[] shape);
    private static native long nativeVonmises(double mu, double kappa, int[] shape);
    private static native long nativeWald(double mean, double scale, int[] shape);
    private static native long nativeGeometric(double p, int[] shape);
    private static native long nativePoisson(double lam, int[] shape);
    private static native long nativeBinomial(int n, double p, int[] shape);
    private static native long nativeNegativeBinomial(int n, double p, int[] shape);
    private static native long nativeHypergeometric(int ngood, int nbad, int nsample, int[] shape);
    private static native long nativeZipf(double a, int[] shape);
    private static native long nativeLogseries(double p, int[] shape);
    private static native long nativePermutation(long aHandle);
    private static native void nativeShuffle(NpcArray x);
    private static native long nativeChoice(long aHandle, int size, boolean replace, long pHandle);
    private static native long nativeMultinomial(int n, long pvalsHandle, int[] shape);
    private static native long nativeMultivariateNormal(long meanHandle, long covHandle, int[] shape);
    private static native long nativeDirichlet(long alphaHandle, int[] shape);
    private static native long nativeRandomBytes(int n);

    // Polynomial
    private static native long nativePoly(long rootsHandle);
    private static native long nativeRoots(long pHandle);
    private static native long nativePolyadd(long aHandle, long bHandle);
    private static native long nativePolysub(long aHandle, long bHandle);
    private static native long nativePolymul(long aHandle, long bHandle);
    private static native long nativePolyder(long pHandle, int m);
    private static native long nativePolyint(long pHandle, int m);
    private static native long nativePolyval(long pHandle, long xHandle);
    private static native long nativePolyfit(long xHandle, long yHandle, int deg);

    // Shape
    private static native long nativeReshape(long aHandle, int[] shape);
    private static native long nativeResize(long aHandle, int[] shape);
    private static native long nativeTranspose(long aHandle);
    private static native long nativeFlatten(long aHandle);
    private static native long nativeRavel(long aHandle, String order);
    private static native long nativeSqueeze(long aHandle, int axis);
    private static native long nativeExpandDims(long aHandle, int axis);
    private static native long nativeConcatenate(long aHandle, long bHandle, int axis);
    private static native long nativeAppend(long aHandle, long vHandle, int axis);
    private static native long nativeFlip(long aHandle, int axis);
    private static native long nativeFliplr(long aHandle);
    private static native long nativeFlipud(long aHandle);
    private static native long nativeRot90(long aHandle, int k, int axis1, int axis2);
    private static native long nativeRoll(long aHandle, int shift, int axis);
    private static native long nativeBroadcastTo(long aHandle, int[] shape);
    private static native long nativeTile(long aHandle, int[] reps);
    private static native long nativeRepeat(long aHandle, long repeatsHandle, int axis);
    private static native long nativeMoveaxis(long aHandle, int source, int dest);
    private static native long nativeRollaxis(long aHandle, int axis, int start);
    private static native long nativeSwapaxes(long aHandle, int axis1, int axis2);
    private static native long nativeAtleast1d(long aHandle);
    private static native long nativeAtleast2d(long aHandle);
    private static native long nativeAtleast3d(long aHandle);
    private static native long nativePad(long aHandle, long pwHandle, String mode, double cv);
    // Diagonal
    private static native long nativeDiag(long aHandle, int k);
    private static native long nativeDiagflat(long aHandle, int k);
    private static native long nativeDiagonal(long aHandle, int offset, int axis1, int axis2);
    private static native long nativeTril(long aHandle, int k);
    private static native long nativeTriu(long aHandle, int k);

    // Sorting
    private static native long nativeSort(long aHandle);
    private static native long nativeMsort(long aHandle);
    private static native long nativeArgsort(long aHandle, int axis, String kind);
    private static native long nativeArgpartition(long aHandle, int kth, int axis);
    private static native long nativePartition(long aHandle, int kth, int axis);
    private static native long nativeUnwrap(long aHandle, double discont, int axis);

    // Set ops
    private static native long nativeIntersect1d(long aHandle, long bHandle, boolean assumeUnique);
    private static native long nativeSetdiff1d(long aHandle, long bHandle);
    private static native long nativeSearchsorted(long aHandle, long vHandle, String side);
    private static native long nativeDigitize(long aHandle, long binsHandle, boolean right);
    private static native long nativeArgwhere(long aHandle);

    // Interpolation
    private static native long nativeInterp(long arrHandle, long xpHandle, long fpHandle, long leftHandle, long rightHandle);
    private static native long nativeDiff(long aHandle, int n, int axis);
    private static native long nativeEdiff1d(long yHandle, long toBeginHandle, long toEndHandle);

    // Window
    private static native long nativeBartlett(int M);
    private static native long nativeBlackman(int M);
    private static native long nativeKaiser(int M, double beta);
    private static native long nativeHanning(int M);
    private static native long nativeHamming(int M);

    // I/O
    private static native long nativeReadtxt(String filename, String delimiter, char comment, int skiplines, int maxRows, int ndmin, boolean unpack, int dtypeOrdinal);
    private static native long nativeGenfromtxt(String filename, String delimiter, int skipHeader);
    private static native int nativeSavetxt(String filename, long aHandle, String fmt, String delimiter, String newline, String header, String footer, String comments);
    private static native int nativeSaveNpy(String filename, long aHandle);
    private static native long nativeLoadNpy(String filename);
    private static native int nativeSavez(String filename, NpcArray[] arrays);

    // Mutation
    private static native int nativePlace(NpcArray arr, long maskHandle, long valsHandle);
    private static native int nativePut(NpcArray arr, long indicesHandle, long valuesHandle, String mode);
    private static native void nativePutmask(NpcArray arr, long maskHandle, long valuesHandle);
    private static native void nativeFillDiagonal(NpcArray arr, double val);
    private static native void nativeSwapRows(NpcArray arr, int row1, int row2);
    private static native void nativeSwapCols(NpcArray arr, int col1, int col2);

    // Misc
    private static native long nativeClip_arr(long aHandle, long loHandle, long hiHandle);
    private static native long nativeClip_scalar(long aHandle, double lo, double hi);
    private static native long nativeConjTranspose(long aHandle);
    private static native long nativeConvolve(long aHandle, long vHandle);
    private static native long nativeTrimZeros(long aHandle, String trim);
    private static native long nativeTake(long aHandle, long indicesHandle, int axis);
    private static native long nativeTakeAlongAxis(long aHandle, long indicesHandle, int axis);
    private static native long nativeCompress(long condHandle, long aHandle, int axis);
    private static native long nativeFlatnonzero(long aHandle);
    private static native long nativeExtract(long condHandle, long aHandle);
    private static native long nativeDelete(long aHandle, long objHandle, int axis);
    private static native long nativeInsert(long aHandle, long objHandle, long valuesHandle, int axis);
    private static native long nativeBincount_w(long aHandle, long weightsHandle, int minlength);
    private static native long nativeBincount(long aHandle, int minlength);
    private static native long nativeFrombuffer(byte[] buffer, int dtypeOrdinal, int count, int offset);
    private static native int nativeNdim(long aHandle);
    // Vandermonde / Triangular / Block
    private static native long nativeVander(long xHandle, int N, int increasing);
    private static native long nativeTri(int N, int M, int k, int dtypeOrdinal);
    private static native long nativeTrilIndices(int n, int k, int m);
    private static native long nativeTrilIndicesFrom(long arrHandle, int k);
    private static native long nativeTriuIndices(int n, int k, int m);
    private static native long nativeTriuIndicesFrom(long arrHandle, int k);
    private static native long nativeBlock(NpcArray[] blocks, int rows, int cols);
    private static native long nativeBmat(NpcArray[] blocks, int rows, int cols);
    private static native int nativeAsize(long aHandle, int axis);
    private static native int[] nativeGetParallelConfig();
    private static native long nativeCreateArray(int[] shape, int dtypeOrdinal);
    private static native long nativeModScalar(long aHandle, double scalar);
    private static native NpcArray[] nativeBroadcastArrays(NpcArray[] arrays);
}
