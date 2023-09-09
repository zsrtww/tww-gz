#include "controller.h"
#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "menus/chart_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"


#define LINE_NUM 4

Cursor ChartMenu::cursor;
bool all_charts = 0;

Line lines[LINE_NUM] = {
    {"treasure charts", TREASURE_CHART_INDEX, "Modify treasure charts"},
    {"special charts", SPECIAL_CHART_INDEX, "Modify special charts"},
    {"triforce charts", TRIFORCE_CHART_INDEX, "Modify triforce charts"},
    {"all charts", ALL_CHARTS_INDEX, "Add or remove all charts",true,&all_charts}
};


const char* chart_to_str(u8 chart_bit, u32 chart_value) {
    if (dComIfGs_getChartCompleted(chart_bit) & chart_value) {
        return "Completed";
    } else if (dComIfGs_getChartOpened(chart_bit) & chart_value) {
        return "Opened";
    } else if (dComIfGs_getChartDeciphered() & chart_value) {
        return "Deciphered";
    }
    if (dComIfGs_getChartOwned(chart_bit) & chart_value) {
        return "Owned";
    } else {
        return "None";
    }
}

void ChartMenu::draw() {
    cursor.move(0, LINE_NUM);
    all_charts = ((dComIfGs_getChartOwned(0) & dComIfGs_getChartOwned(1)) == 0x1FFFFFFF);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case TREASURE_CHART_INDEX:
            GZ_setMenu(GZ_TREASURE_CHART_MENU);
            return;
        case SPECIAL_CHART_INDEX:
            GZ_setMenu(GZ_SPECIAL_CHART_MENU);
            return;
        case TRIFORCE_CHART_INDEX:
            GZ_setMenu(GZ_TRIFORCE_CHART_MENU);
            return;
        case ALL_CHARTS_INDEX:
            if (all_charts) {
                dComIfGs_setChartOwned(0, 0);
                dComIfGs_setChartOwned(0, 1);
            } else {
                dComIfGs_setChartOwned(0xFFFFFFFF, 0);
                dComIfGs_setChartOwned(0x1FFFFFFF, 1);
            }
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}