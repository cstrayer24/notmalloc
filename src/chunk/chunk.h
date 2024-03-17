#ifndef __NMCHUNCK__
#define __NMCHUNCK__
#ifdef __cplusplus
extern "C"
{
#endif              /*__cplusplus*/
#include <string.h> //for size_t
#include <stdbool.h>
#include <stddef.h>
#include "../systemMem/sysmem.h"
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
// do this to avoid typing
#define NMCHUNK struct nmchunk
    NMCHUNK *chunkifyPage(page_t pg, int *numChunck);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*__NMCHUNCK__*/