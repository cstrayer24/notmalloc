#include "./sysmem.h"
#include <unistd.h>
#include <sys/mman.h>

page_t getPage()
{
    page_t pg;

    pg = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (pg == MAP_FAILED)
    {

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
