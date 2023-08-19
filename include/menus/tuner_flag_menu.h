#include "menu.h"

class TunerFlagMenu : public Menu {
public:
    TunerFlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};