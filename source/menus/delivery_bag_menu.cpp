#include "controller.h"
#include "menus/main_menu.h"
#include "menus/delivery_bag_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"

#define LINE_NUM 8

Cursor DeliveryBagMenu::cursor;

Line lines[LINE_NUM] = {
    {"slot 1:", SLOT1_INDEX, "Modify the item in delivery bag slot 1"},
    {"slot 2:", SLOT2_INDEX, "Modify the item in delivery bag slot 2"},
    {"slot 3:", SLOT3_INDEX, "Modify the item in delivery bag slot 3"},
    {"slot 4:", SLOT4_INDEX, "Modify the item in delivery bag slot 4"},
    {"slot 5:", SLOT5_INDEX, "Modify the item in delivery bag slot 5"},
    {"slot 6:", SLOT6_INDEX, "Modify the item in delivery bag slot 6"},
    {"slot 7:", SLOT7_INDEX, "Modify the item in delivery bag slot 7"},
    {"slot 8:", SLOT8_INDEX, "Modify the item in delivery bag slot 8"},
};



void updateDeliveryBagSlot(u8 slot, u8 item_id) {
    dComIfGs_setDeliveryBagSlot(slot, item_id);
}

void updateDeliveryBagItem(u8 slot) {
    u8 new_item_id = dComIfGs_getDeliveryBagSlot(slot);
    Cursor::moveListSimple(new_item_id);
    if (new_item_id == NO_ITEM - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == 0) {
        new_item_id = TOWN_FLOWER;
    } else if (new_item_id == TOWN_FLOWER - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == FILL_UP_COUPON + 1) {
        new_item_id = FILL_UP_COUPON;
    }
    updateDeliveryBagSlot(slot, new_item_id);
}

void DeliveryBagMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
        return;
    }

    switch (cursor.y) {
    case SLOT1_INDEX:
        updateDeliveryBagItem(SLOT1_INDEX);
        break;
    case SLOT2_INDEX:
        updateDeliveryBagItem(SLOT2_INDEX);
        break;
    case SLOT3_INDEX:
        updateDeliveryBagItem(SLOT3_INDEX);
        break;
    case SLOT4_INDEX:
        updateDeliveryBagItem(SLOT4_INDEX);
        break;
    case SLOT5_INDEX:
        updateDeliveryBagItem(SLOT5_INDEX);
        break;
    case SLOT6_INDEX:
        updateDeliveryBagItem(SLOT6_INDEX);
        break;
    case SLOT7_INDEX:
        updateDeliveryBagItem(SLOT7_INDEX);
        break;
    case SLOT8_INDEX:
        updateDeliveryBagItem(SLOT8_INDEX);
        break;
    }

    tww_sprintf(lines[SLOT1_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT1_INDEX)));
    tww_sprintf(lines[SLOT2_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT2_INDEX)));
    tww_sprintf(lines[SLOT3_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT3_INDEX)));
    tww_sprintf(lines[SLOT4_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT4_INDEX)));
    tww_sprintf(lines[SLOT5_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT5_INDEX)));
    tww_sprintf(lines[SLOT6_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT6_INDEX)));
    tww_sprintf(lines[SLOT7_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT7_INDEX)));
    tww_sprintf(lines[SLOT8_INDEX].value, " <%s>",item_id_to_str(dComIfGs_getDeliveryBagSlot(SLOT8_INDEX)));

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}