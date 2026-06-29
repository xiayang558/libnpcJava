package libnpc;

/**
 * Result of QR decomposition.
 *
 * <p>For a matrix A of shape (m, n), the QR decomposition is A = Q @ R, where:</p>
 * <ul>
 *   <li>{@code Q} — (m, n) orthogonal matrix (Q^T @ Q = I)</li>
 *   <li>{@code R} — (n, n) upper triangular matrix</li>
 * </ul>
 *
 * @see Npc#qr(NpcArray)
 */
public final class QrResult implements AutoCloseable {
    public final NpcArray Q;
    public final NpcArray R;

    public QrResult(NpcArray Q, NpcArray R) {
        this.Q = Q;
        this.R = R;
    }

    @Override
    public void close() {
        if (Q != null) Q.close();
        if (R != null) R.close();
    }
}
