#include "menu.h"

enum BottleSlotIndex {
    SLOT_BOTTLE_1 = 14,
    SLOT_BOTTLE_2 = 15,
    SLOT_BOTTLE_3 = 16,
    SLOT_BOTTLE_4 = 17
};

class ItemInventoryMenu : public Menu {
public:
    ItemInventoryMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};