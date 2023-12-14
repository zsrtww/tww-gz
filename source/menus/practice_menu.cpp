#include "menus/main_menu.h"
#include "practice.h"
#include "menus/practice_menu.h"

#define LINE_NUM 2

Cursor PracticeMenu::cursor;

Line lines[LINE_NUM] = {
    {"any\% no mss", ANY_NO_MSS, "Load an any\% no mss save", false},
    {"any\%", ANY_PERCENT, "Load an any\% save (asterisks are for sail/pg skip route files)", false},
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
	case ANY_PERCENT:
	    GZ_setMenu(GZ_ANY_PERCENT_SAVES_MENU);
	    return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
