package libnpc;

/**
 * A multi-dimensional array with automatic memory management.
 *
 * <p>{@code NpcArray} is the central data type of libnpc Java. It wraps a native
 * libnpc C array via JNI and provides automatic cleanup through
 * {@link AutoCloseable}. Use try-with-resources to ensure native memory is freed:</p>
 *
 * <pre>{@code
 * try (NpcArray a = Npc.ones(3, 4);
 *      NpcArray b = Npc.zeros(3, 4)) {
 *     NpcArray c = Npc.add(a, b);
 *     System.out.println(c);
 * }
 * }</pre>
 *
 * <p>Instance methods like {@link #sum()}, {@link #mean()}, {@link #reshape(int...)}
 * delegate to the corresponding static methods in {@link Npc}.</p>
 *
 * @see Npc
 * @see AutoCloseable
 */
public final class NpcArray implements AutoCloseable {

    // ═══════════════════════════════════════════════════════════
    // Native handle (opaque pointer to C++ unique_ptr<npc::Array>)
    // ═══════════════════════════════════════════════════════════

    // package-private — Npc needs direct access for JNI calls
    long nativePtr;

    static {
        NativeLib.ensureLoaded();
    }

    /**
     * Package-private constructor. Use {@link Npc} factory methods to create arrays.
     */
    NpcArray(long nativePtr) {
        this.nativePtr = nativePtr;
    }

    // ═══════════════════════════════════════════════════════════
    // AutoCloseable
    // ═══════════════════════════════════════════════════════════

    /**
     * Frees the native memory held by this array. Idempotent — calling close()
     * multiple times is safe. After close(), all methods will throw.
     */
    @Override
    public void close() {
        if (nativePtr != 0) {
            nativeClose();
            nativePtr = 0;
        }
    }

    /**
     * Returns {@code true} if this array has been closed.
     */
    public boolean isClosed() {
        return nativePtr == 0;
    }

    /**
     * Safety net: calls {@link #close()} if the array is garbage-collected
     * without being explicitly closed.
     */
    @Override
    @SuppressWarnings("deprecation")
    protected void finalize() {
        close();
    }

    // ═══════════════════════════════════════════════════════════
    // Metadata accessors
    // ═══════════════════════════════════════════════════════════

    /** Number of dimensions. 0 for scalar, 1 for vector, 2 for matrix. */
    public int ndim() { return nativeNdim(); }

    /** Total number of elements (product of all shape dimensions). */
    public int size() { return nativeSize(); }

    /** Copy of the shape array. */
    public int[] shape() { return nativeShape(); }

    /** Size of a specific axis. Negative indices count from the end. */
    public int shape(int axis) { return nativeShapeAxis(axis); }

    /** Copy of the strides array. */
    public int[] strides() { return nativeStrides(); }

    /** Data type of the array elements. */
    public DType dtype() { return DType.values()[nativeDtype()]; }

    /** True if this array is a view sharing another array's data. */
    public boolean isView() { return nativeIsView(); }

    /** True if this array wraps no data. */
    public boolean isNull() { return nativePtr == 0; }

    // ═══════════════════════════════════════════════════════════
    // Multi-dimensional element access
    // ═══════════════════════════════════════════════════════════

    /** Get element as double by multi-dimensional indices. */
    public double getDouble(int... indices) { return nativeGetDouble(indices); }

    /** Set element from double by multi-dimensional indices. */
    public void setDouble(double value, int... indices) { nativeSetDouble(indices, value); }

    /** Get 1-D element as double. */
    public double getDouble(int index) { return nativeGetDouble1D(index); }

    /** Set 1-D element from double. */
    public void setDouble(int index, double value) { nativeSetDouble1D(index, value); }

    /** Get the first element as a double scalar. */
    public double scalarDouble() { return nativeScalarDouble(); }

    /** Get the first element as a long scalar. */
    public long scalarLong() { return nativeScalarLong(); }

    /** Get the first element as an int scalar. */
    public int scalarInt() { return nativeScalarInt(); }

    /** Get the first element as a boolean scalar. */
    public boolean scalarBoolean() { return nativeScalarBoolean(); }

    // ═══════════════════════════════════════════════════════════
    // Bulk data extraction
    // ═══════════════════════════════════════════════════════════

    /** Copy all elements into a new double[]. */
    public double[] toDoubleArray() { return nativeToDoubleArray(); }

    /** Copy all elements into a new long[]. */
    public long[] toLongArray() { return nativeToLongArray(); }

    /** Copy all elements into a new int[]. */
    public int[] toIntArray() { return nativeToIntArray(); }

