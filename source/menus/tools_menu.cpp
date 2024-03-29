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
#include "utils/lines.h"
#include "commands.h"
#include "libtww/d/kankyo/d_kankyo.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/dolphin/os/OSCache.h"

#define LINE_NUM TOOL_AMNT

#ifdef NTSCJ
#define INTRO_SKIP_INST0_ADDR 0x8023031c
#define INTRO_SKIP_INST1_ADDR 0x8023032c
#define INTRO_SKIP_ORIG_INST0 0x48000EB9
#define INTRO_SKIP_ORIG_INST1 0x4082000C
#endif

// TODO add other region intro skip data

Cursor ToolsMenu::cursor;

GZTool g_tools[TOOL_AMNT] = {
    {DEBUG_INDEX, false},        {TIME_DISP_INDEX, false},    {TELEPORT_INDEX, false},    
    {AREA_RELOAD_INDEX, false},  {MAP_SELECT_INDEX, false},   {ZH_INDEX, false},          
    {INPUT_VIEWER_INDEX, false}, {ESS_CHECKER_INDEX, false},  {DEADZONE_CHECKER_INDEX, false},  
    {INTRO_SKIP_INDEX, false}, //{DISABLE_SVCHECK_INDEX, false},
};

Line lines[LINE_NUM] = {
    {"link debug info", DEBUG_INDEX, "Display position and angle data for Link", true,
        &g_tools[DEBUG_INDEX].active},
    {"display time info", TIME_DISP_INDEX, "Display current day, time and moon phase", true,
        &g_tools[TIME_DISP_INDEX].active},
    {"teleport", TELEPORT_INDEX, "R+D-pad up to save position. R+D-pad down to load", true,
        &g_tools[TELEPORT_INDEX].active},
    {"area reload", AREA_RELOAD_INDEX, "Reload the current room by pressing L + R + A + Start",
        true, &g_tools[AREA_RELOAD_INDEX].active},
    {"map select", MAP_SELECT_INDEX, "Load map select by holding D-pad down + Y + Z",
        true, &g_tools[MAP_SELECT_INDEX].active},
    {"zombie hover info", ZH_INDEX, "Display A and B button presses per second", true,
        &g_tools[ZH_INDEX].active},
    {"input viewer", INPUT_VIEWER_INDEX, "Show current inputs", true,
        &g_tools[INPUT_VIEWER_INDEX].active},
    {"ess checker", ESS_CHECKER_INDEX, "Change input stick color based on distance from ideal ESS", true,
        &g_tools[ESS_CHECKER_INDEX].active},
    {"deadzone checker", DEADZONE_CHECKER_INDEX, "Change input viewer stick color if stick is in deadzone", true,
        &g_tools[DEADZONE_CHECKER_INDEX].active},
    //{"disable save checks", DISABLE_SVCHECK_INDEX, "Disables save location safety checks", true,
    //    &g_tools[DISABLE_SVCHECK_INDEX].active},
    {"intro skip", INTRO_SKIP_INDEX, "Skips the intro cutscenes when starting a new file", true,
        &g_tools[INTRO_SKIP_INDEX].active},
};

void ToolsMenu::displayTimeInfo() {
    int hour = dKy_getdaytime_hour();
    int min = dKy_getdaytime_minute();
    int moonid = dKy_moon_type_chk();
    int date = dComIfGs_getDate();

    char moonphases[7][20] = {"Full",
                              "Waning Gibbous",
                              "Last Quarter",
                              "Waning Crescent",
                              "Waxing Crescent",
                              "First Quarter",
                              "Waxing Gibbous"};

    char Time[10];
    char Date[10];
    char Moon[20];

    tww_sprintf(Time, "%02d:%02d", hour, min);
    tww_sprintf(Date, "date: %d", date);
    tww_sprintf(Moon, "Moon: %d", moonphases[0]);

    Font::GZ_drawStr(Time, 450.f, 320.f, ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(Date, 450.f, 340.f, ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(moonphases[moonid], 450.f, 360.f, ColorPalette::WHITE, g_dropShadows);
}

void ToolsMenu::draw() {
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
            case AREA_RELOAD_INDEX:
                GZCmd_enable(Commands::CMD_AREA_RELOAD);
                break;
            case INTRO_SKIP_INDEX:
                *reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR) = 0x60000000;  // nop
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));

                *reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR) = 0x60000000;  // nop
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                break;
            }
        } else {
            switch (cursor.y) {
            case TELEPORT_INDEX:
                GZCmd_disable(Commands::CMD_STORE_POSITION);
                GZCmd_disable(Commands::CMD_LOAD_POSITION);
                break;
            case AREA_RELOAD_INDEX:
                GZCmd_disable(Commands::CMD_AREA_RELOAD);
                break;
            case INTRO_SKIP_INDEX:
                *reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR) = INTRO_SKIP_ORIG_INST0;  // bl dScnOpen_proc_c::proc_execute
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));

                *reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR) = INTRO_SKIP_ORIG_INST1;  // bne ret
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                break;
            }
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}

void ToolsMenu::displayLinkInfo() {
    // Generates Link position and angle data.
    if (dComIfGp_getPlayer(0) != nullptr) {
        fopAc_ac_c* playerAc = (fopAc_ac_c*)dComIfGp_getPlayer(0);
        char link_angle[20];
        char link_speed[20];
        char link_x[20];
        char link_y[20];
        char link_z[20];

        tww_sprintf(link_angle, "angle: %d", playerAc->shape_angle.y);
        tww_sprintf(link_speed, "speed: %.4f", playerAc->speedF);
        tww_sprintf(link_x, "x-pos: %.4f", playerAc->current.pos.x);
        tww_sprintf(link_y, "y-pos: %.4f", playerAc->current.pos.y);
        tww_sprintf(link_z, "z-pos: %.4f", playerAc->current.pos.z);

        Font::GZ_drawStr(link_angle, 450.f, 200.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_speed, 450.f, 220.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_x, 450.f, 240.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_y, 450.f, 260.f, ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(link_z, 450.f, 280.f, ColorPalette::WHITE, g_dropShadows);
    }
}

int zombieHoverColor(u8 buttonPressesPerWindow) {
    if (buttonPressesPerWindow == 15) return rainbow();
    if (buttonPressesPerWindow >= 11) return ColorPalette::GREEN;
    if (buttonPressesPerWindow >= 9) return ColorPalette::YELLOW;
    if (buttonPressesPerWindow >= 1) return ColorPalette::RED;
    return ColorPalette::WHITE;
}

void ToolsMenu::displayZombieHoverInfo() {
    // Generates A and B button presses per second
    char a_presses_str[8];
    char b_presses_str[8];

    u8 numAPressesPerWindow = GZ_getAPressesPerWindow();
    u8 numBPressesPerWindow = GZ_getBPressesPerWindow();

    tww_sprintf(a_presses_str, "A: %d", numAPressesPerWindow);
    tww_sprintf(b_presses_str, "B: %d", numBPressesPerWindow);

    Font::GZ_drawStr(a_presses_str, 450.f, 400.f, zombieHoverColor(numAPressesPerWindow), g_dropShadows);
    Font::GZ_drawStr(b_presses_str, 450.f, 420.f, zombieHoverColor(numBPressesPerWindow), g_dropShadows);
}
