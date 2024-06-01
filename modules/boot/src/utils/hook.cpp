#include "utils/hook.h"
#include <cstdio>
#include "boot.h"
#include "controller.h"
#include "tools.h"
#include "save_manager.h"
#include "libtww/include/addrs.h"
#include "libtww/include/f_op/f_op_scene_req.h"
#include "rels/include/patch.h"
#include "rels/include/cxx.h"
#include "rels/include/defines.h"

#define HOOK_DEF(rettype, name, params)                                                            \
    typedef rettype(*tww_##name##_t) params;                                                       \
    tww_##name##_t name##Trampoline;

HOOK_DEF(void, draw, (void*));
HOOK_DEF(u32, PADRead, (u16*));
HOOK_DEF(void, cDyl_InitAsync, (void*, void*, void*));
HOOK_DEF(void, fapGm_Execute, (void));
HOOK_DEF(void, dComIfGs_setGameStartStage, (void));
HOOK_DEF(int, dScnPly_Draw, (void*));
HOOK_DEF(void, putSave, (void*, int));
HOOK_DEF(int, dScnPly__phase_1, (void*));

namespace Hook {
void gameLoopHook(void) {
    game_loop();
    fapGm_ExecuteTrampoline();
    post_game_loop();
}

void drawHook(void* p1) {
    drawTrampoline(p1);
    draw();
}

uint32_t readControllerHook(uint16_t* p1) {
    auto returnValue = PADReadTrampoline(p1);
    GZ_readController();
    return returnValue;
}

void dComIfGs_setGameStartStageHook() {
    /*if (g_tools[DISABLE_SVCHECK_INDEX].active) {
        dComIfGs_setReturnPlace(dComIfGp_getStartStageName(), dComIfGp_roomControl_getStayNo(),
                                0); // fix this to use proper last save point later
    } else {
        dComIfGs_setGameStartStageTrampoline();
    }   */

    dComIfGs_setGameStartStageTrampoline();
}

void putSaveHook(void* addr, int stageNo) {
    return putSaveTrampoline(addr, stageNo);
}

int saveInjectHook(void* i_scene) {
    if (SaveManager::s_injectSave) {
        SaveManager::loadData();
    }
    
    return dScnPly__phase_1Trampoline(i_scene);
}

#ifdef NTSCU
#define menu_data_path (char*)0x80362DAA
#endif

#ifdef NTSCJ
#define menu_data_path (char*)0x80356249
#endif

int dScnPly_DrawHook(void* _this) {
    // if DPAD_DOWN + Y + Z is pressed, change scene to map select
    if (g_tools[MAP_SELECT_INDEX].active && mPadStatus.button == (CButton::DPAD_DOWN | CButton::Y | CButton::Z)) {
        // overwrite original path with our custom path
        strcpy(menu_data_path, "/twwgz/mn/Menu1.dat");

        // 6 is the process ID for map select menu
        fopScnM_ChangeReq(_this, 6, 0, 5);
        return 1;
    } else {
        return dScnPly_DrawTrampoline(_this);
    }
}

#define draw_console draw__17JUTConsoleManagerCFv
#define f_fapGm_Execute fapGm_Execute__Fv

extern "C" {
uint32_t PADRead(uint16_t*);
void draw_console(void*);
void f_fapGm_Execute();
void dComIfGs_setGameStartStage__Fv(void);
int dScnPly_Draw__FP13dScnPly_ply_c(void*);
void putSave__10dSv_info_cFi(void*, int);
int phase_1__FP13dScnPly_ply_c(void*);
}

KEEP_FUNC void applyHooks() {
#define APPLY_HOOK(name, addr, func) name##Trampoline = hookFunction((tww_##name##_t)(addr), func)
    APPLY_HOOK(fapGm_Execute, &f_fapGm_Execute, gameLoopHook);
    APPLY_HOOK(draw, &draw_console, drawHook);
    APPLY_HOOK(PADRead, &PADRead, readControllerHook);

    APPLY_HOOK(dComIfGs_setGameStartStage, &dComIfGs_setGameStartStage__Fv, dComIfGs_setGameStartStageHook);
    APPLY_HOOK(dScnPly_Draw, &dScnPly_Draw__FP13dScnPly_ply_c, dScnPly_DrawHook);
    APPLY_HOOK(putSave, &putSave__10dSv_info_cFi, putSaveHook);
    APPLY_HOOK(dScnPly__phase_1, &phase_1__FP13dScnPly_ply_c, saveInjectHook);

#undef APPLY_HOOK
}
}  // namespace Hook