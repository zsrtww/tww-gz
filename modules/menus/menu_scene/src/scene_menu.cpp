#include "menus/menu_scene/include/scene_menu.h"
#include <cstdio>
#include "libtww/include/d/com/d_com_inf_game.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC SceneMenu::SceneMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"disable bg music", MUTE_BGM_INDEX, "Disables background and enemy music",
                         true, &g_sceneFlags[MUTE_BGM_INDEX].active},
                        {"freeze time", FREEZE_TIME_INDEX, "Freezes ingame time", true,
                         &g_sceneFlags[FREEZE_TIME_INDEX].active},
                        {"wind direction", MODIFY_WIND_INDEX, "Change the current wind direction"},
                        {"chart set", MODIFY_CHART_SET_INDEX, "Change the current chart set"},
                        {"current hour", TIME_HOURS_INDEX, "Change the current hour"},
                        {"current minute", TIME_MINUTES_INDEX, "Change the current minute"},
                        {"current date", MODIFY_DATE_INDEX, "Change the current date/moon phase"},
                        {"collision viewer", COLLISION_VIEW_INDEX, "Change Collision Viewer settings", false},
                    } {}

SceneMenu::~SceneMenu() {}

#define WIND_DIR_E 0x0000
#define WIND_DIR_SE 0x2000
#define WIND_DIR_S 0x4000
#define WIND_DIR_SW 0x6000
#define WIND_DIR_W -0x8000
#define WIND_DIR_NW -0x6000
#define WIND_DIR_N -0x4000
#define WIND_DIR_NE -0x2000

s16 windDirs[8] = {WIND_DIR_W, WIND_DIR_NW, WIND_DIR_N, WIND_DIR_NE,
                   WIND_DIR_E, WIND_DIR_SE, WIND_DIR_S, WIND_DIR_SW};

const char* get_wind_str() {
    s16 wind = dkankyo_getWindDir();
    switch (wind) {
    case WIND_DIR_E:
        return "East";
    case WIND_DIR_SE:
        return "South East";
    case WIND_DIR_S:
        return "South";
    case WIND_DIR_SW:
        return "South West";
    case WIND_DIR_W:
        return "West";
    case WIND_DIR_NW:
        return "North West";
    case WIND_DIR_N:
        return "North";
    case WIND_DIR_NE:
        return "North East";
    default:
        return "East";
    }
}

void updateWindDir() {
    s16 wind_dir = dkankyo_getWindDir();

    u8 wIndex = 0;
    int eventWindCheck = g_env_light.mWind.mEvtWindSet;

    if (wind_dir == WIND_DIR_W) {
        wIndex = 0;
    } else if (wind_dir == WIND_DIR_NW) {
        wIndex = 1;
    } else if (wind_dir == WIND_DIR_N) {
        wIndex = 2;
    } else if (wind_dir == WIND_DIR_NE) {
        wIndex = 3;
    } else if (wind_dir == WIND_DIR_E) {
        wIndex = 4;
    } else if (wind_dir == WIND_DIR_SE) {
        wIndex = 5;
    } else if (wind_dir == WIND_DIR_S) {
        wIndex = 6;
    } else if (wind_dir == WIND_DIR_SW) {
        wIndex = 7;
    }

    Cursor::moveListSimple(wIndex);
    if (wIndex == 255) {
        wIndex = 7;
    } else if (wIndex == 8) {
        wIndex = 0;
    }

    if (eventWindCheck != 0xFF) {
        dKyw_tact_wind_set_go();
        dkankyo_setWindDir(windDirs[wIndex]);
        dComIfGs_setWindX(g_env_light.mWind.mTactWindAngleX);
        dComIfGs_setWindY(g_env_light.mWind.mTactWindAngleY);
    } else {
        dkankyo_setWindDir(windDirs[wIndex]);
        dComIfGs_setWindX(g_env_light.mWind.mTactWindAngleX);
        dComIfGs_setWindY(g_env_light.mWind.mTactWindAngleY);
    }
}

void updateChartSet() {
    u8 chartSet = dComIfGs_getChartSet();
    Cursor::moveListSimple(chartSet);
    if (chartSet == 0xFF) {
        chartSet = 0;
    } else if (chartSet > 3) {
        chartSet = 3;
    }
    dComIfGs_setChartSet(chartSet);
}

void SceneMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    float current_time = dComIfGs_getTime();

    int current_hour = (int)current_time / 15;
    if (current_hour > 23) {
        current_hour = 0;
    }
    int current_minute = (int)((4.0f * current_time) - current_hour * 60);

    int date = dComIfGs_getDate();

    lines[TIME_HOURS_INDEX].printf(" <%d>", current_hour);
    lines[TIME_MINUTES_INDEX].printf(" <%d>", current_minute);
    lines[MODIFY_DATE_INDEX].printf(" <%d>", date);

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_sceneFlags[cursor.y].active = !g_sceneFlags[cursor.y].active;

        switch (cursor.y) {
        case COLLISION_VIEW_INDEX:
            g_menuMgr->push(MN_COLLISION_VIEW_INDEX);
            return;
        }
    }

    switch (cursor.y) {
    case MODIFY_WIND_INDEX:
        updateWindDir();
        break;
    case MODIFY_CHART_SET_INDEX:
        updateChartSet();
        break;
    case TIME_HOURS_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            dComIfGs_setTime(current_time + 15.0f);
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            dComIfGs_setTime(current_time - 15.0f);
        }
        break;
    case TIME_MINUTES_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            dComIfGs_setTime(current_time + 0.25f);
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            dComIfGs_setTime(current_time - 0.25f);
        }
        break;
    case MODIFY_DATE_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            dComIfGs_setDate(date + 1);
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            dComIfGs_setDate(date - 1);
        }
        break;
    }

    if (current_time >= 360.0f) {
        dComIfGs_setTime(current_time - 360.0f);
    } else if (current_time < 0) {
        dComIfGs_setTime(current_time + 360.0f);
    }

    if (date > 6) {
        dComIfGs_setDate(0);
    } else if (date == 0xFFFF) {
        dComIfGs_setDate(6);
    }

    lines[MODIFY_WIND_INDEX].printf(" <%s>", get_wind_str());
    lines[MODIFY_CHART_SET_INDEX].printf(" <%d>", dComIfGs_getChartSet());

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
