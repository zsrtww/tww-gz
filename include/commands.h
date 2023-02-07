#pragma once
#include "libtww/dolphin/gctypes.h"
#include "libtww/SSystem/SComponent/c_xyz.h"

#define COMMANDS_AMNT 3

extern bool g_commandStates[COMMANDS_AMNT];

enum Commands {
    CMD_STORE_POSITION,
    CMD_LOAD_POSITION,
    CMD_MOON_JUMP,
};

struct Command {
    bool& active;
    uint16_t buttons;
    void (*command)();
};

void GZCmd_processInputs();
void GZCmd_enable(int idx);
void GZCmd_disable(int idx);
