#include <stdbool.h>
#ifndef __NMFL__
#define __NMFL__
#include "fl_types.h"
bool fl_isEmpty(fl_t *fl);
void init_fl(fl_t *fl);
nmchunk_t *fl_smallestChunk(fl_t *fl);
#endif /*__NMFL__*/