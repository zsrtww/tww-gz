#include "menus/menu_equip_priority/include/equip_priority_menu.h"
#include "equip_priority.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define ITEM_X_OFFSET 25.0f

KEEP_FUNC ItemEquipPriorityMenu::ItemEquipPriorityMenu(Cursor& cursor) : Menu(cursor) {}

ItemEquipPriorityMenu::~ItemEquipPriorityMenu() {}

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

        sprintf(item_name, "<%s>", item_enum_to_name(g_item_equip_priorities[i].item_name));
        sprintf(high_priority, "<%c>",
                button_enum_to_name(g_item_equip_priorities[i].high_priority, g_item_equip_priorities[i].item_name));
        sprintf(medium_priority, "<%c>",
                button_enum_to_name(g_item_equip_priorities[i].medium_priority, g_item_equip_priorities[i].item_name));

        if (g_item_equip_priorities[i].line_selected) {
            switch ((ItemEquipColumns)cursor.x) {
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
                    sprintf(item_name, "<%s>", item_enum_to_name(g_item_equip_priorities[i].item_name));
                    Font::GZ_drawStr(item_name, ITEM_X_OFFSET - 8.0f, line_y_offset, CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, CURSOR_RGBA, g_dropShadows);
                }
                Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset, WHITE, g_dropShadows);
                Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset, line_y_offset, WHITE, g_dropShadows);
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
                    sprintf(high_priority, "<%c>",
                            button_enum_to_name(g_item_equip_priorities[i].high_priority,
                                                g_item_equip_priorities[i].item_name));
                    Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset - 8.0f, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                } else {
                    Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                }
                Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, WHITE, g_dropShadows);
                Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset, line_y_offset, WHITE, g_dropShadows);
                break;
            case MediumPriority:
                if (g_item_equip_priorities[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (g_item_equip_priorities[i].medium_priority == name_Z) {
                            g_item_equip_priorities[i].medium_priority = name_X;
                            if (g_item_equip_priorities[i].medium_priority ==
                                g_item_equip_priorities[i].high_priority) {
                                g_item_equip_priorities[i].medium_priority++;
                            }
                        } else {
                            g_item_equip_priorities[i].medium_priority++;
                            if (g_item_equip_priorities[i].medium_priority ==
                                g_item_equip_priorities[i].high_priority) {
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
                            if (g_item_equip_priorities[i].medium_priority ==
                                g_item_equip_priorities[i].high_priority) {
                                g_item_equip_priorities[i].medium_priority--;
                            }
                        } else {
                            g_item_equip_priorities[i].medium_priority--;
                            if (g_item_equip_priorities[i].medium_priority ==
                                g_item_equip_priorities[i].high_priority) {
                                if (g_item_equip_priorities[i].medium_priority == name_X) {
                                    g_item_equip_priorities[i].medium_priority = name_Z;
                                } else {
                                    g_item_equip_priorities[i].medium_priority--;
                                }
                            }
                        }
                    }
                    sprintf(medium_priority, "<%c>",
                            button_enum_to_name(g_item_equip_priorities[i].medium_priority,
                                                g_item_equip_priorities[i].item_name));
                    Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset - 8.0f, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                } else {
                    Font::GZ_drawStr(medium_priority, item_equip_medium_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                }
                Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, WHITE, g_dropShadows);
                Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset, WHITE, g_dropShadows);
                break;
            }
        } else {
            int y = cursor.y;
            Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, (y == i ? CURSOR_RGBA : WHITE), g_dropShadows);
            Font::GZ_drawStr(high_priority, item_equip_high_pos_x_offset, line_y_offset, (y == i ? CURSOR_RGBA : WHITE),
                             g_dropShadows);
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
            g_menuMgr->pop();
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
        g_equipPriorityEnabled = !g_equipPriorityEnabled;
    }

    if (GZ_getButtonTrig(GZPad::START)) {
        ItemEquipSettings tmp = g_item_equip_priorities[cursor.y];

        for (int i = cursor.y; i > 0; i--) {
            g_item_equip_priorities[i] = g_item_equip_priorities[i - 1];
        }

        g_item_equip_priorities[0] = tmp;
        cursor.y = 0;
    }

    cursor.move(3, NUM_EQUIPPABLE_ITEMS);

    if (g_equipPriorityEnabled) {
        Font::GZ_drawStr("enable/disable [X]", ITEM_X_OFFSET, 400.f, WHITE, g_dropShadows);
    } else {
        Font::GZ_drawStr("enable/disable [ ]", ITEM_X_OFFSET, 400.f, WHITE, g_dropShadows);
    }

    Font::GZ_drawStr("Press START to move row to top", 25.0f, 440.f, WHITE, g_dropShadows);
    Font::GZ_drawStr("Press Z to toggle menu", 25.0f, 460.f, WHITE, g_dropShadows);
    drawItemEquipLines();
}
