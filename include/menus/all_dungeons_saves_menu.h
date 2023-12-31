#pragma once

#include "menu.h"

enum AllDungeonsSaves {
    MSS_AD,
    PMSS_AD,
    FF1_CS_AD,
    WINDFALL_AD,
    ROPES_2_AD,
    FH_SWIM_AD,
    EARLY_LEAF_HOVER_AD,
    DEKU_TREE_CS_AD,
    FORBIDDEN_WOODS_AD,
    KALLE_DEMOS_AD,
    ENTER_DRC_AD,
    DRC_AD,
    DRC_MB_AD,
    DRC_BKS_AD,
    GOHMA_BOSS_AD,
    NAYRUS_PEARL_AD,
    ENTER_TOTG_AD,
    TOTG_AD,
    DARKNUT_AD,
    TOTG_AFTER_STATUE2_AD,
    GOHDAN_BOSS_AD,
    PUZZLE_SKIP_AD,
    HYRULE_ESCAPE_AD,
    BARRIER_SKIP_AD,
    TRIAL_SKIP_AD,
    BOOMERANG_SKIP_AD,
    PHANTOM_GANON_AD,
    ENTER_HELM_AD,
    HYRULE2_SKIP_AD,
    EARLY_WGA_AD,
    FIRE_MOUNTAIN_AD,
    EARLY_ET_AD,
    ET_AD,
    SONGTONE_SKIP_AD,
    JALHALLA_AD,
    ICE_RING_AD,
    MAKAR_AD,
    ENTER_WT_AD,
    WT_AD,
    WIZZROBE_AD,
    AFTER_HS_AD,
    MOLGERA_AD,
    SWIM_2_FCP_AD,
    FCP_LAYER_MANIP_AD,
    PG_CS_AD,
    PG_SKIP_AD,
    PUPPET_GANON_AD,
    GANONDORF_AD,
    
};

class AllDungeonsSavesMenu : public Menu {
public:
    AllDungeonsSavesMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};
