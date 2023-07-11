#include "menus/flag_menu.h"
#include "menus/korl_flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"

#define LINE_NUM 1
Cursor KorlFlagMenu::cursor;
int cursorOffset;

Line lines[LINE_NUM] = {
    {"Watched Post FF1 KoRL Cutscene", MEETING_KORL_CUTSCENE, "Spawns KoRL, sets savewarp to Windfall and FoF to layer 2", true,
        &g_flags[MEETING_KORL_CUTSCENE]},

};

void KorlFlagMenu::draw() {
    updateFlags();

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);
    cursorOffset = cursor.y + KORL_FLAG_OFFSET;

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursorOffset) {
        case MEETING_KORL_CUTSCENE:
            setEventFlag(0x0F80);
            break;

        }
    }

    GZ_drawMenuLines(lines, cursorOffset, LINE_NUM);
    }
