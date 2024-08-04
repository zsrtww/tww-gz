#include "menus/menu_general_flags/include/general_flags_menu.h"
#include "flags.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC GeneralFlagsMenu::GeneralFlagsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"FF2 Helmaroc Cutscene", WATCHED_FF2_HELMAROC_CUTSCENE, "Switches to animation set 2, among other things",
           true, &g_flags[WATCHED_FF2_HELMAROC_CUTSCENE]},
          {"FF1 Gossip Stone Trigger", GOSSIP_STONE_TRIGGER,
           "Sets Pirate Ship to layer 2 (Ropes 2) and Outset to layer 4", true, &g_flags[GOSSIP_STONE_TRIGGER]},
          {"Post FF1 KoRL Cutscene", GENERAL_POST_FF1_KORL_CUTSCENE,
           "Spawns KoRL, sets savewarp to Windfall and FoF to layer 2", true, &g_flags[GENERAL_POST_FF1_KORL_CUTSCENE]},
          {"Endless Night", ENDLESS_NIGHT, "Activates Endless Night, incompatible with having Nayru's Pearl", true,
           &g_flags[ENDLESS_NIGHT]},
          {"Raise TotG", RAISE_TOTG, "Raises Tower of the Gods", true, &g_flags[RAISE_TOTG]},
          {"Load TotG After T2Z", LOAD_TOTG_AFTER_T2Z, "Sets FF3 Layer and F&I Arrows at M&C", true,
           &g_flags[LOAD_TOTG_AFTER_T2Z]},
          {"Hyrule 3 Warp", OPEN_HYRULE3_WARP, "Opens golden warp to Hyrule 3", true, &g_flags[OPEN_HYRULE3_WARP]},
          {"Hyrule Barrier", DESTROY_HYRULE_BARRIER, "Barrier Skip Skip", true, &g_flags[DESTROY_HYRULE_BARRIER]},
          {"Dark Portal", OPEN_DARK_PORTAL, "Opens dark portal between FF3 and Ganon's Tower", true,
           &g_flags[OPEN_DARK_PORTAL]},
          {"Sea Chart", GET_SEA_CHART, " Gives the sea chart ", true, &g_flags[GET_SEA_CHART]},
      } {}

GeneralFlagsMenu::~GeneralFlagsMenu() {}

void GeneralFlagsMenu::draw() {
    updateFlags();

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
            case WATCHED_FF2_HELMAROC_CUTSCENE:
                setEventFlag(0x2D01);
                break;
            case GOSSIP_STONE_TRIGGER:
                setEventFlag(0x0520);
                break;
            case GENERAL_POST_FF1_KORL_CUTSCENE:
                setEventFlag(0x0F80);
                break;
            case ENDLESS_NIGHT:
                setEventFlag(0x0A02);
                break;
            case RAISE_TOTG:
                setEventFlag(0x1E40);
                break;
            case LOAD_TOTG_AFTER_T2Z:
                setEventFlag(0x1820);
                break;
            case OPEN_HYRULE3_WARP:
                setEventFlag(0x2D08);
                break;
            case DESTROY_HYRULE_BARRIER:
                setEventFlag(0x2C02);
                break;
            case OPEN_DARK_PORTAL:
                setEventFlag(0x3D02);
                break;
            case GET_SEA_CHART:
                setEventFlag(0x0908);
                break;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
