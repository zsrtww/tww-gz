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

#define LINE_NUM 1
Cursor SceneMenu::cursor;

Line lines[LINE_NUM] = {
    {"modify wind direction", MODIFY_WIND_INDEX, "Change the current wind direction (currently broken)"},

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
    };
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

        GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
    }
    tww_sprintf(lines[MODIFY_WIND_INDEX].value, " <%s>", get_wind_str());
    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
