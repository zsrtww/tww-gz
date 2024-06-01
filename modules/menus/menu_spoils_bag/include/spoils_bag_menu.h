#pragma once
#include "menu.h"

enum SpoilsBagMenuIndex {
    SPOILSSLOT1_INDEX,
    SPOILSSLOT2_INDEX,
    SPOILSSLOT3_INDEX,
    SPOILSSLOT4_INDEX,
    SPOILSSLOT5_INDEX,
    SPOILSSLOT6_INDEX,
    SPOILSSLOT7_INDEX,
    SPOILSSLOT8_INDEX,

    SPOILS_MENU_MAX,
};

class SpoilsBagMenu : public Menu {
public:
    SpoilsBagMenu(Cursor&);
    virtual ~SpoilsBagMenu();
    virtual void draw();

private:
    Line lines[SPOILS_MENU_MAX];
};
