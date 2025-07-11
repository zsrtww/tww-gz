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
#include "boot/include/buffer_button.h"

#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6

char bufferButtonStr[10];

KEEP_FUNC SettingsMenu::SettingsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{{"cursor color:", CURSOR_COLOR_INDEX, "change cursor color", false, nullptr, MAX_CURSOR_COLOR_OPTIONS},
            {"font:", FONT_INDEX, "change font", false, nullptr, FONT_OPTIONS_COUNT},
            {"drop shadows", DROP_SHADOWS_INDEX, "adds shadows to all font letters", true, &g_dropShadows},
            {"decimal angles", ANGLE_DECIMAL_INDEX, "display angles in decimal instead of hex", true,
             &g_angleValuesInDecimal},
            {"custom save positions", CUSTOM_POSITIONS_INDEX, "turn on/off custom positions in saves that support them",
             true, &g_customSaveSpawns},
            {"equip priority", ITEM_EQUIP_PRIORITY_INDEX, "adjust priorities on item equips in practice saves", false},
            {"save card", SAVE_CARD_INDEX, "save settings to memory card"},
            {"load card", LOAD_CARD_INDEX, "load settings from memory card"},
            {"delete card", DELETE_CARD_INDEX, "delete settings from memory card"},
            {"menu positions", POS_SETTINGS_MENU_INDEX,
             "change menu object positions (A to toggle selection, DPad to move)", false},
            {"fast swim speed:", WATER_SPEED_INDEX, "change max speed of fast movement cheat for swimming"},
            {"fast land speed:", LAND_SPEED_INDEX, "change max speed of Fast Movement cheat on land"},
            {"spawn id: ", SPAWN_ID_INDEX, "set spawn id for disable save checks tool, invalid id's will crash"},
            {"pause buffer input button:", PAUSE_BUFFER_BUTTON_INDEX,
             "set the button to train buffering after a pause"}} {}

SettingsMenu::~SettingsMenu() {}

void SettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    Buffer_Buttons_enum_to_str(bufferButtonStr, g_buffer_input);

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case DROP_SHADOWS_INDEX:
            g_dropShadows = !g_dropShadows;
            break;
        case ANGLE_DECIMAL_INDEX:
            g_angleValuesInDecimal = !g_angleValuesInDecimal;
            break;
        case CUSTOM_POSITIONS_INDEX:
            g_customSaveSpawns = !g_customSaveSpawns;
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

    // handle list rendering
    switch (cursor.y) {
    case CURSOR_COLOR_INDEX:
        cursor.x = g_cursorColorType;
        cursor.move(MAX_CURSOR_COLOR_OPTIONS, MENU_LINE_NUM);

        if (cursor.y == CURSOR_COLOR_INDEX) {
            g_cursorColorType = cursor.x;
        }
        break;
    case FONT_INDEX: {
        cursor.x = g_fontType;
        uint32_t old_font = g_fontType;
        cursor.move(FONT_OPTIONS_COUNT, MENU_LINE_NUM);

        if (cursor.y == FONT_INDEX) {
            g_fontType = cursor.x;
        }
        if (old_font != g_fontType) {
            if (g_fontType >= 0 && g_fontType < FONT_OPTIONS_COUNT) {
                char buf[40];
                snprintf(buf, sizeof(buf), "twwgz/fonts/%s.fnt", g_font_opt[g_fontType].member);
                Font::loadFont(buf);
            }
        }
        break;
    }

    // Controls the constant speed for link's fast movement cheat. moveList to set and cycle through
    // the numbers, and cursor.move so that the list does not stick once option is selected.
    case WATER_SPEED_INDEX: {
        Cursor::moveList(g_waterSpeed);
        if (GZ_getButtonRepeat(GZPad::A)) {
            g_waterSpeed += 100.0f;
        }
        if (GZ_getButtonRepeat(GZPad::R)) {
            g_waterSpeed -= 100.0f;
        }
        if (g_waterSpeed < 1.0f) {
            g_waterSpeed = 5000.0f;
        }
        if (g_waterSpeed > 5000.0f) {
            g_waterSpeed = 1.0f;
        }
        cursor.move(0, MENU_LINE_NUM);
        break;
    }
    case LAND_SPEED_INDEX: {
        Cursor::moveList(g_landSpeed);
        if (GZ_getButtonRepeat(GZPad::A)) {
            g_landSpeed += 100.0f;
        }
        if (GZ_getButtonRepeat(GZPad::R)) {
            g_landSpeed -= 100.0f;
        }
        if (g_landSpeed < 1.0f) {
            g_landSpeed = 5000.0f;
        }
        if (g_landSpeed > 5000.0f) {
            g_landSpeed = 1.0f;
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
    case PAUSE_BUFFER_BUTTON_INDEX: {
        Cursor::moveListSimple(g_buffer_input);
        if (g_buffer_input < 0) {
            g_buffer_input = 5;
        }
        if (g_buffer_input > 5) {
            g_buffer_input = 0;
        }
        Buffer_Buttons_enum_to_str(bufferButtonStr, g_buffer_input);
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    lines[CURSOR_COLOR_INDEX].printf(" <%s>", cursorCol_opt[g_cursorColorType].member);
    lines[FONT_INDEX].printf(" <%s>", g_font_opt[g_fontType].member);
    lines[WATER_SPEED_INDEX].printf(" <%4.0f>", g_waterSpeed);
    lines[LAND_SPEED_INDEX].printf(" <%4.0f>", g_landSpeed);
    lines[SPAWN_ID_INDEX].printf(" <%d>", spawn_id_input);
    lines[PAUSE_BUFFER_BUTTON_INDEX].printf(" <%s>", bufferButtonStr);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
