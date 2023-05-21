#include "menus/any_no_mss_saves_menu.h"
#include "save_manager.h"

#define LINE_NUM 1
Cursor AnyNoMssSavesMenu::cursor;

Line lines[LINE_NUM] = {
    {"forest of fairies", OUTSET, "about to rescue tetra, except she's not there..."},
};

void AnyNoMssSavesMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_PRACTICE_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        special AnyNoMssSpecials[] = {
            special(OUTSET, nullptr, nullptr)
        };

        SaveManager::triggerLoad(cursor.y, "any_no_mss", AnyNoMssSpecials, sizeof(AnyNoMssSpecials) / sizeof(AnyNoMssSpecials[0]));
        GZ_clearMenu();
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
