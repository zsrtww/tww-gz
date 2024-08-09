#include "utils/link.h"
#include <cstdio>
#include "pos_settings.h"
#include "settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/kankyo/d_kankyo.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "libtww/include/SSystem/SComponent/c_counter.h"
#include "controller.h"
#include "tools.h"
#include "rels/include/defines.h"

u32 t = 0;
bool COUNT_STOP = 0;
KEEP_FUNC void GZ_displayLinkInfo() {
    if (!g_tools[DEBUG_INDEX].active) {
        return;
    }

    if (dComIfGp_getPlayer(0)) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

        char link_angle[22];
        char y_angle[22];
        char link_speed[22];
        char link_x[22];
        char link_y[22];
        char link_z[22];

        snprintf(link_angle, sizeof(link_angle), "angle: %d", player->shape_angle.y);
        snprintf(y_angle, sizeof(y_angle), "y-angle: %d", player->mBodyAngle.y);
        snprintf(link_speed, sizeof(link_speed), "speed: %.4f", player->speedF);
        snprintf(link_x, sizeof(link_x), "x-pos: %.4f", player->current.pos.x);
        snprintf(link_y, sizeof(link_y), "y-pos: %.4f", player->current.pos.y);
        snprintf(link_z, sizeof(link_z), "z-pos: %.4f", player->current.pos.z);

        Font::GZ_drawStr(link_angle, g_spriteOffsets[SPR_DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[SPR_DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(y_angle, g_spriteOffsets[SPR_DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[SPR_DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_speed, g_spriteOffsets[SPR_DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[SPR_DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_x, g_spriteOffsets[SPR_DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[SPR_DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_y, g_spriteOffsets[SPR_DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[SPR_DEBUG_INFO_INDEX].y + 100.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_z, g_spriteOffsets[SPR_DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[SPR_DEBUG_INFO_INDEX].y + 120.0f, 0xFFFFFFFF, g_dropShadows);
    }
}

KEEP_FUNC void GZ_displayTimeInfo() {
    if (!g_tools[TIME_DISP_INDEX].active) {
        return;
    }

    int hour = dKy_getdaytime_hour();
    int min = dKy_getdaytime_minute();
    int moonid = dKy_moon_type_chk();
    u16 date = dComIfGs_getDate();

    const char* moonphases[] = {
        "Full",          "Waning Gibbous", "Last Quarter", "Waning Crescent", "Waxing Crescent",
        "First Quarter", "Waxing Gibbous",
    };

    char Time[10];
    char Date[12];
    char Moon[30];

    sprintf(Time, "%02d:%02d", hour, min);
    sprintf(Date, "date: %d", date);
    sprintf(Moon, "moon: %s", moonphases[moonid]);

    Font::GZ_drawStr(Time, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y,
                     ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(Date, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y + 20.0f,
                     ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(Moon, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y + 40.0f,
                     ColorPalette::WHITE, g_dropShadows);
}

KEEP_FUNC void GZ_frameCounter() {
    if (!g_tools[FRAME_COUNT_INDEX].active) {
        t = 0;
        return;
    }

    if (GZ_getButtonTrig(GZPad::DPAD_UP)) {
        if (!COUNT_STOP) {
            COUNT_STOP = 1;
        } else {
            COUNT_STOP = 0;
        }
    }
    char tm[10];

    if (!COUNT_STOP) {
        t = t + 1;
    }

    sprintf(tm, "count: %d", t);

    Font::GZ_drawStr(tm, g_spriteOffsets[SPR_COUNT_INDEX].x, g_spriteOffsets[SPR_COUNT_INDEX].y + 60.0f,
                     ColorPalette::WHITE, g_dropShadows);
}

int rainbow() {
    switch (cCt_getFrameCount() % 6) {
    case 0:
        return ColorPalette::RED;
    case 1:
        return ColorPalette::ORANGE;
    case 2:
        return ColorPalette::YELLOW;
    case 3:
        return ColorPalette::GREEN;
    case 4:
        return ColorPalette::BLUE;
    default:
        return ColorPalette::PURPLE;
    }
}

int zombieHoverColor(u8 buttonPressesPerWindow) {
    if (buttonPressesPerWindow == 15)
        return rainbow();
    if (buttonPressesPerWindow >= 11)
        return ColorPalette::GREEN;
    if (buttonPressesPerWindow >= 9)
        return ColorPalette::YELLOW;
    if (buttonPressesPerWindow >= 1)
        return ColorPalette::RED;
    return ColorPalette::WHITE;
}

KEEP_FUNC void GZ_displayZombieHoverInfo() {
    if (!g_tools[ZH_INDEX].active) {
        return;
    }

    // Generates A and B button presses per second
    char a_presses_str[8];
    char b_presses_str[8];

    u8 numAPressesPerWindow = GZ_getAPressesPerWindow();
    u8 numBPressesPerWindow = GZ_getBPressesPerWindow();

    sprintf(a_presses_str, "A: %d", numAPressesPerWindow);
    sprintf(b_presses_str, "B: %d", numBPressesPerWindow);

    Font::GZ_drawStr(a_presses_str, g_spriteOffsets[SPR_ZH_INFO_INDEX].x, g_spriteOffsets[SPR_ZH_INFO_INDEX].y,
                     zombieHoverColor(numAPressesPerWindow), g_dropShadows);
    Font::GZ_drawStr(b_presses_str, g_spriteOffsets[SPR_ZH_INFO_INDEX].x, g_spriteOffsets[SPR_ZH_INFO_INDEX].y + 20.0f,
                     zombieHoverColor(numBPressesPerWindow), g_dropShadows);
}
