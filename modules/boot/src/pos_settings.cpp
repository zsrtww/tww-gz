#include "pos_settings.h"
#include "rels/include/defines.h"

KEEP_VAR Vec2 g_spriteOffsets[SPRITES_AMNT];

KEEP_FUNC void GZ_PosSettings_initDefaults() {
    g_spriteOffsets[MENU_INDEX] = {10.f, 60.f};
    g_spriteOffsets[FIFO_SPR_INDEX] = {5.0f, 440.f};
}
