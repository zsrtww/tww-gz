#include "menus/cheat_menu.h"
#include "menus/settings_menu.h"
#include "menu.h"
#include "libtww/MSL_C/string.h"
#include "lib.h"
#include "font.h"
#include "commands.h"
#include "cheats.h"

#define LINE_NUM 12
Cursor CheatMenu::cursor;

Line lines[LINE_NUM] = {
    {"infinite air", InfiniteAir, "Gives infinite air", true,
        &g_cheats[InfiniteAir].active},
    {"infinite arrows", InfiniteArrows, "Always have max arrows", true,
        &g_cheats[InfiniteArrows].active},
    {"infinite bombs", InfiniteBombs, "Always have max bombs", true,
        &g_cheats[InfiniteBombs].active},
    {"infinite hearts", InfiniteHearts, "Always have full hearts", true,
        &g_cheats[InfiniteHearts].active},
    {"infinite magic", InfiniteMagic, "Always have full magic", true,
        &g_cheats[InfiniteMagic].active},
    {"infinite rupees", InfiniteRupees, "Gives infinite rupees", true,
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
        &g_cheats[QuarterHeart].active}
};

void CheatMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);
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
