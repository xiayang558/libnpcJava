package libnpc;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.AfterEach;
import static org.junit.jupiter.api.Assertions.*;

class TestNpcArray {

    private NpcArray arr;

    @AfterEach
    void cleanup() {
        if (arr != null && !arr.isClosed()) arr.close();
    }

    @Test
    void testZeros1D() {
        arr = Npc.zeros(5);
        assertEquals(1, arr.ndim());
        assertEquals(5, arr.size());
        assertEquals(5, arr.shape(0));
        assertEquals(DType.FLOAT64, arr.dtype());
        assertArrayEquals(new int[]{5}, arr.shape());
        for (int i = 0; i < 5; i++) {
            assertEquals(0.0, arr.getDouble(i), 1e-12);
        }
    }

    @Test
    void testOnes2D() {
        arr = Npc.ones(3, 4);
        assertEquals(2, arr.ndim());
        assertEquals(12, arr.size());
        assertEquals(3, arr.shape(0));
        assertEquals(4, arr.shape(1));
        assertArrayEquals(new int[]{3, 4}, arr.shape());
        assertEquals(1.0, arr.getDouble(0, 0), 1e-12);
    }

    @Test
    void testFull() {
        arr = Npc.full(new int[]{2, 3}, 42.0);
        assertEquals(2, arr.ndim());
        assertEquals(42.0, arr.getDouble(0, 0), 1e-12);
        assertEquals(42.0, arr.getDouble(1, 2), 1e-12);
    }

    @Test
    void testArange() {
        arr = Npc.arange(0, 5);
        assertEquals(1, arr.ndim());
        for (int i = 0; i < 5; i++) {
            assertEquals((double) i, arr.getDouble(i), 1e-12);
        }
    }

    @Test
    void testArangeWithStep() {
        arr = Npc.arange(0, 10, 2);
        assertEquals(5, arr.size());
        assertEquals(0.0, arr.getDouble(0), 1e-12);
        assertEquals(8.0, arr.getDouble(4), 1e-12);
    }

    @Test
    void testEye() {
        arr = Npc.eye(3);
        assertEquals(2, arr.ndim());
        assertEquals(1.0, arr.getDouble(0, 0), 1e-12);
        assertEquals(1.0, arr.getDouble(1, 1), 1e-12);
        assertEquals(1.0, arr.getDouble(2, 2), 1e-12);
        assertEquals(0.0, arr.getDouble(0, 1), 1e-12);
    }

    @Test
    void testIdentity() {
        arr = Npc.identity(4);
        assertEquals(2, arr.ndim());
        assertEquals(4, arr.shape(0));
        assertEquals(4, arr.shape(1));
    }

    @Test
    void testLinspace() {
        arr = Npc.linspace(0, 1, 5);
        assertEquals(5, arr.size());
        assertEquals(0.0, arr.getDouble(0), 1e-12);
        assertEquals(1.0, arr.getDouble(4), 1e-12);
        assertEquals(0.5, arr.getDouble(2), 1e-12);
    }

    @Test
    void testCopy() {
        NpcArray orig = Npc.ones(3);
        arr = Npc.copy(orig);
        assertEquals(orig.ndim(), arr.ndim());
        assertEquals(orig.shape(0), arr.shape(0));
        orig.close();
    }

    @Test
    void testAstype() {
        NpcArray orig = Npc.ones(3);
        arr = Npc.astype(orig, DType.INT32);
        assertEquals(DType.INT32, arr.dtype());
        assertEquals(1, arr.getDouble(0), 1e-12);
        orig.close();
    }

    @Test
    void testScalarAccess() {
        try (NpcArray a = Npc.zeros(1)) {
            assertEquals(0.0, a.scalarDouble(), 1e-12);
        }
        try (NpcArray b = Npc.ones(2, 2)) {
            assertEquals(1.0, b.scalarDouble(), 1e-12);
        }
    }

    @Test
    void testToDoubleArray() {
        arr = Npc.ones(4);
        double[] data = arr.toDoubleArray();
        assertEquals(4, data.length);
        for (double v : data) assertEquals(1.0, v, 1e-12);
    }

    @Test
    void testSetAndGetElement() {
        arr = Npc.zeros(5);
        arr.setDouble(2, 99.0);
        assertEquals(99.0, arr.getDouble(2), 1e-12);
        assertEquals(0.0, arr.getDouble(0), 1e-12);
    }

    @Test
    void testMultiDimAccess() {
        arr = Npc.zeros(3, 4);
        arr.setDouble(42.0, 1, 2);
        assertEquals(42.0, arr.getDouble(1, 2), 1e-12);
        assertEquals(0.0, arr.getDouble(0, 0), 1e-12);
    }

    @Test
    void testStrides() {
        arr = Npc.ones(3, 4);
        int[] s = arr.strides();
        assertNotNull(s);
        assertEquals(2, s.length);
    }

    @Test
    void testToString() {
        arr = Npc.ones(2, 3);
        String s = arr.toString();
        assertTrue(s.contains("Array") || s.contains("NpcArray"));
    }
}
