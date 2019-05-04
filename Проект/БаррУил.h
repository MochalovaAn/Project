//#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
 
typedef unsigned char byte;
 
int bwt_pack(byte *buf_in, byte *buf_out, int size, int *primary_index);
int bwt_unpack(byte *buf_in, byte *buf_out, int size, int primary_index);
