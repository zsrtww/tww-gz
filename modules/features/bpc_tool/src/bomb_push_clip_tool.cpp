#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "features/bpc_tool/include/bomb_push_clip_tool.h"
#include "menus/menu_tools/include/tools_menu.h"
#include "controller.h"
#include "gz_flags.h"
#include "pos_settings.h"
#include "bomb_push_clip_tool.h"

char bomb_push_str[50];
u8 animationFrame;
bool getBPress = false;
bool isHoldingBomb;
bool earlyPress = false;
bool isBPressedWithFrameAdvance = false;
u8 inputFrame;
u8 previousFrame;
u8 timeOnScreen = 0;
s32 color = 0x00000000;

namespace BombPushClipTool {

KEEP_FUNC void GZ_BombPushClipTool() {
    if (!g_tools[BOMB_PUSH_INDEX].active) {
        return;
    }

    daPy_lk_c* player_p = (daPy_lk_c*)dComIfGp_getPlayer(0);

    if (player_p != nullptr) {
        isHoldingBomb = (player_p->mCurProcID == daPy_lk_c::PROC_GRAB_WAIT_e);

        if (isHoldingBomb) {
            animationFrame = (u8)(player_p->mFrameCtrlUnder[0].mFrame);
            getBPress = GZ_getButtonTrig(GZPad::B);

            if (!g_FrameAdvEnabled || (g_FrameAdvEnabled && g_FrameTriggered)) {
                // Suspicious way to deal with the abscence of delay with frame advance
                if (g_FrameAdvEnabled && g_FrameTriggered) {
                    animationFrame++;
                }

                // When B was pressed before the last frame triggered with frame advance
                if (isBPressedWithFrameAdvance) {
                    getBPress = true;
                }

                // When the player pauses the game after the wanted frame. If a message is already on screen, don't do
                // anything.
                if (animationFrame >= g_bpc_frame && animationFrame == previousFrame && timeOnScreen == 0) {
                    setBombPushStr(WRONG);
                    earlyPress = false;
                }

                // When the player did the B input on the wanted frame
                if (getBPress && animationFrame == g_bpc_frame && previousFrame != animationFrame) {
                    setBombPushStr(SUCCESS);
                    earlyPress = false;
                }

                // When the player did the B input late (less than 7 frames late)
                if (getBPress && animationFrame > g_bpc_frame && animationFrame < g_bpc_frame + 7 &&
                    previousFrame != animationFrame) {
                    inputFrame = animationFrame - g_bpc_frame;
                    setBombPushStr(LATE, inputFrame);
                    earlyPress = false;
                }

                // When the player did the B input early. Starts a frame counter.
                if (getBPress && animationFrame == g_bpc_frame - 1) {
                    inputFrame = 1;
                    earlyPress = true;
                }

                // Increments the frame counter if B was pressed more than two frames early
                if (earlyPress && !getBPress && animationFrame == g_bpc_frame - 1) {
                    inputFrame++;
                }

                // Used to prevent the B press used to unpause to be considered as the bomb drop input
                if (earlyPress && inputFrame > 9) {
                    earlyPress = false;
                }

                // Put the amount of counted early frames in a string to be displayed
                if (earlyPress && animationFrame == g_bpc_frame) {
                    setBombPushStr(EARLY, inputFrame);
                    earlyPress = false;
                }

                isBPressedWithFrameAdvance = false;
                previousFrame = animationFrame;

                // When frame advance is activated and a frame wasn't triggered and B was buffered
            } else if (getBPress) {
                isBPressedWithFrameAdvance = true;
            }
        }
    }

    // Displays the result
    if (timeOnScreen > 0) {
        Vec2 bomb_push_display_position = g_spriteOffsets[SPR_BOMB_PUSH_INDEX];
        Font::GZ_drawStr(bomb_push_str, bomb_push_display_position.x, bomb_push_display_position.y, color,
                         g_dropShadows);
        timeOnScreen--;
    }
}

void setBombPushStr(int result, u8 inputFrame) {
    switch (result) {
    case BPC_Result::WRONG:
        sprintf(bomb_push_str, "BPC timing : Bad buffer");
        color = (s32)ColorPalette::YELLOW;
        timeOnScreen = 20;
        break;
    case BPC_Result::SUCCESS:
        sprintf(bomb_push_str, "BPC timing : Good !");
        color = (s32)ColorPalette::GREEN;
        timeOnScreen = 60;
        break;
    case BPC_Result::LATE:
        sprintf(bomb_push_str, "BPC timing : %d frames late", inputFrame);
        color = (s32)ColorPalette::RED;
        timeOnScreen = 60;
        break;
    case BPC_Result::EARLY:
        sprintf(bomb_push_str, "BPC timing : %d frames early", inputFrame);
        color = (s32)ColorPalette::YELLOW;
        timeOnScreen = 60;
        break;
    default:
        break;
    }
}

}  // namespace BombPushClipTool