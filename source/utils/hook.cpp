#include "utils/hook.h"
#include "lib.h"
#include "libtww/addrs.h"
#include "utils/patch.h"
#include "controller.h"
#include "menus/tools_menu.h"
#include "libtww/f_op/f_op_scene_req.h"

#define HOOK_DEF(rettype, name, params)                                                            \
    typedef rettype(*tww_##name##_t) params;                                                       \
    tww_##name##_t name##Trampoline;

HOOK_DEF(void, draw, (void*));
HOOK_DEF(u32, PADRead, (u16*));
HOOK_DEF(void, cDyl_InitAsync, (void*, void*, void*));
HOOK_DEF(void, fapGm_Execute, (void));
HOOK_DEF(void, dComIfGs_setGameStartStage, (void));
HOOK_DEF(int, dScnPly_Draw, (void*));

struct {
    u32 a[2];
} trampolines[HOOK_AMNT];

namespace Hook {

void drawHook(void* p1) {
    drawTrampoline(p1);
    draw();
}

void initHook(void* p1, void* p2, void* p3) {
    cDyl_InitAsyncTrampoline(p1, p2, p3);
    init();
}

void gameLoopHook(void) {
    game_loop();
    fapGm_ExecuteTrampoline();
}

u32 readControllerHook(u16* p1) {
    auto returnValue = PADReadTrampoline(p1);
    GZ_readController();
    return returnValue;
}

void dComIfGs_setGameStartStageHook() {
    if (g_tools[DISABLE_SVCHECK_INDEX].active) {
        dComIfGs_setReturnPlace(dComIfGp_getStartStageName(), dComIfGp_roomControl_getStayNo(),
                                dComIfGp_roomControl_getStayNo());
    } else {
        dComIfGs_setGameStartStageTrampoline();
    }
}

#ifdef NTSCU
#define menu_data_path (char*)0x80362DAA
#endif

#ifdef NTSCJ
#define menu_data_path (char*)0x80356249
#endif

int dScnPly_DrawHook(void* _this) {
    // if L + R + B is pressed, change scene to map select
    if (tww_mPadStatus.button == (CButton::L | CButton::R | CButton::B)) {
        // overwrite original path with our custom path
        tww_strcpy(menu_data_path, "/twwgz/mn/Menu1.dat");

        // 6 is the process ID for map select menu
        fopScnM_ChangeReq(_this, 6, 0, 5);
        return 1;
    } else {
        return dScnPly_DrawTrampoline(_this);
    }
}

void applyHooks() {
#define APPLY_HOOK(name, addr, idx, func)                                                          \
    name##Trampoline = hookFunction((tww_##name##_t)addr, trampolines[idx].a, func)
    APPLY_HOOK(draw, tww_draw_console_addr, HK_LIB_DRAW_INDEX, drawHook);
    APPLY_HOOK(cDyl_InitAsync, tww_cDyl_InitAsync_addr, HK_LIB_INIT_INDEX, initHook);
    APPLY_HOOK(fapGm_Execute, tww_fapGm_Execute_addr, HK_LIB_GAME_LOOP_INDEX, gameLoopHook);
    APPLY_HOOK(PADRead, tww_PADRead_addr, HK_LIB_READ_CONTROLLER_INDEX, readControllerHook);
    APPLY_HOOK(dComIfGs_setGameStartStage, tww_dComIfGs_setGameStartStage_addr,
               HK_LIB_SET_SAVE_LOC_INDEX, dComIfGs_setGameStartStageHook);
    APPLY_HOOK(dScnPly_Draw, tww_dScnPly_Draw_addr, HK_LIB_OPEN_WARP_MENU, dScnPly_DrawHook);

#undef APPLY_HOOK
}
}  // namespace Hook