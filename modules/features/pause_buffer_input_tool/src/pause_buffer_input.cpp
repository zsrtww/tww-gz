#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "menus/menu_tools/include/tools_menu.h"
#include "controller.h"
#include "gz_flags.h"
#include "pos_settings.h"
#include "pause_buffer_input.h"
#include "buffer_button.h"

char result_str[50];
f32 animationFrame;
int bufferButton;
bool getButtonPress = false;
bool earlyPress = false;
bool isBPressedWithFrameAdvance = false;
bool isPaused = false;
bool frameAdvanceDelay = false;
int animation;
int previousAnimation;
cXyz position;
cXyz previousPosition;
u8 inputFrame;
f32 previousFrame;
u32 unpauseFrames;
u8 timeOnScreen = 0;
s32 color = 0x00000000;

namespace PauseBufferInputTool {

KEEP_FUNC void GZ_PauseBufferInputTool() {
    if (!g_tools[PAUSE_BUFFER_INPUT_INDEX].active) {
        return;
    }

    daPy_lk_c* player_p = (daPy_lk_c*)dComIfGp_getPlayer(0);

    if (player_p != nullptr) {
        animationFrame = player_p->mFrameCtrlUnder[0].mFrame;
        animation = player_p->mCurProcID;
        position = player_p->current.pos;
        bufferButton = Buffer_Buttons_enum_to_GZPad_enum(g_buffer_input);
        getButtonPress = GZ_getButtonTrig(bufferButton);

        if (!g_FrameAdvEnabled || g_FrameTriggered) {
            // Test if the game is paused by checking if link's position, animation type and animation frame are the
            // same than in the previous frame
            if (animationFrame == previousFrame && previousAnimation == animation && previousPosition.x == position.x &&
                previousPosition.y == position.y && previousPosition.z && previousPosition.z) {
                isPaused = true;
                unpauseFrames = 0;
            } else {
                isPaused = false;
                unpauseFrames++;
            }

            if (frameAdvanceDelay) {
                getButtonPress = true;
                frameAdvanceDelay = false;
            }

            if (isBPressedWithFrameAdvance) {
                frameAdvanceDelay = true;
            }

            // When the player did the B input on the wanted frame
            if (getButtonPress && unpauseFrames == 1) {
                setResultStr(SUCCESS);
                earlyPress = false;
            }

            // When the player did the B input late (less than 7 frames late)
            if (getButtonPress && unpauseFrames > 1 && unpauseFrames < 7) {
                inputFrame = unpauseFrames - 1;
                setResultStr(LATE, inputFrame);
                earlyPress = false;
            }

            // When the player did the B input early. Starts a frame counter.
            if (getButtonPress && isPaused) {
                inputFrame = 1;
                earlyPress = true;
            }

            // Increments the frame counter if B was pressed more than two frames early
            if (earlyPress && !getButtonPress && isPaused) {
                inputFrame++;
            }

            // Used to prevent the B press used to unpause to be considered as the bomb drop input
            if (earlyPress && inputFrame > 9) {
                earlyPress = false;
            }

            // Put the amount of counted early frames in a string to be displayed
            if (earlyPress && !isPaused) {
                setResultStr(EARLY, inputFrame);
                earlyPress = false;
            }

            isBPressedWithFrameAdvance = false;
            previousFrame = animationFrame;
            previousAnimation = animation;
            previousPosition = position;

            // When frame advance is activated and a frame wasn't triggered and B was buffered
        } else if (getButtonPress) {
            isBPressedWithFrameAdvance = true;
        }
    }

    // Displays the result
    if (timeOnScreen > 0) {
        Vec2 bomb_push_display_position = g_spriteOffsets[SPR_BUFFER_INPUT_INDEX];
        Font::GZ_drawStr(result_str, bomb_push_display_position.x, bomb_push_display_position.y, color, g_dropShadows);
        timeOnScreen--;
    }
}

void setResultStr(int result, u8 inputFrame) {
    switch (result) {
    case Buffer_Input_Result::WRONG:
        sprintf(result_str, "Pause Buffer Input timing : Bad buffer");
        color = (s32)ColorPalette::YELLOW;
        timeOnScreen = 20;
        break;
    case Buffer_Input_Result::SUCCESS:
        sprintf(result_str, "Pause Buffer Input timing : Good !");
        color = (s32)ColorPalette::GREEN;
        timeOnScreen = 60;
        break;
    case Buffer_Input_Result::LATE:
        sprintf(result_str, "Pause Buffer Input timing : %d frames late", inputFrame);
        color = (s32)ColorPalette::RED;
        timeOnScreen = 60;
        break;
    case Buffer_Input_Result::EARLY:
        sprintf(result_str, "Pause Buffer Input timing : %d frames early", inputFrame);
        color = (s32)ColorPalette::YELLOW;
        timeOnScreen = 60;
        break;
    default:
        break;
    }
}

}  // namespace PauseBufferInputTool