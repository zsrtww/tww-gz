#include "controller.h"
#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "menus/chart_menu.h"
#include "menus/treasure_chart_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"

#define NUM_TREASURE_CHARTS 41

Cursor TreasureChartMenu::cursor;

Line lines[NUM_TREASURE_CHARTS] = {
    {"Treasure Chart 1:", MENU_TREASURE_CHART_1, "Add/open/complete chart"},
    {"Treasure Chart 2:", MENU_TREASURE_CHART_2, "Add/open/complete chart"},
    {"Treasure Chart 3:", MENU_TREASURE_CHART_3, "Add/open/complete chart"},
    {"Treasure Chart 4:", MENU_TREASURE_CHART_4, "Add/open/complete chart"},
    {"Treasure Chart 5:", MENU_TREASURE_CHART_5, "Add/open/complete chart"},
    {"Treasure Chart 6:", MENU_TREASURE_CHART_6, "Add/open/complete chart"},
    {"Treasure Chart 7:", MENU_TREASURE_CHART_7, "Add/open/complete chart"},
    {"Treasure Chart 8:", MENU_TREASURE_CHART_8, "Add/open/complete chart"},
    {"Treasure Chart 9:", MENU_TREASURE_CHART_9, "Add/open/complete chart"},
    {"Treasure Chart 10:", MENU_TREASURE_CHART_10, "Add/open/complete chart"},
    {"Treasure Chart 11:", MENU_TREASURE_CHART_11, "Add/open/complete chart"},
    {"Treasure Chart 12:", MENU_TREASURE_CHART_12, "Add/open/complete chart"},
    {"Treasure Chart 13:", MENU_TREASURE_CHART_13, "Add/open/complete chart"},
    {"Treasure Chart 14:", MENU_TREASURE_CHART_14, "Add/open/complete chart"},
    {"Treasure Chart 15:", MENU_TREASURE_CHART_15, "Add/open/complete chart"},
    {"Treasure Chart 16:", MENU_TREASURE_CHART_16, "Add/open/complete chart"},
    {"Treasure Chart 17:", MENU_TREASURE_CHART_17, "Add/open/complete chart"},
    {"Treasure Chart 18:", MENU_TREASURE_CHART_18, "Add/open/complete chart"},
    {"Treasure Chart 19:", MENU_TREASURE_CHART_19, "Add/open/complete chart"},
    {"Treasure Chart 20:", MENU_TREASURE_CHART_20, "Add/open/complete chart"},
    {"Treasure Chart 21:", MENU_TREASURE_CHART_21, "Add/open/complete chart"},
    {"Treasure Chart 22:", MENU_TREASURE_CHART_22, "Add/open/complete chart"},
    {"Treasure Chart 23:", MENU_TREASURE_CHART_23, "Add/open/complete chart"},
    {"Treasure Chart 24:", MENU_TREASURE_CHART_24, "Add/open/complete chart"},
    {"Treasure Chart 25:", MENU_TREASURE_CHART_25, "Add/open/complete chart"},
    {"Treasure Chart 26:", MENU_TREASURE_CHART_26, "Add/open/complete chart"},
    {"Treasure Chart 27:", MENU_TREASURE_CHART_27, "Add/open/complete chart"},
    {"Treasure Chart 28:", MENU_TREASURE_CHART_28, "Add/open/complete chart"},
    {"Treasure Chart 29:", MENU_TREASURE_CHART_29, "Add/open/complete chart"},
    {"Treasure Chart 30:", MENU_TREASURE_CHART_30, "Add/open/complete chart"},
    {"Treasure Chart 31:", MENU_TREASURE_CHART_31, "Add/open/complete chart"},
    {"Treasure Chart 32:", MENU_TREASURE_CHART_32, "Add/open/complete chart"},
    {"Treasure Chart 33:", MENU_TREASURE_CHART_33, "Add/open/complete chart"},
    {"Treasure Chart 34:", MENU_TREASURE_CHART_34, "Add/open/complete chart"},
    {"Treasure Chart 35:", MENU_TREASURE_CHART_35, "Add/open/complete chart"},
    {"Treasure Chart 36:", MENU_TREASURE_CHART_36, "Add/open/complete chart"},
    {"Treasure Chart 37:", MENU_TREASURE_CHART_37, "Add/open/complete chart"},
    {"Treasure Chart 38:", MENU_TREASURE_CHART_38, "Add/open/complete chart"},
    {"Treasure Chart 39:", MENU_TREASURE_CHART_39, "Add/open/complete chart"},
    {"Treasure Chart 40:", MENU_TREASURE_CHART_40, "Add/open/complete chart"},
    {"Treasure Chart 41:", MENU_TREASURE_CHART_41, "Add/open/complete chart"},

};

