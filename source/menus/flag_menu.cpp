#include "menus/flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"

#define LINE_NUM 1
Cursor FlagMenu::cursor;

bool l_watched_ff2_helmaroc_cutscene = dComIfGs_isEventBit(g_flags[WATCHED_FF2_HELMAROC_CUTSCENE].flag);

Line lines[LINE_NUM] = {
    {"Watched FF2 Helmaroc Cutscene", WATCHED_FF2_HELMAROC_CUTSCENE, "Switches to animation set 2, among other things", true,
        &l_watched_ff2_helmaroc_cutscene},
};

void FlagMenu::draw() {
    l_watched_ff2_helmaroc_cutscene = dComIfGs_isEventBit(g_flags[WATCHED_FF2_HELMAROC_CUTSCENE].flag);

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        setEventFlag(g_flags[cursor.y].flag);
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
