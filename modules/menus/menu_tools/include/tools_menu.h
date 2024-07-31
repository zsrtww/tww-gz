#pragma once

#include "menu.h"
#include "tools.h"

class ToolsMenu : public Menu {
public:
    ToolsMenu(Cursor&);
    virtual ~ToolsMenu();
    virtual void draw();

private:
    Line lines[TOOLS_COUNT];
};