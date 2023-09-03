#pragma once

#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MENU_NUM 26

enum {
    /* Main Menus */
    GZ_NO_MENU = -1,
    GZ_MAIN_MENU,
    GZ_CHEAT_MENU,
    GZ_FLAGS_MENU,
    GZ_INVENTORY_MENU,
    GZ_MEMORY_MENU,
    GZ_SCENE_MENU,
    GZ_PRACTICE_MENU,
    GZ_SETTINGS_MENU,
    GZ_TOOLS_MENU,

    /* Practice Sub-Menus */
    GZ_ANY_NO_MSS_SAVES_MENU,

    /* Memory Sub-Menus */
    GZ_MEM_EDITOR_MENU,
    GZ_WATCHES_MENU,

    /* Inventory Sub-Menus */
    GZ_AMOUNT_MENU,
    GZ_ITEM_INVENTORY_MENU,
    GZ_QUEST_STATUS_MENU,
    GZ_DELIVERY_MENU,
    GZ_SPOILS_MENU,
    GZ_BAIT_MENU,
    GZ_CHART_MENU,

    /* Chart Sub-Menus */
    GZ_TREASURE_CHART_MENU,
    GZ_SPECIAL_CHART_MENU,
    GZ_TRIFORCE_CHART_MENU,

    /* Flag Sub-Menus */
    GZ_GENERAL_FLAG_MENU,
    GZ_DUNGEON_MENU,
    GZ_SAVEWARP_FLAG_MENU,
    GZ_TUNER_FLAG_MENU,
    
};

void GZ_drawMenu();
void GZ_setMenu(int idx);
void GZ_clearMenu();
bool GZ_checkMenuOpen();

class Menu {
public:
    Menu() {}
};
