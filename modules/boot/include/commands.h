#pragma once
#include "libtww/include/dolphin/gctypes.h"

#define COMMANDS_AMNT 15

extern bool g_commandStates[COMMANDS_AMNT];
extern bool g_timer_reset;
extern bool g_counterToggle;
extern f32 g_landSpeed;
extern f32 g_waterSpeed;

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
    CMD_AREA_RELOAD,
    CMD_REFILL_HEALTH,
    CMD_REFILL_MAGIC,
    CMD_TOGGLE_TIMER,
    CMD_RESET_TIMER,
};

struct Command {
    bool& active;
    uint16_t buttons;
    void (*command)();
};

void GZCmd_processInputs();
void GZCmd_enable(int idx);
void GZCmd_disable(int idx);
