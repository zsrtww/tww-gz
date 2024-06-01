#include "menus/menu_spoils_bag/include/spoils_bag_menu.h"
#include "flags.h"
#include "gz_flags.h"
#include "utils/item.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC SpoilsBagMenu::SpoilsBagMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"slot 1:", SPOILSSLOT1_INDEX, "Modify the item in spoils bag slot 1"},
                        {"slot 2:", SPOILSSLOT2_INDEX, "Modify the item in spoils bag slot 2"},
                        {"slot 3:", SPOILSSLOT3_INDEX, "Modify the item in spoils bag slot 3"},
                        {"slot 4:", SPOILSSLOT4_INDEX, "Modify the item in spoils bag slot 4"},
                        {"slot 5:", SPOILSSLOT5_INDEX, "Modify the item in spoils bag slot 5"},
                        {"slot 6:", SPOILSSLOT6_INDEX, "Modify the item in spoils bag slot 6"},
                        {"slot 7:", SPOILSSLOT7_INDEX, "Modify the item in spoils bag slot 7"},
                        {"slot 8:", SPOILSSLOT8_INDEX, "Modify the item in spoils bag slot 8"},
                    } {}

SpoilsBagMenu::~SpoilsBagMenu() {}

void updateSpoilsBagItemFlag(u8 item_id) {
    if (item_id == JOY_PENDANT) {
        dComIfGs_onGetItemBeast(7);
    } else if (item_id - 0x45 >= 0 && item_id - 0x45 < 8) {
        dComIfGs_onGetItemBeast(item_id - 0x45);
    }
}

void updateSpoilsBagSlot(u8 slot, u8 item_id) {
    dComIfGs_setItemBeast(slot, item_id);
    updateSpoilsBagItemFlag(item_id);
}

void updateSpoilsBagItem(u8 slot) {
    u8 new_item_id = dComIfGs_getItemBeast(slot);
    Cursor::moveListSimple(new_item_id);
    if (new_item_id == NO_ITEM - 1) {
        new_item_id = NO_ITEM;
    }
    else if (new_item_id == 0) {
        new_item_id = JOY_PENDANT;
    }
    else if (new_item_id == JOY_PENDANT - 1) {
        new_item_id = NO_ITEM;
    }
    else if (new_item_id == JOY_PENDANT + 1) {
        new_item_id = SKULL_NECKLACE;
    }
    else if (new_item_id == SKULL_NECKLACE - 1) {
        new_item_id = JOY_PENDANT;
    }
    else if (new_item_id == BLUE_CHU_JELLY + 1) {
        new_item_id = BLUE_CHU_JELLY;
    }
    updateSpoilsBagSlot(slot, new_item_id);
}

void SpoilsBagMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    switch (cursor.y) {
    case SPOILSSLOT1_INDEX:
        updateSpoilsBagItem(SPOILSSLOT1_INDEX);
        break;
    case SPOILSSLOT2_INDEX:
        updateSpoilsBagItem(SPOILSSLOT2_INDEX);
        break;
    case SPOILSSLOT3_INDEX:
        updateSpoilsBagItem(SPOILSSLOT3_INDEX);
        break;
    case SPOILSSLOT4_INDEX:
        updateSpoilsBagItem(SPOILSSLOT4_INDEX);
        break;
    case SPOILSSLOT5_INDEX:
        updateSpoilsBagItem(SPOILSSLOT5_INDEX);
        break;
    case SPOILSSLOT6_INDEX:
        updateSpoilsBagItem(SPOILSSLOT6_INDEX);
        break;
    case SPOILSSLOT7_INDEX:
        updateSpoilsBagItem(SPOILSSLOT7_INDEX);
        break;
    case SPOILSSLOT8_INDEX:
        updateSpoilsBagItem(SPOILSSLOT8_INDEX);
        break;
    }

    lines[SPOILSSLOT1_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT1_INDEX)));
    lines[SPOILSSLOT2_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT2_INDEX)));
    lines[SPOILSSLOT3_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT3_INDEX)));
    lines[SPOILSSLOT4_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT4_INDEX)));
    lines[SPOILSSLOT5_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT5_INDEX)));
    lines[SPOILSSLOT6_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT6_INDEX)));
    lines[SPOILSSLOT7_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT7_INDEX)));
    lines[SPOILSSLOT8_INDEX].printf(" <%s>", item_id_to_str(dComIfGs_getItemBeast(SPOILSSLOT8_INDEX)));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
