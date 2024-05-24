#include "fl.h"
#include "sysmem.h"
#include "debug/debug.h"

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
        /* code */
    }
    return smallest;
}

void fl_insert(fl_t *fl, nmchunk_t *chunk)
{
    if (fl_isEmpty(fl))
    {
        fl->start = chunk;
        fl->end = chunk;
        fl->curr = chunk;
        fl->maxSize = chunk->size;
        fl->minSize = chunk->size;
        fl->numChunks++;
        chunk->isfree = true;
        chunk->prev = NULL;
        chunk->next = NULL;
        return;
    }

    chunk->prev = fl->end;
    chunk->next = NULL;
    fl->maxSize = chunk->size > fl->maxSize ? chunk->size : fl->maxSize;
    fl->minSize = chunk->size < fl->minSize ? chunk->size : fl->minSize;
    fl->numChunks++;
    chunk->isfree = true;
    fl->end = chunk;
}