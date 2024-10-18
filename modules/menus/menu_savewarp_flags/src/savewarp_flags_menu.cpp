#include "menus/menu_savewarp_flags/include/savewarp_flags_menu.h"
#include "flags.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC SavewarpFlagMenu::SavewarpFlagMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"Watched Leaving Outset Cutscene", 0,
                         "Sets savewarp location to Pirate Ship (Overworld Travelling)", true,
                         [](){return g_flags[LEAVING_OUTSET_CUTSCENE];}},
                        {"Tetra Text After Getting Spoils Bag", 1,
                         "Sets savewarp location to Pirate Ship (At Forsaken Fortress 1)", true,
                         [](){return g_flags[TETRA_SPOILS_BAG_TEXT];}},
                        {"Barrel Launch Cutscene", 2, "Sets savewarp location to Forsaken Fortress 1", true,
                         [](){return g_flags[BARREL_LAUNCH_CUTSCENE];}},
                        {"Watched Post FF1 KoRL Cutscene", 3,
                         "Spawns KoRL, sets savewarp to Windfall and FoF to layer 2", true,
                         [](){return g_flags[POST_FF1_KORL_CUTSCENE];}},
                        {"Enter KoRL First Time", 4, "Sets savewarp to most recent loaded area", true,
                         [](){return g_flags[ENTER_KORL_FIRST_TIME];}},
                    } {}

SavewarpFlagMenu::~SavewarpFlagMenu() {}

void SavewarpFlagMenu::draw() {
    updateFlags();

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case 0:
            setEventFlag(0x2401);
            break;
        case 1:
            setEventFlag(0x0808);
            break;
        case 2:
            setEventFlag(0x0801);
            break;
        case 3:
            setEventFlag(0x0F80);
            break;
        case 4:
            setEventFlag(0x2A08);
            break;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
