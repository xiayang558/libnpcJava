package libnpc;

/**
 * Result of 2-D histogram computation.
 *
 * @see Npc#histogram2d(NpcArray, NpcArray, int, int)
 */
public final class Histogram2DResult implements AutoCloseable {
    /** 2-D histogram counts (matrix). */
    public final NpcArray H;
    /** Bin edges for x-axis. */
    public final NpcArray xEdges;
    /** Bin edges for y-axis. */
    public final NpcArray yEdges;

    public Histogram2DResult(NpcArray H, NpcArray xEdges, NpcArray yEdges) {
        this.H = H;
        this.xEdges = xEdges;
        this.yEdges = yEdges;
    }

    @Override
    public void close() {
        if (H != null) H.close();
        if (xEdges != null) xEdges.close();
        if (yEdges != null) yEdges.close();
    }
}
