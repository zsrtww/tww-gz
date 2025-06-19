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
    if (!g_tools[DEBUG_INDEX].active || l_fopScnRq_IsUsingOfOverlap) {
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
        if (g_angleValuesInDecimal) {
            snprintf(link_angle, sizeof(link_angle), "rot y: %d", player->shape_angle.y);
        } else {
            snprintf(link_angle, sizeof(link_angle), "rot y: 0x%04X", (u16)player->shape_angle.y);
        }
        snprintf(link_speed, sizeof(link_speed), "speed: %.4f", player->speedF);
        snprintf(link_action, sizeof(link_action), "action: %s", proc->procName);

        f32 pos_x = g_spriteOffsets[SPR_DEBUG_INFO_INDEX].x;
        f32 pos_y = g_spriteOffsets[SPR_DEBUG_INFO_INDEX].y;
        uint32_t color_white = 0xFFFFFFFF;

        Font::GZ_drawStr(link_x, pos_x, pos_y - 20.0f, color_white, g_dropShadows);
        Font::GZ_drawStr(link_y, pos_x, pos_y, color_white, g_dropShadows);
        Font::GZ_drawStr(link_z, pos_x, pos_y + 20.0f, color_white, g_dropShadows);
        Font::GZ_drawStr(link_angle, pos_x, pos_y + 40.0f, color_white, g_dropShadows);
        Font::GZ_drawStr(link_speed, pos_x, pos_y + 60.0f, color_white, g_dropShadows);
        Font::GZ_drawStr(link_action, pos_x, pos_y + 80.0f, color_white, g_dropShadows);
    }
}

KEEP_FUNC void GZ_displayTimeInfo() {
    if (!g_tools[TIME_DISP_INDEX].active || l_fopScnRq_IsUsingOfOverlap) {
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

        Font::GZ_drawStr(Time, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y,
                         ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(Date, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y + 20.0f,
                         ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(Moon, g_spriteOffsets[SPR_TIME_DISP_INDEX].x, g_spriteOffsets[SPR_TIME_DISP_INDEX].y + 40.0f,
                         ColorPalette::WHITE, g_dropShadows);
    }
}

KEEP_FUNC void GZ_frameCounter() {
    static int l_frameCount = 0;
    static float sTimerSec = 0.0f;

    if (g_counterToggle && g_tools[FRAME_COUNT_INDEX].active && !g_FrameAdvEnabled) {
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

    if (g_tools[FRAME_COUNT_INDEX].active) {
        sprintf(framecount, "frames: %d", l_frameCount);
        sprintf(secondcount, "%.2f", sTimerSec);

        Font::GZ_drawStr(framecount, g_spriteOffsets[SPR_COUNT_INDEX].x, g_spriteOffsets[SPR_COUNT_INDEX].y,
                         ColorPalette::WHITE, g_dropShadows);
        Font::GZ_drawStr(secondcount, g_spriteOffsets[SPR_COUNT_INDEX].x, g_spriteOffsets[SPR_COUNT_INDEX].y + 20.0f,
                         ColorPalette::WHITE, g_dropShadows);
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

KEEP_FUNC void GZ_displayStageInfo() {
    if (!g_tools[STAGE_INFO_INDEX].active || l_fopScnRq_IsUsingOfOverlap) {
        return;
    }

    if (dComIfGp_getPlayer(0)) {
        Vec2 spriteOffset = g_spriteOffsets[SPR_SPRITES_STAGE_INFO_INDEX];
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

// Probably need to change the way this works, but if we are going to have multiple
// trainers could be nice to have one function so there is consistency between the trainers
int trainingToolTextColor(s8 inputFrame) {
    int setTextColor;
        if (inputFrame < 0) {
            setTextColor = ColorPalette::RED;
        } else if (inputFrame > 0) {
            setTextColor = ColorPalette::YELLOW;
        } else if (inputFrame == 0) {
            setTextColor = ColorPalette::GREEN;
        } else {
            setTextColor = ColorPalette::WHITE;
        }
    return setTextColor;
}
KEEP_FUNC void GZ_rollClipInfo() {
    static s8 rollClipFrameCount = -31;
    static s8 rollClipFrame = 0;
    
    if (!g_tools[ROLL_CLIP_INDEX].active) {
        return;
    }
    
    daPy_lk_c* player_p = (daPy_lk_c*)dComIfGp_getPlayer(0);
    
    if (player_p != nullptr) {
        char roll_clip_str[35];
        bool isClimbing = false;
        bool isHanging = false;
       
        isClimbing = (player_p->mCurProcID == daPy_lk_c::PROC_HANG_CLIMB_e);
        isHanging = (player_p->mCurProcID == daPy_lk_c::PROC_HANG_START_e ||
                     player_p->mCurProcID == daPy_lk_c::PROC_HANG_FALL_START_e);

        if (GZ_getButtonTrig(GZPad::A) && g_climbingTrigger) {
            rollClipFrame = rollClipFrameCount;
            g_climbingTrigger = false;
            g_trainerTextColor = trainingToolTextColor(rollClipFrame);
        }

        if (isHanging) {
            rollClipFrameCount = -31;
        }

        if (isClimbing && rollClipFrameCount == -31) {
            g_climbingTrigger = true;
        }

        if (g_climbingTrigger && rollClipFrameCount < 6) {
            if (!g_FrameAdvEnabled) {
                rollClipFrameCount++;
            }
             if (g_FrameTriggered) {
                rollClipFrameCount++;
            }
        }

        if (g_trainerTextColor == (int)ColorPalette::GREEN){
            sprintf(roll_clip_str, "Roll Clip Timing: Good!");
        } else if (g_trainerTextColor == (int)ColorPalette::YELLOW){
            sprintf(roll_clip_str, "Roll Clip Timing: %d Frames Late", rollClipFrame);
        } else if (g_trainerTextColor == (int)ColorPalette::RED){
            sprintf(roll_clip_str, "Roll Clip Timing: %d Frames Early", (rollClipFrame * -1));
        } else {
            sprintf(roll_clip_str, "Roll Clip Timing: Waiting...");
        }
        Vec2 roll_clip_info_offset = g_spriteOffsets[SPR_ROLL_CLIP_INDEX];
        Font::GZ_drawStr(roll_clip_str, roll_clip_info_offset.x, roll_clip_info_offset.y, g_trainerTextColor,
                         GZ_checkDropShadows());
    }
}