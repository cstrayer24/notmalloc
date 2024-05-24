#include "./sysmem.h"
#include "debug/debug.h"
#include <unistd.h>
#include "./align.h"

nmchunk_t *chunkifyPage(page_t pg, int *numchunk)
{

    const int numPossible = getpagesize() / (sizeof(nmchunk_t) + DEFchunkSIZE);
#ifdef DEBUG
    printInfo("numPossible is %d", numPossible);

#endif
    nmchunk_t *chainStart = chunkifyPageSN(pg, numPossible, DEFchunkSIZE);
    if (numchunk != NULL)
    {

        *numchunk = numPossible;
    }
    return chainStart;
}
nmchunk_t *chunkifyPageN(page_t pg, int numchunk, size_t *chunkSize)
{

    size_t sizeOfChunks = getpagesize() / numchunk;

    sizeOfChunks -= sizeof(nmchunk_t);
    *chunkSize = sizeOfChunks;
    nmchunk_t *chainStart = chunkifyPageSN(pg, numchunk, sizeOfChunks);

    return chainStart;
}
nmchunk_t *chunkifyPageS(page_t pg, size_t chunkSize, int *numChunks)
{

    const int chunkNum = getpagesize() / (sizeof(nmchunk_t) + align(chunkSize));

    *numChunks = chunkNum;
    nmchunk_t *chainStart = chunkifyPageSN(pg, chunkNum, align(chunkSize));

    return chainStart;
}

nmchunk_t *chunkifyPageSN(page_t pg, int numchunk, size_t size)
{

    const size_t decSize = sizeof(nmchunk_t) + size;
    void *currentPtr = pg + getpagesize();
    nmchunk_t *chainStart = NULL;
    nmchunk_t *currChunk = NULL;
    int i;
    for (i = 0; i < numchunk; i++)
    {
        // get a pointer to the chunk by subtracting the chunk size plus the decrement size then get pointer to data by subtracting the decrement size
        nmchunk_t *newchunk = currentPtr - (sizeof(nmchunk_t) + size);
        newchunk->data = currentPtr - size;
        newchunk->isfree = true;
        newchunk->size = size;
        // handle first iteration
        if (chainStart == NULL && currChunk == NULL)
        {
            newchunk->prev = NULL;
            newchunk->next = NULL;
            chainStart = newchunk;
            currChunk = newchunk;
        }
        else
        {

            newchunk->prev = currChunk;
            currChunk->next = newchunk;
            currChunk = newchunk;
        }

        if ((currentPtr - decSize) > pg)
        {
            currentPtr -= decSize;
        }
    }
    // we lose some memory try recycling or unmapping it
    printInfo("the amount of space between the pointetrs is %lu", currentPtr - pg);
    size_t unmapSpace = currentPtr - pg;

    return chainStart;
}

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
    newChunk->data = (void *)newChunk + sizeof(nmheader_t);
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
    // look in the asm for as to why the address is off by 8
    nmchunk_t *chunk = (mem - sizeof(nmheader_t) - 8);
    return chunk;
}