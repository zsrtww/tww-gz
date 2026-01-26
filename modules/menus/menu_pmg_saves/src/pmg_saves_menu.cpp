#include "menus/menu_pmg_saves/include/pmg_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC PMGSavesMenu::PMGSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{{"after intro", AFTER_INTRO_PMG, "just after the intro, at bottom of watchtower"},
            {"orca", ORCA_PMG, "inside orca\'s house, about to do sword tutorial"},
            {"forest of fairies", FOREST_OF_FAIRIES_PMG, "inside forest of fairies, about to rescue tetra"},
            {"ropes 1", ROPES_1_PMG, "inside pirate ship, about to play ropes 1 minigame"},
            {"early light cycle", EARLY_LIGHTS_PMG, "outside ship, before barrel launch cutscene"},
            {"forsaken fortress 1", FF1_PMG, "at start of ff1"},
            {"ff1 interior", FF1_INTERIOR_PMG, "ff1 in the rope swing room"},
            {"windfall", WINDFALL_PMG, "at windfall island, just finished talking to korl"},
            {"zephos skip", ZEPHOS_SKIP_PMG, "at dri, about to perform zephos skip for wind\'s requiem"},
            {"submarine swim", BOTTLE_SWIM_PMG, "at dri, about to swim to bomb island submarine"},
            {"delivery bag skip", DB_SKIP_PMG, "at dri, with chest storage, about to climb dri to skip delivery bag"},
            {"dragon roost cavern", DRC_PMG, "start of drc"},
            {"drc chest storage", DRC_CHEST_PMG, "in drc map room, about to get chest storage"},
            {"drc outside climb", DRC_CLIMB_PMG, "in drc outside area, about to climb drc with chest storage"},
            {"drc miniboss", DRC_MINI_PMG, "in miniboss room, outside drc"},
            {"drc boss key skip", DRC_BK_SKIP_PMG, "inside drc in boss door room for bk skip"},
            {"gohma", GOHMA_PMG, "gohma boss fight"},
            {"forest haven swim", FH_SWIM_PMG, "at dri, after din's pearl cutscene about to swim to fh"},
            {"deku tree cutscene skip", DTCS_PMG, "inside fh, about to perform dtcs"},
            {"enter forbidden woods", ENTER_FW_PMG, "inside forest haven, about to leaf to fw"},
            {"forbidden woods", FW_PMG, "start of forbidden woods"},
            {"fw small key skip", FW_KEY_SKIP_PMG, "in main room of fw, about to leaf to the upper part of fw"},
            {"fw miniboss", FW_MINI_PMG, "molduga miniboss room"},
            {"fw boss key skip", FW_BK_SKIP_PMG, "in main room of fw, near warp pot, about to store morth pit chest"},
            {"kalle demos", KALLE_DEMOS_PMG, "kalle demos boss fight"},
            {"placing pearls", PEARLS_PMG, "outside fh for swim to eti/nti"},
            {"islet of steel swim", IOS_SWIM_PMG, "at nti, about to swim to islet of steel"},
            {"windfall swim", WINDFALL_SWIM_PMG, "at greatfish, about to swim to windfall for bombs"},
            {"ropes 2", ROPES_2_PMG, "inside pirate ship, about to get bombs"},
            {"nayru's pearl", NAYRUS_PEARL_PMG, "on windfall docks, about to swim to outset for nayru's pearl"},
            {"enter tower of the gods", ENTER_TOTG_PMG, "outside jabun's cave, about to swim to sti"},
            {"tower of the gods", TOTG_PMG, "entrance of tower of the gods"},
            {"totg second statue", TOTG_STATUE_2_PMG, "inside totg second statue room"},
            {"totg miniboss", TOTG_MINI_PMG, "darknut miniboss fight"},
            {"totg third statue", TOTG_STATUE_3_PMG, "in the room before the third totg statue"},
            {"gohdan", GOHDAN_PMG, "gohdan boss fight"},
            {"puzzle skip", PUZZLE_SKIP_PMG, "inside hyrule castle for puzzle skip"},
            {"hyrule escape", HYRULE_ESCAPE_PMG, "inside hyrule castle after master sword for hyrule escape"},
            {"forsaken fortress 2 swim", FF2_SWIM_PMG, "on nti, about to swim to ff2"},
            {"phantom ganon", PHANTOM_GANON_PMG, "phantom ganon miniboss fight"},
            {"enter helmaroc", ENTER_HELM_PMG, "after phantom ganon fight for chest storage climb"},
            {"helmaroc", HELM_PMG, "at the top of ff2 tower, about to start the helmaroc fight"},
            {"barrier skip", BARRIER_SKIP_PMG, "outside hyrule castle, about to do barrier skip"},
            {"trials skip", TRIALS_SKIP_PMG, "inside ganon's tower, about to do trials skip"},
            {"puppet ganon fight", PG_FIGHT_PMG, "inside ganondorf\'s bedroom, at start of puppet ganon fight"},
            {"morth hover", MORTH_HOVER_PMG, "at the top of ganondorf\'s bedroom for morth hover"},
            {"ganondorf", GANONDORF_PMG, "on top of ganondorf\'s tower, at start of ganondorf fight"}} {}

PMGSavesMenu::~PMGSavesMenu() {}

void PMGSavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special PMGSpecials[] = {
            special(FOREST_OF_FAIRIES_PMG, SaveMngSpecial_SetLayer0),
            special(ROPES_1_PMG, SaveMngSpecial_SetLayer0),
            special(WINDFALL_PMG, SaveMngSpecial_SetLayer0),
            special(ZEPHOS_SKIP_PMG, SaveMngSpecial_BombsSwim_FHSwim_NoMSS),
            special(BOTTLE_SWIM_PMG, SaveMngSpecial_SubmarineSwim_PMG),
            special(DB_SKIP_PMG, SaveMngSpecial_DeliveryBagSkip_PMG),
            special(DRC_CHEST_PMG, SaveMngSpecial_DRCChestStorage_PMG),
            special(DRC_CLIMB_PMG, SaveMngSpecial_DRCClimb_PMG),
            special(FW_KEY_SKIP_PMG, SaveMngSpecial_FWSmallKeySkip_PMG),
            special(HYRULE_ESCAPE_PMG, SaveMngSpecial_HyruleEscape_AD),
            special(PHANTOM_GANON_PMG, SaveMngSpecial_PhantomGanon_AD),
            special(HELM_PMG, SaveMngSpecial_Helmaroc),
            special(PG_FIGHT_PMG, SaveMngSpecial_PuppetGanon),
            special(MORTH_HOVER_PMG, SaveMngSpecial_GanonHover),
            special(GANONDORF_PMG, SaveMngSpecial_Ganondorf),
        };

        SaveManager::triggerLoad(cursor.y, "pmg", PMGSpecials, sizeof(PMGSpecials) / sizeof(PMGSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}