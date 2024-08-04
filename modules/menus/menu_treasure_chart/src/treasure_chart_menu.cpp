#include "menus/menu_treasure_chart/include/treasure_chart_menu.h"
#include "flags.h"
#include "charts.h"
#include "gz_flags.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC TreasureChartMenu::TreasureChartMenu(Cursor& cursor)
    : Menu(cursor), lines{
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
                    } {}

TreasureChartMenu::~TreasureChartMenu() {}

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

static const char* chart_to_str(u8 chart_bit, u32 chart_value) {
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

void TreasureChartMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    updateTreasureChart(g_charts[cursor.y].byte, g_charts[cursor.y].index);

    lines[MENU_TREASURE_CHART_1].printf(" <%s>", chart_to_str(g_charts[0].byte, g_charts[0].index));
    lines[MENU_TREASURE_CHART_2].printf(" <%s>", chart_to_str(g_charts[1].byte, g_charts[1].index));
    lines[MENU_TREASURE_CHART_3].printf(" <%s>", chart_to_str(g_charts[2].byte, g_charts[2].index));
    lines[MENU_TREASURE_CHART_4].printf(" <%s>", chart_to_str(g_charts[3].byte, g_charts[3].index));
    lines[MENU_TREASURE_CHART_5].printf(" <%s>", chart_to_str(g_charts[4].byte, g_charts[4].index));
    lines[MENU_TREASURE_CHART_6].printf(" <%s>", chart_to_str(g_charts[5].byte, g_charts[5].index));
    lines[MENU_TREASURE_CHART_7].printf(" <%s>", chart_to_str(g_charts[6].byte, g_charts[6].index));
    lines[MENU_TREASURE_CHART_8].printf(" <%s>", chart_to_str(g_charts[7].byte, g_charts[7].index));
    lines[MENU_TREASURE_CHART_9].printf(" <%s>", chart_to_str(g_charts[8].byte, g_charts[8].index));
    lines[MENU_TREASURE_CHART_10].printf(" <%s>",
                                         chart_to_str(g_charts[9].byte, g_charts[9].index));
    lines[MENU_TREASURE_CHART_11].printf(" <%s>",
                                         chart_to_str(g_charts[10].byte, g_charts[10].index));
    lines[MENU_TREASURE_CHART_12].printf(" <%s>",
                                         chart_to_str(g_charts[11].byte, g_charts[11].index));
    lines[MENU_TREASURE_CHART_13].printf(" <%s>",
                                         chart_to_str(g_charts[12].byte, g_charts[12].index));
    lines[MENU_TREASURE_CHART_14].printf(" <%s>",
                                         chart_to_str(g_charts[13].byte, g_charts[13].index));
    lines[MENU_TREASURE_CHART_15].printf(" <%s>",
                                         chart_to_str(g_charts[14].byte, g_charts[14].index));
    lines[MENU_TREASURE_CHART_16].printf(" <%s>",
                                         chart_to_str(g_charts[15].byte, g_charts[15].index));
    lines[MENU_TREASURE_CHART_17].printf(" <%s>",
                                         chart_to_str(g_charts[16].byte, g_charts[16].index));
    lines[MENU_TREASURE_CHART_18].printf(" <%s>",
                                         chart_to_str(g_charts[17].byte, g_charts[17].index));
    lines[MENU_TREASURE_CHART_19].printf(" <%s>",
                                         chart_to_str(g_charts[18].byte, g_charts[18].index));
    lines[MENU_TREASURE_CHART_20].printf(" <%s>",
                                         chart_to_str(g_charts[19].byte, g_charts[19].index));
    lines[MENU_TREASURE_CHART_21].printf(" <%s>",
                                         chart_to_str(g_charts[20].byte, g_charts[20].index));
    lines[MENU_TREASURE_CHART_22].printf(" <%s>",
                                         chart_to_str(g_charts[21].byte, g_charts[21].index));
    lines[MENU_TREASURE_CHART_23].printf(" <%s>",
                                         chart_to_str(g_charts[22].byte, g_charts[22].index));
    lines[MENU_TREASURE_CHART_24].printf(" <%s>",
                                         chart_to_str(g_charts[23].byte, g_charts[23].index));
    lines[MENU_TREASURE_CHART_25].printf(" <%s>",
                                         chart_to_str(g_charts[24].byte, g_charts[24].index));
    lines[MENU_TREASURE_CHART_26].printf(" <%s>",
                                         chart_to_str(g_charts[25].byte, g_charts[25].index));
    lines[MENU_TREASURE_CHART_27].printf(" <%s>",
                                         chart_to_str(g_charts[26].byte, g_charts[26].index));
    lines[MENU_TREASURE_CHART_28].printf(" <%s>",
                                         chart_to_str(g_charts[27].byte, g_charts[27].index));
    lines[MENU_TREASURE_CHART_29].printf(" <%s>",
                                         chart_to_str(g_charts[28].byte, g_charts[28].index));
    lines[MENU_TREASURE_CHART_30].printf(" <%s>",
                                         chart_to_str(g_charts[29].byte, g_charts[29].index));
    lines[MENU_TREASURE_CHART_31].printf(" <%s>",
                                         chart_to_str(g_charts[30].byte, g_charts[30].index));
    lines[MENU_TREASURE_CHART_32].printf(" <%s>",
                                         chart_to_str(g_charts[31].byte, g_charts[31].index));
    lines[MENU_TREASURE_CHART_33].printf(" <%s>",
                                         chart_to_str(g_charts[32].byte, g_charts[32].index));
    lines[MENU_TREASURE_CHART_34].printf(" <%s>",
                                         chart_to_str(g_charts[33].byte, g_charts[33].index));
    lines[MENU_TREASURE_CHART_35].printf(" <%s>",
                                         chart_to_str(g_charts[34].byte, g_charts[34].index));
    lines[MENU_TREASURE_CHART_36].printf(" <%s>",
                                         chart_to_str(g_charts[35].byte, g_charts[35].index));
    lines[MENU_TREASURE_CHART_37].printf(" <%s>",
                                         chart_to_str(g_charts[36].byte, g_charts[36].index));
    lines[MENU_TREASURE_CHART_38].printf(" <%s>",
                                         chart_to_str(g_charts[37].byte, g_charts[37].index));
    lines[MENU_TREASURE_CHART_39].printf(" <%s>",
                                         chart_to_str(g_charts[38].byte, g_charts[38].index));
    lines[MENU_TREASURE_CHART_40].printf(" <%s>",
                                         chart_to_str(g_charts[39].byte, g_charts[39].index));
    lines[MENU_TREASURE_CHART_41].printf(" <%s>",
                                         chart_to_str(g_charts[40].byte, g_charts[40].index));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
