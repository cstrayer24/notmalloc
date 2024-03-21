#include "./align.h"
// http://dmitrysoshnikov.com/compilers/writing-a-memory-allocator/
size_t align(size_t initialSize)
{

    return (initialSize + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

size_t alignForchunk(size_t initialSize)
{
    size_t size = initialSize + sizeof(nmchunk_t);

    return align(size);
}