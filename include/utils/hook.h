#pragma once

#define HOOK_AMNT 4
enum HookIndex {
    HK_LIB_DRAW_INDEX = 0,
    HK_LIB_INIT_INDEX = 1,
    HK_LIB_GAME_LOOP_INDEX = 2,
    HK_LIB_READ_CONTROLLER_INDEX = 3,
};

namespace Hook {
void applyHooks();
}  // namespace Hook