#pragma once
#include "menu.h"

enum SpecialChartIndex {
    MENU_TINGLE_CHART,
    MENU_GHOST_SHIP_CHART,
    MENU_INCREDIBLE_CHART,
    MENU_BIG_OCTO_CHART,
    MENU_FAIRY_CHART,
    MENU_HEART_PIECE_CHART,
    MENU_SEA_HEARTS_CHART,
    MENU_SECRET_CAVE_CHART,
    MENU_LIGHT_RING_CHART,
    MENU_PLATFORMS_CHART,
    MENU_BEEDLE_CHART,
    MENU_SUBMARINE_CHART,

    SPECIAL_CHART_INDEX_MAX,
};

class SpecialChartMenu : public Menu {
public:
    SpecialChartMenu(Cursor&);
    virtual ~SpecialChartMenu();
    virtual void draw();

private:
    Line lines[SPECIAL_CHART_INDEX_MAX];
};
