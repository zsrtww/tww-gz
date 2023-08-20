#include "controller.h"
#include "menus/main_menu.h"
#include "menus/bait_bag_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"

#define LINE_NUM 8

Cursor BaitBagMenu::cursor;

Line lines[LINE_NUM] = {
    {"slot 1:", BAITSLOT1_INDEX, "Modify the item in bait bag slot 1 (modify bait amount with A)"},
    {"slot 2:", BAITSLOT2_INDEX, "Modify the item in bait bag slot 2 (modify bait amount with A)"},
    {"slot 3:", BAITSLOT3_INDEX, "Modify the item in bait bag slot 3 (modify bait amount with A)"},
    {"slot 4:", BAITSLOT4_INDEX, "Modify the item in bait bag slot 4 (modify bait amount with A)"},
    {"slot 5:", BAITSLOT5_INDEX, "Modify the item in bait bag slot 5 (modify bait amount with A)"},
    {"slot 6:", BAITSLOT6_INDEX, "Modify the item in bait bag slot 6 (modify bait amount with A)"},
    {"slot 7:", BAITSLOT7_INDEX, "Modify the item in bait bag slot 7 (modify bait amount with A)"},
    {"slot 8:", BAITSLOT8_INDEX, "Modify the item in bait bag slot 8 (modify bait amount with A)"},
};


void updateBaitBagSlot(u8 slot, u8 item_id) {
    dComIfGs_setBaitBagSlot(slot, item_id);
}

void updateBaitBagAmount(u8 index) {
    if (dComIfGs_getBaitBagSlot(index) == ALL_PURPOSE_BAIT) {
        u8 amount = dComIfGs_getBaitNum(index);
        Cursor::moveListSimple(amount);
        if (amount == 0xFF) {
            amount = 3;
        }
        if (amount > 3) {
            amount = 0;
        }
        dComIfGs_setBaitNum(index, amount);
    }
}

void updateBaitBagItem(u8 slot) {
    u8 new_item_id = dComIfGs_getBaitBagSlot(slot);
    Cursor::moveListSimple(new_item_id);
    if (new_item_id == NO_ITEM - 1) {
        new_item_id = NO_ITEM;
    }
    else if (new_item_id == 0) {
        new_item_id = ALL_PURPOSE_BAIT;
        dComIfGs_setBaitNum(slot, 3);
    } else if (new_item_id == ALL_PURPOSE_BAIT - 1) {
        new_item_id = NO_ITEM;
        dComIfGs_setBaitNum(slot, 0);
    } else if ((new_item_id == ALL_PURPOSE_BAIT + 1)) {
        new_item_id = HYOI_PEAR;
        dComIfGs_setBaitNum(slot, 0);
    } else if ((new_item_id == HYOI_PEAR + 1)) {
        new_item_id = HYOI_PEAR;
    }
    if (GZ_getButtonTrig(GZPad::A)) {
        if (new_item_id == ALL_PURPOSE_BAIT) {
            if (dComIfGs_getBaitNum(slot) == 1) {
                dComIfGs_setBaitNum(slot, 2);
            } else if (dComIfGs_getBaitNum(slot) == 2) {
                dComIfGs_setBaitNum(slot, 3);
            } else if ((dComIfGs_getBaitNum(slot) == 3) || (dComIfGs_getBaitNum(slot) == 0)) {
                dComIfGs_setBaitNum(slot, 1);
            }
        }
    }
    updateBaitBagSlot(slot, new_item_id);
}

void BaitBagMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
        return;
    }

    switch (cursor.y) {
    case BAITSLOT1_INDEX:
        updateBaitBagItem(BAITSLOT1_INDEX);
        break;
    case BAITSLOT2_INDEX:
        updateBaitBagItem(BAITSLOT2_INDEX);
        break;
    case BAITSLOT3_INDEX:
        updateBaitBagItem(BAITSLOT3_INDEX);
        break;
    case BAITSLOT4_INDEX:
        updateBaitBagItem(BAITSLOT4_INDEX);
        break;
    case BAITSLOT5_INDEX:
        updateBaitBagItem(BAITSLOT5_INDEX);
        break;
    case BAITSLOT6_INDEX:
        updateBaitBagItem(BAITSLOT6_INDEX);
        break;
    case BAITSLOT7_INDEX:
        updateBaitBagItem(BAITSLOT7_INDEX);
        break;
    case BAITSLOT8_INDEX:
        updateBaitBagItem(BAITSLOT8_INDEX);
        break;
    }

    tww_sprintf(lines[BAITSLOT1_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT1_INDEX)));
    tww_sprintf(lines[BAITSLOT2_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT2_INDEX)));
    tww_sprintf(lines[BAITSLOT3_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT3_INDEX)));
    tww_sprintf(lines[BAITSLOT4_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT4_INDEX)));
    tww_sprintf(lines[BAITSLOT5_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT5_INDEX)));
    tww_sprintf(lines[BAITSLOT6_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT6_INDEX)));
    tww_sprintf(lines[BAITSLOT7_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT7_INDEX)));
    tww_sprintf(lines[BAITSLOT8_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getBaitBagSlot(BAITSLOT8_INDEX)));

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}