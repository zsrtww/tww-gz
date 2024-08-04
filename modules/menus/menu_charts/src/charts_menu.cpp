#include "menus/menu_charts/include/charts_menu.h"
#include "font.h"
#include "gz_flags.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

bool all_charts = 0;

KEEP_FUNC ChartMenu::ChartMenu(Cursor& cursor)
    : Menu(cursor), lines{{"treasure charts", TREASURE_CHART_INDEX, "Modify treasure charts"},
                          {"special charts", SPECIAL_CHART_INDEX, "Modify special charts"},
                          {"triforce charts", TRIFORCE_CHART_INDEX, "Modify triforce charts"},
                          {"all charts", ALL_CHARTS_INDEX, "Add or remove all charts", true,
                           &all_charts}} {}

ChartMenu::~ChartMenu() {}

void ChartMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);
    all_charts = ((dComIfGs_getChartOwned(0) & dComIfGs_getChartOwned(1)) == 0x1FFFFFFF);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case TREASURE_CHART_INDEX:
            g_menuMgr->push(MN_TREASURE_CHART_INDEX);
            return;
        case SPECIAL_CHART_INDEX:
            g_menuMgr->push(MN_SPECIAL_CHART_INDEX);
            return;
        case TRIFORCE_CHART_INDEX:
            g_menuMgr->push(MN_TRIFORCE_CHART_INDEX);
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

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}