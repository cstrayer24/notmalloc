#include "allocator.h"
#include "sysmem.h"
#include "align.h"
#include "chunk.h"
#include "fl.h"
#include "mem_heap.h"

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

#define INRANGE(mi, vl, mx) ((mi) <= (vl) && (vl) <= (mx))

static fl_t fl;
static heap_t heap;
nmchunk_t *getHeader(void *mem)
{
    nmchunk_t *chunk = (mem - sizeof(nmchunk_t));
    return chunk;
}

void *notmalloc(size_t size)
{

    static bool fl_hasbeeninit = false;
    if (!fl_hasbeeninit)
    {
        fl_init(&fl);
        fl_hasbeeninit = true;
    }

    static bool heap_hasbeeninit = false;
    if (!heap_hasbeeninit)
    {
        mh_init(&heap);
        heap_hasbeeninit = true;
    }
    size_t alignedSize = align(size);

    nmchunk_t *newChunk;
    if (fl_isEmpty(&fl))
    {
        newChunk = mh_getChunk(&heap, alignedSize);

        return newChunk->data;
    }
    if (alignedSize == fl.minSize || fl.minSize + sizeof(word_t) == alignedSize)
    {
        newChunk = fl_smallestChunk(&fl);
        fl_remove(&fl, newChunk);
        return newChunk->data;
    }
    if (alignedSize == fl.maxSize || fl.maxSize + sizeof(word_t) == alignedSize)
    {
        newChunk = fl_largestChunk(&fl);
        fl_remove(&fl, newChunk);
        return newChunk->data;
    }

    if (INRANGE(fl.minSize, alignedSize, fl.maxSize))
    {
        newChunk = fl_getChunk(&fl, alignedSize);
        fl_remove(&fl, newChunk);
        return newChunk->data;
    }
    newChunk = mh_getChunk(&heap, alignedSize);
    return newChunk->data;
}

void notfree(void *mem)
{
    nmchunk_t *chunk = getHeader(mem);

    return fl_insert(&fl, chunk);
}
