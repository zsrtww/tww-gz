#include "menus/tools_menu.h"
#include "menus/settings_menu.h"
#include "menus/main_menu.h"
#include "menu.h"
#include "utils/card.h"
#include "libtww/MSL_C/string.h"
#include "lib.h"
#include "font.h"
#include "color.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "commands.h"

#define LINE_NUM 6
Cursor ToolsMenu::cursor;

GZTool g_tools[TOOL_AMNT] = {
    {DEBUG_INDEX, false}, {TELEPORT_INDEX, false},     {AREA_RELOAD_INDEX, false},
    {ZH_INDEX, false},    {INPUT_VIEWER_INDEX, false}, {DISABLE_SVCHECK_INDEX, false},
};

Line lines[LINE_NUM] = {
    {"link debug info", DEBUG_INDEX, "Display position and angle data for Link", true,
     &g_tools[DEBUG_INDEX].active},
    {"teleport", TELEPORT_INDEX, "R+D-pad up to save position. R+D-pad down to load", true,
     &g_tools[TELEPORT_INDEX].active},
    {"area reload", AREA_RELOAD_INDEX, "Reloads the current room by pressing L + R + A + Start",
     true, &g_tools[AREA_RELOAD_INDEX].active},
    {"zombie hover info", ZH_INDEX, "Display A and B button presses per second", true,
     &g_tools[ZH_INDEX].active},
    {"input viewer", INPUT_VIEWER_INDEX, "Show current inputs", true,
     &g_tools[INPUT_VIEWER_INDEX].active},
    {"disable save checks", DISABLE_SVCHECK_INDEX, "Disables save location safety checks", true,
     &g_tools[DISABLE_SVCHECK_INDEX].active},
};

void ToolsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        g_tools[cursor.y].active = !g_tools[cursor.y].active;

        if (g_tools[cursor.y].active) {
            switch (cursor.y) {
            case TELEPORT_INDEX:
                GZCmd_enable(Commands::CMD_STORE_POSITION);
                GZCmd_enable(Commands::CMD_LOAD_POSITION);
                break;
            }
        } else {
            switch (cursor.y) {
            case TELEPORT_INDEX:
                GZCmd_disable(Commands::CMD_STORE_POSITION);
                GZCmd_disable(Commands::CMD_LOAD_POSITION);
                break;
            }
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}

void ToolsMenu::displayLinkInfo() {
    // Generates Link position and angle data.
    if (g_dComIfG_gameInfo.play.mPlayerPtr != nullptr) {
        fopAc_ac_c* playerAc = (fopAc_ac_c*)g_dComIfG_gameInfo.play.mPlayerPtr;
        char link_angle[20];
        char link_speed[20];
        char link_x[20];
        char link_y[20];
        char link_z[20];

        tww_sprintf(link_angle, "angle: %d", playerAc->mCollisionRot.sy);
        tww_sprintf(link_speed, "speed: %.4f", playerAc->mSpeedF);
        tww_sprintf(link_x, "x-pos: %.4f", playerAc->mCurrent.mPosition.x);
        tww_sprintf(link_y, "y-pos: %.4f", playerAc->mCurrent.mPosition.y);
        tww_sprintf(link_z, "z-pos: %.4f", playerAc->mCurrent.mPosition.z);

        Font::GZ_drawStr(link_angle, 450.f, 200.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_speed, 450.f, 220.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_x, 450.f, 240.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_y, 450.f, 260.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_z, 450.f, 280.f, ColorPalette::WHITE, g_dropShadows);
    }
}

void ToolsMenu::displayZombieHoverInfo() {
    // Generates A and B button presses per second
    char a_presses_str[8];
    char b_presses_str[8];

    tww_sprintf(a_presses_str, "A: %d", GZ_getAPressesPerWindow());
    tww_sprintf(b_presses_str, "B: %d", GZ_getBPressesPerWindow());

    Font::GZ_drawStr(a_presses_str, 450.f, 320.f, ColorPalette::GREEN, g_dropShadows);
    Font::GZ_drawStr(b_presses_str, 450.f, 340.f, ColorPalette::RED, g_dropShadows);
}
