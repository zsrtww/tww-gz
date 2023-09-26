#include "controller.h"
#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "menus/chart_menu.h"
#include "menus/triforce_chart_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"

#define NUM_TRIFORCE_CHARTS 8

Cursor TriforceChartMenu::cursor;

Line lines[NUM_TRIFORCE_CHARTS] = {
    {"Triforce Chart 1:", MENU_TRIFORCE_CHART_1, "Add/decipher/complete chart"},
    {"Triforce Chart 2:", MENU_TRIFORCE_CHART_2, "Add/decipher/complete chart"},
    {"Triforce Chart 3:", MENU_TRIFORCE_CHART_3, "Add/decipher/complete chart"},
    {"Triforce Chart 4:", MENU_TRIFORCE_CHART_4, "Add/decipher/complete chart"},
    {"Triforce Chart 5:", MENU_TRIFORCE_CHART_5, "Add/decipher/complete chart"},
    {"Triforce Chart 6:", MENU_TRIFORCE_CHART_6, "Add/decipher/complete chart"},
    {"Triforce Chart 7:", MENU_TRIFORCE_CHART_7, "Add/decipher/complete chart"},
    {"Triforce Chart 8:", MENU_TRIFORCE_CHART_8, "Add/decipher/complete chart"},
};

void updateTriforceChart(u8 chart_bit, u32 chart_value) {
    u32 charts_owned = dComIfGs_getChartOwned(chart_bit);
    u32 charts_deciphered = dComIfGs_getChartDeciphered();
    u32 charts_completed = dComIfGs_getChartCompleted(chart_bit);
    u32 has_chart = charts_owned & chart_value;
    u32 deciphered_chart = charts_deciphered & chart_value;
    u32 completed_chart = charts_completed & chart_value;
    s8 position = 0;
    Cursor::moveListSimple(position);
    if (position == 1 && has_chart == 0) {
        dComIfGs_setChartOwned(charts_owned + chart_value, chart_bit);
    }
    else if (position == 1 && deciphered_chart == 0) {
        dComIfGs_setChartDeciphered(charts_deciphered + chart_value);
    }
    else if (position == 1 && completed_chart == 0) {
        dComIfGs_setChartCompleted(charts_completed + chart_value, chart_bit);
    }
    else if (position == -1 && completed_chart > 0) {
        dComIfGs_setChartCompleted(charts_completed - chart_value, chart_bit);
    }
    else if (position == -1 && deciphered_chart > 0) {
        dComIfGs_setChartDeciphered(charts_deciphered - chart_value);
    }
    else if (position == -1 && has_chart > 0) {
        dComIfGs_setChartOwned(charts_owned - chart_value, chart_bit);
    }
}

void TriforceChartMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_CHART_MENU);
        return;
    }

    updateTriforceChart(g_charts[cursor.y + 53].byte, g_charts[cursor.y + 53].index);

    tww_sprintf(lines[MENU_TRIFORCE_CHART_1].value, " <%s>", chart_to_str(g_charts[53].byte, g_charts[53].index));
    tww_sprintf(lines[MENU_TRIFORCE_CHART_2].value, " <%s>", chart_to_str(g_charts[54].byte, g_charts[54].index));
    tww_sprintf(lines[MENU_TRIFORCE_CHART_3].value, " <%s>", chart_to_str(g_charts[55].byte, g_charts[55].index));
    tww_sprintf(lines[MENU_TRIFORCE_CHART_4].value, " <%s>", chart_to_str(g_charts[56].byte, g_charts[56].index));
    tww_sprintf(lines[MENU_TRIFORCE_CHART_5].value, " <%s>", chart_to_str(g_charts[57].byte, g_charts[57].index));
    tww_sprintf(lines[MENU_TRIFORCE_CHART_6].value, " <%s>", chart_to_str(g_charts[58].byte, g_charts[58].index));
    tww_sprintf(lines[MENU_TRIFORCE_CHART_7].value, " <%s>", chart_to_str(g_charts[59].byte, g_charts[59].index));
    tww_sprintf(lines[MENU_TRIFORCE_CHART_8].value, " <%s>", chart_to_str(g_charts[60].byte, g_charts[60].index));

    cursor.move(0, NUM_TRIFORCE_CHARTS);
    GZ_drawMenuLines(lines, cursor.y, NUM_TRIFORCE_CHARTS);
}