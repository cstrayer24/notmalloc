#include "./debug.h"
#include "../chunk.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
void printErr(const char *message, ...)
{

    printf("[x] %s\n", message);
}

void printInfo(const char *msgFormat, ...)
{
    va_list args;
    va_start(args, msgFormat);

    char buff[1024];
    vsnprintf(buff, sizeof(buff), msgFormat, args);
    printf("[+] %s\n", buff);
    va_end(args);
}
void printChunk(nmchunk_t *chunk)
{
    if (chunk == NULL)
    {
        printInfo("null chunk found");
        return;
    }
    printInfo("the chunks size is %lu", chunk->size);
    printInfo("the chunk %s free", chunk->isfree ? "is" : "isn't");
    printInfo("the previous pointer is %p", chunk->prev);
    printInfo("the next pointer is %p", chunk->prev);
    printInfo("the data pointer is %p", chunk->data);
}

void printFL(fl_t *fl)
{
    if (fl_isEmpty(fl))
    {
        printInfo("the free list is empty");
        return;
    }
    printInfo("the number of chunks is %d", fl->numChunks);
    printInfo("the max size is %lu and the min size is %lu", fl->maxSize, fl->minSize);
    printInfo("the start pointer is %p the curr pointer is %p and the end is %p", fl->start, fl->curr, fl->end);
    nmchunk_t *temp = fl->start;
    while (temp || temp == NULL)
    {
        printChunk(temp);
        temp = temp->next;
    }
}