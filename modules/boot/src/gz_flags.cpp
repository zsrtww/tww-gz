#include "gz_flags.h"
#include <cstring>
#include "controller.h"
#include "scene.h"
#include "save_manager.h"
#include "rels/include/defines.h"

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

    // Timer set after dScnPly__phase_4, delay until objects are fully loaded
    if (SaveManager::s_applyAfterTimer > 0) {
        SaveManager::s_applyAfterTimer--;
    } else if (SaveManager::s_applyAfterTimer == 0) {
        if (gSaveManager.mPracticeFileOpts.inject_options_after_load) {
            gSaveManager.mPracticeFileOpts.inject_options_after_load();
        }
        SaveManager::s_applyAfterTimer = -1;
    }
}
