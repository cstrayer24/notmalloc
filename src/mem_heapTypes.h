#ifndef __MEMHEAP_TYPES__
#define __MEMHEAP_TYPES__
#include <string.h>
typedef struct MEM_HEAP
{

    void *contents;
    size_t size;
    size_t amntFree;
    size_t amntUsed;
} heap_t;
#endif /*__MEMHEAP_TYPES__*/