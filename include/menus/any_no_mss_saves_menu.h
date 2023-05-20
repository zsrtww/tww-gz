#pragma once

#include "menu.h"

enum AnyNoMssSaves {
    OUTSET,
};

class AnyNoMssSavesMenu : public Menu {
public:
    AnyNoMssSavesMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};