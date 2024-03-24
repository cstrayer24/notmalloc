#include "./allocator.h"
#include "./debug/debug.h"
#include "./sysmem.h"
#include "./align.h"
#include "./chunk.h"
#include "fl.h"

static fl_t fl;
static bool flHasBeenInit = false;
void *notmalloc(size_t size)
{

        const size_t alignedSize = align(size);
    // hack alert
    if (!flHasBeenInit)
    {
        init_fl(&fl);
        flHasBeenInit = true;
    }
    if (fl_isEmpty(&fl))
    {
        // just stick 10 in here and change it when the inuse list gets implemented
        fl.start = chunkifyPageN(getPage(), 10, alignedSize);
        fl.maxSize = alignedSize;
        fl.minSize = alignedSize;
        fl.curr = fl.start;
        nmchunk_t *temp = fl.curr;
        for (int i = 0; i < 10; i++)
        {

            temp = temp->next;
        }
        fl.end = temp;
    }
}