#include "menu.h"
#include "rels/include/defines.h"

// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "main", "settings",
};

KEEP_FUNC Menu::Menu(Cursor& cursor) : cursor(cursor) {}