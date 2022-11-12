#include "menu.h"

enum InventoryMenuIndex {
    AMOUNT_INDEX,
    PAUSE_INDEX,
    SPOILS_INDEX,
    DELIVERY_BAG_INDEX,
};

class InventoryMenu : public Menu {
public:
    InventoryMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};