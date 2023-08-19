#include "menu.h"

enum BaitBagMenuIndex {
    BAITSLOT1_INDEX,
    BAITSLOT2_INDEX,
    BAITSLOT3_INDEX,
    BAITSLOT4_INDEX,
    BAITSLOT5_INDEX,
    BAITSLOT6_INDEX,
    BAITSLOT7_INDEX,
    BAITSLOT8_INDEX,
    AMTSLOT1_INDEX,
    AMTSLOT2_INDEX,
    AMTSLOT3_INDEX,
    AMTSLOT4_INDEX,
    AMTSLOT5_INDEX,
    AMTSLOT6_INDEX,
    AMTSLOT7_INDEX,
    AMTSLOT8_INDEX,
};

class BaitBagMenu : public Menu {
public:
    BaitBagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};

const char* item_id_to_str(u8 item_id);
