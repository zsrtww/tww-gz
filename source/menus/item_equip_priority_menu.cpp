#include "libtww/MSL_C/string.h"
#include "libtww/d/save/d_save.h"
#include "menus/item_equip_priority_menu.h"
#include "menus/settings_menu.h"
#include "color.h"

#define ITEM_X_OFFSET 25.0f

Cursor ItemEquipPriorityMenu::cursor;

ItemEquipSettings g_item_equip_priorities[NUM_EQUIPPABLE_ITEMS] = {};
bool g_enable_item_equip_menu;

char button_enum_to_name(u8 button_enum, u8 item_enum) {
    if (item_enum == NO_ITEM_EQUIP) return '?';

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

const char* item_enum_to_name(u8 item_enum) {
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

u8 item_enum_to_item_slot(u8 item_enum) {
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

bool checkItemLineSelected() {
    bool return_value = false;
    for (int i = 0; i < NUM_EQUIPPABLE_ITEMS; i++) {
        if (g_item_equip_priorities[i].line_selected) {
            return_value = true;
        }
    }
    return return_value;
}

bool checkLineValSelected() {
    bool return_value = false;
    for (int i = 0; i < NUM_EQUIPPABLE_ITEMS; i++) {
        if (g_item_equip_priorities[i].value_selected) {
            return_value = true;
        }
    }
    return return_value;
}

void ItemEquipPriorityMenu::drawItemEquipLines() {
    const float item_equip_high_pos_x_offset =
        ITEM_X_OFFSET + maxF(GZ_getTextWidth("Item"), GZ_getTextWidth("<Progressive Picto Box>")) + 5.0f;
    const float item_equip_medium_pos_x_offset =
        item_equip_high_pos_x_offset + maxF(GZ_getTextWidth("High Priority"), GZ_getTextWidth("<X>")) + 5.0f;

    Font::GZ_drawStr("Item", ITEM_X_OFFSET, 60.0f, WHITE, g_dropShadows);
    Font::GZ_drawStr("High Priority", item_equip_high_pos_x_offset, 60.0f, WHITE, g_dropShadows);
    Font::GZ_drawStr("Medium Priority", item_equip_medium_pos_x_offset, 60.0f, WHITE, g_dropShadows);

    for (int i = 0; i < NUM_EQUIPPABLE_ITEMS; i++) {
        const float line_y_offset = (80.0f + (i * 20.0f));
        char item_name[32];
        char high_priority[4];
        char medium_priority[4];

        tww_sprintf(item_name, "<%s>", item_enum_to_name(g_item_equip_priorities[i].item_name));
        tww_sprintf(high_priority, "<%c>", button_enum_to_name(g_item_equip_priorities[i].high_priority, g_item_equip_priorities[i].item_name));
        tww_sprintf(medium_priority, "<%c>", button_enum_to_name(g_item_equip_priorities[i].medium_priority, g_item_equip_priorities[i].item_name));

        if (g_item_equip_priorities[i].line_selected) {
            switch ((ItemEquipColumns) cursor.x) {
            case ItemName:
                if (g_item_equip_priorities[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (g_item_equip_priorities[i].item_name == SKULL_HAMMER_EQUIP) {
                            g_item_equip_priorities[i].item_name = NO_ITEM_EQUIP;
                        } else {
                            g_item_equip_priorities[i].item_name++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (g_item_equip_priorities[i].item_name == NO_ITEM_EQUIP) {
                            g_item_equip_priorities[i].item_name = SKULL_HAMMER_EQUIP;
                        } else {
                            g_item_equip_priorities[i].item_name--;
                        }
                    }
                    tww_sprintf(item_name, "<%s>", item_enum_to_name(g_item_equip_priorities[i].item_name));
                    Font::GZ_drawStr(item_name, ITEM_X_OFFSET - 8.0f, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, CURSOR_RGBA,
                                 g_dropShadows);
                }
                Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset, WHITE,
                                 g_dropShadows);
                Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset, line_y_offset, WHITE,
                                 g_dropShadows);
                break;
            case HighPriority:
                if (g_item_equip_priorities[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (g_item_equip_priorities[i].high_priority == name_Z) {
                            g_item_equip_priorities[i].high_priority = name_X;
                        } else {
                            g_item_equip_priorities[i].high_priority++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (g_item_equip_priorities[i].high_priority == name_X) {
                            g_item_equip_priorities[i].high_priority = name_Z;
                        } else {
                            g_item_equip_priorities[i].high_priority--;
                        }
                    }
                    tww_sprintf(high_priority, "<%c>", button_enum_to_name(g_item_equip_priorities[i].high_priority, g_item_equip_priorities[i].item_name));
                    Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset - 8.0f, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                 g_dropShadows);
                }
                Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, WHITE,
                                 g_dropShadows);
                Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset, line_y_offset, WHITE,
                                 g_dropShadows);
                break;
            case MediumPriority:
                if (g_item_equip_priorities[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (g_item_equip_priorities[i].medium_priority == name_Z) {
                            g_item_equip_priorities[i].medium_priority = name_X;
                            if (g_item_equip_priorities[i].medium_priority == g_item_equip_priorities[i].high_priority) {
                                g_item_equip_priorities[i].medium_priority++;
                            }
                        } else {
                            g_item_equip_priorities[i].medium_priority++;
                            if (g_item_equip_priorities[i].medium_priority == g_item_equip_priorities[i].high_priority) {
                                if (g_item_equip_priorities[i].medium_priority == name_Z) {
                                    g_item_equip_priorities[i].medium_priority = name_X;
                                } else {
                                    g_item_equip_priorities[i].medium_priority++;
                                }
                            }
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (g_item_equip_priorities[i].medium_priority == name_X) {
                            g_item_equip_priorities[i].medium_priority = name_Z;
                            if (g_item_equip_priorities[i].medium_priority == g_item_equip_priorities[i].high_priority) {
                                g_item_equip_priorities[i].medium_priority--;
                            }
                        } else {
                            g_item_equip_priorities[i].medium_priority--;
                            if (g_item_equip_priorities[i].medium_priority == g_item_equip_priorities[i].high_priority) {
                                if (g_item_equip_priorities[i].medium_priority == name_X) {
                                    g_item_equip_priorities[i].medium_priority = name_Z;
                                } else {
                                    g_item_equip_priorities[i].medium_priority--;
                                }
                            }
                        }
                    }
                    tww_sprintf(medium_priority, "<%c>", button_enum_to_name(g_item_equip_priorities[i].medium_priority, g_item_equip_priorities[i].item_name));
                    Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset - 8.0f, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                 g_dropShadows);
                }
                Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, WHITE,
                                 g_dropShadows);
                Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset, WHITE,
                                 g_dropShadows);
                break;
            }
        } else {
            int y = cursor.y;
            Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE), g_dropShadows);
            Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE), g_dropShadows);
            Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE), g_dropShadows);
        }

    }
}

void ItemEquipPriorityMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(GZPad::B)) {
        if (checkLineValSelected()) {
            for (int i = 0; i < NUM_EQUIPPABLE_ITEMS; i++) {
                g_item_equip_priorities[i].value_selected = false;
            }
            g_item_equip_priorities[cursor.y].value_selected = false;
            if (g_item_equip_priorities[cursor.y].high_priority == g_item_equip_priorities[cursor.y].medium_priority) {
                if (g_item_equip_priorities[cursor.y].medium_priority == name_Z) {
                    g_item_equip_priorities[cursor.y].medium_priority = name_X;
                } else {
                    g_item_equip_priorities[cursor.y].medium_priority++;
                }
            }
            cursor.lock_x = false;
        } else if (checkItemLineSelected()) {
            for (int i = 0; i < NUM_EQUIPPABLE_ITEMS; i++) {
                g_item_equip_priorities[i].line_selected = false;
            }
            g_item_equip_priorities[cursor.y].line_selected = false;
            cursor.lock_y = false;
        } else {
            GZ_setMenu(GZ_SETTINGS_MENU);
            return;
        }
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        if (g_item_equip_priorities[cursor.y].value_selected) {
            g_item_equip_priorities[cursor.y].value_selected = false;
            cursor.lock_x = false;
        } else if (g_item_equip_priorities[cursor.y].line_selected) {
            g_item_equip_priorities[cursor.y].value_selected = true;
            cursor.lock_x = true;
        } else {
            g_item_equip_priorities[cursor.y].line_selected = true;
            cursor.lock_y = true;
        }
    }

    if (GZ_getButtonTrig(GZPad::Z)) {
        g_enable_item_equip_menu = !g_enable_item_equip_menu;
    }

    if (GZ_getButtonTrig(GZPad::START)) {
        ItemEquipSettings tmp = g_item_equip_priorities[cursor.y];

        for (int i = cursor.y; i > 0; i--) {
            g_item_equip_priorities[i] = g_item_equip_priorities[i-1];
        }

        g_item_equip_priorities[0] = tmp;
        cursor.y = 0;
    }

    cursor.move(NUM_IEPM_COLUMNS, NUM_EQUIPPABLE_ITEMS);

    if (g_enable_item_equip_menu) {
        Font::GZ_drawStr("enable/disable [X]", ITEM_X_OFFSET, 400.f, WHITE, g_dropShadows);
    } else {
        Font::GZ_drawStr("enable/disable [ ]", ITEM_X_OFFSET, 400.f, WHITE, g_dropShadows);
    }

    Font::GZ_drawStr("Press START to move row to top", 25.0f, 440.f, WHITE, g_dropShadows);
    Font::GZ_drawStr("Press Z to toggle menu", 25.0f, 460.f, WHITE, g_dropShadows);
    drawItemEquipLines();
}