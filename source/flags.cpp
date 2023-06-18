#include "flags.h"
#include "libtww/d/com/d_com_inf_game.h"

bool g_flags[FLAG_AMNT];

void setEventFlag(uint16_t flag) {
    if (dComIfGs_isEventBit(flag)) {
        dComIfGs_offEventBit(flag);
    } else {
        dComIfGs_onEventBit(flag);
    }
}

void updateFlags() {
    g_flags[WATCHED_FF2_HELMAROC_CUTSCENE] = dComIfGs_isEventBit(0x2D01);
}