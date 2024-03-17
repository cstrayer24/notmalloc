#include "./sysmem.h"
#include <sys/mman.h>
int sysfree(nmchunk_t *chunk)
{

    if (chunk == NULL)
    {

        return -1;
    }
    if (!chunk->isfree)
    {

        return -1;
    }

    if (munmap(chunk, sizeof(nmchunk_t) + chunk->size) == -1)
    {

        return -1;
    }

    return 0;
}