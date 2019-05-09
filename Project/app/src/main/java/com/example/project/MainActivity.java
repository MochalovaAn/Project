package com.example.project;

import android.content.Intent;
import android.net.Uri;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.Button;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

import static android.Manifest.permission.READ_EXTERNAL_STORAGE;
import static android.support.v4.content.PermissionChecker.PERMISSION_GRANTED;


public class MainActivity extends AppCompatActivity {

    Button chooseFIle;
    TextView fileName;
    String fileData;
    public static final int PERMISSIONS_REQUEST = 1, CHOOSE_CODE = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        if ( ContextCompat.checkSelfPermission(this, READ_EXTERNAL_STORAGE) != PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(this,new String[]{READ_EXTERNAL_STORAGE},PERMISSIONS_REQUEST);
        }


        chooseFIle = findViewById(R.id.chooseFile);
        chooseFIle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LinearLayout ll = findViewById(R.id.serStatL);
                ll.setVisibility(View.GONE);
                ll = findViewById(R.id.barStatL);
                ll.setVisibility(View.GONE);
                ll = findViewById(R.id.arifmStatL);
                ll.setVisibility(View.GONE);
                ll = findViewById(R.id.hafStatL);
                ll.setVisibility(View.GONE);
                ll = findViewById(R.id.lzssStatL);
                ll.setVisibility(View.GONE);
                ll = findViewById(R.id.shanoStatL);
                ll.setVisibility(View.GONE);
                Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
                intent.setType("*/*");
                startActivityForResult(Intent.createChooser(intent, "Select file"), CHOOSE_CODE);

            }
        });
        Button start = findViewById(R.id.doing);
        start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RadioGroup radioGroup = findViewById(R.id.alg);
                LinearLayout ll;
                ProgressBar pb;
                switch (radioGroup.getCheckedRadioButtonId())
                {
                    case R.id.ser:
                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(RLE.encode(fileData));
                        break;
                    case R.id.bar:
                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(BarYil.encode(fileData));
                        break;
                    case R.id.haf:
                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Haf.encode(fileData));
                        break;
                    case R.id.shano:
                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Shano.encode(fileData));
                        break;
                    case R.id.arifm:
                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Arifm.encode(fileData));
                        break;
                    case R.id.lzss:
                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Lzss.encode(fileData));
                        break;
                    case R.id.all:
                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(RLE.encode(fileData));

                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(BarYil.encode(fileData));

                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Haf.encode(fileData));

                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Shano.encode(fileData));

                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Arifm.encode(fileData));

                        ll = findViewById(R.id.serStatL);
                        pb = findViewById(R.id.serStat);
                        ll.setVisibility(View.VISIBLE);
                        pb.setProgress(Lzss.encode(fileData));

                        break;
                        default:
                            Toast.makeText(MainActivity.this,"!", Toast.LENGTH_SHORT).show();

                }
            }
        });

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == CHOOSE_CODE && resultCode == -1 && data != null) {
            fileName = findViewById(R.id.fileName);
           Uri uri = data.getData();
            fileName.setText(uri.getPath());
          /*  StringBuffer filedata = new StringBuffer();
            BufferedReader reader = null;
            try {
                reader = new BufferedReader(
                        new FileReader(uri.getPath()));
                char[] buf = new char[1024];
                int numRead=0;
                while((numRead=reader.read(buf)) != -1){
                    String readData = String.valueOf(buf, 0, numRead);
                    filedata.append(readData);
                }
                reader.close();
                fileData = filedata.toString();
            } catch (Exception e) {
                e.printStackTrace();
            }*/
            try {
                StringBuffer str = new StringBuffer();
                String name = Environment.getExternalStorageDirectory().toString().substring(0,Environment.getExternalStorageDirectory().toString().length() - 2) + uri.getPath();

                // открываем поток для чтения
                BufferedReader br = new BufferedReader(new InputStreamReader(getContentResolver().openInputStream(uri)));
                String stri = "";
                char[] buf = new char[1024];
                // читаем содержимое
                int numRead = 0;
                while ((stri = br.readLine()) != null) {
                    String readData = stri;
                    fileData +=readData;
                }
                br.close();/*
                fileData = str.toString();*/
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }


        } else Toast.makeText(MainActivity.this, "FAIL", Toast.LENGTH_SHORT).show();
    }
}
