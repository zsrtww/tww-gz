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
#include "commands.h"
#include "menus/menu_tools/include/tools_menu.h"
#include "gz_flags.h"
#include "libtww/include/f_op/f_op_scene_req.h"
#include "actor_proc_data.h"
#include "global_data.h"

#if defined(NTSCJ) || defined(NTSCU)
#define FRAME_RATE 29.97
#else
#define FRAME_RATE 25
#endif

KEEP_FUNC void GZ_displayLinkInfo() {
    if (!GZStng_getData(STNG_TOOLS_DEBUG, false) || l_fopScnRq_IsUsingOfOverlap) {
        freePlayerProcData();  // free player proc data if it still exists
        return;
    }

    loadPlayerProcData();  // allocate and load player proc data if it doesnt already exist

    if (dComIfGp_getPlayer(0)) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

        procBinData* proc = getPlayerProcName(daPy_getPlayerLinkActorClass()->mCurProcID);

        char link_angle[22];
        char link_speed[22];
        char link_x[22];
        char link_y[22];
        char link_z[22];
        char link_action[55];

        snprintf(link_x, sizeof(link_x), "pos x: %.4f", player->current.pos.x);
        snprintf(link_y, sizeof(link_y), "pos y: %.4f", player->current.pos.y);
        snprintf(link_z, sizeof(link_z), "pos z: %.4f", player->current.pos.z);
        if (GZStng_getData<bool>(STNG_ANGLE_VALUES_IN_DECIMAL, false)) {
            snprintf(link_angle, sizeof(link_angle), "rot y: %d", player->shape_angle.y);
        } else {
            snprintf(link_angle, sizeof(link_angle), "rot y: 0x%04X", (u16)player->shape_angle.y);
        }
        snprintf(link_speed, sizeof(link_speed), "speed: %.4f", player->speedF);
        snprintf(link_action, sizeof(link_action), "action: %s", proc->procName);

        Vec2 pos_offset = GZ_getSpriteOffset(STNG_SPRITES_DEBUG_INFO);
        uint32_t color_white = 0xFFFFFFFF;

        Font::GZ_drawStr(link_x, pos_offset.x, pos_offset.y - 20.0f, color_white, GZ_checkDropShadows());
        Font::GZ_drawStr(link_y, pos_offset.x, pos_offset.y, color_white, GZ_checkDropShadows());
        Font::GZ_drawStr(link_z, pos_offset.x, pos_offset.y + 20.0f, color_white, GZ_checkDropShadows());
        Font::GZ_drawStr(link_angle, pos_offset.x, pos_offset.y + 40.0f, color_white, GZ_checkDropShadows());
        Font::GZ_drawStr(link_speed, pos_offset.x, pos_offset.y + 60.0f, color_white, GZ_checkDropShadows());
        Font::GZ_drawStr(link_action, pos_offset.x, pos_offset.y + 80.0f, color_white, GZ_checkDropShadows());
    }
}

KEEP_FUNC void GZ_displayTimeInfo() {
    if (!GZStng_getData(STNG_TOOLS_TIME_DISP, false) || l_fopScnRq_IsUsingOfOverlap) {
        return;
    }

    if (dComIfGp_getPlayer(0)) {
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

        Vec2 time_offset = GZ_getSpriteOffset(STNG_SPRITES_TIME_DISP);
        Font::GZ_drawStr(Time, time_offset.x, time_offset.y,
                         ColorPalette::WHITE, GZ_checkDropShadows());
        Font::GZ_drawStr(Date, time_offset.x, time_offset.y + 20.0f,
                         ColorPalette::WHITE, GZ_checkDropShadows());
        Font::GZ_drawStr(Moon, time_offset.x, time_offset.y + 40.0f,
                         ColorPalette::WHITE, GZ_checkDropShadows());
    }
}

