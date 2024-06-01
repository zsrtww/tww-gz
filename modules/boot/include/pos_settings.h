#pragma once

#include "libtww/include/dolphin/mtx/vec.h"

enum SpritesIndex {
    MENU_INDEX,
    FIFO_SPR_INDEX,

    SPRITES_AMNT,
};

extern Vec2 g_spriteOffsets[SPRITES_AMNT];

void GZ_PosSettings_initDefaults();
