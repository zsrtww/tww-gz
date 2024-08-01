#include "menus/menu_bait_bag/include/bait_bag_menu.h"
#include "flags.h"
#include "gz_flags.h"
#include "utils/item.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC BaitBagMenu::BaitBagMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"slot 1:", BAITSLOT1_INDEX,
                         "Modify the item in bait bag slot 1"},
                        {"slot 2:", BAITSLOT2_INDEX,
                         "Modify the item in bait bag slot 2"},
                        {"slot 3:", BAITSLOT3_INDEX,
                         "Modify the item in bait bag slot 3"},
                        {"slot 4:", BAITSLOT4_INDEX,
                         "Modify the item in bait bag slot 4"},
                        {"slot 5:", BAITSLOT5_INDEX,
                         "Modify the item in bait bag slot 5"},
                        {"slot 6:", BAITSLOT6_INDEX,
                         "Modify the item in bait bag slot 6"},
                        {"slot 7:", BAITSLOT7_INDEX,
                         "Modify the item in bait bag slot 7"},
                        {"slot 8:", BAITSLOT8_INDEX,
                         "Modify the item in bait bag slot 8"},
                    } {}

BaitBagMenu::~BaitBagMenu() {}

void updateBaitBagSlot(u8 slot, u8 item_id) {
    dComIfGs_setItemBait(slot, item_id);
}

void updateBaitBagAmount(u8 index) {
    if (dComIfGs_getItemBait(index) == ALL_PURPOSE_BAIT) {
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
    u8 new_item_id = dComIfGs_getItemBait(slot);
    Cursor::moveListSimple(new_item_id);
    if (new_item_id == NO_ITEM - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == 0) {
        new_item_id = ALL_PURPOSE_BAIT;
        dComIfGs_setBaitNum(slot, 3);
    } else if (new_item_id == ALL_PURPOSE_BAIT - 1) {
        new_item_id = NO_ITEM;
        dComIfGs_setBaitNum(slot, 0);
    } else if ((new_item_id == ALL_PURPOSE_BAIT + 1)) {
        new_item_id = HYOI_PEAR;
        dComIfGs_setBaitNum(slot, 0);
    } else if ((new_item_id == HYOI_PEAR - 1)) {
        new_item_id = ALL_PURPOSE_BAIT;
        dComIfGs_setBaitNum(slot, 3);
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

const char* bait_to_str(u8 slot) {
    if (dComIfGs_getItemBait(slot) != ALL_PURPOSE_BAIT) {
        return item_id_to_str(dComIfGs_getItemBait(slot));
    } else {
        switch (dComIfGs_getBaitNum(slot)) {
        case 0:
            return "All Purpose Bait (0)";
            break;
        case 1:
            return "All Purpose Bait (1)";
            break;
        case 2:
            return "All Purpose Bait (2)";
            break;
        case 3:
            return "All Purpose Bait (3)";
            break;
        default:
            return "All Purpose Bait (0)";
            break;
        }
    }
}

void BaitBagMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
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

    lines[BAITSLOT1_INDEX].printf(" <%s>", bait_to_str(BAITSLOT1_INDEX));
    lines[BAITSLOT2_INDEX].printf(" <%s>", bait_to_str(BAITSLOT2_INDEX));
    lines[BAITSLOT3_INDEX].printf(" <%s>", bait_to_str(BAITSLOT3_INDEX));
    lines[BAITSLOT4_INDEX].printf(" <%s>", bait_to_str(BAITSLOT4_INDEX));
    lines[BAITSLOT5_INDEX].printf(" <%s>", bait_to_str(BAITSLOT5_INDEX));
    lines[BAITSLOT6_INDEX].printf(" <%s>", bait_to_str(BAITSLOT6_INDEX));
    lines[BAITSLOT7_INDEX].printf(" <%s>", bait_to_str(BAITSLOT7_INDEX));
    lines[BAITSLOT8_INDEX].printf(" <%s>", bait_to_str(BAITSLOT8_INDEX));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
