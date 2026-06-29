package libnpc.io;

import libnpc.DType;
import libnpc.Npc;
import libnpc.NpcArray;

/**
 * Fluent builder for customizing text file reading options.
 *
 * <pre>{@code
 * NpcArray data = Npc.readtxtBuilder("data.csv")
 *     .delimiter(",")
 *     .skipLines(1)
 *     .dtype(DType.FLOAT64)
 *     .build();
 * }</pre>
 *
 * @see Npc#readtxtBuilder(String)
 */
public final class ReadtxtBuilder {
    private final String filename;
    private String delimiter = " ";
    private char comment = '#';
    private int skipLines = 0;
    private int maxRows = -1;
    private int ndmin = 0;
    private boolean unpack = false;
    private DType dtype = DType.FLOAT64;

    public ReadtxtBuilder(String filename) {
        this.filename = filename;
    }

    public ReadtxtBuilder delimiter(String d) { this.delimiter = d; return this; }
    public ReadtxtBuilder comment(char c) { this.comment = c; return this; }
    public ReadtxtBuilder skipLines(int n) { this.skipLines = n; return this; }
    public ReadtxtBuilder maxRows(int n) { this.maxRows = n; return this; }
    public ReadtxtBuilder ndmin(int n) { this.ndmin = n; return this; }
    public ReadtxtBuilder unpack(boolean u) { this.unpack = u; return this; }
    public ReadtxtBuilder dtype(DType dt) { this.dtype = dt; return this; }

    /**
     * Execute the read and return the resulting array.
     */
    public NpcArray build() {
        return Npc.readtxt(filename, delimiter, comment, skipLines, maxRows, ndmin, unpack, dtype);
    }
}
