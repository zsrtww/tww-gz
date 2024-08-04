#include "menus/menu_special_chart/include/special_chart_menu.h"
#include "flags.h"
#include "charts.h"
#include "gz_flags.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC SpecialChartMenu::SpecialChartMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"Tingle Chart:", MENU_TINGLE_CHART, "Add/remove chart"},
                        {"Ghost Ship Chart:", MENU_GHOST_SHIP_CHART, "Add/remove chart"},
                        {"Incredible Chart:", MENU_INCREDIBLE_CHART, "Add/remove chart"},
                        {"Big Octo Chart:", MENU_BIG_OCTO_CHART, "Add/remove chart"},
                        {"Fairy Chart:", MENU_FAIRY_CHART, "Add/remove chart"},
                        {"Heart Piece Chart:", MENU_HEART_PIECE_CHART, "Add/remove chart"},
                        {"Sea Hearts Chart:", MENU_SEA_HEARTS_CHART, "Add/remove chart"},
                        {"Secret Cave Chart:", MENU_SECRET_CAVE_CHART, "Add/remove chart"},
                        {"Light Ring Chart:", MENU_LIGHT_RING_CHART, "Add/remove chart"},
                        {"Platforms Chart:", MENU_PLATFORMS_CHART, "Add/remove chart"},
                        {"Beedle Chart:", MENU_BEEDLE_CHART, "Add/remove chart"},
                        {"Submarine Chart:", MENU_SUBMARINE_CHART, "Add/remove chart"},
                    } {}

SpecialChartMenu::~SpecialChartMenu() {}

void updateSpecialChart(u8 chart_bit, u32 chart_value) {
    u32 charts_owned = dComIfGs_getChartOwned(chart_bit);
    u32 has_chart = charts_owned & chart_value;
    s8 position = 0;
    Cursor::moveListSimple(position);
    if (position == 1 && has_chart == 0) {
        dComIfGs_setChartOwned(charts_owned + chart_value, chart_bit);
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

void SpecialChartMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    updateSpecialChart(g_charts[cursor.y + 41].byte, g_charts[cursor.y + 41].index);

    lines[MENU_TINGLE_CHART].printf(" <%s>", chart_to_str(g_charts[41].byte, g_charts[41].index));
    lines[MENU_GHOST_SHIP_CHART].printf(" <%s>",
                                        chart_to_str(g_charts[42].byte, g_charts[42].index));
    lines[MENU_INCREDIBLE_CHART].printf(" <%s>",
                                        chart_to_str(g_charts[43].byte, g_charts[43].index));
    lines[MENU_BIG_OCTO_CHART].printf(" <%s>", chart_to_str(g_charts[44].byte, g_charts[44].index));
    lines[MENU_FAIRY_CHART].printf(" <%s>", chart_to_str(g_charts[45].byte, g_charts[45].index));
    lines[MENU_HEART_PIECE_CHART].printf(" <%s>",
                                         chart_to_str(g_charts[46].byte, g_charts[46].index));
    lines[MENU_SEA_HEARTS_CHART].printf(" <%s>",
                                        chart_to_str(g_charts[47].byte, g_charts[47].index));
    lines[MENU_SECRET_CAVE_CHART].printf(" <%s>",
                                         chart_to_str(g_charts[48].byte, g_charts[48].index));
    lines[MENU_LIGHT_RING_CHART].printf(" <%s>",
                                        chart_to_str(g_charts[49].byte, g_charts[49].index));
    lines[MENU_PLATFORMS_CHART].printf(" <%s>",
                                       chart_to_str(g_charts[50].byte, g_charts[50].index));
    lines[MENU_BEEDLE_CHART].printf(" <%s>", chart_to_str(g_charts[51].byte, g_charts[51].index));
    lines[MENU_SUBMARINE_CHART].printf(" <%s>",
                                       chart_to_str(g_charts[52].byte, g_charts[52].index));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
