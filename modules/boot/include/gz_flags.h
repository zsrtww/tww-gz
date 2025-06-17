#pragma once

#include "font.h"
#include "settings.h"
#include "fifo_queue.h"
#include "libtww/include/d/com/d_com_inf_game.h"

#define MAX_GZ_FLAGS 1

struct GZFlag {
    bool* mpFlag;
    int mPhase;
    void (*mpActiveFunc)();
    void (*mpDeactiveFunc)();
};

extern bool g_FrameAdvEnabled;
extern bool g_FrameTriggered;
extern dCcS* g_dCcSCopy;

enum LoopPhase {
    GAME_LOOP,
    POST_GAME_LOOP
};

inline bool GZ_checkDropShadows() {
    return g_dropShadows;
}

inline void GZ_setFifoVisible(bool visible) {
    g_fifoVisible = visible;
}

void GZ_frameAdvance();
void GZ_execute(int phase);
void GZ_drawFrameTex(Texture* pauseTex, Texture* playTex);
