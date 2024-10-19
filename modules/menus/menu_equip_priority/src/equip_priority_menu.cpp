#include "menus/menu_equip_priority/include/equip_priority_menu.h"
#include "equip_priority.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define ITEM_X_OFFSET 25.0f

KEEP_FUNC ItemEquipPriorityMenu::ItemEquipPriorityMenu(Cursor& cursor) : Menu(cursor) {}

ItemEquipPriorityMenu::~ItemEquipPriorityMenu() {}

bool ItemEquipPriorityMenu::checkItemLineSelected() {
    return l_selectedLine >= 0;
}

bool ItemEquipPriorityMenu::checkLineValSelected() {
    return l_selectedCol >= 0;
}

static const GZSettingID l_setting_ids[] = {
    STNG_ITEM_EQUIP_TELESCOPE,       STNG_ITEM_EQUIP_SAIL,
    STNG_ITEM_EQUIP_WIND_WAKER,      STNG_ITEM_EQUIP_GRAPPLING_HOOK,
    STNG_ITEM_EQUIP_BOOMERANG,       STNG_ITEM_EQUIP_DEKU_LEAF,
    STNG_ITEM_EQUIP_TINGLE_TUNER,    STNG_ITEM_EQUIP_PROGRESSIVE_PICTO_BOX,
    STNG_ITEM_EQUIP_IRON_BOOTS,      STNG_ITEM_EQUIP_MAGIC_ARMOR,
    STNG_ITEM_EQUIP_PROGRESSIVE_BOW, STNG_ITEM_EQUIP_BOMBS,
    STNG_ITEM_EQUIP_HOOKSHOT,        STNG_ITEM_EQUIP_SKULL_HAMMER,
};

static const char* l_names[] = {
    "Telescope",  "Sail",         "Wind Waker",      "Grappling Hook",
    "Boomerang",  "Deku Leaf",    "Tingle Tuner",    "Progressive Picto Box",
    "Iron Boots", "Magic Armor",  "Progressive Bow", "Bombs",
    "Hookshot",   "Skull Hammer",
};

static const char l_button_names[] = {
    'X',
    'Y',
    'Z',
};

void ItemEquipPriorityMenu::drawItemEquipLines() {
    const float item_equip_high_pos_x_offset =
        ITEM_X_OFFSET + maxF(GZ_getTextWidth("Item"), GZ_getTextWidth("Progressive Picto Box")) + 5.0f;
    const float item_equip_medium_pos_x_offset =
        item_equip_high_pos_x_offset + maxF(GZ_getTextWidth("High Priority"), GZ_getTextWidth("<X>")) + 5.0f;

    Font::GZ_drawStr("Item", ITEM_X_OFFSET, 60.0f, WHITE, GZ_checkDropShadows());
    Font::GZ_drawStr("High Priority", item_equip_high_pos_x_offset, 60.0f, WHITE, GZ_checkDropShadows());
    Font::GZ_drawStr("Medium Priority", item_equip_medium_pos_x_offset, 60.0f, WHITE, GZ_checkDropShadows());

    for (int i = 0; i < NUM_ITEM_EQUIPS; i++) {
        const float line_y_offset = (80.0f + (i * 20.0f));
        char item_name[32];
        char high_priority_str[4];
        char medium_priority_str[4];

        auto stng = GZStng_get(l_setting_ids[i]);
        ButtonNames high_priority = ButtonNames::name_X;
        ButtonNames medium_priority = ButtonNames::name_Y;
        if (stng != nullptr) {
            high_priority = (*static_cast<ItemEquipSettings*>(stng->data)).high_priority;
            medium_priority = (*static_cast<ItemEquipSettings*>(stng->data)).medium_priority;
        }
        sprintf(item_name, "%s", l_names[i]);
        sprintf(high_priority_str, "<%c>", l_button_names[(int)high_priority]);
        sprintf(medium_priority_str, "<%c>", l_button_names[(int)medium_priority]);

        if (l_selectedLine == i) {
            if (l_selectedCol >= 0) {
                switch ((ItemEquipColumns)l_selectedCol) {
                case HighPriority:
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (!stng) {
                            stng = new GZSettingEntry{l_setting_ids[i], sizeof(ItemEquipSettings),
                                                      new ItemEquipSettings{name_X, name_Y}};
                            g_settings.push_back(stng);
                        }
                        static_cast<ItemEquipSettings*>(stng->data)->high_priority = static_cast<ButtonNames>(
                            (static_cast<ItemEquipSettings*>(stng->data)->high_priority + 1) % 3);
                        high_priority = (*static_cast<ItemEquipSettings*>(stng->data)).high_priority;
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (!stng) {
                            stng = new GZSettingEntry{l_setting_ids[i], sizeof(ItemEquipSettings),
                                                      new ItemEquipSettings{name_X, name_Y}};
                            g_settings.push_back(stng);
                        }
                        static_cast<ItemEquipSettings*>(stng->data)->high_priority = static_cast<ButtonNames>(
                            (static_cast<ItemEquipSettings*>(stng->data)->high_priority + 2) % 3);
                        high_priority = (*static_cast<ItemEquipSettings*>(stng->data)).high_priority;
                    }
                    sprintf(high_priority_str, "<%c>", l_button_names[high_priority]);
                    Font::GZ_drawStr(high_priority_str, item_equip_high_pos_x_offset - 8.0f, line_y_offset, CURSOR_RGBA,
                                     GZ_checkDropShadows());
                    Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, WHITE, GZ_checkDropShadows());
                    Font::GZ_drawStr(medium_priority_str, item_equip_medium_pos_x_offset, line_y_offset, WHITE,
                                     GZ_checkDropShadows());
                    break;
                case MediumPriority:
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (!stng) {
                            stng = new GZSettingEntry{l_setting_ids[i], sizeof(ItemEquipSettings),
                                                      new ItemEquipSettings{name_X, name_Y}};
                            g_settings.push_back(stng);
                        }
                        static_cast<ItemEquipSettings*>(stng->data)->medium_priority = static_cast<ButtonNames>(
                            (static_cast<ItemEquipSettings*>(stng->data)->medium_priority + 1) % 3);
                        if (static_cast<ItemEquipSettings*>(stng->data)->medium_priority ==
                            static_cast<ItemEquipSettings*>(stng->data)->high_priority) {
                            static_cast<ItemEquipSettings*>(stng->data)->medium_priority = static_cast<ButtonNames>(
                                (static_cast<ItemEquipSettings*>(stng->data)->medium_priority + 1) % 3);
                        }
                        medium_priority = (*static_cast<ItemEquipSettings*>(stng->data)).medium_priority;
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (!stng) {
                            stng = new GZSettingEntry{l_setting_ids[i], sizeof(ItemEquipSettings),
                                                      new ItemEquipSettings{name_X, name_Y}};
                            g_settings.push_back(stng);
                        }
                        static_cast<ItemEquipSettings*>(stng->data)->medium_priority = static_cast<ButtonNames>(
                            (static_cast<ItemEquipSettings*>(stng->data)->medium_priority + 2) % 3);
                        if (static_cast<ItemEquipSettings*>(stng->data)->medium_priority ==
                            static_cast<ItemEquipSettings*>(stng->data)->high_priority) {
                            static_cast<ItemEquipSettings*>(stng->data)->medium_priority = static_cast<ButtonNames>(
                                (static_cast<ItemEquipSettings*>(stng->data)->medium_priority + 2) % 3);
                        }
                        medium_priority = (*static_cast<ItemEquipSettings*>(stng->data)).medium_priority;
                    }
                    sprintf(medium_priority_str, "<%c>", l_button_names[medium_priority]);
                    Font::GZ_drawStr(medium_priority_str, item_equip_medium_pos_x_offset - 8.0f, line_y_offset,
                                     CURSOR_RGBA, GZ_checkDropShadows());
                    Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, WHITE, GZ_checkDropShadows());
                    Font::GZ_drawStr(high_priority_str, item_equip_high_pos_x_offset, line_y_offset, WHITE,
                                     GZ_checkDropShadows());
                    break;
                }
            } else {
                int y = cursor.y;
                int x = cursor.x;
                Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, WHITE, GZ_checkDropShadows());
                Font::GZ_drawStr(high_priority_str, item_equip_high_pos_x_offset, line_y_offset,
                                 (y == i && x == HighPriority ? CURSOR_RGBA : WHITE), GZ_checkDropShadows());
                Font::GZ_drawStr(medium_priority_str, item_equip_medium_pos_x_offset, line_y_offset,
                                 (y == i && x == MediumPriority ? CURSOR_RGBA : WHITE), GZ_checkDropShadows());
            }
        } else {
            int y = cursor.y;
            Font::GZ_drawStr(item_name, ITEM_X_OFFSET, line_y_offset, (y == i ? CURSOR_RGBA : WHITE),
                             GZ_checkDropShadows());
            Font::GZ_drawStr(high_priority_str, item_equip_high_pos_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE), GZ_checkDropShadows());
            Font::GZ_drawStr(medium_priority_str, item_equip_medium_pos_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE), GZ_checkDropShadows());
        }
    }
}

void ItemEquipPriorityMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(GZPad::B)) {
        if (checkLineValSelected()) {
            l_selectedCol = -1;
            auto stng = GZStng_get(l_setting_ids[l_selectedLine]);
            if (stng) {
                if (static_cast<ItemEquipSettings*>(stng->data)->high_priority ==
                    static_cast<ItemEquipSettings*>(stng->data)->medium_priority) {
                    static_cast<ItemEquipSettings*>(stng->data)->medium_priority = static_cast<ButtonNames>(
                        (static_cast<ItemEquipSettings*>(stng->data)->medium_priority + 1) % 3);
                }
            }
            cursor.lock_x = false;
        } else if (checkItemLineSelected()) {
            l_selectedLine = -1;
            cursor.lock_y = false;
        } else {
            g_menuMgr->pop();
            return;
        }
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        if (l_selectedCol >= 0) {
            l_selectedCol = -1;
            cursor.lock_x = false;
        } else if (l_selectedLine >= 0) {
            l_selectedCol = cursor.x;
            cursor.lock_x = true;
        } else {
            if (cursor.y < NUM_ITEM_EQUIPS) {
                l_selectedLine = cursor.y;
                cursor.lock_y = true;
            }
        }
    }

    if (GZ_getButtonTrig(GZPad::Z)) {
        auto stng = GZStng_get(STNG_EQUIP_PRIORITY);
        if (!stng) {
            stng = new GZSettingEntry{STNG_EQUIP_PRIORITY, sizeof(bool), new bool{false}};
            g_settings.push_back(stng);
        }
        *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
    }

    cursor.move(2, NUM_ITEM_EQUIPS);

    if (GZStng_getData<bool>(STNG_EQUIP_PRIORITY, false)) {
        Font::GZ_drawStr("enable/disable [X]", ITEM_X_OFFSET, 400.f, WHITE, GZ_checkDropShadows());
    } else {
        Font::GZ_drawStr("enable/disable [ ]", ITEM_X_OFFSET, 400.f, WHITE, GZ_checkDropShadows());
    }

    Font::GZ_drawStr("Press START to move row to top", 25.0f, 440.f, WHITE, GZ_checkDropShadows());
    Font::GZ_drawStr("Press Z to toggle menu", 25.0f, 460.f, WHITE, GZ_checkDropShadows());
    drawItemEquipLines();
}
