#include "menu.h"

enum BeginnerSaves {
    AFTER_INTRO_B,
    ORCA_B,
    FOREST_OF_FAIRIES_B,
    ROPES_1_B,
    EARLY_LIGHTS_B,
    FF1_B,
    FF1_INTERIOR_B,
    WINDFALL_B,
    ZEPHOS_SKIP_B,
    BOTTLE_SWIM_B,
    PLATFORM_CHEST_B,
    DB_SKIP_B,
    DRC_B,
    DRC_CHEST_B,
    DRC_CLIMB_B,
    DRC_MINI_B,
    DRC_BK_SKIP_B,
    GOHMA_B,
    FH_SWIM_B,
    DTCS_B,
    ENTER_FW_ADV_B,
    ENTER_FW_EZ_B,
    FW_B,
    FW_KEY_SKIP_B,
    FW_MINI_B,
    FW_BK_SKIP_B,
    KALLE_DEMOS_B,
    PEARLS_B,
    IOS_SWIM_B,
    WINDFALL_SWIM_B,
    ROPES_2_B,
    NAYRUS_PEARL_B,
    ENTER_TOTG_B,
    TOTG_B,
    TOTG_STATUE_2_B,
    TOTG_MINI_B,
    TOTG_STATUE_3_B,
    GOHDAN_B,
    PUZZLE_SKIP_B,
    HYRULE_ESCAPE_B,
    FF2_SWIM_ADV_B,
    FF2_SWIM_EZ_B,
    PHANTOM_GANON_B,
    ENTER_HELM_B,
    HELM_B,
    BARRIER_SKIP_B,
    TRIALS_SKIP_B,
    PG_FIGHT_B,
    MORTH_HOVER_B,
    GANONDORF_B,

    BEGINNER_SAVES_COUNT,
};

class BeginnerSavesMenu : public Menu {
public:
    BeginnerSavesMenu(Cursor& cursor);
    virtual ~BeginnerSavesMenu();
    virtual void draw();

private:
    Line lines[BEGINNER_SAVES_COUNT];
};