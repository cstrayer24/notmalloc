#include "./src/allocator.h"

int main()
{

    int *mi = notmalloc(12);
    *mi = 7;
}