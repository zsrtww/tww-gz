#include "menu.h"

enum InventoryMenuIndex {
    AMOUNT_INDEX,
    ITEM_INVENTORY_INDEX,
    QUEST_STATUS_INDEX,
    SPOILS_INDEX,
    DELIVERY_BAG_INDEX,
};

class InventoryMenu : public Menu {
public:
    InventoryMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};

const char* item_id_to_str(u8 item_id);