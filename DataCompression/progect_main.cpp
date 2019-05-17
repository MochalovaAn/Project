#pragma once

#include "GetFileInfo.h"
#include "AHaffman.h"
#include "ShennonFano.h"
#include "RLE.h"
#include "lzss.h"
#include "LZW.h"
#include "ArithmeticAdaptiveCoding.h"
#include "BurrowsWheelerTransform.h"
#include "AHaffman.h"

string AHaffE = "E:\\dir\\AHaff\\EC\\";
string AHaffD = "E:\\dir\\AHaff\\DC\\";

string RLEEC = "E:\\dir\\RLE\\EC\\";
string RLEDC = "E:\\dir\\RLE\\DC\\";

string ShanEC = "E:\\dir\\Shan\\EC\\";
string ShanDC = "E:\\dir\\Shan\\DC\\";

string AACEC = "E:\\dir\\AAC\\EC\\";
string AACDC = "E:\\dir\\AAC\\DC\\";

string LZSSEC = "E:\\dir\\LZSS\\EC\\";
string LZSSDC = "E:\\dir\\LZSS\\DC\\";

string LZWEC = "E:\\dir\\LZW\\EC\\";
string LZWDC = "E:\\dir\\LZW\\DC\\";

string LZHEC = "E:\\dir\\LZH\\EC\\";
string LZHDC = "E:\\dir\\LZH\\DC\\";

string BWTEC = "E:\\dir\\BWT\\EC\\";
string BWTDC = "E:\\dir\\BWT\\DC\\";

void AHaffmanC(tstring A, int i)
{
	COMPRESSED_FILE *output;
	FILE *input;
	input = fopen(get_way(A).c_str(), "rb+");
	

	char st[50];
	string str = to_string(i);
	str = AHaffE + str;
	strcpy(st, str.c_str());

	output = OpenOutputCompressedFile(st);
	
	CompressFile(input, output);
	CloseOutputCompressedFile(output);

	/////////////////////////////////////
	print_ratios(get_way(A).c_str(), st);
	/////////////////////////////////////

	fclose(input);
}
void AHaffmanD(tstring A, int i)
{
	FILE *output;
	COMPRESSED_FILE *input;

	char* st;
	st = new char[50];
	string str = to_string(i);
	str = AHaffE + str;
	strcpy(st, str.c_str());

	input = OpenInputCompressedFile(st);
	

	delete[] st;
	st = new char[50];

	string a;
	for (char x : A)
		a += x;

	str = AHaffD + a;
	strcpy(st, str.c_str());

	output = fopen(st, "wb");
	
	ExpandFile(input, output);
	CloseInputCompressedFile(input);
	fclose(output);
}

void RLEC(tstring A, int i)
{
	

	source_file = fopen(get_way(A).c_str(), "rb+");
	char st[50];
	string str = to_string(i);
	str = RLEEC + str;
	strcpy(st, str.c_str());
	dest_file = fopen(st,"wb");
	rle1encoding();

	/////////////////////////////////////
	print_ratios(get_way(A).c_str(), st);
	/////////////////////////////////////

	fclose(source_file);
	fclose(dest_file);
}
void RLED(tstring A, int i)
{
	char st1[50];
	string str = to_string(i);
	str = RLEEC + str;
	strcpy(st1, str.c_str());
	source_file = fopen(st1, "rb+");

	char st2[50];

	string a;
	for (char x : A)
		a += x;

	str = RLEDC + a;
	strcpy(st2, str.c_str());
	

	dest_file = fopen(st2, "wb");
	rle1decoding();

	fclose(source_file);
	fclose(dest_file);
}

void AACC(tstring A, int i)
{
	char st[50];
	string str = to_string(i);
	str = AACEC + str;
	strcpy(st, str.c_str());

	encode(get_way(A).c_str(), st);

	/////////////////////////////////////
	print_ratios(get_way(A).c_str(), st);
	/////////////////////////////////////
}
void AACD(tstring A, int i)
{
	char st1[50];
	string str = to_string(i);
	str = AACEC + str;
	strcpy(st1, str.c_str());
	
	char st2[50];
	string a;
	for (char x : A)
		a += x;
	str = AACDC + a;
	strcpy(st2, str.c_str());
	
	decode(st1,st2);
}

void ShanC(tstring A, int i)
{
	char st[50];
	string str = to_string(i);
	str = ShanEC + str;
	strcpy(st, str.c_str());
	
	go1(get_way(A).c_str(), st);

	/////////////////////////////////////
	print_ratios(get_way(A).c_str(), st);
	/////////////////////////////////////
}
void ShanD(tstring A, int i)
{
	char st1[50];
	string str = to_string(i);
	str = ShanEC + str;
	strcpy(st1, str.c_str());

	char st2[50];

	string a;
	for (char x : A)
		a += x;

	str = ShanDC + a;
	strcpy(st2, str.c_str());

	go1(st1, st2, false);
}

