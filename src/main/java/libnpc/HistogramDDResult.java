package libnpc;

/**
 * Result of N-D histogram computation.
 *
 * @see Npc#histogramdd(NpcArray, NpcArray)
 */
public final class HistogramDDResult implements AutoCloseable {
    /** N-D histogram counts. */
    public final NpcArray hist;
    /** Bin edges for each dimension. */
    public final NpcArray[] edges;

    public HistogramDDResult(NpcArray hist, NpcArray[] edges) {
        this.hist = hist;
        this.edges = edges;
    }

    @Override
    public void close() {
        if (hist != null) hist.close();
        if (edges != null) {
            for (NpcArray e : edges) {
                if (e != null) e.close();
            }
        }
    }
}
