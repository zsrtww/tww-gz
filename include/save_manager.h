#pragma once

#include "cheats.h"
#include "menus/tools_menu.h"
#include "menus/cheat_menu.h"
#include "menus/watches_menu.h"
#include "commands.h"
#include "libtww/dolphin/mtx/vec.h"
#include "libtww/d/com/d_com_inf_game.h"

#define GZ_SAVE_VERSION_NUMBER 0
#define GZ_SAVE_ENTRIES_AMNT 7//10

#ifdef NTSCJ
#define sTmpBuf 0x803a8540
#endif

#define MEMFILE_BUF ((void*)sTmpBuf)

// index into qlog where these exist
#define SPAWN_INDEX 96
#define ROOM_INDEX 97
#define STAGE_INDEX 88

struct AreaReload {
    uint8_t temp_flags[0x20];
    uint8_t tears[4];
};

typedef void (*LoadingCallback)(void);

class special {
public:
    special(int i_idx, LoadingCallback cb_during, LoadingCallback cb_after) {
        idx = i_idx;
        CallbackDuring = cb_during;
        CallbackAfter = cb_after;
    }

    uint32_t idx;
    LoadingCallback CallbackDuring;
    LoadingCallback CallbackAfter;

private:
};

struct PracticeFileOpts {
    void (*inject_options_before_load)();
    void (*inject_options_during_load)();
    void (*inject_options_after_load)();
    int inject_options_after_counter = 0;
};

struct PracticeSaveInfo {
    uint8_t requirements;
    uint8_t _p0[1];
    uint16_t angle;
    Vec position;
    Vec cam_pos;
    Vec cam_target;
    uint32_t counter;
    char filename[32];
    uint8_t _p1[4];
} __attribute__((packed));

class SaveManager {
public:
    PracticeFileOpts mPracticeFileOpts;
    PracticeSaveInfo mPracticeSaveInfo __attribute__((aligned(32)));
    AreaReload mAreaReloadOpts;
    special* mSpecials;
    bool loading_initiated = false;
    int repeat_count = 0;
    bool repeat_during = false;

    static bool s_injectSave;
    static bool s_injectMemfile;

public:
    static void injectSave(void* buffer);
    static void injectMemfile(void* buffer);
    static void injectDefault_before();
    static void injectDefault_during();
    static void injectMemfile_during();
    static void injectDefault_after();
    static void loadSave(uint32_t id, const char* category, special* i_specials = nullptr,
                         int size = 0);
    static void loadSavefile(const char* fileName);
    static void triggerLoad(uint32_t id, const char* category, special i_specials[], int size);
    static void triggerMemfileLoad();
    static void defaultLoad();
    static void setLinkInfo();
    static void setPositionCamera();

    static void loadData();

    void setSavePosition(float x, float y, float z) {
        mPracticeSaveInfo.position.x = x;
        mPracticeSaveInfo.position.y = y;
        mPracticeSaveInfo.position.z = z;
    }

    void setSaveAngle(int16_t angle) { mPracticeSaveInfo.angle = angle; }
};

extern SaveManager gSaveManager;

// These numbers can only change when we change the GZ_SAVE_VERSION_NUMBER,
// otherwise, only new entries can be added.
enum GZSaveIndex {
    SV_CURSOR_COLOR_INDEX = 0,
    SV_FONT_INDEX = 1,
    SV_DROP_SHADOW_INDEX = 2,
    SV_CHEATS_INDEX = 3,
    SV_TOOLS_INDEX = 4,
    SV_COMMANDS_INDEX = 5,
    SV_WATCHES_INDEX = 6,
};

struct GZSaveHeader {
    u32 version;
    u32 entries;
    u32 offsetsLoc;
    u32 sizesLoc;
};

struct GZSaveLayout {
    GZCheat mCheats[CHEAT_AMNT];
    GZTool mTools[TOOL_AMNT];
    MemoryWatch mWatches[MAX_WATCHES];
    bool mCommandStates[COMMANDS_AMNT];
    bool mDropShadows;
    int mCursorColType;
    int mFontType;
};

struct GZSaveFile {
    GZSaveHeader header;
    u32 offsets[GZ_SAVE_ENTRIES_AMNT];
    u32 sizes[GZ_SAVE_ENTRIES_AMNT];
    GZSaveLayout data;
};