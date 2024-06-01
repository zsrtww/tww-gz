#include "menus/menu_inventory/include/inventory_menu.h"
#include "font.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC InventoryMenu::InventoryMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"amounts", AMOUNT_INDEX, "Modify amounts for health, magic, etc."},
                        {"item inventory", ITEM_INVENTORY_INDEX, "Modify item inventory menu"},
                        {"quest status", QUEST_STATUS_INDEX, "Modify quest status menu"},
                        {"delivery bag", DELIVERY_BAG_INDEX, "Modify delivery bag items/amounts"},
                        {"spoils", SPOILS_INDEX, "Modify spoils bag items/amounts"},
                        {"bait", BAIT_INDEX, "Modify bait bag items/amounts"},
                        {"charts", CHART_INDEX, "Modify charts"},
                    } {}

InventoryMenu::~InventoryMenu() {}

void InventoryMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        /* case ITEM_WHEEL_INDEX:
            g_menuMgr->push(MN_ITEM_WHELL_INDEX);
            return;
        case PAUSE_MENU_INDEX:
            g_menuMgr->push(MN_PAUSE_INDEX);
            return;
        case AMOUNTS_MENU_INDEX:
            g_menuMgr->push(MN_AMOUNTS_INDEX);
            return; */
        }
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}