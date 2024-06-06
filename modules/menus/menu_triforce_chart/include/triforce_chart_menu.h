#pragma once
#include "menu.h"

class TriforceChartMenu : public Menu {
public:
    TriforceChartMenu(Cursor&);
    virtual ~TriforceChartMenu();
    virtual void draw();

private:
    Line lines[8];
};
