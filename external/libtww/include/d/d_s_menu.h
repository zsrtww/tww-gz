#ifndef D_S_MENU
#define D_S_MENU

#include "../dolphin/gctypes.h"
#include "../SSystem/SComponent/c_phase.h"

// This is an incomplete implementation of the real `menu_of_scene_class`.
// This is to avoid copying over a long chain of header dependecies from tww decomp

struct room_inf {
    char name[0x20];
    u8 field_0x20;
    char stageName[0x08];
    s8 roomNo;
    u8 startCode;
    s8 layerNo;
};

struct stage_inf {
    char name[0x20];
    u8 field_0x20;
    u8 roomNum;
    u8 field_0x22;
    u8 field_0x23;
    room_inf* roomPtr;
};

struct menu_inf {
    u8 num;
    stage_inf* stage;
};

typedef struct menu_of_scene_class {
    /* 0x000 */ char scene_class[0x1C4 - 0x0]; // base class not ported
    /* 0x1C4 */ request_of_phase_process_class mPhs;
    /* 0x1CC */ void* command; // real type not ported
    /* 0x1D0 */ void* fontCommand; // real type not ported
    /* 0x1D4 */ menu_inf* info;
    /* 0x1D8 */ void* fontRes; // real type not ported
    /* 0x1DC */ void* font; // real type not ported
    /* 0x1E0 */ u8 startCode;
    /* 0x1E1 */ u8 field_0x1e1;
    /* 0x1E2 */ u8 field_0x1e2;
} menu_of_scene_class;

extern "C" s32 l_timepat;
extern "C" s16 l_weekpat;
extern "C" s8* l_groupPoint;
extern "C" s32 l_cursolID;

#ifdef PAL
extern "C" u8 l_languageType;
#endif

#endif /* D_S_MENU */