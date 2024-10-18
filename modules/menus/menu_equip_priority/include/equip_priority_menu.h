#pragma once
#include "menu.h"

class ItemEquipPriorityMenu : public Menu {
public:
    ItemEquipPriorityMenu(Cursor&);
    virtual ~ItemEquipPriorityMenu();
    virtual void draw();

    void drawItemEquipLines();

private:
    int32_t l_selectedLine = -1;
    int32_t l_selectedCol = -1;

    bool checkItemLineSelected();
    bool checkLineValSelected();
};
