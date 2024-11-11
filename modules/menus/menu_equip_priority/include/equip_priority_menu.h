#pragma once
#include "menu.h"

class ItemEquipPriorityMenu : public Menu {
public:
    ItemEquipPriorityMenu(Cursor&);
    virtual ~ItemEquipPriorityMenu();
    virtual void draw();

    void drawItemEquipLines();
};
