#include "menu.h"

enum SpoilsBagMenuIndex {
    SPOILSSLOT1_INDEX,
    SPOILSSLOT2_INDEX,
    SPOILSSLOT3_INDEX,
    SPOILSSLOT4_INDEX,
    SPOILSSLOT5_INDEX,
    SPOILSSLOT6_INDEX,
    SPOILSSLOT7_INDEX,
    SPOILSSLOT8_INDEX
};

class SpoilsBagMenu : public Menu {
public:
    SpoilsBagMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};

const char* item_id_to_str(u8 item_id);