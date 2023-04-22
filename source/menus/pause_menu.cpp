#include "controller.h"
#include "menus/main_menu.h"
#include "menus/pause_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"

#define NUM_ITEM_SLOTS 21

Cursor PauseMenu::cursor;

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

const char* item_id_to_str(u8 item_id) {
    switch (item_id) {
    case HEART_DROP:
        return "Heart Drop";
    case GREEN_RUPEE_DROP:
        return "Green Rupee Drop";
    case BLUE_RUPEE_DROP:
        return "Blue Rupee Drop";
    case YELLOW_RUPEE_DROP:
        return "Yellow Rupee Drop";
    case RED_RUPEE_DROP:
        return "Red Rupee Drop";
    case PURPLE_RUPEE_DROP:
        return "Purple Rupee Drop";
    case ORANGE_RUPEE_DROP:
        return "Orange Rupee Drop";
    case HEART_PIECE:
        return "Heart Piece";
    case HEART_CONTAINER:
        return "Heart Container";
    case SMALL_MAGIC_DROP:
        return "Small Magic Drop";
    case LARGE_MAGIC_DROP:
        return "Large Magic Drop";
    case BOMB_DROP:
        return "Bomb Drop";
    case SILVER_RUPEE_DROP:
        return "Silver Rupee Drop";
    case SINGLE_ARROW_DROP:
        return "Single Arrow Drop";
    case DOUBLE_ARROW_DROP:
        return "Double Arrow Drop";
    case TRIPLE_ARROW_DROP:
        return "Triple Arrow Drop";
    case KEY_DROP:
        return "Key Drop";
    case FAIRY_DROP:
        return "Fairy Drop";
    case TRIPLE_HEART_DROP:
        return "Triple Heart Drop";
    case JOY_PENDANT:
        return "Joy Pendant";
    case TELESCOPE:
        return "Telescope";
    case TINGLE_TUNER:
        return "Tingle Tuner";
    case WIND_WAKER:
        return "Wind Waker";
    case PICTO_BOX:
        return "Picto Box";
    case SPOILS_BAG:
        return "Spoils Bag";
    case GRAPPLING_HOOK:
        return "Grappling Hook";
    case DELUXE_PICTO_BOX:
        return "Deluxe Picto Box";
    case BOW:
        return "Bow";
    case POWER_BRACELETS:
        return "Power Bracelets";
    case IRON_BOOTS:
        return "Iron Boots";
    case MAGIC_ARMOR:
        return "Magic Armor";
    case WATER_BOOTS:
        return "Water Boots";
    case BAIT_BAG:
        return "Bait Bag";
    case BOOMERANG:
        return "Boomerang";
    case HOOKSHOT:
        return "Hookshot";
    case DELIVERY_BAG:
        return "Delivery Bag";
    case BOMBS:
        return "Bombs";
    case TUNIC:
        return "Tunic";
    case SKULL_HAMMER:
        return "Skull Hammer";
    case DEKU_LEAF:
        return "Deku Leaf";
    case BOW_WITH_FIRE_AND_ICE_ARROWS:
        return "Bow With Fire And Ice Arrows";
    case BOW_WITH_LIGHT_ARROWS:
        return "Bow With Light Arrows";
    case HEROS_SWORD:
        return "Hero\'s Sword";
    case UNCHARGED_MASTER_SWORD:
        return "Uncharged Master Sword";
    case HALF_CHARGED_MASTER_SWORD:
        return "Half Charged Master Sword";
    case HEROS_SHIELD:
        return "Hero\'s Shield";
    case MIRROR_SHIELD:
        return "Mirror Shield";
    case FULLY_CHARGED_MASTER_SWORD:
        return "Fully Charged Master Sword";
    case PIRATES_CHARM:
        return "Pirate\'s Charm";
    case HEROS_CHARM:
        return "Hero\'s Charm";
    case SKULL_NECKLACE:
        return "Skull Necklace";
    case BOKO_BABA_SEED:
        return "Boko Baba Seed";
    case GOLDEN_FEATHER:
        return "Golden Feather";
    case KNIGHTS_CREST:
        return "Knight\'s Crest";
    case RED_CHU_JELLY:
        return "Red Chu Jelly";
    case GREEN_CHU_JELLY:
        return "Green Chu Jelly";
    case BLUE_CHU_JELLY:
        return "Blue Chu Jelly";
    case MAP:
        return "Map";
    case COMPASS:
        return "Compass";
    case BIG_KEY:
        return "Big Key";
    case EMPTY_BOTTLE:
        return "Empty Bottle";
    case RED_POTION:
        return "Red Potion";
    case GREEN_POTION:
        return "Green Potion";
    case BLUE_POTION:
        return "Blue Potion";
    case ELIXIR_SOUP_HALF:
        return "Elixir Soup (Half)";
    case ELIXIR_SOUP:
        return "Elixir Soup (Full)";
    case WATER:
        return "Water";
    case FAIRY:
        return "Fairy";
    case FOREST_FIREFLY:
        return "Forest Firefly";
    case FOREST_WATER:
        return "Forest Water";
    case TRIFORCE_PIECE_1:
        return "Triforce Piece 1";
    case TRIFORCE_PIECE_2:
        return "Triforce Piece 2";
    case TRIFORCE_PIECE_3:
        return "Triforce Piece 3";
    case TRIFORCE_PIECE_4:
        return "Triforce Piece 4";
    case TRIFORCE_PIECE_5:
        return "Triforce Piece 5";
    case TRIFORCE_PIECE_6:
        return "Triforce Piece 6";
    case TRIFORCE_PIECE_7:
        return "Triforce Piece 7";
    case TRIFORCE_PIECE_8:
        return "Triforce Piece 8";
    case NAYRUS_PEARL:
        return "Nayru\'s Pearl";
    case DINS_PEARL:
        return "Din\'s Pearl";
    case FARORES_PEARL:
        return "Farore\'s Pearl";
    case SAIL:
        return "Sail";
    case TRIFORCE_CHART:
        return "Triforce Chart";
    case ALL_PURPOSE_BAIT:
        return "All Purpose Bait";
    case HYOI_PEAR:
        return "Hyoi Pear";
    case TOWN_FLOWER:
        return "Town Flower";
    case SEA_FLOWER:
        return "Sea Flower";
    case EXOTIC_FLOWER:
        return "Exotic Flower";
    case HEROS_FLAG:
        return "Hero\'s Flag";
    case BIG_CATCH_FLAG:
        return "Big Catch Flag";
    case BIG_SALE_FLAG:
        return "Big Sale Flag";
    case PINWHEEL:
        return "Pinwheel";
    case SICKLE_MOON_FLAG:
        return "Sickle Moon Flag";
    case SKULL_TOWER_IDOL:
        return "Skull Tower Idol";
    case FOUNTAIN_IDOL:
        return "Fountain Idol";
    case POSTMAN_STATUE:
        return "Postman Statue";
    case SHOP_GURU_STATUE:
        return "Shop Guru Statue";
    case FATHERS_LETTER:
        return "Father\'s Letter";
    case NOTE_TO_MOM:
        return "Note to Mom";
    case MAGGIES_LETTER:
        return "Maggie\'s Letter";
    case MOBLINS_LETTER:
        return "Moblin\'s Letter";
    case CABANA_DEED:
        return "Cabana Deed";
    case COMPLIMENTARY_ID:
        return "Complimentary ID";
    case FILL_UP_COUPON:
        return "Fill Up Coupon";
    case GOLDEN_TINGLE_HEAD:
        return "Tingle Statue";
    case NO_ITEM:
        return "Empty";
    default:
        return "???";
    };
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
    dComIfGs_setItemSlot(slot, new_item_id);
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
    dComIfGs_setItemSlot(slot, new_item_id);
}

void PauseMenu::draw() {
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
        dComIfGs_setItemSlot(SLOT_CAMERA, new_item_id);
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
        dComIfGs_setItemSlot(SLOT_BOW, new_item_id);
        break;
    case SLOT_BOMB:
        updateSingleItem(SLOT_BOMB, BOMBS);
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