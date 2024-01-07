#pragma once

#include "menu.h"

enum AnyPercentSaves {
    MSS,
    POST_MSS,
    BOMBS_ANY,
    SAIL_SKIP,
    ROPES_2_ANY,
    FH_SWIM_ANY,
    DTCS_ANY,
    LEAF_HOVER,
    QUIVER_FF2,
    FF2_SWIM_ANY,
    HELM_SKIP,
    BARRIER_SKIP_ANY,
    TRIALS_SKIP_ANY,
    LIGHT_ARROW_SKIP,
    PGCS_SKIP,
    PG_SKIP,
    PG_FIGHT_ANY,
    MORTH_HOVER_ANY,
    GANONDORF_ANY,
};

class AnyPercentSavesMenu : public Menu {
public:
    AnyPercentSavesMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
