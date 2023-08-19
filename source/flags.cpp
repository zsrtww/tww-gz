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
    g_flags[ENDLESS_NIGHT] = dComIfGs_isEventBit(0x0A02);
    g_flags[GENERAL_POST_FF1_KORL_CUTSCENE] = dComIfGs_isEventBit(0x0F80);
    g_flags[LEAVING_OUTSET_CUTSCENE] = dComIfGs_isEventBit(0x2401);
    g_flags[TETRA_SPOILS_BAG_TEXT] = dComIfGs_isEventBit(0x0808);
    g_flags[BARREL_LAUNCH_CUTSCENE] = dComIfGs_isEventBit(0x0801);
    g_flags[ENTER_KORL_FIRST_TIME] = dComIfGs_isEventBit(0x2A08);
    g_flags[POST_FF1_KORL_CUTSCENE] = dComIfGs_isEventBit(0x0F80);
    g_flags[RAISE_TOTG] = dComIfGs_isEventBit(0x1E40);
    g_flags[OPEN_DARK_PORTAL] = dComIfGs_isEventBit(0x3D02);
    g_flags[DESTROY_HYRULE_BARRIER] = dComIfGs_isEventBit(0x2C02);
    g_flags[LOAD_TOTG_AFTER_T2Z] = dComIfGs_isEventBit(0x1820);
    g_flags[OPEN_HYRULE3_WARP] = dComIfGs_isEventBit(0x2D08);
    g_flags[GET_HEROES_CLOTHES] = dComIfGs_isEventBit(0x2A80);
    g_flags[GET_SEA_CHART] = dComIfGs_isEventBit(0x0908);
    g_flags[KOOLOO_LIMPAH] = dComIfGs_isEventBit(0x2E08);
    g_flags[BALLOON_DISCOUNT] = dComIfGs_isEventBit(0x1A10);
    g_flags[TINGS_DISCOUNT] = dComIfGs_isEventBit(0x1A08);
    g_flags[HAND_ME_DOWN_TUNER] = dComIfGs_isEventBit(0x1708);
    g_flags[GOSSIP_STONE_TRIGGER] = dComIfGs_isEventBit(0x0520);

}
