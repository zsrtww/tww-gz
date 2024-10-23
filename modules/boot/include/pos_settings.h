#pragma once

#include "settings.h"
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

    SPRITES_AMNT,
};

inline Vec2 GZ_getSpriteOffset(GZSettingID sprIdx) {
    return GZStng_getData(sprIdx, Vec2{0.0f, 0.0f});
}
