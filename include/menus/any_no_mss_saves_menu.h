#pragma once

#include "menu.h"

enum AnyNoMssSaves {
    AFTER_INTRO,
    ORCA,
    FOREST_OF_FAIRIES,
    ROPES_1,
    FF1,
    WINDFALL,
    BOMBS_SWIM,
    ROPES_2,
    FH_SWIM,
    DTCS,
    QUIVER_SWIM,
    FF2_SWIM,
    HELMAROC_SKIP,
    BARRIER_SKIP,
    TRIALS_SKIP,
    PG_FIGHT,
    MORTH_HOVER,
    GANONDORF,
};

class AnyNoMssSavesMenu : public Menu {
public:
    AnyNoMssSavesMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};