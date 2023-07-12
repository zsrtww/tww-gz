#include "menu.h"

class SavewarpFlagMenu : public Menu {
public:
    SavewarpFlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
