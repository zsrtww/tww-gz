#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "libtww/d/save/d_save.h"

#define LINE_NUM 7

Cursor InventoryMenu::cursor;

Line lines[LINE_NUM] = {
    {"amounts", AMOUNT_INDEX, "Modify amounts for health, magic, etc."},
    {"item inventory", ITEM_INVENTORY_INDEX, "Modify item inventory menu"},
    {"quest status", QUEST_STATUS_INDEX, "Modify quest status menu"},
    {"delivery bag", DELIVERY_BAG_INDEX, "Modify delivery bag items/amounts"},
    {"spoils", SPOILS_INDEX, "Modify spoils bag items/amounts"},
    {"bait", BAIT_INDEX, "Modify bait bag items/amounts"},
    {"charts", CHART_INDEX, "Modify charts"},
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
        case QUEST_STATUS_INDEX:
            GZ_setMenu(GZ_QUEST_STATUS_MENU);
            return;
        case SPOILS_INDEX:
            GZ_setMenu(GZ_SPOILS_MENU);
            return;
        case DELIVERY_BAG_INDEX:
            GZ_setMenu(GZ_DELIVERY_MENU);
            return;
        case BAIT_INDEX:
            GZ_setMenu(GZ_BAIT_MENU);
            return;
        case CHART_INDEX:
            GZ_setMenu(GZ_CHART_MENU);
            return;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}