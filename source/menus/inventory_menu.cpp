#include "menus/main_menu.h"
#include "menus/inventory_menu.h"

#define LINE_NUM 4

Cursor InventoryMenu::cursor;

Line lines[LINE_NUM] = {
    {"amounts", AMOUNT_INDEX, "Modify bomb bag, quiver, wallet"},
    {"item inventory", ITEM_INVENTORY_INDEX, "Modify item inventory menu"},
    {"spoils", SPOILS_INDEX, "Modify Spoils Bag items/amounts"},
    {"delivery bag", DELIVERY_BAG_INDEX, "Modify Delivery Bag items/amounts"}, 
};

void InventoryMenu::draw() {
    cursor.move(0, LINE_NUM);
    

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case AMOUNT_INDEX:
            GZ_setMenu(GZ_AMOUNT_MENU);
            return;
        case ITEM_INVENTORY_INDEX:
            GZ_setMenu(GZ_ITEM_INVENTORY_MENU);
            return;
        case SPOILS_INDEX:
            //GZ_setMenu(GZ_SPOILS_MENU);
            return;
        case DELIVERY_BAG_INDEX:
            //GZ_setMenu(GZ_DELIVERY_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}