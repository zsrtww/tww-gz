#ifndef C_MALLOC_H
#define C_MALLOC_H

#include "../../dolphin/gctypes.h"
#include "../../addrs.h"

typedef void (*tww_free_t)(void* memory);
#define tww_free ((tww_free_t)tww_free_addr)

typedef void* (*tww_memalign_t)(s32 align, u32 size);
#define tww_memalign ((tww_memalign_t)tww_memalign_addr)

#endif /* C_MALLOC_H */
