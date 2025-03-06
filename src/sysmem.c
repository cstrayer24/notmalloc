#include "./sysmem.h"
// check if on a unix like OS
#if defined(__APPLE__) || defined(__unix__) || defined(__linux__)
#include <unistd.h>
#include <sys/mman.h>
#endif
int getpgSize()
{
    static int pgSize = 0;
    if (pgSize)
    {
        return pgSize;
    }
// unix version
#if defined(__APPLE__) || defined(__unix__) || defined(__linux__)

    pgSize = getpagesize();
    return pgSize;
#endif
}
page_t getPage()
{
// unix version
#if defined(__APPLE__) || defined(__unix__) || defined(__linux__)
    page_t pg;

    pg = mmap(NULL, getpgSize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (pg == MAP_FAILED)
    {

        return NULL;
    }

    return pg;
#endif
}
bool expandPage(page_t page)
{
#if defined(__APPLE__) || defined(__unix__) || defined(__linux__)
    if (mmap(page, getpgSize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0) == MAP_FAILED)
    {

        return 0;
    }

    return 1;
#endif
}
