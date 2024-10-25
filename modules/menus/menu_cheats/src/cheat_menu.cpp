#include "menus/menu_cheats/include/cheats_menu.h"
#include "cheats.h"
#include "commands.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/patch.h"
#include "libtww/include/defines.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC CheatsMenu::CheatsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"infinite air", InfiniteAir, "Always have max air", true, ACTIVE_FUNC(STNG_CHEATS_INFINITE_AIR)},
          {"infinite arrows", InfiniteArrows, "Always have max arrows", true, ACTIVE_FUNC(STNG_CHEATS_INFINITE_ARROWS)},
          {"infinite bombs", InfiniteBombs, "Always have max bombs", true, ACTIVE_FUNC(STNG_CHEATS_INFINITE_BOMBS)},
          {"infinite hearts", InfiniteHearts, "Always have full hearts", true,
           ACTIVE_FUNC(STNG_CHEATS_INFINITE_HEARTS)},
          {"refill health", RefillHealth, "Hold R+D-pad right to refill health", true,
           ACTIVE_FUNC(STNG_CHEATS_REFILL_HEALTH)},
          {"infinite magic", InfiniteMagic, "Always have full magic", true, ACTIVE_FUNC(STNG_CHEATS_INFINITE_MAGIC)},
          {"refill magic", RefillMagic, "Hold L+D-pad up to refill magic", true, ACTIVE_FUNC(STNG_CHEATS_REFILL_MAGIC)},
          {"infinite rupees", InfiniteRupees, "Always have infinite rupees", true,
           ACTIVE_FUNC(STNG_CHEATS_INFINITE_RUPEES)},
          {"moon jump", MoonJump, "Hold R+A to moon jump", true, ACTIVE_FUNC(STNG_CHEATS_MOON_JUMP)},
          {"storage", StorageCheat, "Press D-pad right to get storage", true, ACTIVE_FUNC(STNG_CHEATS_STORAGE)},
          {"normal collision", NormalCollision, "Hold L+D-pad down to get normal collision", true,
           ACTIVE_FUNC(STNG_CHEATS_NORMAL_COLLISION)},
          {"chest storage", ChestStorage, "Hold L+D-pad right to get chest storage", true,
           ACTIVE_FUNC(STNG_CHEATS_CHEST_STORAGE)},
          {"door cancel", DoorCancel, "Hold L+D-pad left to get door cancel", true,
           ACTIVE_FUNC(STNG_CHEATS_DOOR_CANCEL)},
          {"quarter heart", QuarterHeart, "Hold R+D-pad left to reduce health to quarter heart", true,
           ACTIVE_FUNC(STNG_CHEATS_QUARTER_HEART)},
          {"fast movement", FastMovement, "Hold D-pad left to get super speed. Modify the speed in settings.", true,
           ACTIVE_FUNC(STNG_CHEATS_FAST_MOVEMENT)},
          {"upcharge", Upcharge, "Hold X + Z to get negative speed for upcharge", true,
           ACTIVE_FUNC(STNG_CHEATS_UPCHARGE)},
          {"tingle balloon", Hoverboots, "Hold L+ D-pad left to get tingle balloon.", true,
           ACTIVE_FUNC(STNG_CHEATS_HOVERBOOTS)}} {}

CheatsMenu::~CheatsMenu() {}

GZSettingID l_mapping[] = {
    STNG_CHEATS_INFINITE_AIR,  STNG_CHEATS_INFINITE_ARROWS, STNG_CHEATS_INFINITE_BOMBS,   STNG_CHEATS_INFINITE_HEARTS,
    STNG_CHEATS_REFILL_HEALTH, STNG_CHEATS_INFINITE_MAGIC,  STNG_CHEATS_REFILL_MAGIC,     STNG_CHEATS_INFINITE_RUPEES,
    STNG_CHEATS_MOON_JUMP,     STNG_CHEATS_STORAGE,         STNG_CHEATS_NORMAL_COLLISION, STNG_CHEATS_CHEST_STORAGE,
    STNG_CHEATS_DOOR_CANCEL,   STNG_CHEATS_QUARTER_HEART,   STNG_CHEATS_FAST_MOVEMENT,    STNG_CHEATS_UPCHARGE,
    STNG_CHEATS_HOVERBOOTS,
};
static_assert(ARRAY_COUNT(l_mapping) == CHEAT_AMNT, "l_mapping size does not match CHEAT_AMNT");

void CheatsMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        auto* stng = GZStng_get(l_mapping[cursor.y]);
        if (!stng) {
            stng = new GZSettingEntry{l_mapping[cursor.y], sizeof(bool), new bool{false}};
            g_settings.push_back(stng);
        }
        *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}