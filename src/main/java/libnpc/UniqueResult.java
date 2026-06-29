package libnpc;

/**
 * Result of {@link Npc#unique(NpcArray)}.
 *
 * <p>Decomposes the input array into its unique elements and optionally
 * tracks indices and counts:</p>
 * <ul>
 *   <li>{@code values}  — sorted unique values</li>
 *   <li>{@code indices} — first-occurrence indices (may be null)</li>
 *   <li>{@code inverse} — indices to reconstruct original (may be null)</li>
 *   <li>{@code counts}  — count of each unique value (may be null)</li>
 * </ul>
 */
public final class UniqueResult implements AutoCloseable {
    public final NpcArray values;
    public final NpcArray indices;
    public final NpcArray inverse;
    public final NpcArray counts;

    public UniqueResult(NpcArray values, NpcArray indices,
                        NpcArray inverse, NpcArray counts) {
        this.values = values;
        this.indices = indices;
        this.inverse = inverse;
        this.counts = counts;
    }

    @Override
    public void close() {
        if (values != null) values.close();
        if (indices != null) indices.close();
        if (inverse != null) inverse.close();
        if (counts != null) counts.close();
    }
}
