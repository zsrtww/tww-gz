#include "flags.h"
#include "libtww/d/com/d_com_inf_game.h"

GZFlag g_flags[FLAG_AMNT] = {
    {WATCHED_FF2_HELMAROC_CUTSCENE, false, 0x3101}
};

void setEventFlag(uint16_t flag) {
    if (dComIfGs_isEventBit(flag)) {
        dComIfGs_offEventBit(flag);
    } else {
        dComIfGs_onEventBit(flag);
    }
}

void updateFlags() {
    for (int i = 0; i < FLAG_AMNT; i++) {
        g_flags[i].active = dComIfGs_isEventBit(g_flags[i].flag);
    }
}