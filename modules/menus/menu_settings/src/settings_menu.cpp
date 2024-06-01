#include "menus/menu_settings/include/settings_menu.h"
#include <cstdio>
#include "utils/card.h"
#include "gz_flags.h"
#include "fifo_queue.h"
#include "settings.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define MAX_RELOAD_OPTIONS 2
#define MAX_CURSOR_COLOR_OPTIONS 6

KEEP_FUNC SettingsMenu::SettingsMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr,
                         MAX_CURSOR_COLOR_OPTIONS},
                        {"font:", FONT_INDEX, "Change font", false, nullptr, FONT_OPTIONS_COUNT},
                        {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font letters",
                         true, &g_dropShadows},
                        {"item equip priorities", ITEM_EQUIP_PRIORITY_INDEX, "Adjust priorities on item equips in practice saves", false},
                        {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
                        {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
                        {"delete card", DELETE_CARD_INDEX, "Delete settings from memory card"},
                    } {}

SettingsMenu::~SettingsMenu() {}

void SettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case DROP_SHADOWS_INDEX:
            g_dropShadows = !g_dropShadows;
            break;
        /* case POS_SETTINGS_MENU_INDEX:
            g_menuMgr->push(MN_POS_SETTINGS_INDEX);
            return; */
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

    ListMember cursorCol_opt[MAX_CURSOR_COLOR_OPTIONS] = {"green",  "blue",   "red",
                                                          "orange", "yellow", "purple"};

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
    default:
        cursor.move(0, MENU_LINE_NUM);
        break;
    }

    lines[CURSOR_COLOR_INDEX].printf(" <%s>", cursorCol_opt[g_cursorColorType].member);
    lines[FONT_INDEX].printf(" <%s>", g_font_opt[g_fontType].member);

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
