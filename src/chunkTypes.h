#ifndef __CHUNK_TYPES__
#define __CHUNK_TYPES__
#include <string.h>
// play around with packing and bitfields
typedef struct nmheader
{

    struct nmchunk *prev;
    size_t size;
    bool isfree;
    struct nmchunk *next;

} nmheader_t;
typedef struct nmchunk
{
    struct nmchunk *prev;
    size_t size;
    bool isfree;
    struct nmchunk *next;
    void *data;
} nmchunk_t;
#endif