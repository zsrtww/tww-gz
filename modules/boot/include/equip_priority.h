#pragma once

#include "libtww/include/dolphin/gctypes.h"

#define NUM_EQUIPPABLE_ITEMS 14

enum ItemEquipColumns { ItemName, HighPriority, MediumPriority };
enum ButtonNames { name_X, name_Y, name_Z };
enum ItemEquipNames {
    NO_ITEM_EQUIP,
    TELESCOPE_EQUIP,
    SAIL_EQUIP,
    WIND_WAKER_EQUIP,
    GRAPPLING_HOOK_EQUIP,
    BOOMERANG_EQUIP,
    DEKU_LEAF_EQUIP,
    TINGLE_TUNER_EQUIP,
    PROGRESSIVE_PICTO_BOX_EQUIP,
    IRON_BOOTS_EQUIP,
    MAGIC_ARMOR_EQUIP,
    PROGRESSIVE_BOW_EQUIP,
    BOMBS_EQUIP,
    HOOKSHOT_EQUIP,
    SKULL_HAMMER_EQUIP,
};

struct ItemEquipSettings {
    u8 item_name = NO_ITEM_EQUIP;
    u8 high_priority = name_X;
    u8 medium_priority = name_Y;
    bool line_selected = false;
    bool value_selected = false;
};

u8 item_enum_to_item_slot(u8 item_enum);
char button_enum_to_name(u8 button_enum, u8 item_enum);
const char* item_enum_to_name(u8 item_enum);

extern bool g_enable_item_equip_menu;
extern ItemEquipSettings g_item_equip_priorities[NUM_EQUIPPABLE_ITEMS];