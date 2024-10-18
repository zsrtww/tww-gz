#include "menus/menu_settings/include/settings_menu.h"
#include <cstdio>
#include "utils/card.h"
#include "gz_flags.h"
#include "fifo_queue.h"
#include "settings.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "boot/include/commands.h"
#include "utils/hook.h"

#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6

KEEP_FUNC SettingsMenu::SettingsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"cursor color:", CURSOR_COLOR_INDEX, "change cursor color", false, nullptr, MAX_CURSOR_COLOR_OPTIONS},
          {"font:", FONT_INDEX, "change font", false, nullptr, FONT_OPTIONS_COUNT},
          {"drop shadows", DROP_SHADOWS_INDEX, "adds shadows to all font letters", true, GZ_checkDropShadows},
          {"decimal angles", ANGLE_DECIMAL_INDEX, "display angles in decimal instead of hex", true,
           ACTIVE_FUNC(STNG_ANGLE_VALUES_IN_DECIMAL)},
          {"custom save positions", CUSTOM_POSITIONS_INDEX, "turn on/off custom positions in saves that support them",
           true, []() { return GZStng_getData<bool>(STNG_CUSTOM_SAVE_SPAWNS, DEFAULT_CUSTOM_SAVE_SPAWN); }},
          {"equip priority", ITEM_EQUIP_PRIORITY_INDEX, "adjust priorities on item equips in practice saves", false},
          {"save card", SAVE_CARD_INDEX, "save settings to memory card"},
          {"load card", LOAD_CARD_INDEX, "load settings from memory card"},
          {"delete card", DELETE_CARD_INDEX, "delete settings from memory card"},
          {"menu positions", POS_SETTINGS_MENU_INDEX,
           "change menu object positions (A to toggle selection, DPad to move)", false},
          {"fast swim speed:", WATER_SPEED_INDEX, "change max speed of fast movement cheat for swimming"},
          {"fast land speed:", LAND_SPEED_INDEX, "change max speed of Fast Movement cheat on land"},
          {"spawn id: ", SPAWN_ID_INDEX, "set spawn id for disable save checks tool, invalid id's will crash"},
      } {}

SettingsMenu::~SettingsMenu() {}

void SettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    GZSettingEntry* stng = nullptr;
    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case DROP_SHADOWS_INDEX:
            stng = GZStng_get(STNG_DROP_SHADOWS);
            if (!stng) {
                stng = new GZSettingEntry{STNG_DROP_SHADOWS, sizeof(bool), new bool{false}};
                g_settings.push_back(stng);
            }
            *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
            break;
        case ANGLE_DECIMAL_INDEX:
            stng = GZStng_get(STNG_ANGLE_VALUES_IN_DECIMAL);
            if (!stng) {
                stng = new GZSettingEntry{STNG_ANGLE_VALUES_IN_DECIMAL, sizeof(bool), new bool{false}};
                g_settings.push_back(stng);
            }
            *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
            break;
        case CUSTOM_POSITIONS_INDEX:
            stng = GZStng_get(STNG_CUSTOM_SAVE_SPAWNS);
            if (!stng) {
                stng = new GZSettingEntry{STNG_CUSTOM_SAVE_SPAWNS, sizeof(bool), new bool{DEFAULT_CUSTOM_SAVE_SPAWN}};
                g_settings.push_back(stng);
            }
            *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
            break;
        case POS_SETTINGS_MENU_INDEX:
            g_menuMgr->push(MN_POS_SETTINGS_INDEX);
            return;
        case ITEM_EQUIP_PRIORITY_INDEX:
            g_menuMgr->push(MN_EQUIP_PRIORITY_INDEX);
            return;
        case SAVE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "twwgz01";
            storage.sector_size = SECTOR_SIZE;
            snprintf(storage.file_name_buffer, sizeof(storage.file_name_buffer), storage.file_name);

            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_storeMemCard(storage);
            }
            break;
        }
        case LOAD_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "twwgz01";
            storage.sector_size = SECTOR_SIZE;
            snprintf(storage.file_name_buffer, sizeof(storage.file_name_buffer), storage.file_name);

            storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_loadMemCard(storage);
            }
            break;
        }
        case DELETE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "twwgz01";
            storage.sector_size = SECTOR_SIZE;
            snprintf(storage.file_name_buffer, sizeof(storage.file_name_buffer), storage.file_name);

            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_deleteMemCard(storage);
            }
            break;
        }
        }
    }

    ListMember cursorCol_opt[MAX_CURSOR_COLOR_OPTIONS] = {"green", "blue", "red", "orange", "yellow", "purple"};

    stng = nullptr;
    auto prev_x = cursor.x;
    // handle list rendering
    switch (cursor.y) {
    case CURSOR_COLOR_INDEX:
        stng = GZStng_get(STNG_CURSOR_COLOR);
        cursor.x = stng ? *static_cast<uint32_t*>(stng->data) : 0;
        prev_x = cursor.x;
        cursor.move(MAX_CURSOR_COLOR_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == CURSOR_COLOR_INDEX) {
            if (cursor.x != prev_x) {
                if (!stng) {
                    stng = new GZSettingEntry{STNG_CURSOR_COLOR, sizeof(uint32_t), new uint32_t(cursor.x)};
                    g_settings.push_back(stng);
                } else {
                    *static_cast<uint32_t*>(stng->data) = cursor.x;
                }
            }
        }
        break;
    case FONT_INDEX: {
        stng = GZStng_get(STNG_FONT);
        cursor.x = stng ? *static_cast<uint32_t*>(stng->data) : 0;
        prev_x = cursor.x;
        int32_t old_font = cursor.x;
        cursor.move(FONT_OPTIONS_COUNT, MENU_LINE_NUM);

        if (cursor.y == FONT_INDEX) {
            if (prev_x != cursor.x) {
                if (!stng) {
                    stng = new GZSettingEntry{STNG_FONT, sizeof(uint32_t), new uint32_t(cursor.x)};
                    g_settings.push_back(stng);
                } else {
                    *static_cast<uint32_t*>(stng->data) = cursor.x;
                }
            }
        }
        if (old_font != cursor.x) {
            uint32_t fontType = stng ? *static_cast<uint32_t*>(stng->data) : 0;
            if (fontType >= 0 && fontType < FONT_OPTIONS_COUNT) {
                char buf[40];
                snprintf(buf, sizeof(buf), "twwgz/fonts/%s.fnt", g_font_opt[fontType].member);
                Font::loadFont(buf);
            }
        }
        break;
    }

    // Controls the constant speed for link's fast movement cheat. moveList to set and cycle through
    // the numbers, and cursor.move so that the list does not stick once option is selected.
    case WATER_SPEED_INDEX: {
        stng = GZStng_get(STNG_WATER_SPEED);
        if (!stng) {
            stng = new GZSettingEntry{STNG_WATER_SPEED, sizeof(float), new float{DEFAULT_WATER_SPEED}};
            g_settings.push_back(stng);
        }
        Cursor::moveList(*static_cast<float*>(stng->data));
        if (GZ_getButtonRepeat(GZPad::A)) {
            *static_cast<float*>(stng->data) += 100.0f;
        }
        if (GZ_getButtonRepeat(GZPad::R)) {
            *static_cast<float*>(stng->data) -= 100.0f;
        }
        if (*static_cast<float*>(stng->data) < 1.0f) {
            *static_cast<float*>(stng->data) = 5000.0f;
        }
        if (*static_cast<float*>(stng->data) > 5000.0f) {
            *static_cast<float*>(stng->data) = 1.0f;
        }
        cursor.move(0, MENU_LINE_NUM);
        break;
    }
    case LAND_SPEED_INDEX: {
        stng = GZStng_get(STNG_LAND_SPEED);
        if (!stng) {
            stng = new GZSettingEntry{STNG_LAND_SPEED, sizeof(float), new float{DEFAULT_LAND_SPEED}};
            g_settings.push_back(stng);
        }
        Cursor::moveList(*static_cast<float*>(stng->data));
        if (GZ_getButtonRepeat(GZPad::A)) {
            *static_cast<float*>(stng->data) += 100.0f;
        }
        if (GZ_getButtonRepeat(GZPad::R)) {
            *static_cast<float*>(stng->data) -= 100.0f;
        }
        if (*static_cast<float*>(stng->data) < 1.0f) {
            *static_cast<float*>(stng->data) = 5000.0f;
        }
        if (*static_cast<float*>(stng->data) > 5000.0f) {
            *static_cast<float*>(stng->data) = 1.0f;
        }
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    case SPAWN_ID_INDEX: {
        Cursor::moveList(spawn_id_input);
        if (GZ_getButtonRepeat(GZPad::A)) {
            spawn_id_input += 10;
        }
        if (GZ_getButtonRepeat(GZPad::R)) {
            spawn_id_input -= 10;
        }
        if (spawn_id_input < 0) {
            spawn_id_input = 255;
        }
        if (spawn_id_input > 255) {
            spawn_id_input = 0;
        }
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    lines[CURSOR_COLOR_INDEX].printf(" <%s>", cursorCol_opt[GZStng_getData<uint32_t>(STNG_CURSOR_COLOR, 0)].member);
    lines[FONT_INDEX].printf(" <%s>", g_font_opt[GZStng_getData<uint32_t>(STNG_FONT, 0)].member);
    lines[WATER_SPEED_INDEX].printf(" <%4.0f>", GZStng_getData<float>(STNG_WATER_SPEED, DEFAULT_WATER_SPEED));
    lines[LAND_SPEED_INDEX].printf(" <%4.0f>", GZStng_getData<float>(STNG_LAND_SPEED, DEFAULT_LAND_SPEED));
    lines[SPAWN_ID_INDEX].printf(" <%d>", spawn_id_input);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
