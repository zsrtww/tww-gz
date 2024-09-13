#include "utils/hook.h"
#include <cstdio>
#include "boot.h"
#include "controller.h"
#include "tools.h"
#include "scene.h"
#include "save_manager.h"
#include "geometry_draw.h"
#include "gz_flags.h"
#include "events/pre_loop_listener.h"
#include "libtww/include/addrs.h"
#include "libtww/include/d/d_procname.h"
#include "libtww/include/f_op/f_op_scene_req.h"
#include "libtww/include/SSystem/SComponent/c_phase.h"
#include "libtww/include/d/d_s_menu.h"
#include "libtww/include/JSystem/JUtility/JUTReport.h"
#include "rels/include/patch.h"
#include "rels/include/cxx.h"
#include "rels/include/defines.h"
#include "menus/menu_settings/include/settings_menu.h"
#include "libtww/include/d/com/d_com_inf_game.h"

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
HOOK_DEF(int, dScnPly_Delete, (void*));
HOOK_DEF(void, setDaytime, (void*));
HOOK_DEF(void, BeforeOfPaint, (void));
HOOK_DEF(void, dCcS__draw, (dCcS*));
HOOK_DEF(void, dCcS__MoveAfterCheck, (dCcS*));
HOOK_DEF(BOOL, dScnLogo_Delete, (void*));
HOOK_DEF(BOOL, dScnMenu_Draw, (menu_of_scene_class*));
HOOK_DEF(void, onEventBit, (void*, uint16_t));
HOOK_DEF(void, offEventBit, (void*, uint16_t));
HOOK_DEF(void, onSwitch, (void*, int, int));

int spawn_id_input = 0;
bool g_flagLogEnabled = 0;

