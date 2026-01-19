#include "menus/menu_beginner_saves/include/beginner_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC BeginnerSavesMenu::BeginnerSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{{"after intro", AFTER_INTRO_B, "just after the intro, at bottom of watchtower"},
            {"orca", ORCA_B, "inside orca\'s house, about to do sword tutorial"},
            {"forest of fairies", FOREST_OF_FAIRIES_B, "inside forest of fairies, about to rescue tetra"},
            {"ropes 1", ROPES_1_B, "inside pirate ship, about to play ropes 1 minigame"},
            {"early light cycle", EARLY_LIGHTS_B, "outside ship, before barrel launch cutscene"},
            {"forsaken fortress 1", FF1_B, "at start of ff1"},
            {"ff1 interior", FF1_INTERIOR_B, "ff1 in the rope swing room"},
            {"windfall", WINDFALL_B, "at windfall island, just finished talking to korl"},
            {"zephos skip", ZEPHOS_SKIP_B, "at dri, about to perform zephos skip for wind\'s requiem"},
            {"submarine swim", BOTTLE_SWIM_B, "at dri, about to swim to bomb island submarine"},
            {"lookout platform chest storage", PLATFORM_CHEST_B,
             "on bomb island lookout platform, about to get chest storage"},
            {"delivery bag skip", DB_SKIP_B, "at dri, with chest storage, about to climb dri to skip delivery bag"},
            {"dragon roost cavern", DRC_B, "start of drc"},
            {"drc chest storage", DRC_CHEST_B, "in drc map room, about to get chest storage"},
            {"drc outside climb", DRC_CLIMB_B, "in drc outside area, about to climb drc with chest storage"},
            {"drc miniboss", DRC_MINI_B, "in miniboss room, outside drc"},
            {"drc boss key skip", DRC_BK_SKIP_B, "inside drc in boss door room for bk skip"},
            {"gohma", GOHMA_B, "gohma boss fight"},
            {"forest haven swim", FH_SWIM_B, "at dri, after din's pearl cutscene about to swim to fh"},
            {"deku tree cutscene skip", DTCS_B, "inside fh, about to perform dtcs"},
            {"enter forbidden woods", ENTER_FW_ADV_B, "on korl near fh, about to leaf to fw"},
            {"enter forbidden woods [alt]", ENTER_FW_EZ_B, "inside forest haven, about to leaf to fw"},
            {"forbidden woods", FW_B, "start of forbidden woods"},
            {"fw small key skip", FW_KEY_SKIP_B, "in main room of fw, about to leaf to the upper part of fw"},
            {"fw miniboss", FW_MINI_B, "molduga miniboss room"},
            {"fw boss key skip", FW_BK_SKIP_B, "in main room of fw, near warp pot, about to store morth pit chest"},
            {"kalle demos", KALLE_DEMOS_B, "kalle demos boss fight"},
            {"placing pearls", PEARLS_B, "outside fh for swim to eti/nti"},
            {"islet of steel swim", IOS_SWIM_B, "at nti, about to swim to islet of steel"},
            {"windfall swim", WINDFALL_SWIM_B, "at greatfish, about to swim to windfall for bombs"},
            {"ropes 2", ROPES_2_B, "inside pirate ship, about to get bombs"},
            {"nayru's pearl", NAYRUS_PEARL_B, "on windfall docks, about to swim to outset for nayru's pearl"},
            {"enter tower of the gods", ENTER_TOTG_B, "outside jabun's cave, about to swim to sti"},
            {"tower of the gods", TOTG_B, "entrance of tower of the gods"},
            {"totg second statue", TOTG_STATUE_2_B, "inside totg second statue room"},
            {"totg miniboss", TOTG_MINI_B, "darknut miniboss fight"},
            {"totg third statue", TOTG_STATUE_3_B, "in the room before the third totg statue"},
            {"gohdan", GOHDAN_B, "gohdan boss fight"},
            {"puzzle skip", PUZZLE_SKIP_B, "inside hyrule castle for puzzle skip"},
            {"hyrule escape", HYRULE_ESCAPE_B, "inside hyrule castle after master sword for hyrule escape"},
            {"forsaken fortress 2 swim", FF2_SWIM_ADV_B, "on beedle's boat, about to get storage for ff2 swim"},
            {"forsaken fortress 2 swim [alt]", FF2_SWIM_EZ_B, "on nti, about to swim to ff2"},
            {"phantom ganon", PHANTOM_GANON_B, "phantom ganon miniboss fight"},
            {"enter helmaroc", ENTER_HELM_B, "after phantom ganon fight for chest storage climb"},
            {"helmaroc", HELM_B, "at the top of ff2 tower, about to start the helmaroc fight"},
            {"barrier skip", BARRIER_SKIP_B, "outside hyrule castle, about to do barrier skip"},
            {"trials skip", TRIALS_SKIP_B, "inside ganon's tower, about to do trials skip"},
            {"puppet ganon fight", PG_FIGHT_B, "inside ganondorf\'s bedroom, at start of puppet ganon fight"},
            {"morth hover", MORTH_HOVER_B, "at the top of ganondorf\'s bedroom for morth hover"},
            {"ganondorf", GANONDORF_B, "on top of ganondorf\'s tower, at start of ganondorf fight"}} {}

BeginnerSavesMenu::~BeginnerSavesMenu() {}

void BeginnerSavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special BeginnerSpecials[] = {
            special(FOREST_OF_FAIRIES_B, SaveMngSpecial_SetLayer0),
            special(ROPES_1_B, SaveMngSpecial_SetLayer0),
            special(WINDFALL_B, SaveMngSpecial_SetLayer0),
            special(ZEPHOS_SKIP_B, SaveMngSpecial_BombsSwim_FHSwim_NoMSS),
            special(PLATFORM_CHEST_B, SaveMngSpecial_BombIslandPlatform_B),
            special(DB_SKIP_B, SaveMngSpecial_DeliveryBagSkip_B),
            special(DRC_CHEST_B, SaveMngSpecial_DRCChestStorage_B),
            special(DRC_CLIMB_B, SaveMngSpecial_DRCClimb_B),
            special(FW_KEY_SKIP_B, SaveMngSpecial_FWSmallKeySkip_B),
            special(HYRULE_ESCAPE_B, SaveMngSpecial_HyruleEscape_AD),
            special(FF2_SWIM_ADV_B, SaveMngSpecial_FF2SwimAdvanced),
            special(PHANTOM_GANON_B, SaveMngSpecial_PhantomGanon_AD),
            special(HELM_B, SaveMngSpecial_Helmaroc),
            special(PG_FIGHT_B, SaveMngSpecial_PuppetGanon),
            special(MORTH_HOVER_B, SaveMngSpecial_GanonHover),
            special(GANONDORF_B, SaveMngSpecial_Ganondorf),
        };

        SaveManager::triggerLoad(cursor.y, "beginner", BeginnerSpecials,
                                 sizeof(BeginnerSpecials) / sizeof(BeginnerSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}