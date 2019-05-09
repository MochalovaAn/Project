package com.example.project;

import java.util.*;

public class Arifm {
    static final int BITS = 30;
    static final int HIGHEST_BIT = 1 << (BITS - 1);
    static final int MASK = (1 << BITS) - 1;
    static final int END = 256;
    static long low, high;
    static int additionalBits;
    static long value;
    static int[] cumFreq;
    static int[] bits;
    static int bitsPos;
    static List<Boolean> encodedBits;
    static List<Integer> decodedBytes;


    static public int encode(String file) {
        int[] a = new int[file.length()];
        char[] data = file.toCharArray();
        for (int i = 0; i < file.length(); i++)
            a[i] = (int) data[i];
        cumFreq = createFenwickTree(END + 1);
        encodedBits = new ArrayList<>();
        low = 0;
        high = (1 << BITS) - 1;
        additionalBits = 0;
        for (int c : a)
            encodeSymbol(c);
        encodeSymbol(END);
        outputBit(true);
        int[] bits = new int[encodedBits.size()];
        for (int i = 0; i < bits.length; i++)
            bits[i] = encodedBits.get(i) ? 1 : 0;
        return (int)(100 * bits.length / file.length());
    }

    static void encodeSymbol(int c) {
        long range = high - low + 1;
        high = low + range * sum(cumFreq, c) / sum(cumFreq, END) - 1;
        low = low + range * sum(cumFreq, c - 1) / sum(cumFreq, END);
        while (true) {
            if ((low & HIGHEST_BIT) == (high & HIGHEST_BIT)) {
                outputBit((high & HIGHEST_BIT) != 0);
                low = (low << 1) & MASK;
                high = ((high << 1) + 1) & MASK;
            } else if (high - low < sum(cumFreq, END)) {
                low = (low - (1 << (BITS - 2))) << 1;
                high = ((high - (1 << (BITS - 2))) << 1) + 1;
                ++additionalBits;
            } else {
                break;
            }
        }
        increment(cumFreq, c);
    }

    static void outputBit(boolean bit) {
        encodedBits.add(bit);
        for (; additionalBits > 0; additionalBits--)
            encodedBits.add(!bit);
    }

    static public int[] decode(int[] bits) {
        cumFreq = createFenwickTree(END + 1);
        decodedBytes = new ArrayList<>();
        value = 0;
        for (bitsPos = 0; bitsPos < BITS; bitsPos++)
            value = (value << 1) + (bitsPos < bits.length ? bits[bitsPos] : 0);
        low = 0;
        high = (1 << BITS) - 1;
        while (true) {
            int c = decodeSymbol();
            if (c == END)
                break;
            decodedBytes.add(c);
            increment(cumFreq, c);
        }
        int[] bytes = new int[decodedBytes.size()];
        for (int i = 0; i < bytes.length; i++)
            bytes[i] = decodedBytes.get(i);
        return bytes;
    }

    static int decodeSymbol() {
        int cum = (int) (((value - low + 1) * sum(cumFreq, END) - 1) / (high - low + 1));
        int c = upper_bound(cumFreq, cum);
        long range = high - low + 1;
        high = low + range * sum(cumFreq, c) / sum(cumFreq, END) - 1;
        low = low + range * sum(cumFreq, c - 1) / sum(cumFreq, END);
        while (true) {
            if ((low & HIGHEST_BIT) == (high & HIGHEST_BIT)) {
                low = (low << 1) & MASK;
                high = ((high << 1) + 1) & MASK;
                int b = bitsPos < bits.length ? bits[bitsPos++] : 0;
                value = ((value << 1) + b) & MASK;
            } else if (high - low < sum(cumFreq, END)) {
                low = (low - (1 << (BITS - 2))) << 1;
                high = ((high - (1 << (BITS - 2))) << 1) + 1;
                int b = bitsPos < bits.length ? bits[bitsPos++] : 0;
                value = ((value - (1 << (BITS - 2))) << 1) + b;
            } else {
                break;
            }
        }
        return c;
    }

    // T[i] += 1
    static void increment(int[] t, int i) {
        for (; i < t.length; i |= i + 1)
            ++t[i];
    }

    // sum[0..i]
    static int sum(int[] t, int i) {
        int res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }

    // Returns min(p|sum[0,p]>sum)
    static int upper_bound(int[] t, int sum) {
        int pos = -1;
        for (int blockSize = Integer.highestOneBit(t.length); blockSize != 0; blockSize >>= 1) {
            int nextPos = pos + blockSize;
            if (nextPos < t.length && sum >= t[nextPos]) {
                sum -= t[nextPos];
                pos = nextPos;
            }
        }
        return pos + 1;
    }

    static int[] createFenwickTree(int n) {
        int[] res = new int[n];
        for (int i = 0; i < n; i++) {
            ++res[i];
            int j = i | (i + 1);
            if (j < n)
                res[j] += res[i];
        }
        return res;
    }
}