#include "menus/any_no_mss_saves_menu.h"

#define LINE_NUM 1
Cursor AnyNoMssSavesMenu::cursor;

Line lines[LINE_NUM] = {
    {"outset", OUTSET, "Just after the intro"},
};

void AnyNoMssSavesMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_PRACTICE_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        // load the save at cursor.y
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
