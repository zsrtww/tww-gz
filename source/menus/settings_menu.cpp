#include "menus/settings_menu.h"
#include "utils/card.h"
#include "libtww/MSL_C/string.h"

#define LINE_NUM 6
#define MAX_CURSOR_COLOR_OPTIONS 6
#define MAX_FONT_OPTIONS 7

Cursor SettingsMenu::cursor;
bool g_dropShadows;
int g_fontType = 0;

Line lines[LINE_NUM] = {
    {"cursor color:", CURSOR_COLOR_INDEX, "Change cursor color", false, nullptr,
     MAX_CURSOR_COLOR_OPTIONS},
    {"font:", FONT_INDEX, "Change font", false, nullptr, MAX_FONT_OPTIONS},
    {"drop shadows", DROP_SHADOWS_INDEX, "Adds shadows to all font characters", true,
     &g_dropShadows},
    {"save card", SAVE_CARD_INDEX, "Save settings to memory card"},
    {"load card", LOAD_CARD_INDEX, "Load settings from memory card"},
    {"delete card", DELETE_CARD_INDEX, "Delete settings on memory card"},
};

ListMember font_opt[MAX_FONT_OPTIONS] = {
    "consola",   "calamity-bold",  "lib-sans",       "lib-sans-bold",
    "lib-serif", "lib-serif-bold", "press-start-2p",
};

void SettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case DROP_SHADOWS_INDEX:
            g_dropShadows = !g_dropShadows;
            break;
        case SAVE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "twwgz01";
            storage.sector_size = SECTOR_SIZE;
            tww_sprintf(storage.file_name_buffer, storage.file_name);

            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_storeMemCard(storage);
                tww_printf("save_card");
            }
            break;
        }
        case LOAD_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "twwgz01";
            storage.sector_size = SECTOR_SIZE;
            tww_sprintf(storage.file_name_buffer, storage.file_name);

            storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_loadMemCard(storage);
                tww_printf("load_card");
            }
            break;
        }
        case DELETE_CARD_INDEX: {
            static Storage storage;
            storage.file_name = "twwgz01";
            storage.sector_size = SECTOR_SIZE;
            tww_sprintf(storage.file_name_buffer, storage.file_name);

            storage.result = CARDProbeEx(0, nullptr, &storage.sector_size);
            if (storage.result == Ready) {
                GZ_deleteMemCard(storage);
                tww_printf("delete_card");
            }
            break;
        }
        }
    }

    // handle list rendering
    switch (cursor.y) {
    case CURSOR_COLOR_INDEX:
        cursor.x = g_cursorColorType;
        cursor.move(MAX_CURSOR_COLOR_OPTIONS, LINE_NUM);

        if (cursor.y == CURSOR_COLOR_INDEX) {
            g_cursorColorType = cursor.x;
        }
        break;
    case FONT_INDEX: {
        cursor.x = g_fontType;
        int old_font = g_fontType;
        cursor.move(MAX_FONT_OPTIONS, LINE_NUM);

        if (cursor.y == FONT_INDEX) {
            g_fontType = cursor.x;
        }

        if (old_font != g_fontType) {
            if (g_fontType >= 0 && g_fontType < MAX_FONT_OPTIONS) {
                char buf[40];
                tww_sprintf(buf, "twwgz/fonts/%s.fnt", font_opt[g_fontType].member);
                Font::loadFont(buf);
            }
        }
        break;
    }
    default:
        cursor.move(0, LINE_NUM);
        break;
    }

    ListMember cursorCol_opt[MAX_CURSOR_COLOR_OPTIONS] = {
        "green", "blue", "red", "orange", "yellow", "purple",
    };

    tww_sprintf(lines[CURSOR_COLOR_INDEX].value, " <%s>", cursorCol_opt[g_cursorColorType].member);
    tww_sprintf(lines[FONT_INDEX].value, " <%s>", font_opt[g_fontType].member);

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}

void SettingsMenu::initFont() {
    if (g_fontType >= 0 && g_fontType < MAX_FONT_OPTIONS) {
        char buf[40];
        tww_sprintf(buf, "twwgz/fonts/%s.fnt", font_opt[g_fontType].member);
        Font::loadFont(buf);
    }
}