void updateTreasureChart(u8 chart_bit, u32 chart_value) {
    u32 charts_owned = dComIfGs_getChartOwned(chart_bit);
    u32 charts_opened = dComIfGs_getChartOpened(chart_bit);
    u32 charts_completed = dComIfGs_getChartCompleted(chart_bit);
    u32 has_chart = charts_owned & chart_value;
    u32 opened_chart = charts_opened & chart_value;
    u32 completed_chart = charts_completed & chart_value;
    s8 position = 0;
    Cursor::moveListSimple(position);
    if (position == 1 && has_chart == 0) {
        dComIfGs_setChartOwned(charts_owned + chart_value, chart_bit);
    } else if (position == 1 && opened_chart == 0) {
        dComIfGs_setChartOpened(charts_opened + chart_value, chart_bit);
    } else if (position == 1 && completed_chart == 0) {
        dComIfGs_setChartCompleted(charts_completed + chart_value, chart_bit);
    } else if (position == -1 && completed_chart > 0) {
        dComIfGs_setChartCompleted(charts_completed - chart_value, chart_bit);
    } else if (position == -1 && opened_chart > 0) {
        dComIfGs_setChartOpened(charts_opened - chart_value, chart_bit);
    } else if (position == -1 && has_chart > 0) {
        dComIfGs_setChartOwned(charts_owned - chart_value, chart_bit);
    }
}

void TreasureChartMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_CHART_MENU);
        return;
    }

    updateTreasureChart(g_charts[cursor.y].byte, g_charts[cursor.y].index);

    tww_sprintf(lines[MENU_TREASURE_CHART_1].value, " <%s>", chart_to_str(g_charts[0].byte,g_charts[0].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_2].value, " <%s>", chart_to_str(g_charts[1].byte,g_charts[1].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_3].value, " <%s>", chart_to_str(g_charts[2].byte,g_charts[2].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_4].value, " <%s>", chart_to_str(g_charts[3].byte,g_charts[3].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_5].value, " <%s>", chart_to_str(g_charts[4].byte,g_charts[4].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_6].value, " <%s>", chart_to_str(g_charts[5].byte,g_charts[5].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_7].value, " <%s>", chart_to_str(g_charts[6].byte,g_charts[6].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_8].value, " <%s>", chart_to_str(g_charts[7].byte,g_charts[7].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_9].value, " <%s>", chart_to_str(g_charts[8].byte,g_charts[8].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_10].value, " <%s>", chart_to_str(g_charts[9].byte,g_charts[9].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_11].value, " <%s>", chart_to_str(g_charts[10].byte,g_charts[10].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_12].value, " <%s>", chart_to_str(g_charts[11].byte,g_charts[11].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_13].value, " <%s>", chart_to_str(g_charts[12].byte,g_charts[12].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_14].value, " <%s>", chart_to_str(g_charts[13].byte,g_charts[13].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_15].value, " <%s>", chart_to_str(g_charts[14].byte,g_charts[14].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_16].value, " <%s>", chart_to_str(g_charts[15].byte,g_charts[15].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_17].value, " <%s>", chart_to_str(g_charts[16].byte,g_charts[16].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_18].value, " <%s>", chart_to_str(g_charts[17].byte,g_charts[17].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_19].value, " <%s>", chart_to_str(g_charts[18].byte,g_charts[18].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_20].value, " <%s>", chart_to_str(g_charts[19].byte,g_charts[19].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_21].value, " <%s>", chart_to_str(g_charts[20].byte,g_charts[20].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_22].value, " <%s>", chart_to_str(g_charts[21].byte,g_charts[21].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_23].value, " <%s>", chart_to_str(g_charts[22].byte,g_charts[22].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_24].value, " <%s>", chart_to_str(g_charts[23].byte,g_charts[23].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_25].value, " <%s>", chart_to_str(g_charts[24].byte,g_charts[24].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_26].value, " <%s>", chart_to_str(g_charts[25].byte,g_charts[25].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_27].value, " <%s>", chart_to_str(g_charts[26].byte,g_charts[26].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_28].value, " <%s>", chart_to_str(g_charts[27].byte,g_charts[27].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_29].value, " <%s>", chart_to_str(g_charts[28].byte,g_charts[28].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_30].value, " <%s>", chart_to_str(g_charts[29].byte,g_charts[29].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_31].value, " <%s>", chart_to_str(g_charts[30].byte,g_charts[30].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_32].value, " <%s>", chart_to_str(g_charts[31].byte,g_charts[31].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_33].value, " <%s>", chart_to_str(g_charts[32].byte,g_charts[32].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_34].value, " <%s>", chart_to_str(g_charts[33].byte,g_charts[33].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_35].value, " <%s>", chart_to_str(g_charts[34].byte,g_charts[34].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_36].value, " <%s>", chart_to_str(g_charts[35].byte,g_charts[35].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_37].value, " <%s>", chart_to_str(g_charts[36].byte,g_charts[36].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_38].value, " <%s>", chart_to_str(g_charts[37].byte,g_charts[37].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_39].value, " <%s>", chart_to_str(g_charts[38].byte,g_charts[38].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_40].value, " <%s>", chart_to_str(g_charts[39].byte,g_charts[39].index));
    tww_sprintf(lines[MENU_TREASURE_CHART_41].value, " <%s>", chart_to_str(g_charts[40].byte,g_charts[40].index));


    cursor.move(0, NUM_TREASURE_CHARTS);
    GZ_drawMenuLines(lines, cursor.y, NUM_TREASURE_CHARTS);
}