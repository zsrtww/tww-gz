#include "gz_flags.h"
#include <cstring>
#include "controller.h"
#include "scene.h"
#include "tools.h"
#include "rels/include/defines.h"
#include "geometry_draw.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "libtww/include/m_Do/m_Do_controller_pad.h"
#include "libtww/include/d/d_s_play.h"
#include "libtww/include/d/com/d_com_inf_game.h"

GZFlag g_gzFlags[MAX_GZ_FLAGS] = {
    {&g_sceneFlags[MUTE_BGM_INDEX].active, GAME_LOOP, GZ_disableBGM, GZ_enableBGM},
};

void GZ_execute(int phase) {
    for (int i = 0; i < MAX_GZ_FLAGS; i++) {
        if (g_gzFlags[i].mPhase == phase && g_gzFlags[i].mpFlag != nullptr) {
            if (*g_gzFlags[i].mpFlag && g_gzFlags[i].mpActiveFunc) {
                g_gzFlags[i].mpActiveFunc();
            } else if (g_gzFlags[i].mpDeactiveFunc) {
                g_gzFlags[i].mpDeactiveFunc();
            }
        }
    }
}

bool g_FrameAdvEnabled = false;
bool g_FrameTriggered = false;
dCcS* g_dCcSCopy;

KEEP_FUNC void GZ_frameAdvance() {
    static int sAdvHoldCounter = 0;
    static u16 sBufferedInputs;

    if (g_tools[FRAME_ADVANCE_INDEX].active) {
        bool openingMenu = CPad_CHECK_HOLD_R(CONTR_1) && CPad_CHECK_HOLD_L(CONTR_1);

        if (!openingMenu && CPad_CHECK_TRIG_DOWN(CONTR_1)) {
            g_FrameAdvEnabled = !g_FrameAdvEnabled;

            if (g_FrameAdvEnabled) {
                g_dCcSCopy = new dCcS();
            } else {
                dCcS__dtor(g_dCcSCopy);
                delete g_dCcSCopy;
            }
        } else if (g_FrameAdvEnabled) {
            dScnPlay_nextPauseTimer = 1;  // constantly set the timer to 1 to freeze the game

            GZ_drawCc(g_dCcSCopy);

            if (CPad_CHECK_HOLD_UP(CONTR_1)) {
                sAdvHoldCounter++;
            } else {
                sAdvHoldCounter = 0;
            }

            // Save any buttons pressed during the pause, to buffer them later when a frame is advanced
            u16 pressedButtons;
            memcpy(&pressedButtons, &g_mDoCPd_cpadInfo[CONTR_1].mButtonTrig, sizeof(pressedButtons));
            sBufferedInputs |= pressedButtons;

            // Frame triggered state is stored to check in dCcS hooks later
            g_FrameTriggered = CPad_CHECK_TRIG_UP(CONTR_1) || sAdvHoldCounter >= 30;

            if (g_FrameTriggered) {
                // copy buffered inputs to controller
                memcpy(&g_mDoCPd_cpadInfo[CONTR_1].mButtonTrig, &sBufferedInputs, sizeof(sBufferedInputs));
                memcpy(&g_mDoCPd_cpadInfo[CONTR_1].mButtonHold, &sBufferedInputs, sizeof(sBufferedInputs));
                sBufferedInputs = 0;  // clear stored inputs

                // unset dpad up to prevent opening the map
                g_mDoCPd_cpadInfo[CONTR_1].mButtonTrig.up = 0;
                g_mDoCPd_cpadInfo[CONTR_1].mButtonHold.up = 0;

                dScnPlay_nextPauseTimer = 0;  // set pause timer to 0 to advance one frame
            }
        }
    }
}
