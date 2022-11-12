#include "menu.h"

#define CURSOR_RGBA g_cursorColor

enum SettingsMenuIndex {
    CURSOR_COLOR_INDEX,
    FONT_INDEX,
    DROP_SHADOWS_INDEX,
    SAVE_CARD_INDEX,
    LOAD_CARD_INDEX,
    DELETE_CARD_INDEX,
};

extern bool g_dropShadows;
extern int g_fontType;

class SettingsMenu : public Menu {
public:
    SettingsMenu() : Menu() {}
    static void draw();
    static void initFont();

    static Cursor cursor;
};