#include "pos_settings.h"
#include "rels/include/defines.h"

KEEP_VAR Vec2 g_spriteOffsets[SPRITES_AMNT];

KEEP_FUNC void GZ_PosSettings_initDefaults() {
    g_spriteOffsets[SPR_MENU_INDEX] = {10.f, 60.f};
    g_spriteOffsets[SPR_FIFO_INDEX] = {5.0f, 440.f};
    g_spriteOffsets[SPR_VIEWER_INDEX] = {220.f, 380.f};
    g_spriteOffsets[SPR_COUNT_INDEX] = {200.f, 350.f};
    g_spriteOffsets[SPR_DEBUG_INFO_INDEX] = {450.0f, 200.f};
    g_spriteOffsets[SPR_TIME_DISP_INDEX] = {450.0f, 320.f};
    g_spriteOffsets[SPR_ZH_INFO_INDEX] = {450.0f, 400.f};
}
