#pragma once

#include "menu.h"
#include "flags.h"

enum FlagMenuIndex {
    GENERAL_FLAG_INDEX,
    DUNGEON_FLAG_INDEX,
    SAVEWARP_FLAG_INDEX,
    TUNER_FLAG_INDEX,
    //QUEST_FLAG_INDEX,
};

class FlagMenu : public Menu {
public:
    FlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
