#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/main_menu.h"
#include "menu.h"
#include "utils/card.h"
#include "libtww/MSL_C/string.h"
#include "lib.h"
#include "font.h"
#include "color.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "commands.h"
#include "libtww/d/kankyo/d_kankyo.h"

#define LINE_NUM 3
Cursor SceneMenu::cursor;

GZScene g_scene[3] = {
    {MODIFY_WIND_INDEX, false},{TIME_DISP_INDEX, false},{MODIFY_CHART_SET_INDEX, false},
};

Line lines[LINE_NUM] = {
    {"modify wind direction", MODIFY_WIND_INDEX, "Change the current wind direction (currently broken)"},
    {"display time info", TIME_DISP_INDEX, "Display current day, time and moon phase", true,
     &g_scene[TIME_DISP_INDEX].active},
    {"modify chart set", MODIFY_CHART_SET_INDEX, "Change the current chart set"},
};

s16 windDirs[8] = { 0, 32, 64, 96, 128, 160, 192, 224 };

const char* get_wind_str() {
    s16 wind = dkankyo_getWindDir();
    switch (wind) {
    case 0:
        return "East";
    case 32:
        return "South East";
    case 64:
        return "South";
    case 96:
        return "South West";
    case 128:
        return "West";
    case 160:
        return "North West";
    case 192:
        return "North";
    case 224:
        return "North East";
    default:
        return "East";
    };
}

const char* get_chart_set_str() {
    switch (dComIfGs_getChartSet()) {
    case 0:
        return "0";
        break;
    case 1:
        return "1";
        break;
    case 2:
        return "2";
        break;
    case 3:
        return "3";
        break;
    default:
        return "0";
        break;
    }
}

void updateWindDir() {
    s16 wind_dir = dkankyo_getWindDir();
    if (wind_dir == 255) {
        wind_dir = 0;
    }
    u8 wIndex = wind_dir / 32;
    Cursor::moveListSimple(wIndex);
    if (wIndex == 255) {
        wIndex = 7;
    }
    else if (wIndex == 8) {
        wIndex = 0;
    }
    dkankyo_setWindDir(windDirs[wIndex]);
}

void SceneMenu::displayTimeInfo() {
    int hour = dKy_getdaytime_hour();
    int min = dKy_getdaytime_minute();
    int moonid = dKy_moon_type_chk();
    int date = dComIfGs_getDate();

    char moonphases[7][20] = {"Full",
                              "Waning Gibbous",
                              "Last Quarter",
                              "Waning Crescent",
                              "Waxing Crescent",
                              "First Quarter",
                              "Waxing Gibbous"};

    char Time[10];
    char Date[10];
    char Moon[20];

    tww_sprintf(Time, "%02d:%02d", hour, min);
    tww_sprintf(Date, "date: %d", date);
    tww_sprintf(Moon, "Moon: %d", moonphases[0]);

    Font::GZ_drawStr(Time, 450.f, 300.f, ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(Date, 450.f, 320.f, ColorPalette::WHITE, g_dropShadows);
    Font::GZ_drawStr(moonphases[moonid], 450.f, 340.f, ColorPalette::WHITE, g_dropShadows);
}

void updateChartSet() {
    u8 chartSet = dComIfGs_getChartSet();
    Cursor::moveListSimple(chartSet);
    if (chartSet == 255) {
        chartSet = 0;
    } else if (chartSet == 4) {
        chartSet = 3;
    }
    dComIfGs_setChartSet(chartSet);
}

void SceneMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    switch (cursor.y) {
    case MODIFY_WIND_INDEX:
        updateWindDir();
        break;
    case TIME_DISP_INDEX:
        if (GZ_getButtonTrig(GZPad::A)) {
            g_scene[cursor.y].active = !g_scene[cursor.y].active;
        }
        break;
    case MODIFY_CHART_SET_INDEX:
        updateChartSet();
        break;

    }
    tww_sprintf(lines[MODIFY_WIND_INDEX].value, " <%s>", get_wind_str());
    tww_sprintf(lines[MODIFY_CHART_SET_INDEX].value, " <%s>", get_chart_set_str());
    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
