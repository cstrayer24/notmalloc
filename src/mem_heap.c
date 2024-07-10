#include "mem_heap.h"
#include "sysmem.h"
#include "debug/debug.h"

#include <unistd.h>
bool mh_init(heap_t *mh)
{
    if ((mh->contents = getPage()) == NULL)
    {
        return false;
    }
    mh->size = getpagesize();
    mh->amntFree = mh->size;
    mh->amntUsed = 0;
    return true;
}

static bool mh_expand(heap_t *mh, size_t targetSize)
{

    if (!expandPage(mh->contents))
    {

        return false;
    }
    mh->size += getpagesize();
    mh->amntFree += getpagesize();
    if (mh->size < targetSize)
    {

        return mh_expand(mh, targetSize);
    }

    return true;
}

nmchunk_t *mh_getChunk(heap_t *mh, size_t size)
{
    if (mh->amntFree <= size || mh->amntFree - size <= 0)
    {
        size_t targetSize = mh->size + size;
        mh_expand(mh, targetSize);
    }
    size_t totalSize = sizeof(nmchunk_t) + size;
    nmchunk_t *chunk = (nmchunk_t *)((void *)mh->contents + mh->amntUsed);
    chunk->isfree = false;
    chunk->size = size;
    chunk->data = (void *)((void *)chunk + sizeof(nmchunk_t));
    mh->amntUsed += totalSize;
    mh->amntFree -= totalSize;
    memset(chunk->data, 0, chunk->size);

    return chunk;
}