#pragma once


#include "../mtx/mtx.h"
#include "gcn_c/include/gfx.h"
#include "../gctypes.h"

struct GXFogAdjTable {
    u16 r[10];
};

extern "C" {
#define GFX_FIFO(T) (*(volatile T*)0xCC008000)

inline void GXPosition3float(float x, float y, float z) {
    GFX_FIFO(float) = x;
    GFX_FIFO(float) = y;
    GFX_FIFO(float) = z;
}

inline void GXColor1uint32_t(u32 c) {
    GFX_FIFO(u32) = c;
}

inline void GXTexCoord2float(float s, float t) {
    GFX_FIFO(float) = s;
    GFX_FIFO(float) = t;
}

inline void GXTexCoord2uint8_t(u8 s, u8 t) {
    GFX_FIFO(u8) = s;
    GFX_FIFO(u8) = t;
}

inline void GXPosition2uint16_t(u16 x, u16 y) {
    GFX_FIFO(u16) = x;
    GFX_FIFO(u16) = y;
}

inline void GXPosition1x8(u8 x) {
    GFX_FIFO(u8) = x;
}

inline void GXEnd() {}
};