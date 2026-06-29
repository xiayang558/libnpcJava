package libnpc;

/**
 * Result of LU decomposition with partial pivoting.
 *
 * <p>For a square matrix A of shape (n, n), the LU decomposition yields
 * P @ A = L @ U, where:</p>
 * <ul>
 *   <li>{@code P} — (n, n) permutation matrix</li>
 *   <li>{@code L} — (n, n) unit lower triangular matrix (ones on diagonal)</li>
 *   <li>{@code U} — (n, n) upper triangular matrix</li>
 * </ul>
 *
 * @see Npc#lu(NpcArray)
 */
public final class LuResult implements AutoCloseable {
    public final NpcArray P;
    public final NpcArray L;
    public final NpcArray U;

    public LuResult(NpcArray P, NpcArray L, NpcArray U) {
        this.P = P;
        this.L = L;
        this.U = U;
    }

    @Override
    public void close() {
        if (P != null) P.close();
        if (L != null) L.close();
        if (U != null) U.close();
    }
}
