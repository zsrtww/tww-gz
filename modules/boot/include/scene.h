#pragma once

#define SCENE_FLAG_AMNT 2

enum SceneIndex {
    // Flags
    MUTE_BGM_INDEX,
    FREEZE_TIME_INDEX,

    // Other
    MODIFY_WIND_INDEX,
    MODIFY_CHART_SET_INDEX,
    TIME_HOURS_INDEX,
    TIME_MINUTES_INDEX,
    MODIFY_DATE_INDEX,
    COLLISION_VIEW_INDEX,

    SCENE_MENU_MAX
};

struct SceneItem {
    enum SceneIndex id;
    bool active;
};

extern SceneItem g_sceneFlags[SCENE_FLAG_AMNT];

void GZ_freezeTime();
void GZ_disableBGM();
void GZ_enableBGM();
