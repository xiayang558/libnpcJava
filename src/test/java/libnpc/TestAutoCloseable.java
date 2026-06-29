package libnpc;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class TestAutoCloseable {

    @Test
    void testTryWithResources() {
        NpcArray a;
        try (NpcArray arr = Npc.ones(3)) {
            a = arr;
            assertFalse(arr.isClosed());
            assertEquals(3, arr.size());
        }
        assertTrue(a.isClosed());
    }

    @Test
    void testCloseIdempotent() {
        NpcArray a = Npc.zeros(5);
        assertFalse(a.isClosed());
        a.close();
        assertTrue(a.isClosed());
        a.close(); // second close should be safe
        assertTrue(a.isClosed());
    }

    @Test
    void testMultipleArrays() {
        try (NpcArray a = Npc.ones(2, 3);
             NpcArray b = Npc.zeros(2, 3)) {
            assertFalse(a.isClosed());
            assertFalse(b.isClosed());
            NpcArray c = Npc.add(a, b);
            assertFalse(c.isClosed()); // c is not in try()
            c.close();
            assertTrue(c.isClosed());
        }
    }

    @Test
    void testClosedThrowsOnAccess() {
        NpcArray a = Npc.zeros(3);
        a.close();
        assertThrows(RuntimeException.class, () -> a.ndim());
        assertThrows(RuntimeException.class, () -> a.getDouble(0));
        assertThrows(RuntimeException.class, () -> a.sum());
    }
}
