#include "allocator.h"
#include "debug/debug.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
    int *ip = notmalloc(sizeof(int) * getpagesize());
    int *ip2 = notmalloc(sizeof(int));

    *ip = 6;
    notfree(ip);
    notfree(ip2);
}