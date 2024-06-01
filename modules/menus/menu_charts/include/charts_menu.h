#include "menu.h"

enum ChartMenuIndex {
    TREASURE_CHART_INDEX,
    SPECIAL_CHART_INDEX,
    TRIFORCE_CHART_INDEX,
    ALL_CHARTS_INDEX,

    CHART_MENU_MAX
};

class ChartMenu : public Menu {
public:
    ChartMenu(Cursor&);
    virtual ~ChartMenu();
    virtual void draw();

private:
    Line lines[CHART_MENU_MAX];
};