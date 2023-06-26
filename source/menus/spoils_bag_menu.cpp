#include "controller.h"
#include "menus/main_menu.h"
#include "menus/spoils_bag_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"

#define LINE_NUM 8

Cursor SpoilsBagMenu::cursor;

Line lines[LINE_NUM] = {
    {"slot 1:", SPOILSSLOT1_INDEX, "Modify the item in spoils bag slot 1"},
    {"slot 2:", SPOILSSLOT2_INDEX, "Modify the item in spoils bag slot 2"},
    {"slot 3:", SPOILSSLOT3_INDEX, "Modify the item in spoils bag slot 3"},
    {"slot 4:", SPOILSSLOT4_INDEX, "Modify the item in spoils bag slot 4"},
    {"slot 5:", SPOILSSLOT5_INDEX, "Modify the item in spoils bag slot 5"},
    {"slot 6:", SPOILSSLOT6_INDEX, "Modify the item in spoils bag slot 6"},
    {"slot 7:", SPOILSSLOT7_INDEX, "Modify the item in spoils bag slot 7"},
    {"slot 8:", SPOILSSLOT8_INDEX, "Modify the item in spoils bag slot 8"},
};

void updateSpoilsBagItemFlag(u8 item_id) {
  //  u8 collected_item = item_id == NO_ITEM ? 0 : 1;
    if (item_id == JOY_PENDANT) {
        dComIfGs_setSpoilFlag(7);
    } else {
        dComIfGs_setSpoilFlag(item_id - 0x45);
    }
}

void updateSpoilsBagSlot(u8 slot, u8 item_id) {
    dComIfGs_setSpoilsBagSlot(slot, item_id);
    updateSpoilsBagItemFlag(item_id);
}

void updateSpoilsBagItem(u8 slot) {
    u8 new_item_id = dComIfGs_getSpoilsBagSlot(slot);
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

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
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

    tww_sprintf(lines[SPOILSSLOT1_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT1_INDEX)));
    tww_sprintf(lines[SPOILSSLOT2_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT2_INDEX)));
    tww_sprintf(lines[SPOILSSLOT3_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT3_INDEX)));
    tww_sprintf(lines[SPOILSSLOT4_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT4_INDEX)));
    tww_sprintf(lines[SPOILSSLOT5_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT5_INDEX)));
    tww_sprintf(lines[SPOILSSLOT6_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT6_INDEX)));
    tww_sprintf(lines[SPOILSSLOT7_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT7_INDEX)));
    tww_sprintf(lines[SPOILSSLOT8_INDEX].value, " <%s>", item_id_to_str(dComIfGs_getSpoilsBagSlot(SPOILSSLOT8_INDEX)));

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}