#ifndef C_LIB_H
#define C_LIB_H

#include "../../dolphin/gctypes.h"
#include "../../addrs.h"

typedef void (*tww_memset_t)(void* addr, int value, u32 size);
#define tww_memset ((tww_memset_t)tww_memset_addr)

#endif /* C_LIB_H */
