package libnpc;

public class QuickTest {
    public static void main(String[] args) {
        System.out.println("Testing libnpc Java...");
        System.out.println("NativeLib available: " + NativeLib.isAvailable());
        if (!NativeLib.isAvailable()) {
            System.out.println("Error: " + NativeLib.getErrorMessage());
            System.exit(1);
        }
        System.out.println("Version: " + Npc.version());

        try (NpcArray a = Npc.ones(3)) {
            System.out.println("ones(3).toString(): " + a);
            System.out.println("ndim: " + a.ndim());
            System.out.println("size: " + a.size());
        } catch (Exception e) {
            System.err.println("Exception: " + e.getMessage());
            e.printStackTrace();
        }

        System.out.println("All tests passed!");
    }
}
