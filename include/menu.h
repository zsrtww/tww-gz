#pragma once

#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#define MENU_NUM 3

enum {
    /* Main Menus */
    GZ_NO_MENU = -1,
    GZ_MAIN_MENU,
    GZ_INVENTORY_MENU,
    GZ_SETTINGS_MENU,
    GZ_AMOUNT_MENU,
    GZ_PAUSE_MENU,
    GZ_SPOILS_MENU,
    GZ_DELIVERY_MENU,
};

void GZ_drawMenu();
void GZ_setMenu(int idx);
void GZ_clearMenu();
bool GZ_checkMenuOpen();

class Menu {
public:
    Menu() {}
};