#include "./allocator.h"
#include "./debug/debug.h"
#include "./systemMem/sysmem.h"
#include "./align.h"
#include "./chunk/chunk.h"
void *notmalloc(size_t size)
{

    page_t pg = getPage();
    int numChunks;
    nmchunk_t *chunck = chunkifyPage(pg, &numChunks);
    nmchunk_t *temp = chunck;
#ifdef DEBUG
    printInfo("called align with size %lu got %lu", size, align(size));
    printInfo("numChunks is %d", numChunks);
#endif /*DEBUG*/
    for (int i = 0; i < numChunks; i++)
    {

        printInfo("on iteration %d the chunck size is %lu and its freedness is %d", i, temp->size, temp->isfree);
        temp = temp->next;
    }
}