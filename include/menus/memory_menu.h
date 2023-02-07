#pragma once
#include "menu.h"

class MemoryMenu : public Menu {
public:
    MemoryMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
