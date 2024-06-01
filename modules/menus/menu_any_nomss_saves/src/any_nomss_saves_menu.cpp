#include "menus/menu_any_nomss_saves/include/any_nomss_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AnyNoMssSavesMenu::AnyNoMssSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"after intro", AFTER_INTRO, "just after the intro, at bottom of watchtower"},
          {"orca", ORCA, "inside orca\'s house, about to do sword tutorial"},
          {"forest of fairies", FOREST_OF_FAIRIES,
           "inside forest of fairies, about to rescue tetra"},
          {"ropes 1", ROPES_1, "inside pirate ship, about to play ropes 1 minigame"},
          {"forsaken fortress 1", FF1, "at start of ff1, before gossip stone cutscene"},
          {"windfall", WINDFALL, "at windfall island, just finished talking to korl"},
          {"bombs swim", BOMBS_SWIM, "at dragon roost island, just got the wind waker"},
          {"ropes 2", ROPES_2, "inside pirate ship, about to play ropes 2 minigame"},
          {"forest haven swim", FH_SWIM, "at windfall island, about to swim to forest haven"},
          {"deku tree cutscene skip", DTCS, "at forest haven, about to do dtcs"},
          {"quiver swim", QUIVER_SWIM, "at forest haven, about to swim to thorned fairy island"},
          {"ff2 swim", FF2_SWIM, "at thorned fairy island, about to swim to ff2"},
          {"helmaroc skip", HELMAROC_SKIP, "inside ff2 tower, at start of helmaroc king fight"},
          {"barrier skip", BARRIER_SKIP, "outside hyrule castle, about to do barrier skip"},
          {"trials skip", TRIALS_SKIP, "inside ganon's tower, about to do trials skip"},
          {"puppet ganon fight", PG_FIGHT,
           "inside ganondorf\'s bedroom, at start of puppet ganon fight"},
          {"morth hover", MORTH_HOVER, "inside ganondorf\'s bedroom after fight, at top of room"},
          {"ganondorf", GANONDORF, "on top of ganondorf\'s tower, at start of ganondorf fight"},
      } {}

AnyNoMssSavesMenu::~AnyNoMssSavesMenu() {}

void AnyNoMssSavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special AnyNoMssSpecials[] = {
            special(FOREST_OF_FAIRIES, SaveMngSpecial_ForestOfFairies_FirstVisit, nullptr),
            special(ROPES_1, SaveMngSpecial_Ropes1, nullptr),
            special(FF1, SaveMngSpecial_FF1_PirateShip_Night, nullptr),
            special(WINDFALL, SaveMngSpecial_Windfall_Day0, nullptr),
            special(BOMBS_SWIM, SaveMngSpecial_Windfall_Day0, nullptr),
            special(ROPES_2, SaveMngSpecial_Ropes2, nullptr),
            special(FH_SWIM, SaveMngSpecial_Windfall_Day0, nullptr),
            special(DTCS, SaveMngSpecial_DTCS, nullptr),
            special(QUIVER_SWIM, nullptr, SaveMngSpecial_QuiverAny_After),
            special(FF2_SWIM, SaveMngSpecial_ExitThornedFairy, SaveMngSpecial_QuiverAny_After),
            special(HELMAROC_SKIP, SaveMngSpecial_HelmarocKing, nullptr),
            special(BARRIER_SKIP, SaveMngSpecial_Hyrule2_BarrierSkip, SaveMngSpecial_Hyrule2_BarrierSkip_After),
            special(TRIALS_SKIP, SaveMngSpecial_TrialsSkip, SaveMngSpecial_TrialsSkip_After),
            special(PG_FIGHT, SaveMngSpecial_PuppetGanon, SaveMngSpecial_PuppetGanon_After),
            special(MORTH_HOVER, SaveMngSpecial_MorthHover_during, SaveMngSpecial_MorthHover_after),
            special(GANONDORF, SaveMngSpecial_Ganondorf, SaveMngSpecial_Ganondorf_After),
        };

        SaveManager::triggerLoad(cursor.y, "any_no_mss", AnyNoMssSpecials,
                                 sizeof(AnyNoMssSpecials) / sizeof(AnyNoMssSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}