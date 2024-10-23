#include "menus/menu_tuner_flags/include/tuner_flags_menu.h"
#include "flags.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define LINE_NUM 4

KEEP_FUNC TunerFlagMenu::TunerFlagMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"Kooloo-Limpah 10s Balloon+Shield", 0, "Adds the 10s Balloon+Shield to the Kooloo-Limpah pool",
                         true, []() { return g_flags[KOOLOO_LIMPAH]; }},
                        {"Tingle Balloon Discount", 1, "Gives Tingle Balloon Discount from 30 to 20 rupees", true,
                         []() { return g_flags[BALLOON_DISCOUNT]; }},
                        {"Tings Discount", 2, "Gives 50 percent off discount for all tings", true,
                         []() { return g_flags[TINGS_DISCOUNT]; }},
                        {"Hand-Me-Down Tingle Tuner", 3, "Unlocks the Hand-Me-Down Tingle Tuner item in the tuner shop",
                         true, []() { return g_flags[HAND_ME_DOWN_TUNER]; }},
                    } {}

TunerFlagMenu::~TunerFlagMenu() {}

void TunerFlagMenu::draw() {
    updateFlags();

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case 0:
            setEventFlag(0x2E08);
            break;
        case 1:
            setEventFlag(0x1A10);
            break;
        case 2:
            setEventFlag(0x1A08);
            break;
        case 3:
            setEventFlag(0x1708);
            break;
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
