#pragma once

#include "addrs.h"
#include "gctypes.h"

extern "C" {
#define main_trampoline ((void (*)(void))0x803737b4)

void game_loop();
void init();
void draw();
void apply_lib_hooks();
};
