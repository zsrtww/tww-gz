#ifndef OSCACHE_H
#define OSCACHE_H

#include <stdint.h>

extern "C" {
void DCFlushRange(void* startAddr, uint32_t nBytes);
void ICInvalidateRange(void* startAddr, uint32_t nBytes);
}

#endif /* OSCACHE_H */
