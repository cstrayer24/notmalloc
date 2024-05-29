#ifndef __NMchunk__
#define __NMchunk__
#include <string.h> //for size_t
#include <stdbool.h>
typedef struct nmchunk
{
    struct nmchunk *prev;
    size_t size;
    bool isfree;
    struct nmchunk *next;
    void *data;
} nmchunk_t;

#endif /*__NMchunk__*/