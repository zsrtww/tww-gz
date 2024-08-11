#include "menu.h"
#include "rels/include/defines.h"

// This array must correspond to the order of the MenuIndex enum.
const char* g_menuPaths[MN_COUNT] = {
    "main",          "cheats",    "flags",          "inventory",     "memory",         "practice",
    "scene",         "settings",  "tools",          "general_flags", "dungeon_flags",  "savewarp_flags",
    "tuner_flags",   "amounts",   "item_inventory", "quest_status",  "delivery_bag",   "spoils_bag",
    "bait_bag",      "charts",    "treasure_chart", "special_chart", "triforce_chart", "watches",
    "memory_editor", "any_saves", "nomss_saves",    "ad_saves",      "collision_view", "actor_list", "equip_priority",
    "pos_settings",
};

KEEP_FUNC Menu::Menu(Cursor& cursor) : cursor(cursor) {}