namespace Hook {

static char buf[40];
void onEventBitHook(void* addr, uint16_t pFlag) {
    if (g_flagLogEnabled) {
        if (addr == &g_dComIfG_gameInfo.info.mTmp) {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | ON", "Event Tmp", pFlag >> 8, pFlag & 0xFF);
        } else {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | ON", "Event", pFlag >> 8, pFlag & 0xFF);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }

    return onEventBitTrampoline(addr, pFlag);
}

void offEventBitHook(void* addr, uint16_t pFlag) {
    if (g_flagLogEnabled) {
        if (addr == &g_dComIfG_gameInfo.info.mTmp) {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | OFF", "Event Tmp", pFlag >> 8, pFlag & 0xFF);
        } else {
            snprintf(buf, sizeof(buf), "%s[0x%X] : %X | OFF", "Event", pFlag >> 8, pFlag & 0xFF);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }

    return offEventBitTrampoline(addr, pFlag);
}

void onSwitchHook(void* addr, int pFlag, int i_roomNo) {
    int tmp = pFlag;
    if (g_flagLogEnabled) {
        if (pFlag < 0x80) {
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Memory Switch", tmp >> 5, tmp & 0x1F);
        } else if (pFlag < 0xC0) {
            tmp -= 0x80;
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Dan Switch", tmp >> 5, tmp & 0x1F);
        } else if (pFlag < 0xE0) {
            tmp -= 0xC0;
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Zone Switch", tmp >> 5, tmp & 0x1F);
        } else {
            tmp -= 0xE0;
            snprintf(buf, sizeof(buf), "%s[%d] : %d | ON", "Zone OneSwitch", tmp >> 5, tmp & 0x1F);
        }
        FIFOQueue::push(buf, Queue, 0xFFFFFF00);
    }
    return onSwitchTrampoline(addr, pFlag, i_roomNo);
}

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
    if (g_tools[DISABLE_SVCHECK_INDEX].active) {
        dComIfGs_setReturnPlace(dComIfGp_getStartStageName(), dComIfGp_roomControl_getStayNo(), spawn_id_input);
    } else {
        dComIfGs_setGameStartStageTrampoline();
    }
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
    s16 scene = fpcM_GetName(i_scene);

    if (scene == PROC_OPENING_SCENE || scene == PROC_OPENING2_SCENE) {
        g_PreLoopListener->addListener(GZ_endlessNightOnTitle);
    }

    return ret;
}

int dScnPly_DeleteHook(void* i_scene) {
    s16 scene = fpcM_GetName(i_scene);

    if (scene == PROC_OPENING_SCENE || scene == PROC_OPENING2_SCENE) {
        g_PreLoopListener->removeListener(GZ_endlessNightOnTitle);
    }

    return dScnPly_DeleteTrampoline(i_scene);
}

#define f_onEventBit onEventBit__11dSv_event_cFUs
#define f_offEventBit offEventBit__11dSv_event_cFUs
#define f_onSwitch onSwitch__12dSv_memBit_cFi

#ifdef NTSCU
#define menu_data_path (char*)0x80362DAA
#endif

#ifdef NTSCJ
#define menu_data_path (char*)0x80356249
#endif

#ifdef PAL
#define menu_data_path (char*)0x80369919
#endif

extern "C" {
void f_onEventBit(void*, uint16_t);
void f_offEventBit(void*, uint16_t);
void f_onSwitch(void*, int, int);
}

f32 g_savedMapSelectTime = 120.0f;

int dScnPly_DrawHook(void* i_this) {
    // if DPAD_DOWN + Y + Z is pressed, change scene to map select
    if (g_tools[MAP_SELECT_INDEX].active && mPadStatus.button == (CButton::DPAD_DOWN | CButton::Y | CButton::Z)) {
        // overwrite original path with our custom path
        strcpy(menu_data_path, "/twwgz/mn/Menu1.dat");
        fopScnM_ChangeReq(i_this, PROC_MENU_SCENE, 0, 5);
        g_savedMapSelectTime = dComIfGs_getTime();
    }

    return dScnPly_DrawTrampoline(i_this);
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
    if (g_FrameAdvEnabled && g_dCcSCopy != nullptr) {
        // Draw the dCcS copy instead of the real instance, when frame advance is active
        GZ_drawCc(g_dCcSCopy);
    } else {
        GZ_drawCc(i_this);
    }

    return dCcS__drawTrampoline(i_this);
}

void dCcSMoveAfterCheckHook(dCcS* i_this) {
    if (g_FrameAdvEnabled && g_dCcSCopy != nullptr) {
        // Copy dCcS data every time a frame is advanced, to draw later
        if (g_FrameTriggered) {
            memcpy(g_dCcSCopy, dComIfG_Ccsp(), sizeof(dCcS));
        }

        dCcS_Data::at_obj_count = g_dCcSCopy->mObjAtCount;
        dCcS_Data::tg_obj_count = g_dCcSCopy->mObjTgCount;
        dCcS_Data::co_obj_count = g_dCcSCopy->mObjCoCount;
    } else {
        dCcS_Data::at_obj_count = i_this->mObjAtCount;
        dCcS_Data::tg_obj_count = i_this->mObjTgCount;
        dCcS_Data::co_obj_count = i_this->mObjCoCount;
    }

    return dCcS__MoveAfterCheckTrampoline(i_this);
}

BOOL dScnLogo_DeleteHook(void* i_this) {
    GZ_handleCardLoad();
    return dScnLogo_DeleteTrampoline(i_this);
}

BOOL dScnMenu_DrawHook(menu_of_scene_class* i_this) {
    const char* time_strings[] = {
        // Note these are not direct translations.
        // The time speed features of the original map select are broken.
        "default",  // this redunant morning option is repurposed
        "Morning", "Morning 2", "Afternoon", "Evening", "Night",
    };
    const char* day_strings[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",
    };
    BOOL ret = dScnMenu_DrawTrampoline(i_this);

    JUTReport(40, 40, "Map Select - tww-gz");

#ifdef PAL
    const char* language_strings[] = {
        "English", "German", "French", "Spanish", "Italian",
    };
    JUTReport(350, 20, "Z (Ctrl 4)");
    JUTReport(350, 40, "Language: %s", language_strings[l_languageType]);
#endif

    JUTReport(40, 410, "Day (dpad-r/l): %s", day_strings[l_weekpat]);

    if (l_timepat <= 5) {
        JUTReport(40, 430, "Time (X/Y): %s", time_strings[l_timepat]);

        if (l_timepat == 0) {
            // restore saved time for "default"
            dComIfGs_setTime(g_savedMapSelectTime);
            g_env_light.mCurTime = g_savedMapSelectTime;
        }
    } else if (l_timepat == 6) {
        JUTReport(40, 430, "Time (X/Y): 12:00am");
    } else if (l_timepat >= 7 && l_timepat <= 17) {
        JUTReport(40, 430, "Time (X/Y): %d:00am", l_timepat - 6);
    } else if (l_timepat == 18) {
        JUTReport(40, 430, "Time (X/Y): 12:00pm");
    } else {
        JUTReport(40, 430, "Time (X/Y): %d:00pm", l_timepat - 18);
    }

    if (i_this->startCode == 0) {
        JUTReport(40, 450, "Spawn Point (R/L): default");
    } else {
        JUTReport(40, 450, "Spawn Point (R/L): %d", i_this->startCode - 1);
    }

    JUTReport(400, 410, "A (Ctrl 3)");
    if (dComIfGs_isEventBit(0x2d01)) {
        JUTReport(400, 430, "FF2 CS Flag: ON");
    } else {
        JUTReport(400, 430, "FF2 CS Flag: OFF");
    }

    return ret;
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
int dScnPly_Delete__FP13dScnPly_ply_c(void*);
void setDaytime__18dScnKy_env_light_cFv(void*);
void dScnPly_BeforeOfPaint__Fv();
void Draw__4dCcSFv(dCcS*);
void MoveAfterCheck__4dCcSFv(dCcS*);
BOOL dScnLogo_Delete__FP10dScnLogo_c(void*);
BOOL dScnMenu_Draw__FP19menu_of_scene_class(menu_of_scene_class*);
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
    APPLY_HOOK(dScnPly_Delete, &dScnPly_Delete__FP13dScnPly_ply_c, dScnPly_DeleteHook);
    APPLY_HOOK(setDaytime, &setDaytime__18dScnKy_env_light_cFv, setDaytimeHook);
    APPLY_HOOK(BeforeOfPaint, &dScnPly_BeforeOfPaint__Fv, beforeOfPaintHook);
    APPLY_HOOK(dCcS__draw, &Draw__4dCcSFv, dCcSDrawHook);
    APPLY_HOOK(dCcS__MoveAfterCheck, &MoveAfterCheck__4dCcSFv, dCcSMoveAfterCheckHook);
    APPLY_HOOK(dScnLogo_Delete, &dScnLogo_Delete__FP10dScnLogo_c, dScnLogo_DeleteHook);
    APPLY_HOOK(dScnMenu_Draw, &dScnMenu_Draw__FP19menu_of_scene_class, dScnMenu_DrawHook);

    APPLY_HOOK(onEventBit, &f_onEventBit, onEventBitHook);
    APPLY_HOOK(offEventBit, &f_offEventBit, offEventBitHook);
    APPLY_HOOK(onSwitch, &f_onSwitch, onSwitchHook);
#undef APPLY_HOOK
}
}  // namespace Hook