package libnpc.io;

import libnpc.Npc;
import libnpc.NpcArray;

/**
 * Fluent builder for customizing text file saving options.
 *
 * <pre>{@code
 * Npc.savetxtBuilder("out.csv", data)
 *     .fmt("%.6f")
 *     .delimiter(",")
 *     .header("x,y,z")
 *     .save();
 * }</pre>
 *
 * @see Npc#savetxtBuilder(String, NpcArray)
 */
public final class SavetxtBuilder {
    private final String filename;
    private final NpcArray arr;
    private String fmt = "%g";
    private String delimiter = " ";
    private String newline = "\n";
    private String header = null;
    private String footer = null;
    private String comments = "# ";

    public SavetxtBuilder(String filename, NpcArray arr) {
        this.filename = filename;
        this.arr = arr;
    }

    public SavetxtBuilder fmt(String f) { this.fmt = f; return this; }
    public SavetxtBuilder delimiter(String d) { this.delimiter = d; return this; }
    public SavetxtBuilder newline(String nl) { this.newline = nl; return this; }
    public SavetxtBuilder header(String h) { this.header = h; return this; }
    public SavetxtBuilder footer(String f) { this.footer = f; return this; }
    public SavetxtBuilder comments(String c) { this.comments = c; return this; }

    /**
     * Execute the save operation.
     */
    public void save() {
        Npc.savetxt(filename, arr, fmt, delimiter, newline, header, footer, comments);
    }
}
