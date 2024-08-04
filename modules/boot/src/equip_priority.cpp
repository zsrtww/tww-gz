#include "equip_priority.h"
#include "libtww/include/d/save/d_save.h"
#include "rels/include/defines.h"

KEEP_VAR ItemEquipSettings g_item_equip_priorities[NUM_EQUIPPABLE_ITEMS] = {};
KEEP_VAR bool g_enable_item_equip_menu = false;

KEEP_FUNC char button_enum_to_name(u8 button_enum, u8 item_enum) {
    if (item_enum == NO_ITEM_EQUIP)
        return '?';

    switch (button_enum) {
        case name_X:
            return 'X';
        case name_Y:
            return 'Y';
        case name_Z:
            return 'Z';
        default:
            return 'X';
    }
}

KEEP_FUNC const char* item_enum_to_name(u8 item_enum) {
    switch (item_enum) {
        case NO_ITEM_EQUIP:
            return "No Item";
        case TELESCOPE_EQUIP:
            return "Telescope";
        case SAIL_EQUIP:
            return "Sail";
        case WIND_WAKER_EQUIP:
            return "Wind Waker";
        case GRAPPLING_HOOK_EQUIP:
            return "Grappling Hook";
        case BOOMERANG_EQUIP:
            return "Boomerang";
        case DEKU_LEAF_EQUIP:
            return "Deku Leaf";
        case TINGLE_TUNER_EQUIP:
            return "Tingle Tuner";
        case PROGRESSIVE_PICTO_BOX_EQUIP:
            return "Progressive Picto Box";
        case IRON_BOOTS_EQUIP:
            return "Iron Boots";
        case MAGIC_ARMOR_EQUIP:
            return "Magic Armor";
        case PROGRESSIVE_BOW_EQUIP:
            return "Progressive Bow";
        case BOMBS_EQUIP:
            return "Bombs";
        case HOOKSHOT_EQUIP:
            return "Hookshot";
        case SKULL_HAMMER_EQUIP:
            return "Skull Hammer";
        default:
            return "No Item";
    }
}

KEEP_FUNC u8 item_enum_to_item_slot(u8 item_enum) {
    switch (item_enum) {
        case NO_ITEM_EQUIP:
            return NO_ITEM;
        case TELESCOPE_EQUIP:
            return SLOT_TELESCOPE;
        case SAIL_EQUIP:
            return SLOT_SAIL;
        case WIND_WAKER_EQUIP:
            return SLOT_WIND_WAKER;
        case GRAPPLING_HOOK_EQUIP:
            return SLOT_ROPE;
        case BOOMERANG_EQUIP:
            return SLOT_BOOMERANG;
        case DEKU_LEAF_EQUIP:
            return SLOT_DEKU_LEAF;
        case TINGLE_TUNER_EQUIP:
            return SLOT_TUNER;
        case PROGRESSIVE_PICTO_BOX_EQUIP:
            return SLOT_CAMERA;
        case IRON_BOOTS_EQUIP:
            return SLOT_IRON_BOOTS;
        case MAGIC_ARMOR_EQUIP:
            return SLOT_MAGIC_ARMOR;
        case PROGRESSIVE_BOW_EQUIP:
            return SLOT_BOW;
        case BOMBS_EQUIP:
            return SLOT_BOMB;
        case HOOKSHOT_EQUIP:
            return SLOT_HOOKSHOT;
        case SKULL_HAMMER_EQUIP:
            return SLOT_HAMMER;
        default:
            return NO_ITEM;
    }
}