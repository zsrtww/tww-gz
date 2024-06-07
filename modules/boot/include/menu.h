#pragma once
// #include "commands.h"
#include "controller.h"
#include "font.h"
#include "libtww/include/JSystem/JUtility/JUTGamePad.h"
#include "libtww/include/dolphin/mtx/vec.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MAX_MENU_RENDER_FLAGS 30

#define SELECTION_BUTTON (GZPad::A)
#define BACK_BUTTON (GZPad::B)

enum MenuIndex {
    MN_NONE_INDEX = -1,
    MN_MAIN_MENU_INDEX = 0,

    // Main menu's sub menus
    MN_CHEAT_INDEX,
    MN_FLAGS_INDEX,
    MN_INVENTORY_INDEX,
    MN_MEMORY_INDEX,
    MN_PRACTICE_INDEX,
    MN_SCENE_INDEX,
    MN_SETTINGS_INDEX,
    MN_TOOLS_INDEX,

    // Flag menu's sub menus
    MN_GENERAL_FLAGS_INDEX,
    MN_DUNGEON_FLAGS_INDEX,
    MN_SAVEWARP_FLAGS_INDEX,
    MN_TUNER_FLAGS_INDEX,

    // Inventory sub menus
    MN_AMOUNTS_INDEX,
    MN_ITEM_INVENTORY_INDEX,
    MN_QUEST_STATUS_INDEX,
    MN_DELIVERY_BAG_INDEX,
    MN_SPOILS_BAG_INDEX,
    MN_BAIT_BAG_INDEX,
    MN_CHARTS_INDEX,

    // Chart sub menus
    MN_TREASURE_CHART_INDEX,
    MN_SPECIAL_CHART_INDEX,
    MN_TRIFORCE_CHART_INDEX,

    // Memory menu's sub menus
    MN_WATCHES_INDEX,
    MN_MEMORY_EDITOR_INDEX,

    // Practice menu's sub menus
    MN_ANY_SAVES_INDEX,
    MN_ANY_NOMSS_SAVES_INDEX,
    MN_AD_SAVES_INDEX,

    // Settings sub menus
    MN_EQUIP_PRIORITY_INDEX,
    MN_POS_SETTINGS_INDEX,

    // This entry is used only to get a count of the number of valid entries.
    MN_COUNT
};

extern const char* g_menuPaths[MN_COUNT];

#define LIST_COUNT(list) (sizeof(list) / sizeof((list)[0]))
#define MENU_LINE_NUM LIST_COUNT(lines)

class Menu {
public:
    Menu(Cursor& cursor);

    virtual void draw() = 0;

protected:
    Cursor& cursor;
};