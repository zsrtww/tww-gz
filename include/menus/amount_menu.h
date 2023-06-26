#include "menu.h"

enum AmountMenuIndex {
    HEALTH_INDEX,
    BOMB_INDEX,
    ARROW_INDEX,
    RUPEE_INDEX,
    MAGIC_INDEX,
    HEART_PIECE_INDEX,
    JOY_PENDANT_INDEX,
    SKULL_NECKLACE_INDEX,
    BOKO_BABA_SEED_INDEX,
    GOLDEN_FEATHER_INDEX,
    KNIGHTS_CREST_INDEX,
    RED_CHU_JELLY_INDEX,
    GREEN_CHU_JELLY_INDEX,
    BLUE_CHU_JELLY_INDEX
};

class AmountMenu : public Menu {
public:
    AmountMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};