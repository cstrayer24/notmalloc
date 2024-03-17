#include "./chunk.h"
#include "../systemMem/sysmem.h"
#include "../debug/debug.h"
#include <unistd.h>
// default chunk size play around with this value to minimize truncate and expansion operations
#define DEFCHUNCKSIZE 16

NMCHUNK *chunkifyPage(page_t pg, int *numChunck)
{
    const int numPossible = getpagesize() / (sizeof(nmchunk_t) + DEFCHUNCKSIZE);
    void *currentPtr = pg + getpagesize();
#ifdef DEBUG
    printInfo("the number of possible chunks is %d", numPossible);
    printInfo("the address of the numChunks is %p");
#endif
    nmchunk_t *chainStart = NULL;
    nmchunk_t *currChunk = NULL;
    int i;
    for (i = 0; i < numPossible; i++)
    {

        nmchunk_t *newChunck = currentPtr - (sizeof(nmchunk_t) + DEFCHUNCKSIZE);
        newChunck->data = currentPtr - DEFCHUNCKSIZE;
        newChunck->isfree = true;
        newChunck->size = DEFCHUNCKSIZE;
        // handle first iteration
        if (chainStart == NULL && currChunk == NULL)
        {
            newChunck->prev = NULL;
            newChunck->next = NULL;
            chainStart = newChunck;
            currChunk = newChunck;
        }
        else
        {

            newChunck->prev = currChunk;
            currChunk->next = newChunck;
            currChunk = newChunck;
        }
#ifdef DEBUG
        printInfo("currentPtr is %u", currentPtr);
        // printInfo("iteration number is %d", i);
#endif

        if (currentPtr - (sizeof(nmchunk_t) + DEFCHUNCKSIZE) > pg)
        {
            currentPtr -= (sizeof(nmchunk_t) + DEFCHUNCKSIZE);
        }
    }
    if (numChunck != NULL)
    {

        *numChunck = i;
    }

    return chainStart;
}