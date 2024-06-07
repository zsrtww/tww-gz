#include "gz_flags.h"
#include <cstring>
#include "controller.h"
#include "scene.h"
#include "rels/include/defines.h"

bool g_framePaused = false;

GZFlag g_gzFlags[MAX_GZ_FLAGS] = {};

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
