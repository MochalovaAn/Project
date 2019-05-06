#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
 
size_t bwt_encode(char *buf_in, char *buf_out, size_t size);
size_t bwt_decode(char *buf_in, char *buf_out, size_t size);
