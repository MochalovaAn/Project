#include <stdio.h>

/* ���� ������ */
#define NO_ERROR 0
#define BAD_FILE 1
#define BAD_ARGUMENT 2 

typedef unsigned char uchar;
typedef unsigned int uint;


// ��������� LZSS �����������/�������������

#define N 4096 /* ������ ���������� ������ */
#define F 128 /* ������ ���������������� ������ */
#define THRESHOLD 3 /* minimum match length */

#define N_BITS 12 /* log<2>N */
#define F_BITS 7 /* log<2>F */

int lzss_encode(char *buf_in, char *buf_out, int size);
int lzss_decode(char *buf_in, char *buf_out, int size);
