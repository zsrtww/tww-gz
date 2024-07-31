#pragma once
#include "menu.h"

class SavewarpFlagMenu : public Menu {
public:
    SavewarpFlagMenu(Cursor&);
    virtual ~SavewarpFlagMenu();
    virtual void draw();

private:
    Line lines[5];
};
