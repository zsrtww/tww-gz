#pragma once

#define HOOK_AMNT 6
enum HookIndex {
    HK_LIB_DRAW_INDEX = 0,
    HK_LIB_INIT_INDEX = 1,
    HK_LIB_GAME_LOOP_INDEX = 2,
    HK_LIB_READ_CONTROLLER_INDEX = 3,
    HK_LIB_SET_SAVE_LOC_INDEX = 4,
    HK_LIB_OPEN_WARP_MENU = 5,
};

namespace Hook {
void applyHooks();
}  // namespace Hook