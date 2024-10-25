#pragma once
#include "libtww/include/dolphin/gctypes.h"

#define COMMANDS_AMNT 17
#define DEFAULT_WATER_SPEED 1500.0f
#define DEFAULT_LAND_SPEED 150.0f

extern bool g_commandStates[COMMANDS_AMNT];
extern bool g_timer_reset;
extern bool g_counterToggle;
extern bool g_medli_room;
extern bool g_makar_room;

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
    CMD_VOID,
    CMD_HOVER_BOOTS,
};

struct Command {
    bool& active;
    uint16_t buttons;
    void (*command)();
};

void GZCmd_processInputs();
void GZCmd_enable(int idx);
void GZCmd_disable(int idx);
