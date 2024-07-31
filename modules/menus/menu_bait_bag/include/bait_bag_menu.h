#pragma once
#include "menu.h"

enum BaitBagMenuIndex {
    BAITSLOT1_INDEX,
    BAITSLOT2_INDEX,
    BAITSLOT3_INDEX,
    BAITSLOT4_INDEX,
    BAITSLOT5_INDEX,
    BAITSLOT6_INDEX,
    BAITSLOT7_INDEX,
    BAITSLOT8_INDEX,

    BAIT_MENU_INDEX
};

class BaitBagMenu : public Menu {
public:
    BaitBagMenu(Cursor&);
    virtual ~BaitBagMenu();
    virtual void draw();

private:
    Line lines[BAIT_MENU_INDEX];
};
