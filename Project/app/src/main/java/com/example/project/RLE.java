package com.example.project;

import android.os.Environment;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class RLE {
    static public int encode(byte[] file) {
        int size;
        Integer cnt;
        byte smb;
        byte[] encode;

        smb = file[0];
        cnt = 0;

        File newData = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/download", "RLEenc.sj");


        try {
            newData.createNewFile();
            DataOutputStream tmp = new DataOutputStream( new FileOutputStream(newData));
            for (int i = 0; i < file.length; i++) {
                if (file[i]==smb) {
                    cnt++;
                    if (i == file.length-1)
                    {
                        tmp.writeInt(cnt);
                        tmp.writeByte(smb);
                    }
                }
                else {
                    tmp.writeInt(cnt);
                    tmp.writeByte(smb);
                    smb = file[i];
                    cnt = 1;
                }

            }


            size= tmp.size();
            tmp.close();
            int t = (int)(100*size/file.length) ;
            return t;

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        catch (IOException e) {
            e.printStackTrace();
        }

      return -1;
    }

    static public int decode(String zipFile){ return 0;};



}
