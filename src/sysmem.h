// these functions are here to provide a generic interface into the os allocators
#ifndef __MEMALLOCSYSMEM__
#define __MEMALLOCSYSMEM__
#ifdef __cplusplus
extern "C"
{
#endif
#include "chunk.h"
#include "smTypes.h"
    page_t getPage();
    bool sysfree(void *startPtr, size_t size);
    bool expandPage(page_t page);
#ifdef __cplusplus
}
#endif
#endif