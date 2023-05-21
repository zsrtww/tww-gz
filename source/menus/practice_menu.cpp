#include "menus/main_menu.h"
#include "practice.h"
#include "menus/practice_menu.h"

#define LINE_NUM 1

Cursor PracticeMenu::cursor;

Line lines[LINE_NUM] = {
    {"any\% no mss", ANY_NO_MSS, "Load an any\% no mss save", false},
};

void PracticeMenu::draw() {
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case ANY_NO_MSS:
            GZ_setMenu(GZ_ANY_NO_MSS_SAVES_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}