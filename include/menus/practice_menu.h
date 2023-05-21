#pragma once
#include "menu.h"

class PracticeMenu : public Menu {
public:
    PracticeMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
