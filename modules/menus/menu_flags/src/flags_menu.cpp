#include "menus/menu_flags/include/flags_menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC FlagsMenu::FlagsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"general", GENERAL_FLAGS_INDEX, "General Flags"},
          {"dungeons", DUNGEON_FLAGS_INDEX, "dungeon flags"},
          {"savewarp", SAVEWARP_FLAG_INDEX, "Savewarp Flags"},
          {"tuner", TUNER_FLAG_INDEX, "Tuner Flags (flags must be set before connection)"},
      } {}

FlagsMenu::~FlagsMenu() {}

void FlagsMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case GENERAL_FLAGS_INDEX:
            g_menuMgr->push(MN_GENERAL_FLAGS_INDEX);
            return;
        case DUNGEON_FLAGS_INDEX:
            g_menuMgr->push(MN_DUNGEON_FLAGS_INDEX);
            return;
        case SAVEWARP_FLAG_INDEX:
            g_menuMgr->push(MN_SAVEWARP_FLAGS_INDEX);
            return;
        case TUNER_FLAG_INDEX:
            g_menuMgr->push(MN_TUNER_FLAGS_INDEX);
            return;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
