#include "controller.h"
#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "menus/item_inventory_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"

#define NUM_ITEM_SLOTS 21

#define DEFAULT_ARROW_CAPACITY 30
#define DEFAULT_BOMB_CAPACITY 30

Cursor ItemInventoryMenu::cursor;

Line lines[NUM_ITEM_SLOTS] = {
    {"Telescope:", SLOT_TELESCOPE, "Add/remove Telescope to/from inventory"},
    {"Sail:", SLOT_SAIL, "Add/remove Sail to/from inventory"},
    {"Wind Waker:", SLOT_WIND_WAKER, "Add/remove Wind Waker to/from inventory"},
    {"Grappling Hook:", SLOT_ROPE, "Add/remove Grappling Hook to/from inventory"},
    {"Spoils Bag:", SLOT_SPOILS_BAG, "Add/remove Spoils Bag to/from inventory"},
    {"Boomerang:", SLOT_BOOMERANG, "Add/remove Boomerang to/from inventory"},
    {"Deku Leaf:", SLOT_DEKU_LEAF, "Add/remove Deku Leaf to/from inventory"},
    {"Tingle Tuner:", SLOT_TUNER, "Add/remove Tingle Tuner to/from inventory"},
    {"Progressive Picto Box:", SLOT_CAMERA, "Add/remove/upgrade Picto Box"},
    {"Iron Boots:", SLOT_IRON_BOOTS, "Add/remove Iron Boots to/from inventory"},
    {"Magic Armor:", SLOT_MAGIC_ARMOR, "Add/remove Magic Armor to/from inventory"},
    {"Bait Bag:", SLOT_BAIT_BAG, "Add/remove Bait Bag to/from inventory"},
    {"Progressive Bow:", SLOT_BOW, "Add/remove/upgrade Bow"},
    {"Bombs:", SLOT_BOMB, "Add/remove Bombs to/from inventory"},
    {"Bottle 1:", SLOT_BOTTLE_1, "Add/remove Bottle 1 to/from inventory"},
    {"Bottle 2:", SLOT_BOTTLE_2, "Add/remove Bottle 2 to/from inventory"},
    {"Bottle 3:", SLOT_BOTTLE_3, "Add/remove Bottle 3 to/from inventory"},
    {"Bottle 4:", SLOT_BOTTLE_4, "Add/remove Bottle 4 to/from inventory"},
    {"Delivery Bag:", SLOT_TRADE_ITEM, "Add/remove Delivery Bag to/from inventory"},
    {"Hookshot:", SLOT_HOOKSHOT, "Add/remove Hookshot to/from inventory"},
    {"Skull Hammer:", SLOT_HAMMER, "Add/remove Skull Hammer to/from inventory"}
};


void updateItemFlag(u8 slot, u8 item_id) {
    u8 has_item = item_id == NO_ITEM ? 0 : 1;
    dComIfGs_setItemFlag(slot, has_item);
}

void updateItem(u8 slot, u8 item_id) {
    dComIfGs_setItemSlot(slot, item_id);
    updateItemFlag(slot, item_id);
}

void updateSingleItem(u8 slot, u8 item_id) {
    u8 new_item_id = dComIfGs_getItemSlot(slot);
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
        new_item_id = dComIfGs_getItemSlot(slot);
    }
    updateItem(slot, new_item_id);
}

void updateBottle(u8 slot) {
    u8 new_item_id = dComIfGs_getItemSlot(slot);
    Cursor::moveListSimple(new_item_id);
    if (new_item_id == NO_ITEM - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == 0) {
        new_item_id = EMPTY_BOTTLE;
    } else if (new_item_id == EMPTY_BOTTLE - 1) {
        new_item_id = NO_ITEM;
    } else if (new_item_id == FOREST_FIREFLY + 1) {
        dComIfGs_setForestWaterTimer(36000);
    } else if (new_item_id == FOREST_WATER - 1) {
        dComIfGs_setForestWaterTimer(0);
    } else if (new_item_id == FOREST_WATER + 1) {
        new_item_id = FOREST_WATER;
    }
    updateItem(slot, new_item_id);
}

void ItemInventoryMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
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
        new_item_id = dComIfGs_getItemSlot(SLOT_CAMERA);
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
            new_item_id = dComIfGs_getItemSlot(SLOT_CAMERA);
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
        new_item_id = dComIfGs_getItemSlot(SLOT_BOW);
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
        if (GZ_getButtonTrig(GZPad::DPAD_RIGHT) && dComIfGs_getArrowCapacity() == 0) {
            dComIfGs_setArrowCapacity(DEFAULT_ARROW_CAPACITY);
            dComIfGs_setArrowNum(DEFAULT_ARROW_CAPACITY);
        }
        break;
    case SLOT_BOMB:
        updateSingleItem(SLOT_BOMB, BOMBS);
    if (GZ_getButtonTrig(GZPad::DPAD_RIGHT) && dComIfGs_getBombCapacity() == 0) {
            dComIfGs_setBombCapacity(DEFAULT_BOMB_CAPACITY);
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
    };

    tww_sprintf(lines[SLOT_TELESCOPE].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_TELESCOPE)));
    tww_sprintf(lines[SLOT_SAIL].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_SAIL)));
    tww_sprintf(lines[SLOT_WIND_WAKER].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_WIND_WAKER)));
    tww_sprintf(lines[SLOT_ROPE].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_ROPE)));
    tww_sprintf(lines[SLOT_SPOILS_BAG].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_SPOILS_BAG)));
    tww_sprintf(lines[SLOT_BOOMERANG].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BOOMERANG)));
    tww_sprintf(lines[SLOT_DEKU_LEAF].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_DEKU_LEAF)));
    tww_sprintf(lines[SLOT_TUNER].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_TUNER)));
    tww_sprintf(lines[SLOT_CAMERA].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_CAMERA)));
    tww_sprintf(lines[SLOT_IRON_BOOTS].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_IRON_BOOTS)));
    tww_sprintf(lines[SLOT_MAGIC_ARMOR].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_MAGIC_ARMOR)));
    tww_sprintf(lines[SLOT_BAIT_BAG].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BAIT_BAG)));
    tww_sprintf(lines[SLOT_BOW].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BOW)));
    tww_sprintf(lines[SLOT_BOMB].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BOMB)));
    tww_sprintf(lines[SLOT_BOTTLE_1].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BOTTLE_1)));
    tww_sprintf(lines[SLOT_BOTTLE_2].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BOTTLE_2)));
    tww_sprintf(lines[SLOT_BOTTLE_3].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BOTTLE_3)));
    tww_sprintf(lines[SLOT_BOTTLE_4].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_BOTTLE_4)));
    tww_sprintf(lines[SLOT_TRADE_ITEM].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_TRADE_ITEM)));
    tww_sprintf(lines[SLOT_HOOKSHOT].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_HOOKSHOT)));
    tww_sprintf(lines[SLOT_HAMMER].value, " <%s>", item_id_to_str(dComIfGs_getItemSlot(SLOT_HAMMER)));

    cursor.move(0, NUM_ITEM_SLOTS);
    GZ_drawMenuLines(lines, cursor.y, NUM_ITEM_SLOTS);
}