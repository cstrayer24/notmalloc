#ifndef __NMMEM_HEAP__
#define __NMMEM_HEAP__
#include "mem_heapTypes.h"
#include "chunk.h"

#include <string.h>
bool mh_init(heap_t *mh);
nmchunk_t *mh_getChunk(heap_t *mh, size_t size);
#endif /*__NMMEM_HEAP__*/