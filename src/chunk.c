#include "./sysmem.h"
#include "debug/debug.h"
#include <unistd.h>
#include "./align.h"

nmchunk_t *subDivideChunk(nmchunk_t *chunk)
{

    if (chunk->size % 2 != 0)
    {

        return NULL;
    }
    if (!chunk->isfree)
    {

        return NULL;
    }
    const size_t amount = alignForChunk(chunk->size / 2);

#ifdef DEBUG
    printInfo("the amount is %lu ", amount);
#endif

    nmchunk_t *newChunk = chunk->data + amount;
    newChunk->size = chunk->size / 2;
    newChunk->data = (void *)newChunk + sizeof(nmchunk_t);
    chunk->size /= 2;
    nmchunk_t *temp = chunk->next;

    chunk->next = newChunk;
    newChunk->next = temp;
    newChunk->prev = chunk;
    newChunk->size = chunk->size;

    return newChunk;
}

nmchunk_t *getHeader(void *mem)
{
    nmchunk_t *chunk = (mem - sizeof(nmchunk_t));
    return chunk;
}