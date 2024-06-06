#ifndef OSCACHE_H
#define OSCACHE_H

#include "../gctypes.h"

extern "C" {
void DCFlushRange(void* startAddr, u32 nBytes);
void DCStoreRangeNoSync(void* start, u32 nBytes);
void ICInvalidateRange(void* startAddr, u32 nBytes);
}

#endif /* OSCACHE_H */
