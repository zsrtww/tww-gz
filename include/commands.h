#pragma once
#include "libtww/dolphin/gctypes.h"
#include "libtww/SSystem/SComponent/c_xyz.h"

#define COMMANDS_AMNT 11

extern bool g_commandStates[COMMANDS_AMNT];

enum Commands {
    CMD_STORE_POSITION,
    CMD_LOAD_POSITION,
    CMD_MOON_JUMP,
    CMD_STORAGE,
    CMD_NORMAL_COLLISION,
    CMD_CHEST_STORAGE,
    CMD_DOOR_CANCEL,
    CMD_QUARTER_HEART,
    CMD_FAST_MOVEMENT,
    CMD_UPCHARGE,
    CMD_AREA_RELOAD
};

struct Command {
    bool& active;
    uint16_t buttons;
    void (*command)();
};

void GZCmd_processInputs();
void GZCmd_enable(int idx);
void GZCmd_disable(int idx);
