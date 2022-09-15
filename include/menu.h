#pragma once

#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MENU_NUM 2

enum {
    /* Main Menus */
    GZ_NO_MENU = -1,
    GZ_MAIN_MENU,

    GZ_SETTINGS_MENU,
};

void GZ_drawMenu();
void GZ_setMenu(int idx);
void GZ_clearMenu();
bool GZ_checkMenuOpen();

class Menu {
public:
    Menu() {}
};