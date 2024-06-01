#pragma once
#include "menu.h"

enum FlagsIndex {
    GENERAL_FLAGS_INDEX,
    DUNGEON_FLAGS_INDEX,
    SAVEWARP_FLAG_INDEX,
    TUNER_FLAG_INDEX,

    FLAGS_MENU_MAX,
};

class FlagsMenu : public Menu {
public:
    FlagsMenu(Cursor&);
    virtual ~FlagsMenu();
    virtual void draw();

private:
    Line lines[FLAGS_MENU_MAX];
};
