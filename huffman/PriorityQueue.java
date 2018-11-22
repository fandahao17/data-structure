public class PriorityQueue <K extends Comparable<K>>{
    private class Node {
        private K item;
        private Node next;

        public Node(K item, Node next) {
            this.item = item;
            this.next = next;
        }
    }

    private Node sentinel;
    private int size;

    public PriorityQueue() {
        sentinel = new Node(null, null);
    }

    public void enqueue(K elem) {
        Node n = sentinel;
        while (n.next != null) {
            if (elem.compareTo(n.next.item) < 0) {
                break;
            }
            n = n.next;
        }
        n.next = new Node(elem, n.next);
        size += 1;
    }

    public K dequeue() {
        Node n = sentinel.next;
        sentinel.next = n.next;
        size -= 1;
        return n.item;
    }

    public int size() {
        return this.size;
    }
}
