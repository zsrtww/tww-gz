#include "menu.h"
#include "menus/main_menu.h"
#include "menus/flag_menu.h"
#include "menus/general_flag_menu.h"
#include "menus/tuner_flag_menu.h"
#include "menus/savewarp_flag_menu.h"
#include "menus/inventory_menu.h"
#include "menus/amount_menu.h"
#include "menus/item_inventory_menu.h"
#include "menus/quest_status_menu.h"
#include "menus/delivery_bag_menu.h"
#include "menus/spoils_bag_menu.h"
#include "menus/bait_bag_menu.h"
#include "menus/chart_menu.h"
#include "menus/treasure_chart_menu.h"
#include "menus/special_chart_menu.h"
#include "menus/triforce_chart_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "menus/practice_menu.h"
#include "menus/cheat_menu.h"
#include "menus/memory_menu.h"
#include "menus/scene_menu.h"
#include "menus/dungeon_menu.h"

#include "menus/item_equip_priority_menu.h"

#include "menus/memory_editor_menu.h"
#include "menus/watches_menu.h"

#include "menus/any_no_mss_saves_menu.h"
#include "menus/any_percent_saves_menu.h"

typedef void (*menu_render_t)();

menu_render_t l_menuDrawList[MENU_NUM] = {
    MainMenu::draw,
    CheatMenu::draw,
    FlagMenu::draw,
    InventoryMenu::draw,
    MemoryMenu::draw,
    SceneMenu::draw,
    PracticeMenu::draw,
    SettingsMenu::draw,
    ToolsMenu::draw,

    ItemEquipPriorityMenu::draw,

    AnyNoMssSavesMenu::draw,
    AnyPercentSavesMenu::draw,

    MemoryEditorMenu::draw,
    WatchesMenu::draw,

    AmountMenu::draw,
    ItemInventoryMenu::draw,
    QuestStatusMenu::draw,
    DeliveryBagMenu::draw,
    SpoilsBagMenu::draw,
    BaitBagMenu::draw,
    ChartMenu::draw,

    TreasureChartMenu::draw,
    SpecialChartMenu::draw,
    TriforceChartMenu::draw,

    GeneralFlagMenu::draw,
    DungeonMenu::draw,
    SavewarpFlagMenu::draw,
    TunerFlagMenu::draw,
    
};

menu_render_t l_currentMenu = nullptr;

void GZ_drawMenu() {
    if (l_currentMenu != nullptr) {
        l_currentMenu();
    }
}

void GZ_setMenu(int menu_idx) {
    if (menu_idx > GZ_NO_MENU) {
        l_currentMenu = l_menuDrawList[menu_idx];
    } else {
        l_currentMenu = nullptr;
    }
}

void GZ_clearMenu() {
    if (l_currentMenu) {
        l_currentMenu = nullptr;
    }
}

bool GZ_checkMenuOpen() {
    return l_currentMenu != nullptr;
}
