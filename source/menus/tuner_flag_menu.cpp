#include "menus/flag_menu.h"
#include "menus/tuner_flag_menu.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "flags.h"


#define LINE_NUM 4
Cursor TunerFlagMenu::cursor;
int cursorOffset;


Line lines[LINE_NUM] = {
    {"Kooloo-Limpah 10s Balloon+Shield", KOOLOO_LIMPAH, "Adds the 10s Balloon+Shield to the Kooloo-Limpah pool", true,
        &g_flags[KOOLOO_LIMPAH]},
    {"Tingle Balloon Discount", BALLOON_DISCOUNT, "Gives Tingle Balloon Discount from 30 to 20 rupees", true,
        &g_flags[BALLOON_DISCOUNT]},
    {"Tings Discount", TINGS_DISCOUNT, "Gives 50 percent off discount for all tings", true,
        &g_flags[TINGS_DISCOUNT]},
    {"Hand-Me-Down Tingle Tuner", HAND_ME_DOWN_TUNER, "Unlocks the Hand-Me-Down Tingle Tuner item in the tuner shop", true,
        &g_flags[HAND_ME_DOWN_TUNER]},


};


void TunerFlagMenu::draw() {
    updateFlags();


    cursor.move(0, LINE_NUM);
    cursorOffset = cursor.y + TUNER_FLAG_OFFSET;


    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }


    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursorOffset) {
        case KOOLOO_LIMPAH:
            setEventFlag(0x2E08);
            break;
        case BALLOON_DISCOUNT:
            setEventFlag(0x1A10);
            break;
        case TINGS_DISCOUNT:
            setEventFlag(0x1A08);
            break;
        case HAND_ME_DOWN_TUNER:
            setEventFlag(0x1708);
            break;


        }
    }


    GZ_drawMenuLines(lines, cursorOffset, LINE_NUM);
    }
