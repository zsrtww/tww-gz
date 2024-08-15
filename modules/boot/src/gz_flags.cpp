#include "gz_flags.h"
#include <cstring>
#include "controller.h"
#include "scene.h"
#include "rels/include/defines.h"
#include "libtww/include/d/d_s_play.h"

bool g_framePaused = false;

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

#define HOLD_BTNS g_mDoCPd_cpadInfo[0].mButtonFlags
#define TRIG_BTNS g_mDoCPd_cpadInfo[0].mPressedButtonFlags
#define FRAME_ADVANCE_BTN GZPad::R

KEEP_FUNC void GZ_frameAdvance() {
    if (!g_framePaused) {
        return;
    }
    static int holdCounter = 0;
    static uint32_t buttonsPrev = 0;
    dScnPlay_nextPauseTimer = 1;

    TRIG_BTNS = HOLD_BTNS & ~buttonsPrev;

    if (HOLD_BTNS & FRAME_ADVANCE_BTN) {
        holdCounter++;
    } else {
        holdCounter = 0;
    }

    if (TRIG_BTNS & FRAME_ADVANCE_BTN) {
        // this sets pause timer to 0 for 1 frame,
        // which lets 1 frame pass before pausing again
        dScnPlay_nextPauseTimer = 0;
        buttonsPrev = HOLD_BTNS;
        HOLD_BTNS &= ~FRAME_ADVANCE_BTN;
    }

    // frames start passing at normal speed after holding for 30 frames
    if (holdCounter >= 30) {
        dScnPlay_nextPauseTimer = 0;
        buttonsPrev = HOLD_BTNS;
        HOLD_BTNS &= ~FRAME_ADVANCE_BTN;
    }
}
