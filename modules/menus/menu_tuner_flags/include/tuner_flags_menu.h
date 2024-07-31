#pragma once
#include "menu.h"

class TunerFlagMenu : public Menu {
public:
    TunerFlagMenu(Cursor&);
    virtual ~TunerFlagMenu();
    virtual void draw();

private:
    Line lines[4];
};
