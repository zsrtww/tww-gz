#include "menu.h"

class ImportantFlagMenu : public Menu {
public:
    ImportantFlagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};