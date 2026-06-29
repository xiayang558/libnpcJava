/**
 * libnpc Java — JNI binding for the libnpc NumPy-compatible numerical computing library.
 *
 * <h2>Quick Start</h2>
 * <pre>{@code
 * import libnpc.Npc;
 * import libnpc.NpcArray;
 *
 * // Create arrays
 * try (NpcArray a = Npc.ones(3, 4);
 *      NpcArray b = Npc.full(new int[]{3, 4}, 2.0)) {
 *
 *     // Element-wise operations
 *     NpcArray c = Npc.add(a, b);
 *     NpcArray d = Npc.sqrt(c);
 *
 *     // Aggregation
 *     NpcArray s = d.sum();
 *     System.out.println("Sum: " + s.scalarDouble());
 *
 *     // Linear algebra
 *     NpcArray I = Npc.eye(3);
 *     SvdResult svd = Npc.svd(I);
 *
 *     // Arrays are auto-closed by try-with-resources
 * }
 * }</pre>
 *
 * <h2>Key Classes</h2>
 * <ul>
 *   <li>{@link NpcArray} — Core multi-dimensional array with RAII via {@link AutoCloseable}</li>
 *   <li>{@link Npc} — Static factory and computation methods (~300+ functions)</li>
 *   <li>{@link DType} — Data type enumeration (Float64, Int32, etc.)</li>
 *   <li>{@link SvdResult}, {@link QrResult}, etc. — Result structs for decompositions</li>
 * </ul>
 *
 * @version 1.0.0
 * @see <a href="https://github.com/xiayang558/libnpc">libnpc (C)</a>
 * @see <a href="https://github.com/xiayang558/libnpcJava">libnpc Java</a>
 */
package libnpc;
