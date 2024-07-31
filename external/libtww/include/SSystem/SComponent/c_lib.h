#ifndef C_LIB_H
#define C_LIB_H

#include "../../dolphin/gctypes.h"
#include "../../dolphin/mtx/mtx.h"
#include "../../addrs.h"
#include "../../defines.h"
#include "c_xyz.h"

typedef void (*tww_memset_t)(void* addr, int value, u32 size);
#define tww_memset ((tww_memset_t)tww_memset_addr)

LIBTWW_DEFINE_FUNC(MtxTrans__FfffUc,
                   void, MtxTrans, (f32, f32, f32, u8))

extern "C" Mtx* calc_mtx;

#endif /* C_LIB_H */
