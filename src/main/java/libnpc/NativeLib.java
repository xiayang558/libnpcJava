package libnpc;

/**
 * Native library loader for libnpc JNI bridge.
 *
 * <p>Loads the native shared library ({@code libnpcjni.dylib} on macOS,
 * {@code libnpcjni.so} on Linux) that provides the JNI bindings to libnpc.</p>
 *
 * <p>The library is loaded automatically by the static initializer. Set the
 * {@code java.library.path} system property to point to the directory containing
 * the native library. For example:</p>
 *
 * <pre>{@code
 * java -Djava.library.path=/path/to/libnpcJava/build ...
 * }</pre>
 */
public final class NativeLib {

    private static volatile boolean loaded = false;
    private static volatile String errorMessage = null;

    static {
        try {
            System.loadLibrary("npcjni");
            loaded = true;
        } catch (UnsatisfiedLinkError e) {
            errorMessage = "Failed to load native library 'npcjni'. " +
                "Make sure the native library is built (cmake + make) and " +
                "java.library.path includes the build directory. " +
                "Error: " + e.getMessage();
        }
    }

    private NativeLib() {}

    /**
     * Returns {@code true} if the native library was loaded successfully.
     */
    public static boolean isAvailable() {
        return loaded;
    }

    /**
     * Returns the error message if library loading failed, or {@code null}.
     */
    public static String getErrorMessage() {
        return errorMessage;
    }

    /**
     * Ensures the native library is loaded. Throws if not available.
     *
     * @throws UnsatisfiedLinkError if the native library could not be loaded
     */
    public static void ensureLoaded() {
        if (!loaded) {
            throw new UnsatisfiedLinkError(errorMessage != null ? errorMessage :
                "Native library 'npcjni' is not available");
        }
    }
}
