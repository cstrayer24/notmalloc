#include "sysmem.h"
#include "../debug/debug.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
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