KEEP_FUNC void GZ_frameCounter() {
    static int l_frameCount = 0;
    static float sTimerSec = 0.0f;

    if (g_counterToggle && GZStng_getData(STNG_TOOLS_FRAME_COUNT, false) && !g_FrameAdvEnabled) {
        l_frameCount++;
        sTimerSec = l_frameCount / FRAME_RATE;
    }

    if (g_FrameTriggered && g_counterToggle) {
        l_frameCount++;
        sTimerSec = l_frameCount / FRAME_RATE;
    }

    if (g_timer_reset) {
        g_counterToggle = false;
        g_timer_reset = false;
        l_frameCount = 0;
        sTimerSec = 0.0f;
    }

    char framecount[5] = {0};
    char secondcount[8] = {0};
    ;

    if (GZStng_getData(STNG_TOOLS_FRAME_COUNT, false)) {
        sprintf(framecount, "frames: %d", l_frameCount);
        sprintf(secondcount, "%.2f", sTimerSec);

        Vec2 framecount_offset = GZ_getSpriteOffset(STNG_SPRITES_COUNT);
        Font::GZ_drawStr(framecount, framecount_offset.x, framecount_offset.y,
                         ColorPalette::WHITE, GZ_checkDropShadows());
        Font::GZ_drawStr(secondcount, framecount_offset.x, framecount_offset.y + 20.0f,
                         ColorPalette::WHITE, GZ_checkDropShadows());
    }
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
    if (!GZStng_getData(STNG_TOOLS_ZH, false)) {
        return;
    }

    // Generates A and B button presses per second
    char a_presses_str[8];
    char b_presses_str[8];

    u8 numAPressesPerWindow = GZ_getAPressesPerWindow();
    u8 numBPressesPerWindow = GZ_getBPressesPerWindow();

    sprintf(a_presses_str, "A: %d", numAPressesPerWindow);
    sprintf(b_presses_str, "B: %d", numBPressesPerWindow);

    Vec2 zh_info_offset = GZ_getSpriteOffset(STNG_SPRITES_ZH_INFO);
    Font::GZ_drawStr(a_presses_str, zh_info_offset.x, zh_info_offset.y,
                     zombieHoverColor(numAPressesPerWindow), GZ_checkDropShadows());
    Font::GZ_drawStr(b_presses_str, zh_info_offset.x, zh_info_offset.y + 20.0f,
                     zombieHoverColor(numBPressesPerWindow), GZ_checkDropShadows());
}

KEEP_FUNC void GZ_displayStageInfo() {
    if (!GZStng_getData(STNG_TOOLS_STAGE_INFO, false) || l_fopScnRq_IsUsingOfOverlap) {
        return;
    }

    if (dComIfGp_getPlayer(0)) {
        Vec2 spriteOffset = GZ_getSpriteOffset(STNG_SPRITES_STAGE_INFO);
        char cur_stage[15];
        char cur_room[10];
        char cur_point[11];
        char cur_layer[10];

        snprintf(cur_stage, sizeof(cur_stage), "Stage: %s", g_dComIfG_gameInfo.play.mStartStage.getName());
        snprintf(cur_room, sizeof(cur_room), "Room: %d", dStage_roomControl_c__mStayNo);
        snprintf(cur_point, sizeof(cur_point), "Point: %d", g_dComIfG_gameInfo.play.mStartStage.getPoint());
        snprintf(cur_layer, sizeof(cur_layer), "Layer: %d", dComIfG_play_c__getLayerNo(0));

        Font::GZ_drawStr(cur_stage, spriteOffset.x, spriteOffset.y, 0xFFFFFFFF, GZ_checkDropShadows());
        Font::GZ_drawStr(cur_room, spriteOffset.x, spriteOffset.y + 20.0f, 0xFFFFFFFF, GZ_checkDropShadows());
        Font::GZ_drawStr(cur_point, spriteOffset.x, spriteOffset.y + 40.0f, 0xFFFFFFFF, GZ_checkDropShadows());
        Font::GZ_drawStr(cur_layer, spriteOffset.x, spriteOffset.y + 60.0f, 0xFFFFFFFF, GZ_checkDropShadows());

        char save_stage[20];
        char save_room[15];
        char save_point[16];

        dComIfGs_setGameStartStage();

        snprintf(save_stage, sizeof(save_stage), "Save Stage: %s",
                 g_dComIfG_gameInfo.info.getPlayer().getPlayerReturnPlace().getName());
        snprintf(save_room, sizeof(save_room), "Save Room: %d",
                 g_dComIfG_gameInfo.info.getPlayer().getPlayerReturnPlace().getRoomNo());
        snprintf(save_point, sizeof(save_point), "Save Point: %d",
                 g_dComIfG_gameInfo.info.getPlayer().getPlayerReturnPlace().getPoint());
        Font::GZ_drawStr(save_stage, spriteOffset.x - 180.0f, spriteOffset.y, 0xFFFFFFFF, GZ_checkDropShadows());
        Font::GZ_drawStr(save_room, spriteOffset.x - 180.0f, spriteOffset.y + 20.0f, 0xFFFFFFFF, GZ_checkDropShadows());
        Font::GZ_drawStr(save_point, spriteOffset.x - 180.0f, spriteOffset.y + 40.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
    }
}
