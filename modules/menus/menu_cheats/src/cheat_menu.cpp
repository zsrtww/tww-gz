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
          {"infinite air", InfiniteAir, "Always have max air", true, &g_cheats[InfiniteAir].active},
          {"infinite arrows", InfiniteArrows, "Always have max arrows", true,
           &g_cheats[InfiniteArrows].active},
          {"infinite bombs", InfiniteBombs, "Always have max bombs", true,
           &g_cheats[InfiniteBombs].active},
          {"infinite hearts", InfiniteHearts, "Always have full hearts", true,
           &g_cheats[InfiniteHearts].active},
          {"refill health", RefillHealth, "Hold R+D-pad right to refill health", true,
           &g_cheats[RefillHealth].active},
          {"infinite magic", InfiniteMagic, "Always have full magic", true,
           &g_cheats[InfiniteMagic].active},
          {"refill magic", RefillMagic, "Hold L+D-pad up to refill magic", true,
           &g_cheats[RefillMagic].active},
          {"infinite rupees", InfiniteRupees, "Always have infinite rupees", true,
           &g_cheats[InfiniteRupees].active},
          {"moon jump", MoonJump, "Hold R+A to moon jump", true, &g_cheats[MoonJump].active},
          {"storage", StorageCheat, "Press D-pad right to get storage", true,
           &g_cheats[StorageCheat].active},
          {"normal collision", NormalCollision, "Hold L+D-pad down to get normal collision", true,
           &g_cheats[NormalCollision].active},
          {"chest storage", ChestStorage, "Hold L+D-pad right to get chest storage", true,
           &g_cheats[ChestStorage].active},
          {"door cancel", DoorCancel, "Hold L+D-pad left to get door cancel", true,
           &g_cheats[DoorCancel].active},
          {"quarter heart", QuarterHeart, "Hold R+D-pad left to reduce health to quarter heart",
           true, &g_cheats[QuarterHeart].active},
          {"fast movement", FastMovement, "Hold D-pad left to get super speed", true,
           &g_cheats[FastMovement].active},
          {"upcharge", Upcharge, "Hold X + Z to get negative speed for upcharge", true,
           &g_cheats[Upcharge].active}} {}

CheatsMenu::~CheatsMenu() {}

void CheatsMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_cheats[cursor.y].active = !g_cheats[cursor.y].active;
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}