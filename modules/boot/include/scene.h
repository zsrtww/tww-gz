#pragma once

#define SCENE_FLAG_AMNT 1

enum SceneIndex {
    // Flags
    FREEZE_TIME_INDEX,

    // Other
    MODIFY_WIND_INDEX,
    MODIFY_CHART_SET_INDEX,
    TIME_HOURS_INDEX,
    TIME_MINUTES_INDEX,
    MODIFY_DATE_INDEX,

    SCENE_MENU_MAX
};

struct SceneItem {
    enum SceneIndex id;
    bool active;
};

extern SceneItem g_sceneFlags[SCENE_FLAG_AMNT];

void GZ_freezeTime();
