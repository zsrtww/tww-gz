#include "menu.h"

enum BottleSlotIndex {
    SLOT_BOTTLE_1 = 14,
    SLOT_BOTTLE_2 = 15,
    SLOT_BOTTLE_3 = 16,
    SLOT_BOTTLE_4 = 17
};

class PauseMenu : public Menu {
public:
    PauseMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};