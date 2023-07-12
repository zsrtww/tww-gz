#include "menus/main_menu.h"
#include "menus/flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"

#define LINE_NUM 5

Cursor FlagMenu::cursor;

Line lines[LINE_NUM] = {
    {"important", IMPORTANT_FLAG_INDEX, "Important Flags"},
    {"cutscenes", CUTSCENE_FLAG_INDEX, "Cutscene Flags"},
    {"korl", KORL_FLAG_INDEX, "KORL Flags"},
    {"savewarp", SAVEWARP_FLAG_INDEX, "Savewarp Flags"},
    {"quests", QUEST_FLAG_INDEX, "Quest Flags (disabled)"},
    
};

void FlagMenu::draw() {
    updateFlags();

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);


    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case IMPORTANT_FLAG_INDEX:
            GZ_setMenu(GZ_IMPORTANT_FLAG_MENU);
            return;
        case CUTSCENE_FLAG_INDEX:
            GZ_setMenu(GZ_CUTSCENE_FLAG_MENU);
            return;
        case KORL_FLAG_INDEX:
            GZ_setMenu(GZ_KORL_FLAG_MENU);
            return;
        case SAVEWARP_FLAG_INDEX:
            GZ_setMenu(GZ_SAVEWARP_FLAG_MENU);
            return;
        case QUEST_FLAG_INDEX:
            //GZ_setMenu(GZ_PLACEHOLDER1_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
