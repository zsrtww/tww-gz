#include "menus/menu_delivery_bag/include/delivery_bag_menu.h"
#include "flags.h"
#include "gz_flags.h"
#include "utils/item.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC DeliveryBagMenu::DeliveryBagMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"slot 1:", SLOT1_INDEX, "Modify the item in delivery bag slot 1"},
                        {"slot 2:", SLOT2_INDEX, "Modify the item in delivery bag slot 2"},
                        {"slot 3:", SLOT3_INDEX, "Modify the item in delivery bag slot 3"},
                        {"slot 4:", SLOT4_INDEX, "Modify the item in delivery bag slot 4"},
                        {"slot 5:", SLOT5_INDEX, "Modify the item in delivery bag slot 5"},
                        {"slot 6:", SLOT6_INDEX, "Modify the item in delivery bag slot 6"},
                        {"slot 7:", SLOT7_INDEX, "Modify the item in delivery bag slot 7"},
                        {"slot 8:", SLOT8_INDEX, "Modify the item in delivery bag slot 8"},
                    } {}

DeliveryBagMenu::~DeliveryBagMenu() {}

void updateDeliveryBagSlot(u8 slot, u8 item_id) {
    dComIfGs_setItemReserve(slot, item_id);
}

void updateDeliveryBagItem(u8 slot) {
    u8 new_item_id = dComIfGs_getItemReserve(slot);
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

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
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

    lines[SLOT1_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT1_INDEX)));
    lines[SLOT2_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT2_INDEX)));
    lines[SLOT3_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT3_INDEX)));
    lines[SLOT4_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT4_INDEX)));
    lines[SLOT5_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT5_INDEX)));
    lines[SLOT6_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT6_INDEX)));
    lines[SLOT7_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT7_INDEX)));
    lines[SLOT8_INDEX].printf(" <%s>",item_id_to_str(dComIfGs_getItemReserve(SLOT8_INDEX)));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
