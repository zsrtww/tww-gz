#include "features/rollclip_tool/include/rollclip_tool.h"
#include "fifo_queue.h"
#include <cstdio>
#include "pos_settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/kankyo/d_kankyo.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "libtww/include/SSystem/SComponent/c_counter.h"
#include "controller.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "commands.h"
#include "menus/menu_tools/include/tools_menu.h"
#include "gz_flags.h"

char roll_clip_str[35];
s8 rollClipFrameCount = -31;
s8 rollClipFrame = 0;
bool isClimbing = false;
bool isHangingLong = false;
bool isHangingShort = false;
ColorPalette trainerTextColor;
bool g_climbingTrigger = false;
bool getApress = false;
bool frameAdvancePreClimb = false;
bool frameAdvancePostClimb = false;
bool frameAdvanceWait = false;
s16 timeOnScreen = 0;
s32 color = 0x00000000;
s32 dropColor = DROP_SHADOWS_RGBA;

namespace RollClip {

KEEP_FUNC void GZ_rollClipInfo() {
    if (!g_tools[ROLL_CLIP_INDEX].active) {
        return;
    }

    daPy_lk_c* player_p = (daPy_lk_c*)dComIfGp_getPlayer(0);

    getApress = GZ_getButtonTrig(GZPad::A);

    if (player_p != nullptr) {
        isClimbing = (player_p->mCurProcID == daPy_lk_c::PROC_HANG_CLIMB_e);
        isHangingLong = (player_p->mCurProcID == daPy_lk_c::PROC_HANG_START_e ||
                         player_p->mCurProcID == daPy_lk_c::PROC_HANG_FALL_START_e);
        isHangingShort = (player_p->mCurProcID == daPy_lk_c::PROC_HANG_WALL_CATCH_e);

        if (g_climbingTrigger && rollClipFrameCount < 6) {
            if (!g_FrameAdvEnabled) {
                rollClipFrameCount++;
                frameAdvancePreClimb = false;
                frameAdvancePostClimb = false;
                frameAdvanceWait = false;
            } else if (g_FrameTriggered) {
                rollClipFrameCount++;
                frameAdvancePostClimb = true;
            }
        }

        if ((getApress || rollClipFrameCount == 6) && g_climbingTrigger) {
            rollClipFrame = rollClipFrameCount;
            setRollClipText(rollClipFrame);
            timeOnScreen = 200;
            dropColor = DROP_SHADOWS_RGBA;
            g_climbingTrigger = false;
            frameAdvancePreClimb = false;
            frameAdvancePostClimb = false;
            frameAdvanceWait = false;
        }

        if (timeOnScreen > 0 && ((color & 255) > 0)) {
            Vec2 roll_clip_info_offset = g_spriteOffsets[SPR_ROLL_CLIP_INDEX];

            if (timeOnScreen < 52) {
                color = color - 5;
                dropColor = dropColor - 5;
            }

            if (GZ_checkDropShadows()) {
                Font::GZ_drawStr(roll_clip_str, roll_clip_info_offset.x - 4.0f, roll_clip_info_offset.y - 9.0f,
                                 dropColor, false);
                Font::GZ_drawStr(roll_clip_str, roll_clip_info_offset.x - 5.0f, roll_clip_info_offset.y - 10.0f, color,
                                 false);
            } else {
                Font::GZ_drawStr(roll_clip_str, roll_clip_info_offset.x - 5.0f, roll_clip_info_offset.y - 10.0f, color,
                                 false);
            }
            timeOnScreen--;
        }

        if (isHangingLong) {
            rollClipFrameCount = -31;
            if (g_FrameAdvEnabled){
                frameAdvancePreClimb = true;
            }
        } else if (isHangingShort) {
            rollClipFrameCount = -29;
            if (g_FrameAdvEnabled){
                frameAdvancePreClimb = true;
            }
        }

        if (isClimbing && (rollClipFrameCount == -31 || rollClipFrameCount == -29)) {
            g_climbingTrigger = true;
        }
        if (g_FrameAdvEnabled && (player_p->mCurProcID == daPy_lk_c::PROC_HANG_WAIT_e)) {
            frameAdvanceWait = true;
        }
    }
}

void setRollClipText(s8 inputFrame) {
    
    if (g_FrameAdvEnabled) {
        if ((frameAdvanceWait || frameAdvancePreClimb) && frameAdvancePostClimb) {
            inputFrame++;
        } else if (frameAdvancePostClimb) {
            inputFrame += 3;
        }
    }

    if (inputFrame < 0) {
        sprintf(roll_clip_str, "Roll Clip Timing: %d Frames Early", (inputFrame * -1));
        trainerTextColor = ColorPalette::RED;
        color = trainerTextColor;
        // FIFOQueue::push(roll_clip_str, Queue, trainerTextColor);

    } else if (inputFrame == 0) {
        sprintf(roll_clip_str, "Roll Clip Timing: Good!");
        trainerTextColor = ColorPalette::GREEN;
        color = trainerTextColor;
        // FIFOQueue::push(roll_clip_str, Queue, trainerTextColor);

    } else if (inputFrame > 0 && inputFrame < 6) {
        sprintf(roll_clip_str, "Roll Clip Timing: %d Frames Late", inputFrame);
        trainerTextColor = ColorPalette::YELLOW;
        color = trainerTextColor;
        // FIFOQueue::push(roll_clip_str, Queue, trainerTextColor);

    } else if (inputFrame == 6) {
        sprintf(roll_clip_str, "Roll Clip Timing: Timeout...");
        trainerTextColor = ColorPalette::WHITE;
        color = trainerTextColor;
        // FIFOQueue::push(roll_clip_str, Queue, trainerTextColor);
    }
}
}  // namespace RollClip
