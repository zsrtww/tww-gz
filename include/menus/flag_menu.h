#pragma once

#include "menu.h"
#include "flags.h"

enum FlagMenuIndex {
    IMPORTANT_FLAG_INDEX,
    CUTSCENE_FLAG_INDEX,
    KORL_FLAG_INDEX,
    SAVEWARP_FLAG_INDEX,
    QUEST_FLAG_INDEX,
    DUNGEON_FLAG_INDEX,
};

class FlagMenu : public Menu {
public:
    FlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
