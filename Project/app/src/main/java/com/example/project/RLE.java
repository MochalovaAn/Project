package com.example.project;

public class RLE {
    static public int encode(String file)
    {
        int size = file.length();
        Integer cnt;
        char smb;
        char code[] =file.toCharArray();
        String encode = "";

        smb = code[0];
        cnt = 0;

        for (int i = 0; i < size; i++) {
            if (code[i]==smb) {
                cnt++;
                if (i == size-1)
                {
                    encode = encode + cnt.toString() + smb;
                }
            }
            else {
                encode = encode + cnt.toString() + smb;
                smb = code[i];
                cnt = 1;
            }
        }
        int t = encode.length();
        int tmp = (int)(100*t/size) ;
        return tmp;
    };

    static public int decode(String zipFile){ return 0;};



}
