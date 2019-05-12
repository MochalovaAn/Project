package com.example.project;

public class Huffman {

    private static final byte ENCODING_TABLE_SIZE = 127;

    public static int encode(byte[] file) {//подается путь к файлу

        int k;
        Haf operator = new Haf(new HuffmanTree(file));
        k = operator.getCompressedString();
        return k;
    }

    public static void decode(){

       /* String str2 = operator.extract(str, operator.encodingArray);
    */
    };


}
