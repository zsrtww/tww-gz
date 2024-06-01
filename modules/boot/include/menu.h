#pragma once
// #include "commands.h"
#include "controller.h"
#include "font.h"
#include "libtww/include/JSystem/JUtility/JUTGamePad.h"
#include "libtww/include/dolphin/mtx/vec.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MAX_MENU_RENDER_FLAGS 30

#define SELECTION_BUTTON (GZPad::A)
#define BACK_BUTTON (GZPad::B)

enum MenuIndex {
    MN_NONE_INDEX = -1,
    MN_MAIN_MENU_INDEX = 0,
    // Main menu's sub menus
    MN_SETTINGS_INDEX,

    // This entry is used only to get a count of the number of valid entries.
    MN_COUNT
};

extern const char* g_menuPaths[MN_COUNT];

#define LIST_COUNT(list) (sizeof(list) / sizeof((list)[0]))
#define MENU_LINE_NUM LIST_COUNT(lines)

class Menu {
public:
    Menu(Cursor& cursor);

    virtual void draw() = 0;

protected:
    Cursor& cursor;
};