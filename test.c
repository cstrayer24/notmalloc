#include <allocator.h>
#include <stdio.h>
int main()
{

    int *mint = notmalloc(sizeof(int) * 10);
    int *intarr = notcalloc(10, sizeof(int));
    for (size_t i = 0; i < 10; i++)
    {
        intarr[i] = i; /* code */
    }
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n", intarr[i]);
    }


    notfree(intarr);
}