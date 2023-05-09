#include "menu.h"

enum AmountMenuIndex {
    HEALTH_INDEX,
    BOMB_INDEX,
    ARROW_INDEX,
    RUPEE_INDEX,
    MAGIC_INDEX,
    HEART_PIECE_INDEX,
    MAX_MAGIC_INDEX
};

class AmountMenu : public Menu {
public:
    AmountMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};