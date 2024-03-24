// #include "./chunk.h"
#include "./sysmem.h"
#include "debug/debug.h"
#include <unistd.h>
// default chunk size play around with this value to minimize truncate and expansion operations
// #define DEFchunkSIZE 2048

nmchunk_t *chunkifyPage(page_t pg, int *numchunk)
{

    const int numPossible = getpagesize() / (sizeof(nmchunk_t) + DEFchunkSIZE);
#ifdef DEBUG
    printInfo("numPossible is %d", numPossible);

#endif
    nmchunk_t *chainStart = chunkifyPageN(pg, numPossible, DEFchunkSIZE);
    if (numchunk != NULL)
    {

        *numchunk = numPossible;
    }
    //     void *currentPtr = pg + getpagesize();
    // #ifdef DEBUG
    //     printInfo("the number of possible chunks is %d", numPossible);
    //     printInfo("the address of the numChunks is %p");
    // #endif
    //     // keep track of start and current
    //     nmchunk_t *chainStart = NULL;
    //     nmchunk_t *currChunk = NULL;
    //     int i;
    //     for (i = 0; i < numPossible; i++)
    //     {

    //         nmchunk_t *newchunk = currentPtr - (sizeof(nmchunk_t) + DEFchunkSIZE);
    //         newchunk->data = currentPtr - DEFchunkSIZE;
    //         newchunk->isfree = true;
    //         newchunk->size = DEFchunkSIZE;
    //         // handle first iteration
    //         if (chainStart == NULL && currChunk == NULL)
    //         {
    //             newchunk->prev = NULL;
    //             newchunk->next = NULL;
    //             chainStart = newchunk;
    //             currChunk = newchunk;
    //         }
    //         else
    //         {

    //             newchunk->prev = currChunk;
    //             currChunk->next = newchunk;
    //             currChunk = newchunk;
    //         }
    // #ifdef DEBUG
    //         printInfo("currentPtr is %u", currentPtr);
    //         // printInfo("iteration number is %d", i);
    // #endif

    //         if (currentPtr - (sizeof(nmchunk_t) + DEFchunkSIZE) > pg)
    //         {
    //             currentPtr -= (sizeof(nmchunk_t) + DEFchunkSIZE);
    //         }
    //     }
    //     if (numchunk != NULL)
    //     {

    //         *numchunk = i;
    //     }

    return chainStart;
}

nmchunk_t *chunkifyPageN(page_t pg, int numchunk, size_t size)
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

    // if (sysfree(pg, unmapSpace) <= -1)
    // {
    //     printErr("err for sysfree");
    // }
    return chainStart;
}