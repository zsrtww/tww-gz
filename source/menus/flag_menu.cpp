#include "menus/main_menu.h"
#include "menus/flag_menu.h"

#define LINE_NUM 5

Cursor FlagMenu::cursor;

Line lines[LINE_NUM] = {
    {"important", IMPORTANT_FLAG_INDEX, "Important Flags"},
    {"cutscenes", CUTSCENE_FLAG_INDEX, "Cutscene Flags (disabled)"},
    {"quests", QUEST_FLAG_INDEX, "Quest Flags (disabled)"},
    {"temp1", PLACEHOLDER1_FLAG_INDEX, "TEST (disabled)"},
    {"temp2", PLACEHOLDER2_FLAG_INDEX, "TEST (disabled)"},
};

void FlagMenu::draw() {
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
        case QUEST_FLAG_INDEX:
            //GZ_setMenu(GZ_QUEST_FLAG_MENU);
            return;
        case PLACEHOLDER1_FLAG_INDEX:
            //GZ_setMenu(GZ_PLACEHOLDER1_MENU);
            return;
        case PLACEHOLDER2_FLAG_INDEX:
            //GZ_setMenu(GZ_PLACEHOLDER2_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}