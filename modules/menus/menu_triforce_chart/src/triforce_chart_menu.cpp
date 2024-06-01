#include "menus/menu_triforce_chart/include/triforce_chart_menu.h"
#include "flags.h"
#include "charts.h"
#include "gz_flags.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC TriforceChartMenu::TriforceChartMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"Triforce Chart 1:", 0, "Add/decipher/complete chart"},
                        {"Triforce Chart 2:", 1, "Add/decipher/complete chart"},
                        {"Triforce Chart 3:", 2, "Add/decipher/complete chart"},
                        {"Triforce Chart 4:", 3, "Add/decipher/complete chart"},
                        {"Triforce Chart 5:", 4, "Add/decipher/complete chart"},
                        {"Triforce Chart 6:", 5, "Add/decipher/complete chart"},
                        {"Triforce Chart 7:", 6, "Add/decipher/complete chart"},
                        {"Triforce Chart 8:", 7, "Add/decipher/complete chart"},
                    } {}

TriforceChartMenu::~TriforceChartMenu() {}

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
    } else if (position == 1 && deciphered_chart == 0) {
        dComIfGs_setChartDeciphered(charts_deciphered + chart_value);
    } else if (position == 1 && completed_chart == 0) {
        dComIfGs_setChartCompleted(charts_completed + chart_value, chart_bit);
    } else if (position == -1 && completed_chart > 0) {
        dComIfGs_setChartCompleted(charts_completed - chart_value, chart_bit);
    } else if (position == -1 && deciphered_chart > 0) {
        dComIfGs_setChartDeciphered(charts_deciphered - chart_value);
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

void TriforceChartMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    updateTriforceChart(g_charts[cursor.y + 53].byte, g_charts[cursor.y + 53].index);

    lines[0].printf(" <%s>", chart_to_str(g_charts[53].byte, g_charts[53].index));
    lines[1].printf(" <%s>", chart_to_str(g_charts[54].byte, g_charts[54].index));
    lines[2].printf(" <%s>", chart_to_str(g_charts[55].byte, g_charts[55].index));
    lines[3].printf(" <%s>", chart_to_str(g_charts[56].byte, g_charts[56].index));
    lines[4].printf(" <%s>", chart_to_str(g_charts[57].byte, g_charts[57].index));
    lines[5].printf(" <%s>", chart_to_str(g_charts[58].byte, g_charts[58].index));
    lines[6].printf(" <%s>", chart_to_str(g_charts[59].byte, g_charts[59].index));
    lines[7].printf(" <%s>", chart_to_str(g_charts[60].byte, g_charts[60].index));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
