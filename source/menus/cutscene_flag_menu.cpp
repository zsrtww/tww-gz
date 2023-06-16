#include "menus/flag_menu.h"
#include "menus/cutscene_flag_menu.h"
#include "flags.h"

#define LINE_NUM 2
Cursor CutsceneFlagMenu::cursor;
int cursorOffset;

Line lines[LINE_NUM] = {
    {"Watched Orca Intro Cutscene", ORCA_INTRO_CUTSCENE, "Sets initial Orca cutscene to seen", true,
        &g_flags[ORCA_INTRO_CUTSCENE].active},
    {"Watched Puppet Ganon Cutscene", PUPPET_GANON_CUTSCENE, "Sets Puppet Ganon cutscene to seen", true,
     &g_flags[PUPPET_GANON_CUTSCENE].active},
};

void CutsceneFlagMenu::draw() {
    GZ_updateFlags();

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);
    cursorOffset = cursor.y + CUTSCENE_FLAG_OFFSET;

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }
   
    if (GZ_getButtonTrig(GZPad::A)) {
        g_flags[cursorOffset].active = !g_flags[cursorOffset].active;

        if (g_flags[cursorOffset].active) GZ_activate((FlagId) cursorOffset);
        else GZ_deactivate((FlagId) cursorOffset);
    }

    GZ_drawMenuLines(lines, cursorOffset, LINE_NUM);
}
