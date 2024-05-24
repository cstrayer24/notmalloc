#include "ul.h"
#include <stdbool.h>

bool ul_isEmpty(ul_t *ul)
{

    return ul->numChunks == 0 || (ul->end == NULL && ul->start == NULL);
}
void init_ul(ul_t *ul)
{

    ul->numChunks = 0;
    ul->start = NULL;
    ul->end = NULL;
}

void insert_ul(ul_t *ul, nmchunk_t *chunk)
{
    chunk->isfree = false;
    if (ul_isEmpty(ul))
    {

        ul->start = chunk;
        ul->start->prev = NULL;
        ul->end = chunk;
        ul->numChunks++;
        return;
    }

    ul->end->next = chunk;
    chunk->prev = ul->end;
    ul->end = chunk;

    return;
}