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

using namespace std;

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif


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