    // ═══════════════════════════════════════════════════════════
    // Printing
    // ═══════════════════════════════════════════════════════════

    /** Print array contents to stdout. */
    public void print() { nativePrint(); }

    /** Print array metadata (dtype, ndim, shape, strides). */
    public void info() { nativeInfo(); }

    @Override
    public String toString() { return nativeToString(); }

    // ═══════════════════════════════════════════════════════════
    // Instance methods — delegate to Npc static methods
    // ═══════════════════════════════════════════════════════════

    /** Deep copy. */
    public NpcArray copy() { return Npc.copy(this); }

    /** Cast to a different data type. */
    public NpcArray astype(DType dtype) { return Npc.astype(this, dtype); }

    // -- Unary math --
    /** Element-wise absolute value. */
    public NpcArray abs() { return Npc.abs(this); }
    /** Element-wise square root. */
    public NpcArray sqrt() { return Npc.sqrt(this); }
    /** Element-wise exponential (e^x). */
    public NpcArray exp() { return Npc.exp(this); }
    /** Element-wise natural logarithm. */
    public NpcArray log() { return Npc.log(this); }
    /** Element-wise base-10 logarithm. */
    public NpcArray log10() { return Npc.log10(this); }
    /** Element-wise base-2 logarithm. */
    public NpcArray log2() { return Npc.log2(this); }
    /** Element-wise sine. */
    public NpcArray sin() { return Npc.sin(this); }
    /** Element-wise cosine. */
    public NpcArray cos() { return Npc.cos(this); }
    /** Element-wise tangent. */
    public NpcArray tan() { return Npc.tan(this); }
    /** Element-wise hyperbolic sine. */
    public NpcArray sinh() { return Npc.sinh(this); }
    /** Element-wise hyperbolic cosine. */
    public NpcArray cosh() { return Npc.cosh(this); }
    /** Element-wise hyperbolic tangent. */
    public NpcArray tanh() { return Npc.tanh(this); }
    /** Element-wise inverse sine. */
    public NpcArray arcsin() { return Npc.arcsin(this); }
    /** Element-wise inverse cosine. */
    public NpcArray arccos() { return Npc.arccos(this); }
    /** Element-wise inverse tangent. */
    public NpcArray arctan() { return Npc.arctan(this); }
    /** Element-wise floor (round down). */
    public NpcArray floor() { return Npc.floor(this); }
    /** Element-wise ceil (round up). */
    public NpcArray ceil() { return Npc.ceil(this); }
    /** Round to nearest integer, ties to even. */
    public NpcArray rint() { return Npc.rint(this); }
    /** Truncate toward zero. */
    public NpcArray trunc() { return Npc.trunc(this); }
    /** Round toward zero. */
    public NpcArray fix() { return Npc.fix(this); }
    /** Round to given number of decimals. */
    public NpcArray round(int decimals) { return Npc.around(this, decimals); }
    /** Element-wise sign (-1, 0, +1). */
    public NpcArray sign() { return Npc.sign(this); }
    /** Element-wise reciprocal (1/x). */
    public NpcArray reciprocal() { return Npc.reciprocal(this); }
    /** Element-wise cube root. */
    public NpcArray cbrt() { return Npc.cbrt(this); }
    /** Element-wise square (x²). */
    public NpcArray square() { return Npc.square(this); }
    /** Deg2rad conversion. */
    public NpcArray deg2rad() { return Npc.deg2rad(this); }
    /** Rad2deg conversion. */
    public NpcArray rad2deg() { return Npc.rad2deg(this); }

