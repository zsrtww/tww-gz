#include "menus/main_menu.h"

#define LINE_NUM 8

Cursor MainMenu::cursor;

Line lines[LINE_NUM] = {
    {"cheats", CHEAT_INDEX, "Toggle cheats", false},
    {"flags", FLAGS_INDEX, "Toggle in-game flags", false},
    {"inventory", INVENTORY_INDEX, "Set items and equipment", false},
    {"memory", MEMORY_INDEX, "View/edit memory, add watches, and save/load memfiles", false},
    {"practice", PRACTICE_INDEX, "Load practice files (coming soon...)", false},
    {"scene", SCENE_INDEX, "Adjust current scene settings (coming soon...)", false},
    {"settings", SETTINGS_INDEX, "Configure settings", false},
    {"tools", TOOLS_INDEX, "Use various tools for practice and testing", false},
};

void MainMenu::draw() {
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_clearMenu();
        //GZ_setFifoVisible(true);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case CHEAT_INDEX:
            GZ_setMenu(GZ_CHEAT_MENU);
            return;
        case FLAGS_INDEX:
            GZ_setMenu(GZ_FLAGS_MENU);
            return;
        case INVENTORY_INDEX:
            GZ_setMenu(GZ_INVENTORY_MENU);
            return;
        case MEMORY_INDEX:
            GZ_setMenu(GZ_MEMORY_MENU);
            return;
        case PRACTICE_INDEX:
            //GZ_setMenu(GZ_PRACTICE_MENU);
            return;
        case SCENE_INDEX:
            //GZ_setMenu(GZ_SCENE_MENU);
            return;
        case SETTINGS_INDEX:
            GZ_setMenu(GZ_SETTINGS_MENU);
            return;
        case TOOLS_INDEX:
            GZ_setMenu(GZ_TOOLS_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}