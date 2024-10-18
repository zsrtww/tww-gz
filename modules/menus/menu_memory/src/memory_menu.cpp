#include "menus/menu_memory/include/memory_menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "utils/hook.h"

KEEP_FUNC MemoryMenu::MemoryMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"watches", WATCHES_INDEX, "Manage memory watches", false},
                        {"memory editor", MEM_EDITOR_INDEX, "View/edit memory", false},
                        {"flag logger", FLAG_LOGGER_INDEX, "Toggle outputting triggered events/switches to screen",
                         true, [](){return g_flagLogEnabled;}},
                    } {}

MemoryMenu::~MemoryMenu() {}

void MemoryMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case WATCHES_INDEX:
            g_menuMgr->push(MN_WATCHES_INDEX);
            return;
        case MEM_EDITOR_INDEX:
            g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
            return;
        case FLAG_LOGGER_INDEX:
            g_flagLogEnabled = !g_flagLogEnabled;
            break;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
