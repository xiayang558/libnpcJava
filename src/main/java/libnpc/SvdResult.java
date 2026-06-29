package libnpc;

/**
 * Result of Singular Value Decomposition (SVD).
 *
 * <p>For a matrix A of shape (m, n), the SVD is A = U @ diag(s) @ Vt, where:</p>
 * <ul>
 *   <li>{@code U}  — (m, k) orthogonal matrix (k = min(m, n) for economy SVD)</li>
 *   <li>{@code s}  — (k,) singular values in descending order</li>
 *   <li>{@code Vt} — (k, n) orthogonal matrix (rows are right singular vectors)</li>
 * </ul>
 *
 * <p>All member arrays should be closed when no longer needed. Call {@link #close()}
 * to close all three at once.</p>
 *
 * @see Npc#svd(NpcArray)
 */
public final class SvdResult implements AutoCloseable {
    public final NpcArray U;
    public final NpcArray s;
    public final NpcArray Vt;

    public SvdResult(NpcArray U, NpcArray s, NpcArray Vt) {
        this.U = U;
        this.s = s;
        this.Vt = Vt;
    }

    @Override
    public void close() {
        if (U != null) U.close();
        if (s != null) s.close();
        if (Vt != null) Vt.close();
    }
}
