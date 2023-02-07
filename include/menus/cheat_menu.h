#pragma once

#include "menu.h"

enum CHEAT_e {
    MOON_JUMP_INDEX,
};

struct GZCheat {
    int index;
    bool active;
};

#define CHEAT_AMNT 1
extern GZCheat g_cheats[CHEAT_AMNT];

class CheatMenu : public Menu {
public:
    CheatMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};