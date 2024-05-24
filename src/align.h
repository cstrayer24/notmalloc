#ifndef __NMALIGN__
#define __NMALIGN__
#include <stdint.h>
#include <string.h>
#include "./chunk.h"
// this is here since alignment with the architecture is generally based on the system word
typedef intptr_t word_t;
// align with the system word
size_t align(size_t initialSize);
// align for a notmalloc chunks
size_t alignForChunk(size_t initialSize);
#endif /*__NMALIGN__*/