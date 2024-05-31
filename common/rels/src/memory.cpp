
#include "memory.h"

#include <cstring>

#include "libtww/include/dolphin/os/OSCache.h"

void* clearMemory(void* ptr, size_t size) {
    return memset(ptr, 0, size);
}

void clear_DC_IC_Cache(void* ptr, uint32_t size) {
    DCFlushRange(ptr, size);
    ICInvalidateRange(ptr, size);
}