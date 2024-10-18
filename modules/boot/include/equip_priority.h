#pragma once

#include "libtww/include/dolphin/gctypes.h"
#include "libtww/include/d/save/d_save.h"
#include "settings.h"

enum ItemEquipColumns {
    HighPriority,
    MediumPriority
};
enum ButtonNames {
    name_X,
    name_Y,
    name_Z
};
enum ItemEquips {
    NO_ITEM_EQUIP = -1,
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

    NUM_ITEM_EQUIPS,
};

struct ItemEquipSettings {
    ButtonNames high_priority = name_X;
    ButtonNames medium_priority = name_Y;
};
