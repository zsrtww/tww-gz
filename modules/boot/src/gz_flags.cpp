#include "gz_flags.h"
#include <cstring>
#include "controller.h"
#include "scene.h"
#include "tools.h"
#include "rels/include/defines.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "libtww/include/m_Do/m_Do_controller_pad.h"
#include "libtww/include/d/d_s_play.h"


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

KEEP_FUNC void GZ_frameAdvance() {
    static bool sFrameAdvEnabled = false;
    static u16 sPrevHold;
    static int sHoldCounter = 0;

    if (g_tools[FRAME_ADVANCE_INDEX].active) {
        if (CPad_CHECK_TRIG_DOWN(CONTROLLER_1)) {
            sFrameAdvEnabled = !sFrameAdvEnabled;
        } else if (sFrameAdvEnabled) {
            dScnPlay_nextPauseTimer = 1;

            // Working with bitfields is awkward. Have to use memcpy to move values in an out of 
            // the whole bitfield at once.
            // The point here is to save buttons on the current and previous frame to allow
            // for input buffering between frames.
            u16 curFrameHold;
            memcpy(&curFrameHold, &g_mDoCPd_cpadInfo[CONTROLLER_1].mButtonHold, sizeof(curFrameHold));

            u16 newTrig = curFrameHold & ~sPrevHold;
            memcpy(&g_mDoCPd_cpadInfo[CONTROLLER_1].mButtonTrig, &newTrig, sizeof(newTrig));

            if (CPad_CHECK_HOLD_UP(CONTROLLER_1)) {
                sHoldCounter++;
            } else {
                sHoldCounter = 0;
            }

            if (CPad_CHECK_TRIG_UP(CONTROLLER_1) || sHoldCounter >= 30) {
                dScnPlay_nextPauseTimer = 0;
                sPrevHold = curFrameHold;
            }

            // unset dpad up to prevent opening the map
            g_mDoCPd_cpadInfo[CONTROLLER_1].mButtonTrig.up = 0;
        }
    }
}
