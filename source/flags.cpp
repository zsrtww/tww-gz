#include "flags.h"
#include "libtww/d/com/d_com_inf_game.h"

GZFlag g_flags[FLAG_AMNT] = {
    {WATCHED_FF2_HELMAROC_CUTSCENE, 0x3101}
};

void setEventFlag(uint16_t flag) {
    if (dComIfGs_isEventBit(flag)) {
        dComIfGs_offEventBit(flag);
    } else {
        dComIfGs_onEventBit(flag);
    }
}