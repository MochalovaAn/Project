#include "get_files.h"
#include "Haffman.h"
#include "ирэю.h"

string HaffE = "E:\\dir\\Haff\\EC\\";
string HaffD = "E:\\dir\\Haff\\DC\\";


void HaffmanC(tstring A, int i)
{
	cout << endl << "go";
	COMPRESSED_FILE *output;
	FILE *input;
	input = fopen(get_way(A).c_str(), "rb+");
	if (input == NULL)
		fatal_error("Error open source file.\n");

	char st[50];
	string str = to_string(i);
	str = HaffE + str;
	strcpy(st, str.c_str());

	output = OpenOutputCompressedFile(st);
	if (output == NULL)
		fatal_error("Error open target file.s\n");
	CompressFile(input, output);
	CloseOutputCompressedFile(output);
	fclose(input);
}

void HaffmanD(tstring A, int i)
{
	FILE *output;
	COMPRESSED_FILE *input;

	char* st;
	st = new char[50];
	string str = to_string(i);
	str = HaffE + str;
	strcpy(st, str.c_str());

	input = OpenInputCompressedFile(st);
	if (input == NULL)
		fatal_error("Error open source file.\n");


	delete[] st;
	st = new char[50];

	string a;
	for (char x : A)
		a += x;

	str = HaffD + a;
	strcpy(st, str.c_str());
	cout << str;

	output = fopen(st, "wb");
	if (output == NULL)
		fatal_error("Error open target file.s\n");
	ExpandFile(input, output);
	CloseInputCompressedFile(input);
	fclose(output);
}


int main(void) {

	
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

	

	for (int i = 0; i < fs.size(); i++)
	{
		HaffmanC(fs[i], i+1);
		HaffmanD(fs[i], i + 1);
	}

	for (int i = 0; i < fs.size(); i++)
	{
		////////////////////////////ирэю/////////////////////
	}
	_gettchar();
	return 0;
}