#include "menus/cheat_menu.h"
#include "menus/settings_menu.h"
#include "menu.h"
#include "libtww/MSL_C/string.h"
#include "lib.h"
#include "font.h"
#include "commands.h"
#include "cheats.h"
#include "libtww/d/com/d_com_inf_game.h"

#define LINE_NUM 16
Cursor CheatMenu::cursor;

Line lines[LINE_NUM] = {
    {"infinite air", InfiniteAir, "Always have max air", true,
        &g_cheats[InfiniteAir].active},
    {"infinite arrows", InfiniteArrows, "Always have max arrows", true,
        &g_cheats[InfiniteArrows].active},
    {"infinite bombs", InfiniteBombs, "Always have max bombs", true,
        &g_cheats[InfiniteBombs].active},
    {"infinite hearts", InfiniteHearts, "Always have full hearts", true,
        &g_cheats[InfiniteHearts].active},
    {"refill health", RefillHealth, "Hold R+D-pad right to refill health",
     true, &g_cheats[RefillHealth].active},
    {"infinite magic", InfiniteMagic, "Always have full magic", true,
        &g_cheats[InfiniteMagic].active},
    {"refill magic", RefillMagic, "Hold L+D-pad up to refill magic", true,
        &g_cheats[RefillMagic].active},
    {"infinite rupees", InfiniteRupees, "Always have infinite rupees", true,
        &g_cheats[InfiniteRupees].active},
    {"moon jump", MoonJump, "Hold R+A to moon jump", true,
        &g_cheats[MoonJump].active},
    {"storage", StorageCheat, "Press D-pad right to get storage", true,
        &g_cheats[StorageCheat].active},
    {"normal collision", NormalCollision, "Hold L+D-pad down to get normal collision", true,
        &g_cheats[NormalCollision].active},
    {"chest storage", ChestStorage, "Hold L+D-pad right to get chest storage", true,
        &g_cheats[ChestStorage].active},
    {"door cancel", DoorCancel, "Hold L+D-pad left to get door cancel", true,
        &g_cheats[DoorCancel].active},
    {"quarter heart", QuarterHeart, "Hold R+D-pad left to reduce health to quarter heart", true,
        &g_cheats[QuarterHeart].active},
    {"fast movement", FastMovement, "Hold D-pad left to get super speed. Modify the speed in settings.", true,
        &g_cheats[FastMovement].active},
    {"upcharge", Upcharge, "Hold X + Z to get negative speed for upcharge", true,
        &g_cheats[Upcharge].active}
};

void CheatMenu::draw() {
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        g_cheats[cursor.y].active = !g_cheats[cursor.y].active;
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
