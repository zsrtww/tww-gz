#pragma once

#include "menu.h"
#include "libtww/d/kankyo/d_kankyo.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/f_op/f_op_scene_req.h"
#include "libtww/m_Do/m_Do_main.h"
#include "controller.h"

#define CURSOR_RGBA g_cursorColor

enum ToolsMenuIndex {
    DEBUG_INDEX,
    TELEPORT_INDEX,
    AREA_RELOAD_INDEX,
    ZH_INDEX,
    INPUT_VIEWER_INDEX,
    DISABLE_SVCHECK_INDEX,
};

struct GZTool {
    int index;
    bool active;
};

#define TOOL_AMNT 6
extern GZTool g_tools[TOOL_AMNT];

class ToolsMenu : public Menu {
public:
    ToolsMenu() : Menu() {}
    static void draw();
    static void initFont();
    static void displayLinkInfo();
    static void displayZombieHoverInfo();

    static Cursor cursor;
};
