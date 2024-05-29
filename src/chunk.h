#ifndef __NMchunk__
#define __NMchunk__
#ifdef __cplusplus
extern "C"
{
#endif              /*__cplusplus*/
#include <string.h> //for size_t
#include <stdbool.h>
#include <stddef.h>
#include "sysmem.h"
#include "chunkTypes.h"
#include "smTypes.h"
#define DEFchunkSIZE 2048
#define NMCHUNK struct nmchunk
    nmchunk_t *subDivideChunk(nmchunk_t *chunk);
    nmchunk_t *getHeader(void *rawPtr);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*__NMchunk__*/