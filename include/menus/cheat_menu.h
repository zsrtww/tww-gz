#pragma once

#include "menu.h"

struct GZCheat {
    int index;
    bool active;
};

class CheatMenu : public Menu {
public:
    CheatMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};