#include "fl.h"
#include "sysmem.h"
#include "debug/debug.h"
void init_fl(fl_t *fl)
{

    nmchunk_t *chunk = chunkifyPage(getPage(), &fl->numChunks);
    fl->start = chunk;
    nmchunk_t *temp = fl->start;
    for (int i = 0; i < fl->numChunks - 1; i++)
    {

        temp = temp->next;
    }
    fl->end = temp;
    fl->maxSize = DEFchunkSIZE;
    fl->minSize = DEFchunkSIZE;
}

inline bool fl_isEmpty(fl_t *fl)
{

    return (fl->numChunks == 0 || (fl->minSize == 0 && fl->maxSize == 0));
}