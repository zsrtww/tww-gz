#include "utils/link.h"
#include <cstdio>
#include "pos_settings.h"
#include "settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/kankyo/d_kankyo.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "tools.h"
#include "rels/include/defines.h"

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
    int date = dComIfGs_getDate();

    const char* moonphases[] = {
        "Full",          "Waning Gibbous", "Last Quarter", "Waning Crescent", "Waxing Crescent",
        "First Quarter", "Waxing Gibbous",
    };

    char Time[10];
    char Date[10];
    char Moon[20];

    sprintf(Time, "%02d:%02d", hour, min);
    sprintf(Date, "date: %d", date);
    sprintf(Moon, "moon: %s", moonphases[moonid]);

    Font::GZ_drawStr(Time, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y, ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(Date, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y + 20.0f, ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(Moon, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y + 40.0f, ColorPalette::WHITE, g_dropShadows);
}