#include "allocator.h"
#include "debug/debug.h"
#include "sysmem.h"
#include "align.h"
#include "chunk.h"
#include "fl.h"
#include "ul.h"

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
static fl_t fl;
static ul_t ul;

static nmchunk_t *getBelowSizedChunk(nmchunk_t *chunk, size_t size)
{

    if (chunk->size == size)
    {

        return chunk;
    }
    nmchunk_t *newChunk = subDivideChunk(chunk);

    return getBelowSizedChunk(chunk, size);
}
static struct MEM_HEAP
{

    void *contents;
    size_t size;
    size_t amntFree;
    size_t amntUsed;
} heap = {};
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
int initheap(struct MEM_HEAP *heap)
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

    printInfo("heap contents is %p", heap->contents);

    if (heap->amntFree <= size | heap->amntFree - size <= 0)
    {
        size_t targetSize = heap->size + size;
        expandHeap(heap, targetSize);
        // expand heap
    }
    size_t totalSize = sizeof(nmchunk_t) + size;
    nmchunk_t *chunk = (nmchunk_t *)((void *)heap->contents + heap->amntUsed);
    printInfo("the new chunks pointer %p", chunk);
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
        printInfo("here");
        return NULL;
    }

    return getChunk(&heap, alignedSize)->data;
}
