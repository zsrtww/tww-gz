#include "menu.h"
#include "rels/include/defines.h"

// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "main",  "cheats",   "flags", "inventory", "memory",          "practice",
    "scene", "settings", "tools", "any_saves", "any_nomss_saves", "all_dungeons_saves",
};

KEEP_FUNC Menu::Menu(Cursor& cursor) : cursor(cursor) {}