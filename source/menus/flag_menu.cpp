#include "menus/main_menu.h"
#include "menus/flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"

#define LINE_NUM 4

Cursor FlagMenu::cursor;

Line lines[LINE_NUM] = {
    {"general", GENERAL_FLAG_INDEX, "General Flags"},
    {"dungeons",DUNGEON_FLAG_INDEX,"dungeon flags"},
    {"savewarp", SAVEWARP_FLAG_INDEX, "Savewarp Flags"},
    {"tuner", TUNER_FLAG_INDEX, "Tuner Flags (flags must be set before connection)"},
    //{"quests", QUEST_FLAG_INDEX, "Quest Flags"},
    
    
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
        case GENERAL_FLAG_INDEX:
            GZ_setMenu(GZ_GENERAL_FLAG_MENU);
            return;
        case DUNGEON_FLAG_INDEX:
             GZ_setMenu(GZ_DUNGEON_MENU);
            return;
        case SAVEWARP_FLAG_INDEX:
            GZ_setMenu(GZ_SAVEWARP_FLAG_MENU);
            return;
        case TUNER_FLAG_INDEX:
            GZ_setMenu(GZ_TUNER_FLAG_MENU);
            return;
        //case QUEST_FLAG_INDEX:
            //GZ_setMenu(GZ_PLACEHOLDER1_MENU);
            //return;
        
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);

}
