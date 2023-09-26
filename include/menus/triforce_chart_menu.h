#include "menu.h"

enum TriforceChartIndex {
    MENU_TRIFORCE_CHART_1,
    MENU_TRIFORCE_CHART_2,
    MENU_TRIFORCE_CHART_3,
    MENU_TRIFORCE_CHART_4,
    MENU_TRIFORCE_CHART_5,
    MENU_TRIFORCE_CHART_6,
    MENU_TRIFORCE_CHART_7,
    MENU_TRIFORCE_CHART_8,
};

class TriforceChartMenu : public Menu {
public:
    TriforceChartMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
