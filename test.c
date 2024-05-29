#include "allocator.h"
#include "debug/debug.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("sizeof a void pointer is %lu\n", sizeof(void *));
    int *ip = notmalloc(sizeof(int) * getpagesize());
    int *ip2 = notmalloc(sizeof(int));

    *ip = 6;
    notfree(ip);
    notfree(ip2);
}