    // -- Aggregation --
    /** Sum of all elements. */
    public NpcArray sum() { return Npc.sum(this); }
    /** Sum along axis. */
    public NpcArray sum(int axis) { return Npc.sum(this, axis); }
    /** Sum along axis with keepdims. */
    public NpcArray sum(int axis, boolean keepdims) { return Npc.sum(this, axis, keepdims); }
    /** Arithmetic mean of all elements. */
    public NpcArray mean() { return Npc.mean(this); }
    /** Mean along axis. */
    public NpcArray mean(int axis) { return Npc.mean(this, axis); }
    /** Mean along axis with keepdims. */
    public NpcArray mean(int axis, boolean keepdims) { return Npc.mean(this, axis, keepdims); }
    /** Minimum value. */
    public NpcArray min() { return Npc.min(this); }
    public NpcArray min(int axis) { return Npc.min(this, axis); }
    public NpcArray min(int axis, boolean keepdims) { return Npc.min(this, axis, keepdims); }
    /** Maximum value. */
    public NpcArray max() { return Npc.max(this); }
    public NpcArray max(int axis) { return Npc.max(this, axis); }
    public NpcArray max(int axis, boolean keepdims) { return Npc.max(this, axis, keepdims); }
    /** Product of all elements. */
    public NpcArray prod() { return Npc.prod(this); }
    public NpcArray prod(int axis) { return Npc.prod(this, axis); }
    public NpcArray prod(int axis, boolean keepdims) { return Npc.prod(this, axis, keepdims); }
    /** Population standard deviation. */
    public NpcArray stddev() { return Npc.stddev(this); }
    public NpcArray stddev(int axis) { return Npc.stddev(this, axis); }
    public NpcArray stddev(int axis, boolean keepdims) { return Npc.stddev(this, axis, keepdims); }
    /** Variance. */
    public NpcArray var() { return Npc.var(this); }
    public NpcArray var(int axis) { return Npc.var(this, axis); }
    public NpcArray var(int axis, int ddof) { return Npc.var(this, axis, ddof); }
    public NpcArray var(int axis, int ddof, boolean keepdims) { return Npc.var(this, axis, ddof, keepdims); }
    /** Median. */
    public NpcArray median() { return Npc.median(this); }
    public NpcArray median(int axis) { return Npc.median(this, axis); }
    public NpcArray median(int axis, boolean keepdims) { return Npc.median(this, axis, keepdims); }
    /** Index of maximum value. */
    public NpcArray argmax() { return Npc.argmax(this); }
    public NpcArray argmax(int axis) { return Npc.argmax(this, axis); }
    public NpcArray argmax(int axis, boolean keepdims) { return Npc.argmax(this, axis, keepdims); }
    /** Index of minimum value. */
    public NpcArray argmin() { return Npc.argmin(this); }
    public NpcArray argmin(int axis) { return Npc.argmin(this, axis); }
    public NpcArray argmin(int axis, boolean keepdims) { return Npc.argmin(this, axis, keepdims); }
    /** Test if all elements are true. */
    public NpcArray all() { return Npc.all(this); }
    public NpcArray all(int axis) { return Npc.all(this, axis); }
    public NpcArray all(int axis, boolean keepdims) { return Npc.all(this, axis, keepdims); }
    /** Test if any element is true. */
    public NpcArray any() { return Npc.any(this); }
    public NpcArray any(int axis) { return Npc.any(this, axis); }
    public NpcArray any(int axis, boolean keepdims) { return Npc.any(this, axis, keepdims); }
    /** Count non-zero elements. */
    public NpcArray countNonzero() { return Npc.countNonzero(this); }
    public NpcArray countNonzero(int axis) { return Npc.countNonzero(this, axis); }
    /** Peak-to-peak (max - min). */
    public NpcArray ptp() { return Npc.ptp(this); }
    public NpcArray ptp(int axis) { return Npc.ptp(this, axis); }
    public NpcArray ptp(int axis, boolean keepdims) { return Npc.ptp(this, axis, keepdims); }
    /** Cumulative sum. */
    public NpcArray cumsum() { return Npc.cumsum(this); }
    public NpcArray cumsum(int axis) { return Npc.cumsum(this, axis); }
    /** Cumulative product. */
    public NpcArray cumprod() { return Npc.cumprod(this); }
    public NpcArray cumprod(int axis) { return Npc.cumprod(this, axis); }

    // -- Shape --
    /** Reshape to new dimensions. */
    public NpcArray reshape(int... shape) { return Npc.reshape(this, shape); }
    /** Full transpose. */
    public NpcArray transpose() { return Npc.transpose(this); }
    /** Flatten to 1-D. */
    public NpcArray flatten() { return Npc.flatten(this); }
    /** Flatten with order. */
    public NpcArray ravel() { return Npc.ravel(this); }
    public NpcArray ravel(String order) { return Npc.ravel(this, order); }
    /** Remove dimensions of length 1. */
    public NpcArray squeeze() { return Npc.squeeze(this); }
    public NpcArray squeeze(int axis) { return Npc.squeeze(this, axis); }
    /** Add a new axis. */
    public NpcArray expandDims(int axis) { return Npc.expandDims(this, axis); }
    /** Reverse elements. */
    public NpcArray flip() { return Npc.flip(this); }
    public NpcArray flip(int axis) { return Npc.flip(this, axis); }
    /** Roll elements. */
    public NpcArray roll(int shift) { return Npc.roll(this, shift); }
    public NpcArray roll(int shift, int axis) { return Npc.roll(this, shift, axis); }
    /** Broadcast to shape. */
    public NpcArray broadcastTo(int... shape) { return Npc.broadcastTo(this, shape); }
    /** Tile. */
    public NpcArray tile(int... reps) { return Npc.tile(this, reps); }
    /** Swap axes. */
    public NpcArray swapaxes(int axis1, int axis2) { return Npc.swapaxes(this, axis1, axis2); }

