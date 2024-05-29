// these functions are here to provide a generic interface into the os allocators
#ifndef __MEMALLOCSYSMEM__
#define __MEMALLOCSYSMEM__
#include <stdbool.h>
#include "smTypes.h"
page_t getPage();
bool expandPage(page_t page);
#endif