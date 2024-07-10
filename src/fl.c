#include "fl.h"
#include "sysmem.h"
#include "debug/debug.h"
#include "align.h"
#define INRANGE(mi, vl, mx) ((mi) <= (vl) && (vl) <= (mx))

void fl_init(fl_t *fl)
{
    fl->numChunks = 0;
    fl->maxSize = 0;
    fl->minSize = 0;
    fl->start = NULL;
    fl->end = NULL;
    fl->curr = NULL;
}
nmchunk_t *fl_smallestChunk(fl_t *fl)
{

    nmchunk_t *smallest = NULL;
    nmchunk_t *endptr = fl->end;
    nmchunk_t *startptr = fl->start;

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
        /* code */
    }
    return smallest;
}
nmchunk_t *fl_largestChunk(fl_t *fl)
{
    nmchunk_t *largest = NULL;
    nmchunk_t *startptr = fl->start;
    nmchunk_t *endptr = fl->end;

    while (startptr != endptr)
    {
        if (largest == NULL)
        {

            if (startptr->size >= endptr->size)
            {
                largest = startptr;
            }
            else
            {

                largest = endptr;
            }
            startptr = startptr->next;
            endptr = endptr->prev;
            continue;
        }

        if (startptr->size >= endptr->size)
        {

            largest = startptr;
        }
        else
        {
            largest = endptr;
        }

        startptr = startptr->next;
        endptr = endptr->next;
    }

    return largest;
}

nmchunk_t *fl_getChunk(fl_t *fl, size_t targetSize)
{
    size_t realTargetSize = alignForChunk(targetSize);
    while ((fl->curr->size / realTargetSize < 2) && fl->curr != NULL)
    {

        fl->curr = fl->curr->next;
    }
    nmchunk_t *newChunk = (nmchunk_t *)((void *)(fl->curr->data + fl->curr->size) - realTargetSize);
    newChunk->prev = fl->curr;
    newChunk->next = fl->curr->next;
    newChunk->size = targetSize;
    fl->curr->next = newChunk;
    fl->curr->size -= realTargetSize;
    fl->curr = newChunk;

    return newChunk;
}
void fl_insert(fl_t *fl, nmchunk_t *chunk)
{
    if (fl_isEmpty(fl))
    {
        fl->start = chunk;
        fl->end = chunk;
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
void fl_remove(fl_t *fl, nmchunk_t *chunk)
{
    chunk->next->prev = chunk->prev;
    chunk->prev->next = chunk->next;
    chunk->prev = NULL;
    chunk->next = NULL;
    chunk->isfree = false;
    fl->numChunks--;
}