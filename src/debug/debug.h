#ifndef _MEMALLOCDEBUG_
#define _MEMALLOCDEBUG_
#include "../fl.h"
void printErr(const char *message, ...);
void printInfo(const char *msgFormat, ...);
void printFL(fl_t *fl);
void printChunk(nmchunk_t *chunk);
#endif /*_MEMALLOCDEBUG_*/