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
#include "utils/lines.h"
#include "commands.h"
#include "libtww/d/kankyo/d_kankyo.h"
#include "libtww/d/com/d_com_inf_game.h"

#define LINE_NUM 5
Cursor SceneMenu::cursor;

GZScene g_scene[5] = {
    {MODIFY_WIND_INDEX, false},{MODIFY_CHART_SET_INDEX, false},{TIME_HOURS_INDEX, false},{TIME_MINUTES_INDEX, false},{MODIFY_DATE_INDEX, false},
};

Line lines[LINE_NUM] = {
    {"modify wind direction", MODIFY_WIND_INDEX, "Change the current wind direction (currently broken)"},
    {"modify chart set", MODIFY_CHART_SET_INDEX, "Change the current chart set"},
    {"modify current hour", TIME_HOURS_INDEX, "Change the current hour"},
    {"modify current minute", TIME_MINUTES_INDEX, "Change the current minute"},
    {"modify current date", MODIFY_DATE_INDEX, "Change the current date/moon phase"},
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

    float current_time = dComIfGs_getTime();

    int current_hour = (int)current_time / 15;
    if (current_hour > 23) {
        current_hour = 0;
    }
    int current_minute = (int)((4.0f * current_time) - current_hour * 60);

    int date = dComIfGs_getDate();

    tww_sprintf(lines[TIME_HOURS_INDEX].value, "<%d>", current_hour);
    tww_sprintf(lines[TIME_MINUTES_INDEX].value, "<%d>", current_minute);
    tww_sprintf(lines[MODIFY_DATE_INDEX].value, "<%d>", date);

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

    if (date >= 7 && date <8) {
        dComIfGs_setDate(date - 7);
    } else if (date >= 9 && date <=65535) {
        dComIfGs_setDate(date - 65529);
    }

    tww_sprintf(lines[MODIFY_WIND_INDEX].value, " <%s>", get_wind_str());
    tww_sprintf(lines[MODIFY_CHART_SET_INDEX].value, " <%s>", get_chart_set_str());
    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
