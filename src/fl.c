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

nmchunk_t *fl_smallestChunk(fl_t *fl)
{

    nmchunk_t *smallest = NULL;
    nmchunk_t *endptr = fl->end;
    nmchunk_t *startptr = fl->start;

    int i = 0;
    while (endptr != startptr)
    {

        if (smallest == NULL)
        {
            if (startptr->size >= endptr->size)
            {

                smallest = startptr;
            }
            else
            {

                smallest = endptr;
            }
            endptr = endptr->prev;
            startptr = startptr->next;
            i++;
            continue;
        }

        if (startptr->size >= endptr->size)
        {

            smallest = startptr;
        }
        else
        {

            smallest = endptr;
        }
        endptr = endptr->prev;
        startptr = startptr->next;
        i++;
        printInfo("i is %d", i);
        /* code */
    }
    return smallest;
}