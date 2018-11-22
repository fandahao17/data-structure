public class HuffmanDecoder {
    public static void decode(String fileName) {
        String suffix = ".huff";
        String toFileName =  fileName.substring(0, fileName.length() - suffix.length()) + ".decode";
        ObjectReader or = new ObjectReader(fileName);
        BinaryTrie decodingTrie = (BinaryTrie) or.readObject();
        int symbolCount = (int) or.readObject();
        BitSequence hugeBits = (BitSequence) or.readObject();
        char[] symbols = new char[symbolCount];
        for (int i = 0; i < symbolCount; i++) {
            Match m = decodingTrie.longestPrefixMatch(hugeBits);
            symbols[i] = m.getSymbol();
            hugeBits = hugeBits.allButFirstNBits(m.getSequence().length());
        }
        FileUtils.writeCharArray(toFileName, symbols);
    }
}
