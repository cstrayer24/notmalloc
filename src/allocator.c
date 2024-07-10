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
static nmchunk_t *getHeader(void *mem)
{
    return (nmchunk_t *)(mem - sizeof(nmchunk_t));
}
static nmchunk_t *getFittedChunk(size_t targetSize)
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
    size_t alignedSize = align(targetSize);

    nmchunk_t *newChunk;
    if (fl_isEmpty(&fl))
    {
        newChunk = mh_getChunk(&heap, alignedSize);

        return newChunk;
    }
    if (alignedSize == fl.minSize || fl.minSize + sizeof(word_t) == alignedSize)
    {
        newChunk = fl_smallestChunk(&fl);
        fl_remove(&fl, newChunk);
        return newChunk;
    }
    if (alignedSize == fl.maxSize || fl.maxSize + sizeof(word_t) == alignedSize)
    {
        newChunk = fl_largestChunk(&fl);
        fl_remove(&fl, newChunk);
        return newChunk;
    }

    if (INRANGE(fl.minSize, alignedSize, fl.maxSize))
    {
        newChunk = fl_getChunk(&fl, alignedSize);
        fl_remove(&fl, newChunk);
        return newChunk;
    }
    newChunk = mh_getChunk(&heap, alignedSize);
    return newChunk;
}
void *notmalloc(size_t size)
{
    nmchunk_t *chunk = getFittedChunk(size);
    return chunk->data;
}
void *notcalloc(size_t count, size_t size)
{
    nmchunk_t *chunk = getFittedChunk(count * size);
    memset(chunk->data, 0, chunk->size);
    return chunk->data;
}
void notfree(void *mem)
{
    nmchunk_t *chunk = getHeader(mem);

    return fl_insert(&fl, chunk);
}
