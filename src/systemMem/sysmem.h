// these functions are here to provide a generic interface into the os allocators
#ifndef __MEMALLOCSYSMEM__
#define __MEMALLOCSYSMEM__
#ifdef __cplusplus
extern "C"
{
// this probably could have been a single translation unit without a directory but whatever
#endif
#include "../chunk/chunk.h"
    typedef void *page_t;
    page_t getPage();
    int sysfree(nmchunk_t *chunk);
#ifdef __cplusplus
}
#endif
#endif