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
bool expandPage(page_t page)
{
    if (mmap(page, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0) == MAP_FAILED)
    {

        return 0;
    }

    return 1;
}
bool sysfree(void *startPtr, size_t size)
{
    if (munmap(startPtr, size) == -1)
    {
        perror("munmap");
        return -1;
    }
    return 0;
}