#pragma once

#include "menu.h"
#include "flags.h"

class FlagMenu : public Menu {
public:
    FlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};