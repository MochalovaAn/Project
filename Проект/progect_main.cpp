#include "Header.h"


int main(void) {
	const TCHAR fn[] = _T("E:\\dir\\*.jpg*");
	std::vector<tstring> fs;
	std::vector<tstring>::const_iterator i;

	get_files(fn, &fs);
	for (i = fs.begin(); i != fs.end(); ++i)
		_putts(i->c_str());


	//������������ ����
	tstring A = fs[1];
	string a;
	for (char x : A)
		a += x;
	string b = { "E:\\dir\\" };
	string c = b + a;


	long sLen;
	char * str;
	FILE *f = fopen(c.c_str(), "rb+");
	if (!f)
		printf("Error open\n"); 
	else
	{
		fseek(f, 0, SEEK_END);//��������� ������ �����
		sLen = ftell(f);//�������� ������ �����
		fseek(f, 0, SEEK_SET);//��������� ������� �����
		if (!(str = (char *)malloc((sLen + 1) * sizeof(char))))
			printf("Allocation memory error\n");
		else
		{
			fread(str, sLen, 1, f);
			str[sLen] = '\0';//���������� ������ ������ �����������!
		}
		fclose(f);

		/*if (str) {
			for(int k=0; k<sLen;k++)
			{
				cout << str[k];
			}*/
		//}//� ���� if ���������� �������� �� ��������� ����� �� ����� - ��� ��� � str
	}


	string newdata1 = haffman_encode(str);

	_gettchar();
	return 0;
}