    // -- Linear algebra --
    /** Dot product. */
    public NpcArray dot(NpcArray other) { return Npc.dot(this, other); }
    /** Matrix multiplication. */
    public NpcArray matmul(NpcArray other) { return Npc.matmul(this, other); }
    /** Trace (sum of diagonal). */
    public NpcArray trace() { return Npc.trace(this); }
    /** Determinant. */
    public NpcArray det() { return Npc.det(this); }
    /** Matrix inverse. */
    public NpcArray inv() { return Npc.inv(this); }
    /** Conjugate (Hermitian) transpose. */
    public NpcArray conjTranspose() { return Npc.conjTranspose(this); }

    // -- Comparison --
    /** Element-wise equality. */
    public NpcArray equal(NpcArray other) { return Npc.equal(this, other); }
    /** Element-wise inequality. */
    public NpcArray notEqual(NpcArray other) { return Npc.notEqual(this, other); }
    /** Element-wise greater-than. */
    public NpcArray greater(NpcArray other) { return Npc.greater(this, other); }
    /** Element-wise greater-or-equal. */
    public NpcArray greaterEqual(NpcArray other) { return Npc.greaterEqual(this, other); }
    /** Element-wise less-than. */
    public NpcArray less(NpcArray other) { return Npc.less(this, other); }
    /** Element-wise less-or-equal. */
    public NpcArray lessEqual(NpcArray other) { return Npc.lessEqual(this, other); }

    // -- Clip --
    /** Clip to range [lo, hi]. */
    public NpcArray clip(double lo, double hi) { return Npc.clip(this, lo, hi); }
    public NpcArray clip(NpcArray lo, NpcArray hi) { return Npc.clip(this, lo, hi); }

    // -- NaN utilities --
    /** Test for NaN. */
    public NpcArray isnan() { return Npc.isnan(this); }
    /** Test for infinity. */
    public NpcArray isinf() { return Npc.isinf(this); }
    /** Test for finiteness. */
    public NpcArray isfinite() { return Npc.isfinite(this); }
    /** Replace NaN/inf with finite values. */
    public NpcArray nanToNum() { return Npc.nanToNum(this); }

    // -- Sorting --
    /** Sort along first axis. */
    public NpcArray sort() { return Npc.sort(this); }
    /** Indices that would sort. */
    public NpcArray argsort() { return Npc.argsort(this); }
    public NpcArray argsort(int axis) { return Npc.argsort(this, axis); }
    public NpcArray argsort(int axis, String kind) { return Npc.argsort(this, axis, kind); }

    // -- Misc --
    /** Extract diagonal. */
    public NpcArray diag() { return Npc.diag(this); }
    public NpcArray diag(int k) { return Npc.diag(this, k); }
    /** Trim leading/trailing zeros. */
    public NpcArray trimZeros() { return Npc.trimZeros(this); }
    public NpcArray trimZeros(String trim) { return Npc.trimZeros(this, trim); }
    /** Element-wise floating-point modulo. */
    public NpcArray fmod(NpcArray divisor) { return Npc.fmod(this, divisor); }

    // ═══════════════════════════════════════════════════════════
    // I/O instance methods
    // ═══════════════════════════════════════════════════════════

    /** Save as text file. */
    public void savetxt(String filename) { Npc.savetxt(filename, this); }
    /** Save as .npy binary file. */
    public void saveNpy(String filename) { Npc.saveNpy(filename, this); }

    // ═══════════════════════════════════════════════════════════
    // Native methods
    // ═══════════════════════════════════════════════════════════

    private native long nativeCreateFromHandle(long handle);
    private native void nativeClose();
    private native boolean nativeIsClosed();
    private native int nativeNdim();
    private native int nativeSize();
    private native int[] nativeShape();
    private native int nativeShapeAxis(int axis);
    private native int[] nativeStrides();
    private native int nativeDtype();
    private native boolean nativeIsView();
    private native double nativeGetDouble(int[] indices);
    private native void nativeSetDouble(int[] indices, double value);
    private native double nativeGetDouble1D(int index);
    private native void nativeSetDouble1D(int index, double value);
    private native double nativeScalarDouble();
    private native long nativeScalarLong();
    private native int nativeScalarInt();
    private native boolean nativeScalarBoolean();
    private native double[] nativeToDoubleArray();
    private native long[] nativeToLongArray();
    private native int[] nativeToIntArray();
    private native void nativePrint();
    private native void nativeInfo();
    private native String nativeToString();
}
