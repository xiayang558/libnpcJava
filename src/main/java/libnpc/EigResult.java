package libnpc;

/**
 * Result of eigenvalue decomposition.
 *
 * <p>For a square matrix A, the eigenvalue decomposition yields
 * A @ v = λ @ v, where:</p>
 * <ul>
 *   <li>{@code eigenvalues}  — array of eigenvalues λ</li>
 *   <li>{@code eigenvectors} — matrix whose columns are the eigenvectors v</li>
 * </ul>
 *
 * @see Npc#eig(NpcArray)
 */
public final class EigResult implements AutoCloseable {
    public final NpcArray eigenvalues;
    public final NpcArray eigenvectors;

    public EigResult(NpcArray eigenvalues, NpcArray eigenvectors) {
        this.eigenvalues = eigenvalues;
        this.eigenvectors = eigenvectors;
    }

    @Override
    public void close() {
        if (eigenvalues != null) eigenvalues.close();
        if (eigenvectors != null) eigenvectors.close();
    }
}
