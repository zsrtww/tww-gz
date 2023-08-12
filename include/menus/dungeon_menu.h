#include "menu.h"
#include "libtww/d/kankyo/d_kankyo.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/f_op/f_op_scene_req.h"
#include "libtww/m_Do/m_Do_main.h"
#include "controller.h"

enum DungeonMenuIndex {
    PICK_DUNGEON_INDEX,
    MODIFY_KEYS_INDEX,
    BOSS_KEY_INDEX,
    MAP_INDEX,
    COMPASS_INDEX,
    PARTNER_INDEX,
};


class DungeonMenu : public Menu {
public:
    DungeonMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};

