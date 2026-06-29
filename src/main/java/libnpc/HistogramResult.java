package libnpc;

/**
 * Result of 1-D histogram computation.
 *
 * @see Npc#histogram(NpcArray, int)
 */
public final class HistogramResult implements AutoCloseable {
    /** Histogram bin counts. */
    public final NpcArray hist;
    /** Bin edges (length = hist.length + 1). */
    public final NpcArray binEdges;

    public HistogramResult(NpcArray hist, NpcArray binEdges) {
        this.hist = hist;
        this.binEdges = binEdges;
    }

    @Override
    public void close() {
        if (hist != null) hist.close();
        if (binEdges != null) binEdges.close();
    }
}
