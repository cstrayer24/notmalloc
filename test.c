#include "allocator.h"
#include "debug/debug.h"
#include <stdio.h>
int main()
{

    int *ip = notmalloc(sizeof(int));
    int *ip2 = notmalloc(sizeof(int));
    printf("int pointer is %p\n", ip);
    *ip = 6;
    printf("int is %d\n", *ip);
}