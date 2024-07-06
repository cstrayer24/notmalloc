#include <allocator.h>

int main()
{

    int *mint = notmalloc(sizeof(int) * 10);
    for (size_t i = 0; i < 10; i++)
    {
        mint[i] = i; /* code */
    }
}