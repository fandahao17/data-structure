import org.junit.Test;
import static org.junit.Assert.*;

public class TestPQ {
    @Test
    public void TestInAndDe() {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        pq.enqueue(1);
        pq.enqueue(3);
        pq.enqueue(2);
        pq.enqueue(5);
        pq.enqueue(0);
        pq.enqueue(4);
        assertEquals(0, (int)pq.dequeue());
        assertEquals(1, (int)pq.dequeue());
        assertEquals(2, (int)pq.dequeue());
        assertEquals(3, (int)pq.dequeue());
        assertEquals(4, (int)pq.dequeue());
        assertEquals(5, (int)pq.dequeue());
    }
}
