import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

public class BinaryTrie implements Serializable {

    private class Node implements Comparable<Node> , Serializable {
        private char ch;
        private int freq;
        private Node left;
        private Node right;

        public Node(char ch, int freq, Node left, Node right) {
            this.ch = ch;
            this.freq = freq;
            this.left = left;
            this.right = right;
        }

        private boolean isLeaf() {
            return this.left == null && this.right == null;
        }
        @Override
        public int compareTo(Node o) {
            return this.freq - o.freq;
        }
    }

    private static final int R = 256;
    public Node root;

    public BinaryTrie(Map<Character, Integer> frequencyTable) {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        for (char i = 0; i < R; i++) {
            if (!frequencyTable.containsKey(i)) {
                continue;
            }
            int freq = frequencyTable.get(i);
            if (freq > 0) {
                pq.enqueue(new Node(i, freq, null, null));
            }
        }

        while (pq.size() > 1) {
            Node left = pq.dequeue();
            Node right = pq.dequeue();
            Node root = new Node('\0', left.freq + right.freq, left, right);
            pq.enqueue(root);
        }
        this.root = pq.dequeue();
    }

    public Match longestPrefixMatch(BitSequence querySequence) {
        Node n = this.root;
        int i = 0;
        while (!n.isLeaf()) {
            if (querySequence.bitAt(i) == 0) {
                n = n.left;
            } else {
                n = n.right;
            }
            i += 1;
        }
        return new Match(querySequence.firstNBits(i), n.ch);
    }

    private void buildLookupTable(Map<Character, BitSequence> dest, Node root, BitSequence prefix) {
        if (root.isLeaf()) {
            dest.put(root.ch, prefix);
            return;
        }
        buildLookupTable(dest, root.left, prefix.appended(0));
        buildLookupTable(dest, root.right, prefix.appended(1));
    }

    public Map<Character, BitSequence> buildLookupTable() {
        Map<Character, BitSequence> m = new HashMap<>();
        buildLookupTable(m, this.root, new BitSequence());
        return m;
    }
}