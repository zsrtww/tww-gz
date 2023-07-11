#include "menus/flag_menu.h"
#include "menus/important_flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"

#define LINE_NUM 3 
Cursor ImportantFlagMenu::cursor;

Line lines[LINE_NUM] = {
    {"Watched FF2 Helmaroc Cutscene", WATCHED_FF2_HELMAROC_CUTSCENE, "Switches to animation set 2, among other things", true,
        &g_flags[WATCHED_FF2_HELMAROC_CUTSCENE]},
    {"Have Hurricane Spin", HAVE_HURRICANE_SPIN, "Gives Hurricane Spin", true,
        &g_flags[HAVE_HURRICANE_SPIN]},
    {"Endless Night", ENDLESS_NIGHT, "Activates Endless Night, incompatible with having Nayru's Pearl", true,
        &g_flags[ENDLESS_NIGHT]},

};

void ImportantFlagMenu::draw() {
    updateFlags();

    cursor.setMode(Cursor::MODE_LIST);
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case WATCHED_FF2_HELMAROC_CUTSCENE:
            setEventFlag(0x2D01);
            break;
        case HAVE_HURRICANE_SPIN:
            setEventFlag(0x0B20);
            break;
        case ENDLESS_NIGHT:
            setEventFlag(0x0A02);
            break;
        }
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
