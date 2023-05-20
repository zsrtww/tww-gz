#pragma once
#include "menu.h"

enum SpeedrunCategories {
    ANY_NO_MSS,
};

class PracticeMenu : public Menu {
public:
    PracticeMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
