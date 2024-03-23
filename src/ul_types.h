#ifndef UL_TYPES
#define UL_TYPES
#include <stdbool.h>
#include "chunk.h"
typedef struct UL
{
    int numChunks;
    nmchunk_t *start;
    nmchunk_t *end;
} ul_t;

#endif