void LZSSC(tstring A, int i)
{
	infile = fopen(get_way(A).c_str(), "rb+");
	char st[50];
	string str = to_string(i);
	str = LZSSEC + str;
	strcpy(st, str.c_str());
	outfile = fopen(st, "wb");
	lzss_encode();

	/////////////////////////////////////
	print_ratios(get_way(A).c_str(), st);
	/////////////////////////////////////

	fclose(infile);
	fclose(outfile);
}
void LZSSD(tstring A, int i)
{
	char st1[50];
	string str = to_string(i);
	str = LZSSEC + str;
	strcpy(st1, str.c_str());
	infile = fopen(st1, "rb+");

	char st2[50];

	string a;
	for (char x : A)
		a += x;

	str = LZSSDC + a;
	strcpy(st2, str.c_str());


	outfile = fopen(st2, "wb");
	lzss_decode();

	fclose(infile);
	fclose(outfile);
}

void BWTC(tstring A, int i)
{}
void BWTD(tstring A, int i)
{}

void LZWC(tstring A, int i)
{
	FILE *input;
	input = fopen(get_way(A).c_str(), "rb+");
	char st[50];
	string str = to_string(i);
	str = LZWEC + str;
	strcpy(st, str.c_str());

	BFILE *output;
	output = OpenOutputBFile(st);
	
	CompressFile(input, output);

	/////////////////////////////////////
	print_ratios(get_way(A).c_str(), st);
	/////////////////////////////////////

	fclose(input);
	CloseOutputBFile(output);
}
void LZWD(tstring A, int i)
{
	BFILE *input;
	FILE *output;

	char st1[50];
	string str = to_string(i);
	str = LZWEC + str;
	strcpy(st1, str.c_str());
	input = OpenInputBFile(st1);


	char st2[50];

	string a;
	for (char x : A)
		a += x;

	str = LZWDC + a;
	strcpy(st2, str.c_str());


	output = fopen(st2, "wb");

	ExpandFile(input, output);

	fclose(output);
	CloseInputBFile(input);
}

void LZHC(tstring A, int i)
{
	infile = fopen(get_way(A).c_str(), "rb+");
	char st[50];
	string str = to_string(i);
	str = LZHEC + str;
	strcpy(st, str.c_str());
	outfile = fopen(st, "wb");
	lzss_encode();

	/////////////////////////////////////
	print_ratios(get_way(A).c_str(), st);
	/////////////////////////////////////

	fclose(infile);
	fclose(outfile);
}
void LZHD(tstring A, int i)
{
	char st1[50];
	string str = to_string(i);
	str = LZHEC + str;
	strcpy(st1, str.c_str());
	infile = fopen(st1, "rb+");

	char st2[50];

	string a;
	for (char x : A)
		a += x;

	str = LZHDC + a;
	strcpy(st2, str.c_str());


	outfile = fopen(st2, "wb");
	lzss_decode();

	fclose(infile);
	fclose(outfile);
}


int main(void)
{

	
	const TCHAR fn[] = _T("E:\\dir\\*.txt*");
	std::vector<tstring> fs;
	std::vector<tstring>::const_iterator i;

	get_files(fn, &fs);
	for (i = fs.begin(); i != fs.end(); ++i)
		_putts(i->c_str());

	
	/*long sLen = 0;
	char* file_data_c = get_string(fs[1], sLen);
	string file_data;
	strcpy(file_data_c, file_data.c_str());*/

	
	cout << endl << "    AdaptivHaffman" << endl;
	for (int i = 0; i < fs.size(); i++)
	{
		AHaffmanC(fs[i], i+1);
		AHaffmanD(fs[i], i + 1);
	}

	cout << endl<<endl<<endl << "    RLE" << endl;
	for (int i = 0; i < fs.size(); i++)
	{
		RLEC(fs[i], i + 1);
		RLED(fs[i], i + 1);
	}

	cout << endl << endl << endl << "    AAC" << endl;
	for (int i = 0; i < fs.size(); i++)
	{
		AACC(fs[i], i + 1);
		AACD(fs[i], i + 1);
	}

	cout << endl << endl << endl << "    LZSS" << endl;
	for (int i = 0; i < fs.size(); i++)
	{
		LZSSC(fs[i], i + 1);
		LZSSD(fs[i], i + 1);
	}

	cout << endl << endl << endl << "    LZW" << endl;
	for (int i = 0; i < fs.size(); i++)
	{
		LZWC(fs[i], i + 1);
		LZWD(fs[i], i + 1);
	}

	cout << endl << endl << endl << "    LZH" << endl;
	for (int i = 0; i < fs.size(); i++)
	{
		LZHC(fs[i], i + 1);
		LZHD(fs[i], i + 1);
	}
	/*cout << endl << endl << endl << "    BWT" << endl;          xyinia
	for (int i = 0; i < fs.size(); i++)
	{
		BWTC(fs[i], i + 1);
		BWTD(fs[i], i + 1);
	}*/


	/*for (int i = 0; i < fs.size(); i++)        wary long work
	{
		ShanC(fs[i], i + 1);
		ShanD(fs[i], i + 1);
	}*/
	_gettchar();
	return 0;
}