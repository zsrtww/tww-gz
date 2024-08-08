#include "utils/hook.h"
#include <cstdio>
#include "boot.h"
#include "controller.h"
#include "tools.h"
#include "scene.h"
#include "save_manager.h"
#include "geometry_draw.h"
#include "libtww/include/addrs.h"
#include "libtww/include/d/d_procname.h"
#include "libtww/include/f_op/f_op_scene_req.h"
#include "libtww/include/SSystem/SComponent/c_phase.h"
#include "rels/include/patch.h"
#include "rels/include/cxx.h"
#include "rels/include/defines.h"

#define HOOK_DEF(rettype, name, params)                                                                                \
    typedef rettype(*tww_##name##_t) params;                                                                           \
    tww_##name##_t name##Trampoline;

HOOK_DEF(void, draw, (void*));
HOOK_DEF(u32, PADRead, (u16*));
HOOK_DEF(void, cDyl_InitAsync, (void*, void*, void*));
HOOK_DEF(void, fapGm_Execute, (void));
HOOK_DEF(void, dComIfGs_setGameStartStage, (void));
HOOK_DEF(int, dScnPly_Draw, (void*));
HOOK_DEF(void, putSave, (void*, int));
HOOK_DEF(int, dScnPly__phase_1, (void*));
HOOK_DEF(int, dScnPly__phase_4, (void*));
HOOK_DEF(int, dScnPly__phase_compleate, (void*));
HOOK_DEF(void, setDaytime, (void*));
HOOK_DEF(void, BeforeOfPaint, (void));
HOOK_DEF(void, dCcS__draw, (dCcS*));
HOOK_DEF(void, dCcS__MoveAfterCheck, (dCcS*));
HOOK_DEF(BOOL, dScnLogo_Delete, (void*));

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

int dScnPly__phase_1Hook(void* i_scene) {
    SaveManager::loadData();

    return dScnPly__phase_1Trampoline(i_scene);
}

int dScnPly__phase_4Hook(void* i_scene) {
    int ret = dScnPly__phase_4Trampoline(i_scene);

    // Only apply the `after` options now if phase 4 indicates the loading proccess is complete.
    // If the rest of the phases need to run, the options will be applied later in
    // `dScnPly__phase_compleate`.
    if (ret == cPhs_COMPLEATE_e) {
        SaveManager::applyAfterOptions();
    }

    if (fpcM_GetName(i_scene) == PROC_OPENING_SCENE) {
        
    }

    return ret;
}

int dScnPly__phase_compleateHook(void* i_scene) {
    // If execution reaches this point, it means that the loading process did not exit early in
    // `dScnPly__phase_4`. So, apply the `after` options now.
    SaveManager::applyAfterOptions();
    return dScnPly__phase_compleateTrampoline(i_scene);
}

#ifdef NTSCU
#define menu_data_path (char*)0x80362DAA
#endif

#ifdef NTSCJ
#define menu_data_path (char*)0x80356249
#endif

#ifdef PAL
#define menu_data_path (char*)0x80369919
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

void setDaytimeHook(void* i_this) {
    if (g_sceneFlags[FREEZE_TIME_INDEX].active) {
        return;
    } else {
        return setDaytimeTrampoline(i_this);
    }
}

void beforeOfPaintHook() {
    BeforeOfPaintTrampoline();
    dDbVw_deleteDrawPacketList();
}

void dCcSDrawHook(dCcS* i_this) {
    GZ_drawCc(i_this);
    return dCcS__drawTrampoline(i_this);
}

void dCcSMoveAfterCheckHook(dCcS* i_this) {
    dCcS_Data::at_obj_count = i_this->mObjAtCount;
    dCcS_Data::tg_obj_count = i_this->mObjTgCount;
    dCcS_Data::co_obj_count = i_this->mObjCoCount;
    return dCcS__MoveAfterCheckTrampoline(i_this);
}

BOOL dScnLogo_DeleteHook(void* i_this) {
    GZ_handleCardLoad();
    return dScnLogo_DeleteTrampoline(i_this);
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
int phase_4__FP13dScnPly_ply_c(void*);
int phase_compleate__FPv(void*);
void setDaytime__18dScnKy_env_light_cFv(void*);
void dScnPly_BeforeOfPaint__Fv();
void Draw__4dCcSFv(dCcS*);
void MoveAfterCheck__4dCcSFv(dCcS*);
BOOL dScnLogo_Delete__FP10dScnLogo_c(void*);
}

KEEP_FUNC void applyHooks() {
#define APPLY_HOOK(name, addr, func) name##Trampoline = hookFunction((tww_##name##_t)(addr), func)
    APPLY_HOOK(fapGm_Execute, &f_fapGm_Execute, gameLoopHook);
    APPLY_HOOK(draw, &draw_console, drawHook);
    APPLY_HOOK(PADRead, &PADRead, readControllerHook);

    APPLY_HOOK(dComIfGs_setGameStartStage, &dComIfGs_setGameStartStage__Fv, dComIfGs_setGameStartStageHook);
    APPLY_HOOK(dScnPly_Draw, &dScnPly_Draw__FP13dScnPly_ply_c, dScnPly_DrawHook);
    APPLY_HOOK(putSave, &putSave__10dSv_info_cFi, putSaveHook);
    APPLY_HOOK(dScnPly__phase_1, &phase_1__FP13dScnPly_ply_c, dScnPly__phase_1Hook);
    APPLY_HOOK(dScnPly__phase_4, &phase_4__FP13dScnPly_ply_c, dScnPly__phase_4Hook);
    APPLY_HOOK(dScnPly__phase_compleate, &phase_compleate__FPv, dScnPly__phase_compleateHook);
    APPLY_HOOK(setDaytime, &setDaytime__18dScnKy_env_light_cFv, setDaytimeHook);
    APPLY_HOOK(BeforeOfPaint, &dScnPly_BeforeOfPaint__Fv, beforeOfPaintHook);
    APPLY_HOOK(dCcS__draw, &Draw__4dCcSFv, dCcSDrawHook);
    APPLY_HOOK(dCcS__MoveAfterCheck, &MoveAfterCheck__4dCcSFv, dCcSMoveAfterCheckHook);
    APPLY_HOOK(dScnLogo_Delete, &dScnLogo_Delete__FP10dScnLogo_c, dScnLogo_DeleteHook);

#undef APPLY_HOOK
}
}  // namespace Hook