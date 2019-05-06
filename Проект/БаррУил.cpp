#include "ÁàððÓèë.h"

typedef unsigned char byte;

byte *rotlexcmp_buf = NULL;
int rottexcmp_bufsize = 0;
 
int rotlexcmp(const void *l, const void *r)
{
    int li = *(const int*)l, ri = *(const int*)r, ac=rottexcmp_bufsize;
    while (rotlexcmp_buf[li] == rotlexcmp_buf[ri])
    {
        if (++li == rottexcmp_bufsize)
            li = 0;
        if (++ri == rottexcmp_bufsize)
            ri = 0;
        if (!--ac)
            return 0;
    }
    if (rotlexcmp_buf[li] > rotlexcmp_buf[ri])
        return 1;
    else
        return -1;
}
 
int bwt_pack(byte *buf_in, byte *buf_out, int size, int *primary_index)
{
    int *indices;
    int i;
 
    indices = (int *)malloc(size * sizeof(int));

    for(i=0; i<size; i++)
        indices[i] = i;

    rotlexcmp_buf = buf_in;
    rottexcmp_bufsize = size;
    qsort (indices, size, sizeof(int), rotlexcmp);
 
    for (i=0; i<size; i++)
        buf_out[i] = buf_in[(indices[i]+size-1)%size];
    for (i=0; i<size; i++)
    {
        if (indices[i] == 1) {
            *primary_index = i;
            free(indices);
            return 0;
        }
    }

    free(indices);
    return -1;
}
 
int bwt_unpack(byte *buf_in, byte *buf_out, int size, int primary_index)
{
    byte *F;
    int buckets[256];
    int i,j,k;
    int *indices;
 
    F = (byte *)malloc(size * sizeof(byte));
    indices = (int *)malloc(size * sizeof(int));

    for (i=0; i<256; i++)
        buckets[i] = 0;
    for (i=0; i<size; i++)
        buckets[buf_in[i]] ++;
    for (i=0,k=0; i<256; i++)
        for (j=0; j<buckets[i]; j++)
            F[k++] = i;
    
    if (k != size)
    {
        free(F);
        free(indices);
        return -1;
    }

    for (i=0,j=0; i<256; i++)
    {
        while (i>F[j] && j<size)
            j++;
        buckets[i] = j; // it will get fake values if there is no i in F, but
                        // that won't bring us any problems
    }
    for(i=0; i<size; i++)
        indices[buckets[buf_in[i]]++] = i;
    for(i=0,j=primary_index; i<size; i++)
    {
        buf_out[i] = buf_in[j];
        j=indices[j];
    }

    free(F);
    free(indices);

    return 0;
}

size_t bwt_encode(char *buf_in, char *buf_out, size_t size)
{
    return 0;
}

size_t bwt_decode(char *buf_in, char *buf_out, size_t size)
{
    return 0;
}

//int main()
//{
//    byte buf1[] = "Wikipedia";
//    int size = strlen(buf1);
//    byte buf2[size];
//    byte buf3[size];
//    int primary_index;
// 
//    bwt_encode (buf1, buf2, size, &primary_index);
//    bwt_decode (buf2, buf3, size, primary_index);
// 
//    assert (!memcmp (buf1, buf3, size));
//    printf ("Result is the same as input, that is: <%.*s>\n", size, buf3);
//    return 0;
//}