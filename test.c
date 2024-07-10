#include <allocator.h>
#include <stdio.h>
int main()
{
    char *str = notmalloc(sizeof(char) * 10);
    char *str2 = notmalloc(sizeof(char) * 15);
    void *thing = notmalloc(100);
    int *it = notmalloc(sizeof(int));
    notfree(str);
    notfree(str2);
    notfree(thing);
    notfree(it);
    char *str3 = notmalloc(sizeof(char) * 10);
    void *thing2 = notmalloc(100);
    
}