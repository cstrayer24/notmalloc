#include "allocator.h"
#include "debug/debug.h"
#include "sysmem.h"
#include "align.h"
#include "chunk.h"
#include "fl.h"

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

#define INRANGE(mi, vl, mx) ((mi) <= (vl) && (vl) <= (mx))

static struct MEM_HEAP
{

    void *contents;
    size_t size;
    size_t amntFree;
    size_t amntUsed;
} heap;
static fl_t fl;

nmchunk_t *getHeader(void *mem)
{
    nmchunk_t *chunk = (mem - sizeof(nmchunk_t));
    return chunk;
}

static void _initfl(fl_t *fl)
{
    fl->numChunks = 0;
    fl->maxSize = 0;
    fl->minSize = 0;
    fl->start = NULL;
    fl->end = NULL;
    fl->curr = NULL;
}

void initfl(fl_t *fl)
{

    static bool hasBeenInit = false;

    if (!hasBeenInit)
    {

        _initfl(fl);
        hasBeenInit = true;
    }
}
static bool _initheap(struct MEM_HEAP *heap)
{

    if ((heap->contents = getPage()) == NULL)
    {
        return false;
    }
    heap->size = getpagesize();
    heap->amntFree = heap->size;
    heap->amntUsed = 0;
    return true;
}
bool initheap(struct MEM_HEAP *heap)
{
    static bool hasBeenInitalized = 0;
    if (!hasBeenInitalized)
    {

        if (_initheap(heap))
        {
            return 1;
        }

        return 0;
    }

    return 1;
}
bool expandHeap(struct MEM_HEAP *heap, size_t targetSize)
{
    if (!expandPage(heap->contents))
    {

        return 0;
    }
    heap->size += getpagesize();
    heap->amntFree += getpagesize();
    if (heap->size < targetSize)
    {

        return expandHeap(heap, targetSize);
    }

    return 1;
}
nmchunk_t *getChunk(struct MEM_HEAP *heap, size_t size)
{

    if (heap->amntFree <= size | heap->amntFree - size <= 0)
    {
        size_t targetSize = heap->size + size;
        expandHeap(heap, targetSize);
    }
    size_t totalSize = sizeof(nmchunk_t) + size;
    nmchunk_t *chunk = (nmchunk_t *)((void *)heap->contents + heap->amntUsed);
    chunk->isfree = false;
    chunk->size = size;
    chunk->data = (void *)((void *)chunk + sizeof(nmchunk_t));
    heap->amntUsed += totalSize;
    heap->amntFree -= totalSize;
    memset(chunk->data, 0, chunk->size);

    return chunk;
}
void *notmalloc(size_t size)
{
    size_t alignedSize = align(size);
    if (!initheap(&heap))
    {
        return NULL;
    }
    nmchunk_t *newChunk;
    if (fl_isEmpty(&fl))
    {
        newChunk = getChunk(&heap, alignedSize);
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
    newChunk = getChunk(&heap, alignedSize);
    return newChunk->data;
}

void notfree(void *mem)
{
    nmchunk_t *chunk = getHeader(mem);

    return fl_insert(&fl, chunk);
}
