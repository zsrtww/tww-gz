#include "menus/flag_menu.h"
#include "menus/cutscene_flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"

#define LINE_NUM 3
Cursor CutsceneFlagMenu::cursor;
int cursorOffset;
Line lines[LINE_NUM] = {
    {"Watched Orca Intro Cutscene", ORCA_INTRO_CUTSCENE, "Sets initial Orca cutscene to seen", true,
        &g_flags[ORCA_INTRO_CUTSCENE]},
    {"Watched Puppet Ganon Cutscene", PUPPET_GANON_CUTSCENE, "Sets Puppet Ganon cutscene to seen", true,
     &g_flags[PUPPET_GANON_CUTSCENE]},
    {"Courtyard Cutscene", COURTYARD_CUTSCENE, "Sets H1 courtyard cutscene to seen", true,
        &g_flags[COURTYARD_CUTSCENE]},

};

void CutsceneFlagMenu::draw() {
    updateFlags();

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);
    cursorOffset = cursor.y + CUTSCENE_FLAG_OFFSET;

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }
   
    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursorOffset) {
        case ORCA_INTRO_CUTSCENE:
            setEventFlag(0x0640);
            break;
        case PUPPET_GANON_CUTSCENE:
            setEventFlag(0x3B02);
            break;
        case COURTYARD_CUTSCENE:
            setEventFlag(0x3804);
            break;

        }
    }

    GZ_drawMenuLines(lines, cursorOffset, LINE_NUM);
}
