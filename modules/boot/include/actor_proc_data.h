#pragma once

#include "libtww/include/dolphin/gctypes.h"

struct procBinData {
    s16 procId;
    char procName[30];
} __attribute__((aligned(32)));

void loadActorName(s16&);
void loadActorName();
void loadPlayerProc(int&);