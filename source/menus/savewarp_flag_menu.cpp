#include "menus/flag_menu.h"
#include "menus/savewarp_flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"

#define LINE_NUM 5
Cursor SavewarpFlagMenu::cursor;
int cursorOffset;

Line lines[LINE_NUM] = {
    {"Watched Leaving Outset Cutscene", LEAVING_OUTSET_CUTSCENE, "Sets savewarp location to Pirate Ship (Overworld Travelling)", true,
        &g_flags[LEAVING_OUTSET_CUTSCENE]},
    {"Tetra Text After Getting Spoils Bag", TETRA_SPOILS_BAG_TEXT, "Sets savewarp location to Pirate Ship (At Forsaken Fortress 1)", true,
        &g_flags[TETRA_SPOILS_BAG_TEXT]},
    {"Barrel Launch Cutscene", BARREL_LAUNCH_CUTSCENE, "Sets savewarp location to Forsaken Fortress 1", true,
        &g_flags[BARREL_LAUNCH_CUTSCENE]},
    {"Watched Post FF1 KoRL Cutscene", POST_FF1_KORL_CUTSCENE, "Spawns KoRL, sets savewarp to Windfall and FoF to layer 2", true,
        &g_flags[POST_FF1_KORL_CUTSCENE]},
    {"Enter KoRL First Time", ENTER_KORL_FIRST_TIME, "Sets savewarp to most recent loaded area", true,
        &g_flags[ENTER_KORL_FIRST_TIME]},

};

void SavewarpFlagMenu::draw() {
    updateFlags();

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);
    cursorOffset = cursor.y + SAVEWARP_FLAG_OFFSET;

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursorOffset) {
        case LEAVING_OUTSET_CUTSCENE:
            setEventFlag(0x2401);
            break;
        case TETRA_SPOILS_BAG_TEXT:
            setEventFlag(0x0808);
            break;
        case BARREL_LAUNCH_CUTSCENE:
            setEventFlag(0x0801);
            break;
        case POST_FF1_KORL_CUTSCENE:
            setEventFlag(0x0F80);
            break;
        case ENTER_KORL_FIRST_TIME:
            setEventFlag(0x2A08);
            break;

        }
    }

    GZ_drawMenuLines(lines, cursorOffset, LINE_NUM);
    }
