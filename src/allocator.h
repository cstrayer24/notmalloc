#ifndef __NMALLOC__
#define __NMALLOC__
#ifdef __cplusplus
extern "C"
{
#endif
#include <strings.h> //for size_t

    void *notmalloc(size_t size);

    void notfree(void *mem);
#ifdef __cplusplus
}
#endif

#endif /*__NMALLOC__*/