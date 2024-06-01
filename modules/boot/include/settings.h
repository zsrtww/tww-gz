#pragma once

#include <stdint.h>
#include "utils/lines.h"

#define CURSOR_RGBA g_cursorColor
#define FONT_OPTIONS_COUNT (sizeof(g_font_opt) / sizeof(g_font_opt[0]))

#define LOAD_AREA 0
#define LOAD_FILE 1

extern bool g_dropShadows;
extern uint32_t g_fontType;
extern uint32_t g_cursorColorType;
extern ListMember g_font_opt[7];

enum cursor_colors {
    CURSOR_GREEN,
    CURSOR_BLUE,
    CURSOR_RED,
    CURSOR_ORANGE,
    CURSOR_YELLOW,
    CURSOR_PURPLE
};

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

extern ItemEquipSettings g_item_equip_priorities[NUM_EQUIPPABLE_ITEMS];

void GZ_initFont();
