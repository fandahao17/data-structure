public class LinkedListDeque<T>{
    private class Node {
        private T first;
        private Node next;
        private Node prev;

        public Node(T i, Node n, Node p) {
            first = i;
            next = n;
            prev = p;
        }
    }

    private Node sentinel;
    private int size;

    public LinkedListDeque() {
        sentinel = new Node(null, null, null);
        sentinel.next = sentinel;
        sentinel.prev = sentinel;
        size = 0;
    }

    public void addFirst(T item) {
        sentinel.next = new Node(item, sentinel.next, sentinel);
        sentinel.next.next.prev = sentinel.next;
        size += 1;
    }

    public void addLast(T item) {
        Node newLast = new Node(item, sentinel, sentinel.prev);
        sentinel.prev.next = newLast;
        sentinel.prev = newLast;
        size += 1;
    }

    public void addAtPos(int n, T item) {
        Node dest = sentinel.next;
        while (n-- > 0) {
            dest = dest.next;
        }
        Node newItem = new Node(item, dest, dest.prev);
        dest.prev.next = newItem;
        dest.prev = newItem;
        size += 1;
    }

    public T removeAtPos(int n) {
        Node dest = sentinel.next;
        while (n-- > 0) {
            dest = dest.next;
        }
        dest.prev.next = dest.next;
        dest.next.prev = dest.prev;
        size -= 1;
        return dest.first;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return size;
    }

    public void printDeque() {
        for (Node p = sentinel.next; p != sentinel; p = p.next) {
            System.out.print(p.first + " ");
        }
        System.out.println();
    }

    public T removeFirst() {
        if (size == 0) {
            return null;
        }
        Node p = sentinel.next;
        sentinel.next = sentinel.next.next;
        sentinel.next.prev = sentinel;
        size -= 1;
        return p.first;
    }

    public T removeLast() {
        Node p = sentinel.prev;
        sentinel.prev = sentinel.prev.prev;
        sentinel.prev.next = sentinel;
        size -= 1;
        return p.first;
    }

    public T get(int index) {
        if (index >= size) {
            return null;
        }
        Node p = sentinel.next;
        while (index-- > 0) {
            p = p.next;
        }
        return p.first;
    }

    private T getRecurHelper(Node p, int index) {
        if (index == 0) {
            return p.first;
        }
        return getRecurHelper(p.next, index - 1);
    }

    public T getRecursive(int index) {
        return getRecurHelper(sentinel.next, index);
    }
}
