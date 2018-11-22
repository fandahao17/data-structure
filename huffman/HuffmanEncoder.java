import edu.princeton.cs.algs4.BST;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class HuffmanEncoder {
    public static Map<Character, Integer> buildFrequencyTable(char[] inputSymbols) {
        Map<Character, Integer> m = new HashMap<>();
        for (char c : inputSymbols) {
            if (m.containsKey(c)) {
                m.put(c, m.get(c) + 1);
            } else {
                m.put(c, 1);
            }
        }
        return m;
    }

    public static void encode(String fileName) {
        String toFileName = fileName + ".huff";
        char [] inputSymbols = FileUtils.readFile(fileName);
        int symbolCount = inputSymbols.length;
        Map<Character, Integer> frequencyTable = buildFrequencyTable(inputSymbols);
        BinaryTrie decodingTrie = new BinaryTrie(frequencyTable);
        ObjectWriter ow = new ObjectWriter(toFileName);
        // TODO: write the number of symbols to the .huf file
        Map<Character, BitSequence> encodingMap = decodingTrie.buildLookupTable();
        List<BitSequence> bitList = new LinkedList<>();
        for (char c : inputSymbols) {
            ((LinkedList<BitSequence>) bitList).addLast(encodingMap.get(c));
        }
        BitSequence hugeBits = BitSequence.assemble(bitList);
        ow.writeObject(decodingTrie);
        ow.writeObject(symbolCount);
        ow.writeObject(hugeBits);
    }
}
