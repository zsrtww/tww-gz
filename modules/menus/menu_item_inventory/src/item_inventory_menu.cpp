#include "menus/menu_item_inventory/include/item_inventory_menu.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "font.h"
#include "gz_flags.h"
#include "utils/item.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define NUM_ITEM_SLOTS 21

#define DEFAULT_ARROW_CAPACITY 30
#define DEFAULT_BOMB_CAPACITY 30

enum BottleSlotIndex {
    SLOT_BOTTLE_1 = 14,
    SLOT_BOTTLE_2 = 15,
    SLOT_BOTTLE_3 = 16,
    SLOT_BOTTLE_4 = 17
};

KEEP_FUNC ItemInventoryMenu::ItemInventoryMenu(Cursor& cursor)
    : Menu(cursor), lines{{"Telescope:", SLOT_TELESCOPE, "Add/remove telescope to/from inventory"},
                          {"Sail:", SLOT_SAIL, "Add/remove sail to/from inventory"},
                          {"Wind Waker:", SLOT_WIND_WAKER, "Add/remove wind waker to/from inventory"},
                          {"Grappling Hook:", SLOT_ROPE, "Add/remove grappling hook to/from inventory"},
                          {"Spoils Bag:", SLOT_SPOILS_BAG, "Add/remove spoils bag to/from inventory"},
                          {"Boomerang:", SLOT_BOOMERANG, "Add/remove boomerang to/from inventory"},
                          {"Deku Leaf:", SLOT_DEKU_LEAF, "Add/remove deku leaf to/from inventory"},
                          {"Tingle Tuner:", SLOT_TUNER, "Add/remove tingle tuner to/from inventory"},
                          {"Progressive Picto Box:", SLOT_CAMERA, "Add/remove/upgrade picto box"},
                          {"Iron Boots:", SLOT_IRON_BOOTS, "Add/remove iron boots to/from inventory"},
                          {"Magic Armor:", SLOT_MAGIC_ARMOR, "Add/remove magic armor to/from inventory"},
                          {"Bait Bag:", SLOT_BAIT_BAG, "Add/remove bait bag to/from inventory"},
                          {"Progressive Bow:", SLOT_BOW, "Add/remove/upgrade bow"},
                          {"Bombs:", SLOT_BOMB, "Add/remove bombs to/from inventory"},
                          {"Bottle 1:", SLOT_BOTTLE_1, "Add/remove bottle 1 to/from inventory"},
                          {"Bottle 2:", SLOT_BOTTLE_2, "Add/remove bottle 2 to/from inventory"},
                          {"Bottle 3:", SLOT_BOTTLE_3, "Add/remove bottle 3 to/from inventory"},
                          {"Bottle 4:", SLOT_BOTTLE_4, "Add/remove bottle 4 to/from inventory"},
                          {"Delivery Bag:", SLOT_TRADE_ITEM, "Add/remove delivery bag to/from inventory"},
                          {"Hookshot:", SLOT_HOOKSHOT, "Add/remove hookshot to/from inventory"},
                          {"Skull Hammer:", SLOT_HAMMER, "Add/remove skull hammer to/from inventory"}} {}

ItemInventoryMenu::~ItemInventoryMenu() {}

void updateItemFlag(u8 slot, u8 item_id, u8 bit) {
    if (item_id != NO_ITEM) {
        dComIfGs_onGetItem(slot, bit);
    } else {
        dComIfGs_offGetItem(slot, bit);
    }
}

void updateItem(u8 slot, u8 item_id) {
    dComIfGs_setItem(slot, item_id);
    updateItemFlag(slot, item_id, 0);
}

void updateSingleItem(u8 slot, u8 item_id) {
    u8 new_item_id = dComIfGs_getItem(slot);
    Cursor::moveListSimple(new_item_id);
    if (new_item_id == NO_ITEM - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == 0) {
        new_item_id = item_id;
    } else if (new_item_id == item_id - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == item_id + 1) {
        new_item_id = item_id;
    } else {
        new_item_id = dComIfGs_getItem(slot);
    }

    updateItem(slot, new_item_id);
}

void updateBottle(u8 slot) {
    u8 new_item_id = dComIfGs_getItem(slot);
    Cursor::moveListSimple(new_item_id);
    if (new_item_id == NO_ITEM - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == 0) {
        new_item_id = EMPTY_BOTTLE;
    } else if (new_item_id == EMPTY_BOTTLE - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == FOREST_FIREFLY + 1) {
        dComIfGs_resetFwaterTimer(36000);
    } else if (new_item_id == FOREST_WATER - 1) {
        dComIfGs_resetFwaterTimer(0);
    } else if (new_item_id == FOREST_WATER + 1) {
        new_item_id = FOREST_WATER;
    }
    updateItem(slot, new_item_id);
}

void ItemInventoryMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    u8 new_item_id = 0;

    switch (cursor.y) {
    case SLOT_TELESCOPE:
        updateSingleItem(SLOT_TELESCOPE, TELESCOPE);
        break;
    case SLOT_SAIL:
        updateSingleItem(SLOT_SAIL, SAIL);
        break;
    case SLOT_WIND_WAKER:
        updateSingleItem(SLOT_WIND_WAKER, WIND_WAKER);
        break;
    case SLOT_ROPE:
        updateSingleItem(SLOT_ROPE, GRAPPLING_HOOK);
        break;
    case SLOT_SPOILS_BAG:
        updateSingleItem(SLOT_SPOILS_BAG, SPOILS_BAG);
        break;
    case SLOT_BOOMERANG:
        updateSingleItem(SLOT_BOOMERANG, BOOMERANG);
        break;
    case SLOT_DEKU_LEAF:
        updateSingleItem(SLOT_DEKU_LEAF, DEKU_LEAF);
        break;
    case SLOT_TUNER:
        updateSingleItem(SLOT_TUNER, TINGLE_TUNER);
        break;
    case SLOT_CAMERA:
        new_item_id = dComIfGs_getItem(SLOT_CAMERA);
        Cursor::moveListSimple(new_item_id);
        if (new_item_id == NO_ITEM - 1) {
            new_item_id = NO_ITEM;
        } else if (new_item_id == 0) {
            new_item_id = PICTO_BOX;
        } else if (new_item_id == PICTO_BOX - 1) {
            new_item_id = NO_ITEM;
        } else if (new_item_id == PICTO_BOX + 1) {
            new_item_id = DELUXE_PICTO_BOX;
        } else if (new_item_id == DELUXE_PICTO_BOX - 1) {
            new_item_id = PICTO_BOX;
        } else if (new_item_id == DELUXE_PICTO_BOX + 1) {
            new_item_id = DELUXE_PICTO_BOX;
        } else {
            new_item_id = dComIfGs_getItem(SLOT_CAMERA);
        }
        updateItem(SLOT_CAMERA, new_item_id);
        break;
    case SLOT_IRON_BOOTS:
        updateSingleItem(SLOT_IRON_BOOTS, IRON_BOOTS);
        break;
    case SLOT_MAGIC_ARMOR:
        updateSingleItem(SLOT_MAGIC_ARMOR, MAGIC_ARMOR);
        break;
    case SLOT_BAIT_BAG:
        updateSingleItem(SLOT_BAIT_BAG, BAIT_BAG);
        break;
    case SLOT_BOW:
        new_item_id = dComIfGs_getItem(SLOT_BOW);
        Cursor::moveListSimple(new_item_id);
        if (new_item_id == NO_ITEM - 1) {
            new_item_id = NO_ITEM;
        } else if (new_item_id == 0) {
            new_item_id = BOW;
        } else if (new_item_id == BOW - 1) {
            new_item_id = NO_ITEM;
        } else if (new_item_id == BOW + 1) {
            new_item_id = BOW_WITH_FIRE_AND_ICE_ARROWS;
        } else if (new_item_id == BOW_WITH_FIRE_AND_ICE_ARROWS - 1) {
            new_item_id = BOW;
        } else if (new_item_id == BOW_WITH_LIGHT_ARROWS + 1) {
            new_item_id = BOW_WITH_LIGHT_ARROWS;
        }
        updateItem(SLOT_BOW, new_item_id);
        if (GZ_getButtonTrig(GZPad::DPAD_RIGHT) && dComIfGs_getArrowMax() == 0) {
            dComIfGs_setArrowMax(DEFAULT_ARROW_CAPACITY);
            dComIfGs_setArrowNum(DEFAULT_ARROW_CAPACITY);
        }
        break;
    case SLOT_BOMB:
        updateSingleItem(SLOT_BOMB, BOMBS);
        if (GZ_getButtonTrig(GZPad::DPAD_RIGHT) && dComIfGs_getBombMax() == 0) {
            dComIfGs_setBombMax(DEFAULT_BOMB_CAPACITY);
            dComIfGs_setBombNum(DEFAULT_BOMB_CAPACITY);
        }
        break;
    case SLOT_BOTTLE_1:
        updateBottle(SLOT_BOTTLE_1);
        break;
    case SLOT_BOTTLE_2:
        updateBottle(SLOT_BOTTLE_2);
        break;
    case SLOT_BOTTLE_3:
        updateBottle(SLOT_BOTTLE_3);
        break;
    case SLOT_BOTTLE_4:
        updateBottle(SLOT_BOTTLE_4);
        break;
    case SLOT_TRADE_ITEM:
        updateSingleItem(SLOT_TRADE_ITEM, DELIVERY_BAG);
        break;
    case SLOT_HOOKSHOT:
        updateSingleItem(SLOT_HOOKSHOT, HOOKSHOT);
        break;
    case SLOT_HAMMER:
        updateSingleItem(SLOT_HAMMER, SKULL_HAMMER);
        break;
    }

    lines[SLOT_TELESCOPE].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_TELESCOPE)));
    lines[SLOT_SAIL].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_SAIL)));
    lines[SLOT_WIND_WAKER].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_WIND_WAKER)));
    lines[SLOT_ROPE].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_ROPE)));
    lines[SLOT_SPOILS_BAG].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_SPOILS_BAG)));
    lines[SLOT_BOOMERANG].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BOOMERANG)));
    lines[SLOT_DEKU_LEAF].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_DEKU_LEAF)));
    lines[SLOT_TUNER].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_TUNER)));
    lines[SLOT_CAMERA].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_CAMERA)));
    lines[SLOT_IRON_BOOTS].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_IRON_BOOTS)));
    lines[SLOT_MAGIC_ARMOR].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_MAGIC_ARMOR)));
    lines[SLOT_BAIT_BAG].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BAIT_BAG)));
    lines[SLOT_BOW].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BOW)));
    lines[SLOT_BOMB].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BOMB)));
    lines[SLOT_BOTTLE_1].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BOTTLE_1)));
    lines[SLOT_BOTTLE_2].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BOTTLE_2)));
    lines[SLOT_BOTTLE_3].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BOTTLE_3)));
    lines[SLOT_BOTTLE_4].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_BOTTLE_4)));
    lines[SLOT_TRADE_ITEM].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_TRADE_ITEM)));
    lines[SLOT_HOOKSHOT].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_HOOKSHOT)));
    lines[SLOT_HAMMER].printf(" <%s>", item_id_to_str(dComIfGs_getItem(SLOT_HAMMER)));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}