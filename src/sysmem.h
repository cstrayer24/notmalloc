// these functions are here to provide a generic interface into the os allocators
#ifndef __MEMALLOCSYSMEM__
#define __MEMALLOCSYSMEM__
#ifdef __cplusplus
extern "C"
{
#endif
#include "./chunk.h"
#include "smTypes.h"
    // typedef void *page_t;
    page_t getPage();
    int sysfree(nmchunk_t *chunk);
#ifdef __cplusplus
}
#endif
#endif