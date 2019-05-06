#include "Header.h"
#include "’аффман.h"
#include "lzss.h"
#include "Ѕарр”ил.h"
#include "Ўано.h"
#include " одированиеƒлинн—ерий.h"

BOOL get_files(LPCTSTR folder, std::vector<tstring>* files, BOOL full_path = FALSE)
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

void encode_file(const TCHAR *name)
{
    size_t len1, len2;
    char *str1 = NULL, *str2 = NULL;
    FILE *f = _wfopen(name, _T("rb+"));

    if (!f)
    {
        printf("%ls: File open error\n", name); 
        return;
    }

    if (fseek(f, 0, SEEK_END) == -1) //”казатель вконец файла
    {
        printf("%ls: File read error\n", name);
        goto e;
    }
    
    len1 = ftell(f); //ѕолучаем длинну файла
    if (len1 < 1)
    {
        printf("%ls: Empty file or file access error\n", name);
        goto e;
    }

    str1 = (char *)malloc((len1 + 1) * sizeof(char));
    str2 = (char *)malloc((len1 + 1) * sizeof(char));

    if (!str1 || !str2)
    {
        printf("%ls: Memory allocate error\n", name);
        goto e;
    }

    if ((fseek(f, 0, SEEK_SET) == -1) || //”казатель вначало файла
        (fread(str1, 1, len1, f) != len1))
    {
        printf("%ls: File read error\n", name);
        goto e;
    }

    str1[len1] = '\0'; //“ерминатор вконце строки об€зательно!

    len2 = haffman_encode(str1, str2, len1);
    if (len2)
    {
        len2 = (len2 * 100) / len1;
        printf("%ls: Haffman encode got %d%% size redution\n", name, len2);
    }
    else
        printf("%ls: Haffman encode error\n", name);

    len2 = lzss_encode(str1, str2, len1);
    if (len2)
    {
        len2 = (len2 * 100) / len1;
        printf("%ls: LZSS encode got %d%% size redution\n", name, len2);
    }
    else
        printf("%ls: LZSS encode error\n", name);

    len2 = bwt_encode(str1, str2, len1);
    if (len2)
    {
        len2 = (len2 * 100) / len1;
        printf("%ls: BurrowsЦWheeler encode got %d%% size redution\n", name, len2);
    }
    else
        printf("%ls: BurrowsЦWheeler encode error\n", name);

    len2 = shannon_encode(str1, str2, len1);
    if (len2)
    {
        len2 = (len2 * 100) / len1;
        printf("%ls: Shannon-Fano encode got %d%% size redution\n", name, len2);
    }
    else
        printf("%ls: Shannon-Fano encode error\n", name);

    len2 = series_encode(str1, str2, len1);
    if (len2)
    {
        len2 = (len2 * 100) / len1;
        printf("%ls: Series encode got %d%% size redution\n", name, len2);
    }
    else
        printf("%ls: Series encode error\n", name);

e:

    if (str1) free(str1);
    if (str2) free(str2);
    fclose(f);
}

int _tmain(int argc, _TCHAR *argv[])
{
    TCHAR *fn;
    std::vector<tstring> fs;
    std::vector<tstring>::const_iterator i;

    if (argc < 2)
    {
        printf("Usage: проект.exe dir_with_mask\n");
        return 0;
    };

    fn = argv[1];

    get_files(fn, &fs, TRUE);
    printf("Found %d files\n", fs.capacity());

    for (i = fs.begin(); i != fs.end(); ++i)
    {
        //‘ормирование пути
        //const tstring A = fs[i];
        //string a;
        ////for (char x : A)
        ////	a += x;
        //string b = ( "E:\\dir\\" );
        //string c = b + a;

        //encode_file(c.c_str());
        encode_file(i->c_str());
    }

    printf("Press ENTER to continue...\n");
    _gettchar();

    return 0;
}

