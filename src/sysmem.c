#include "./sysmem.h"
#include "debug/debug.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

page_t getPage()
{
    page_t pg;

    pg = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (pg == MAP_FAILED)
    {

#ifdef DEBUG
        perror("mmap:");
#endif

        return NULL;
    }

    return pg;
}

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