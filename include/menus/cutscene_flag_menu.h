#include "menu.h"

class CutsceneFlagMenu : public Menu {
public:
    CutsceneFlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};