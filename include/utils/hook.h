#pragma once

#define HOOK_AMNT 8
enum HookIndex {
    HK_LIB_DRAW_INDEX = 0,
    HK_LIB_INIT_INDEX = 1,
    HK_LIB_GAME_LOOP_INDEX = 2,
    HK_LIB_READ_CONTROLLER_INDEX = 3,
    HK_LIB_SET_SAVE_LOC_INDEX = 4,
    HK_LIB_OPEN_WARP_MENU = 5,
    HK_LIB_PUT_SAVE_INDEX = 6,
    HK_LIB_DRAW_SCREEN_PLAYER_INDEX = 7,
};

namespace Hook {
void applyHooks();
}  // namespace Hook