#include "menus/cheat_menu.h"
#include "menus/settings_menu.h"
#include "menu.h"
#include "libtww/MSL_C/string.h"
#include "lib.h"
#include "font.h"
#include "commands.h"

#define LINE_NUM 1
Cursor CheatMenu::cursor;

GZCheat g_cheats[CHEAT_AMNT] = {
    {MOON_JUMP_INDEX, false},
};

Line lines[LINE_NUM] = {
    {"moon jump", MOON_JUMP_INDEX, "Hold R+A to moon jump", true,
     &g_cheats[MOON_JUMP_INDEX].active},
};

void CheatMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        g_cheats[cursor.y].active = !g_cheats[cursor.y].active;

        if (g_cheats[cursor.y].active) {
            switch (cursor.y) {
            case MOON_JUMP_INDEX:
                GZCmd_enable(CMD_MOON_JUMP);
                break;
            }
        } else {
            switch (cursor.y) {
            case MOON_JUMP_INDEX:
                GZCmd_disable(CMD_MOON_JUMP);
                break;
            }
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
