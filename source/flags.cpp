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
    g_flags[HAVE_HURRICANE_SPIN] = dComIfGs_isEventBit(0x0B20);
    g_flags[ENDLESS_NIGHT] = dComIfGs_isEventBit(0x0A02);
    g_flags[ORCA_INTRO_CUTSCENE] = dComIfGs_isEventBit(0x0640);
    g_flags[PUPPET_GANON_CUTSCENE] = dComIfGs_isEventBit(0x3B02);
    g_flags[MEETING_KORL_CUTSCENE] = dComIfGs_isEventBit(0x0F80);
    g_flags[COURTYARD_CUTSCENE] = dComIfGs_isEventBit(0x3804);
    g_flags[LEAVING_OUTSET_CUTSCENE] = dComIfGs_isEventBit(0x2401);
    g_flags[TETRA_SPOILS_BAG_TEXT] = dComIfGs_isEventBit(0x0808);
    g_flags[BARREL_LAUNCH_CUTSCENE] = dComIfGs_isEventBit(0x0801);
    g_flags[ENTER_KORL_FIRST_TIME] = dComIfGs_isEventBit(0x2A08);
    g_flags[POST_FF1_KORL_CUTSCENE] = dComIfGs_isEventBit(0x0F80);

}
