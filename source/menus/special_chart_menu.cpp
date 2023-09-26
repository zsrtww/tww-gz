#include "controller.h"
#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "menus/chart_menu.h"
#include "menus/special_chart_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"

#define NUM_SPECIAL_CHARTS 12

Cursor SpecialChartMenu::cursor;

Line lines[NUM_SPECIAL_CHARTS] = {
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
};

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

void SpecialChartMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_CHART_MENU);
        return;
    }

    updateSpecialChart(g_charts[cursor.y + 41].byte, g_charts[cursor.y + 41].index);

    tww_sprintf(lines[MENU_TINGLE_CHART].value, " <%s>", chart_to_str(g_charts[41].byte, g_charts[41].index));
    tww_sprintf(lines[MENU_GHOST_SHIP_CHART].value, " <%s>", chart_to_str(g_charts[42].byte, g_charts[42].index));
    tww_sprintf(lines[MENU_INCREDIBLE_CHART].value, " <%s>", chart_to_str(g_charts[43].byte, g_charts[43].index));
    tww_sprintf(lines[MENU_BIG_OCTO_CHART].value, " <%s>", chart_to_str(g_charts[44].byte, g_charts[44].index));
    tww_sprintf(lines[MENU_FAIRY_CHART].value, " <%s>", chart_to_str(g_charts[45].byte, g_charts[45].index));
    tww_sprintf(lines[MENU_HEART_PIECE_CHART].value, " <%s>", chart_to_str(g_charts[46].byte, g_charts[46].index));
    tww_sprintf(lines[MENU_SEA_HEARTS_CHART].value, " <%s>", chart_to_str(g_charts[47].byte, g_charts[47].index));
    tww_sprintf(lines[MENU_SECRET_CAVE_CHART].value, " <%s>", chart_to_str(g_charts[48].byte, g_charts[48].index));
    tww_sprintf(lines[MENU_LIGHT_RING_CHART].value, " <%s>", chart_to_str(g_charts[49].byte, g_charts[49].index));
    tww_sprintf(lines[MENU_PLATFORMS_CHART].value, " <%s>", chart_to_str(g_charts[50].byte, g_charts[50].index));
    tww_sprintf(lines[MENU_BEEDLE_CHART].value, " <%s>", chart_to_str(g_charts[51].byte, g_charts[51].index));
    tww_sprintf(lines[MENU_SUBMARINE_CHART].value, " <%s>", chart_to_str(g_charts[52].byte, g_charts[52].index));

    cursor.move(0, NUM_SPECIAL_CHARTS);
    GZ_drawMenuLines(lines, cursor.y, NUM_SPECIAL_CHARTS);
}