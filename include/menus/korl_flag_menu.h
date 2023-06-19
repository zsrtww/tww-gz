#include "menu.h"

class KorlFlagMenu : public Menu {
public:
    KorlFlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};