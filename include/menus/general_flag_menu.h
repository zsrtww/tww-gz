#include "menu.h"

class GeneralFlagMenu : public Menu {
public:
    GeneralFlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};