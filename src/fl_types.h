#ifndef __NMFLTYPES__
#define __NMFLTYPES__
#include <string.h>
#include "chunk.h"
typedef struct fl
{
    int numChunks;
    size_t maxSize, minSize;
    nmchunk_t *start;
    nmchunk_t *end;
    nmchunk_t *curr;

} fl_t;
#endif /*__NMFLTYPES*/