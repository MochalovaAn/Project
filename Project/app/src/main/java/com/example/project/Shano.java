package com.example.project;

import android.os.Environment;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Map;

public class Shano {
    static int tsize; // table size (number of chars)
    static ShNone[] ptable; // table of probabilities
    static String[] codes;
    static int codesSize;

    static public int encode(byte[] file) {
        int[] freqs = new int[1]; // frequency for each char from input text
        int size = 0;
        int total = 0;
        byte ch;
        for (int i = 0; i < file.length; i++) {
            ch = file[i];
            if (ch < size) {
                freqs[ch]++;
            } else {
                int[] a = new int[ch + 1];
                size = ch + 1;
                for (int j = 0; j < freqs.length; j++)
                    a[j] = freqs[j];
                freqs = a;
                freqs[ch]++;

            }
            total++;
        }

        for (int i = 0; i < freqs.length; i++)
            if (freqs[i] != 0)
                tsize++;

        //  Building decreasing freqs table
        //
        ptable = new ShNone[tsize];
        float ftot = (float) total;

        int j = 0;
        for (int i = 0; i < size; i++) {
            if (freqs[i] != 0) {
                ptable[j].ch = (byte) i;
                ptable[j].p = (float) (freqs[i] / ftot);
                j++;
            }
        }

        Sort(0, ptable.length - 1);//otsortirovat po chastote

        //  Encoding
        //
        EncShannon(0, tsize - 1);

        //  Opening output file
        //
        /*String newData = "";
        FILE * outputFile;
        outputFile = fopen(outputFilename, "wb");
        assert (outputFile);

        //  Outputing ptable and codes
        //
        newData += tsize;
      //  printf("%i"NL, tsize);
      //  fprintf(outputFile, "%i"NL, tsize);
        for (int i = 0; i < tsize; i++) {
            newData += (ptable[i].ch + ptable[i].p + codes[ptable[i].ch]);
           // printf("%c\t%f\t%s"NL, ptable[i].ch, ptable[i].p, codes[ptable[i].ch].c_str());
            // fprintf(outputFile, "%c\t%f\t%s"NL, ptable[i].ch, ptable[i].p, codes[ptable[i].ch].c_str());
        }*/

        //  Outputing encoded text
        //

        File newData = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/download", "Sh.sj");

        try {
            DataOutputStream tmp = new DataOutputStream( new FileOutputStream(newData));
            if (codes != null)
                for (int i = 0; i < tsize; i++) {

                    if (ptable[i].ch != 0)
                    {
                        tmp.writeByte(ptable[i].ch);
                        tmp.writeUTF(codes[ptable[i].ch]);
                    }
                }


            for (int i = 0; i < file.length; i++) {
                tmp.writeUTF(codes[file[i]]);
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
        /*
        fseek(inputFile, SEEK_SET, 0);
        printf(NL);
        fprintf(outputFile, NL);
        while (fscanf(inputFile, "%c", & ch) !=EOF )
        {
            printf("%s", codes[ch].c_str());
            fprintf(outputFile, "%s", codes[ch].c_str());
        }
        printf(NL);

        //  Cleaning
        //
        codes.clear();
        delete[] ptable;

        //  Closing files
        //
        fclose(outputFile);
        fclose(inputFile);*/
    }

    ;

    static void EncShannon(int li, int ri) {
        int i, isp;
        float p;
        float pfull;
        float phalf;

        if (li == ri) {
            return;
        } else if (ri - li == 1) {
            if ((int) ptable[li].ch < codesSize)
                codes[(ptable[li].ch)]+= '0';
            else {
                int tmp = codesSize;
                codesSize = ptable[li].ch + 1;
                String[] a = new String[ptable[li].ch + 1];
                for (i = 0; i < tmp; i++)
                    a[i] = codes[i];
                codes = a;
                codes[ptable[li].ch] = codes[ptable[li].ch] + '0';

            }

            if ((int) ptable[ri].ch < codesSize)
                codes[ptable[ri].ch] += '0';
            else {
                int tmp = codesSize;
                codesSize = ptable[li].ch + 1;
                String[] a = new String[ptable[ri].ch + 1];
                for (i = 0; i < tmp; i++)
                    a[i] = codes[i];
                codes = a;
                codes[ptable[ri].ch] += '1';
            }
        } else {
            //  Calculating sum of probabilities at specified interval
            //
            pfull = 0;
            for (i = li; i <= ri; ++i) {
                pfull += ptable[i].p;
            }

            //  Searching center
            //
            p = 0;
            isp = -1; // index of split pos
            phalf = pfull * 0.5f;
            for (i = li; i <= ri; ++i) {
                if (ptable[i].ch != 0) {
                    p += ptable[i].p;
                    if (p <= phalf) {
                        //индексы переделать! Смотри сишный код
                        //забыла еще одну строшку
                        if ((int) ptable[i].ch < codesSize)
                            codes[ptable[i].ch] += '0';
                        else {
                            int tmp = codesSize;
                            codesSize = ptable[ri].ch + 1;
                            String[] a = new String[ptable[li].ch + 1];
                            for (i = 0; i < tmp; i++)
                                a[i] = codes[i];
                            codes = a;
                            codes[ptable[li].ch] += '0';
                            codesSize = ptable[li].ch + 1;

                        }
                    } else {
                        if ((int) ptable[ri].ch < codesSize)
                            codes[ptable[ri].ch] += '0';
                        else {
                            codesSize = ptable[ri].ch + 1;
                            int tmp = codesSize;
                            String[] a = new String[ptable[ri].ch + 1];
                            for (i = 0; i < tmp; i++)
                                a[i] = codes[i];
                            codes = a;
                            codes[ptable[ri].ch] += '1';

                        }
                        if (isp < 0) isp = i;
                    }
                }
            }

            if (isp < 0) isp = li + 1;

            //  Next step (recursive)
            //
            EncShannon(li, isp - 1);
            EncShannon(isp, ri);

        }

    }


    private static void Sort(int start, int end) {
        if (start >= end)
            return;
        int i = start, j = end;
        int cur = i - (i - j) / 2;
        while (i < j) {
            while (i < cur && (ptable[i].p <= ptable[cur].p)) {
                i++;
            }
            while (j > cur && (ptable[cur].p <= ptable[j].p)) {
                j--;
            }
            if (i < j) {
                ShNone temp = ptable[i];
                ptable[i] = ptable[j];
                ptable[j] = temp;
                if (i == cur)
                    cur = j;
                else if (j == cur)
                    cur = i;
            }
        }
        Sort(start, cur);
        Sort(cur + 1, end);
    }
/*

    static void Decode( const char *inputFilename, const char *outputFilename) {
        //  Opening input file
        //
        FILE * inputFile;
        inputFile = fopen(inputFilename, "r");
        assert (inputFile);

        //  Loading codes
        //
        fscanf(inputFile, "%i", & tsize );
        char ch, code[ 128];
        float p;
        int i;
        fgetc(inputFile); // skip end line
        for (i = 0; i < tsize; i++) {
            ch = fgetc(inputFile);
            fscanf(inputFile, "%f %s", & p, code );
            codes[ch] = code;
            fgetc(inputFile); // skip end line
        }
        fgetc(inputFile); // skip end line

        //  Opening output file
        //
        FILE * outputFile;
        outputFile = fopen(outputFilename, "w");
        assert (outputFile);

        //  Decoding and outputing to file
        //
        string accum = "";
        map<char, string>::iterator ci;
        while ((ch = fgetc(inputFile)) != EOF) {
            accum += ch;
            for (ci = codes.begin(); ci != codes.end(); ++ci)
                if (!strcmp(( * ci).second.c_str(),accum.c_str() ) )
            {
                accum = "";
                printf("%c", ( * ci).first );
                fprintf(outputFile, "%c", ( * ci).first );
            }
        }
        printf(NL);

        //  Cleaning
        //
        fclose(outputFile);
        fclose(inputFile);
    }
*/

}
