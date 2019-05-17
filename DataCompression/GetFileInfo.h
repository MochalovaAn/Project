#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <codecvt>
#include <conio.h> 

using namespace std;

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

string way = "E:\\dir\\";

BOOL get_files(LPCTSTR folder, std::vector<tstring>* files,	BOOL full_path = FALSE)
 {
	WIN32_FIND_DATA inf;
	LPCTSTR pf = _tcsrchr(folder, _T('\\'));

	HANDLE  fp = FindFirstFile(folder, &inf);
	if (fp == INVALID_HANDLE_VALUE)
		return FALSE;

	files->clear();
	do {
		if (!(inf.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (full_path) { // если указан полный путь к файлу
				files->push_back(tstring(folder, pf + 1));
				files->back().append(inf.cFileName);
			}
			else
				files->push_back(inf.cFileName);
		}
	} while (FindNextFile(fp, &inf));

	FindClose(fp);
	return TRUE;
}

string get_way(tstring A)
{
	string a;
	for (char x : A)
		a += x;

	string c = way + a;
	return c;
}

char* get_string(tstring A, long& sLen)
{ 
	char * str;
	FILE *f = fopen( get_way(A).c_str(), "rb+");
	if (!f)
		printf("Error open\n");
	else
	{
		fseek(f, 0, SEEK_END);//Указатель вконец файла
		sLen = ftell(f);//Получаем длинну файла
		fseek(f, 0, SEEK_SET);//Указатель вначало файла
		if (!(str = (char *)malloc((sLen + 1) * sizeof(char))))
			printf("Allocation memory error\n");
		else
		{
			fread(str, sLen, 1, f);
			str[sLen] = '\0';//Терминатор вконце строки обязательно!
		}
		fclose(f);

		return str;
	}
}

long file_size(const char *name)
{
	long eof_ftell;
	FILE *file;

	file = fopen(name, "r");
	if (file == NULL)
		return(0L);
	fseek(file, 0L, SEEK_END);
	eof_ftell = ftell(file);
	fclose(file);
	return(eof_ftell);
}

void print_ratios(const char *input,const char *output)
{
	long input_size;
	long output_size;
	int ratio;

	input_size = file_size(input);
	if (input_size == 0)
		input_size = 1;
	output_size = file_size(output);
	ratio = 100 - (int)(output_size * 100L / input_size);
	printf("\nSource filesize:\t%ld\n", input_size);
	printf("Target Filesize:\t%ld\n", output_size);
	if (output_size == 0)
		output_size = 1;
	printf("Compression ratio:\t\t%d%%\n", ratio);
}
