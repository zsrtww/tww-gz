#include "menus/flag_menu.h"
#include "flags.h"

#define LINE_NUM 1
Cursor FlagMenu::cursor;

Line lines[LINE_NUM] = {
    {"Watched FF2 Helmaroc Cutscene", WATCHED_FF2_HELMAROC_CUTSCENE, "Switches to animation set 2, among other things", true,
        &g_flags[WATCHED_FF2_HELMAROC_CUTSCENE].active},
};

void FlagMenu::draw() {
    GZ_updateFlags();

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        g_flags[cursor.y].active = !g_flags[cursor.y].active;

        if (g_flags[cursor.y].active) GZ_activate((FlagId) cursor.y);
        else GZ_deactivate((FlagId) cursor.y);
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
