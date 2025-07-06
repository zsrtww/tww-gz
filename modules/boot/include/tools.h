#pragma once

enum ToolsIndex {
    DEBUG_INDEX,
    TIME_DISP_INDEX,
    STAGE_INFO_INDEX,
    TELEPORT_INDEX,
    AREA_RELOAD_INDEX,
    MAP_SELECT_INDEX,
    ZH_INDEX,
    INPUT_VIEWER_INDEX,
    FRAME_COUNT_INDEX,
    FRAME_ADVANCE_INDEX,
    ESS_CHECKER_INDEX,
    DEADZONE_CHECKER_INDEX,
    DISABLE_SVCHECK_INDEX,
    INTRO_SKIP_INDEX,
    VOID_INDEX,
    ROLL_CLIP_INDEX,
    BOMB_PUSH_INDEX,

    // Entry used as a counter
    TOOLS_COUNT
};

struct Tool {
    enum ToolsIndex id;
    bool active;
};

extern Tool g_tools[TOOLS_COUNT];
