package libnpc;

/**
 * Data type enumeration for libnpc array elements.
 *
 * <p>Corresponds to the C {@code DataType} enum in libnpc. Each value maps to
 * a specific primitive type in Java:</p>
 *
 * <table>
 *   <tr><th>DType</th><th>C Type</th><th>Java Type</th><th>Bytes</th></tr>
 *   <tr><td>BOOL</td><td>bool</td><td>boolean</td><td>1</td></tr>
 *   <tr><td>INT8</td><td>int8_t</td><td>byte</td><td>1</td></tr>
 *   <tr><td>INT16</td><td>int16_t</td><td>short</td><td>2</td></tr>
 *   <tr><td>INT32</td><td>int32_t</td><td>int</td><td>4</td></tr>
 *   <tr><td>INT64</td><td>int64_t</td><td>long</td><td>8</td></tr>
 *   <tr><td>UINT8</td><td>uint8_t</td><td>byte</td><td>1</td></tr>
 *   <tr><td>UINT16</td><td>uint16_t</td><td>short</td><td>2</td></tr>
 *   <tr><td>UINT32</td><td>uint32_t</td><td>int</td><td>4</td></tr>
 *   <tr><td>UINT64</td><td>uint64_t</td><td>long</td><td>8</td></tr>
 *   <tr><td>FLOAT32</td><td>float</td><td>float</td><td>4</td></tr>
 *   <tr><td>FLOAT64</td><td>double</td><td>double</td><td>8 (default)</td></tr>
 *   <tr><td>FLOAT128</td><td>long double</td><td>—</td><td>16</td></tr>
 *   <tr><td>COMPLEX64</td><td>complex float</td><td>double[2]</td><td>8</td></tr>
 *   <tr><td>COMPLEX128</td><td>complex double</td><td>double[2]</td><td>16</td></tr>
 *   <tr><td>COMPLEX256</td><td>complex long double</td><td>double[2]</td><td>32</td></tr>
 *   <tr><td>DATETIME64</td><td>int64_t</td><td>long</td><td>8</td></tr>
 *   <tr><td>STRING</td><td>char*</td><td>String</td><td>varies</td></tr>
 *   <tr><td>UNKNOWN</td><td>—</td><td>—</td><td>—</td></tr>
 * </table>
 */
public enum DType {
    BOOL,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    FLOAT32,
    FLOAT64,
    FLOAT128,
    COMPLEX64,
    COMPLEX128,
    COMPLEX256,
    DATETIME64,
    STRING,
    UNKNOWN;

    /**
     * Returns the size of this data type in bytes.
     */
    public int sizeBytes() {
        switch (this) {
            case BOOL:       return 1;
            case INT8:       return 1;
            case INT16:      return 2;
            case INT32:      return 4;
            case INT64:      return 8;
            case UINT8:      return 1;
            case UINT16:     return 2;
            case UINT32:     return 4;
            case UINT64:     return 8;
            case FLOAT32:    return 4;
            case FLOAT64:    return 8;
            case FLOAT128:   return 16;
            case COMPLEX64:  return 8;
            case COMPLEX128: return 16;
            case COMPLEX256: return 32;
            case DATETIME64: return 8;
            default:         return 0;
        }
    }

    /**
     * Returns a human-readable name for this data type.
     */
    public String typeName() {
        switch (this) {
            case BOOL:       return "bool";
            case INT8:       return "int8";
            case INT16:      return "int16";
            case INT32:      return "int32";
            case INT64:      return "int64";
            case UINT8:      return "uint8";
            case UINT16:     return "uint16";
            case UINT32:     return "uint32";
            case UINT64:     return "uint64";
            case FLOAT32:    return "float32";
            case FLOAT64:    return "float64";
            case FLOAT128:   return "float128";
            case COMPLEX64:  return "complex64";
            case COMPLEX128: return "complex128";
            case COMPLEX256: return "complex256";
            case DATETIME64: return "datetime64";
            case STRING:     return "string";
            default:         return "unknown";
        }
    }

    /**
     * Returns {@code true} if this is an integer type.
     */
    public boolean isInteger() {
        return this == INT8 || this == INT16 || this == INT32 || this == INT64
            || this == UINT8 || this == UINT16 || this == UINT32 || this == UINT64;
    }

    /**
     * Returns {@code true} if this is a floating-point type.
     */
    public boolean isFloat() {
        return this == FLOAT32 || this == FLOAT64 || this == FLOAT128;
    }

    /**
     * Returns {@code true} if this is a complex number type.
     */
    public boolean isComplex() {
        return this == COMPLEX64 || this == COMPLEX128 || this == COMPLEX256;
    }
}
