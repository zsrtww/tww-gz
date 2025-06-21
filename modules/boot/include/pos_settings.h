#pragma once

#include "libtww/include/dolphin/mtx/vec.h"

enum SpritesIndex {
    SPR_MENU_INDEX,
    SPR_FIFO_INDEX,
    SPR_DEBUG_INFO_INDEX,
    SPR_TIME_DISP_INDEX,
    SPR_VIEWER_INDEX,
    SPR_COUNT_INDEX,
    SPR_ZH_INFO_INDEX,
    SPR_SPRITES_STAGE_INFO_INDEX,
    SPR_ROLL_CLIP_INDEX,

    SPRITES_AMNT,
};

extern Vec2 g_spriteOffsets[SPRITES_AMNT];

void GZ_PosSettings_initDefaults();
