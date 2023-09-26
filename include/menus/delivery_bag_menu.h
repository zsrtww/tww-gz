#include "menu.h"

enum DeliveryBagMenuIndex {
    SLOT1_INDEX,
    SLOT2_INDEX,
    SLOT3_INDEX,
    SLOT4_INDEX,
    SLOT5_INDEX,
    SLOT6_INDEX,
    SLOT7_INDEX,
    SLOT8_INDEX
};

class DeliveryBagMenu : public Menu {
public:
    DeliveryBagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};

const char* item_id_to_str(u8 item_id);