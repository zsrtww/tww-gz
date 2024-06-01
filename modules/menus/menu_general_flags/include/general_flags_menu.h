#pragma once
#include "menu.h"

class GeneralFlagsMenu : public Menu {
public:
    GeneralFlagsMenu(Cursor&);
    virtual ~GeneralFlagsMenu();
    virtual void draw();

private:
    Line lines[10];
};
