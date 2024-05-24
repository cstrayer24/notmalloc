#include "allocator.h"
#include "debug/debug.h"
#include <stdio.h>
int main()
{

    int *ip = notmalloc(sizeof(int));
    int *ip2 = notmalloc(sizeof(int));

    *ip = 6;
    notfree(ip);
    notfree(ip2);
}