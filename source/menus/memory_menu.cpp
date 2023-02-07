#include "menus/main_menu.h"
#include "menus/memory_menu.h"

#define LINE_NUM 2

Cursor MemoryMenu::cursor;

Line lines[LINE_NUM] = {
    {"memory editor", 0, "View/edit memory", false},
    {"watches", 1, "Manage memory watches", false},
};

void MemoryMenu::draw() {
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case 0:
            GZ_setMenu(GZ_MEM_EDITOR_MENU);
            return;
        case 1:
            GZ_setMenu(GZ_WATCHES_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}