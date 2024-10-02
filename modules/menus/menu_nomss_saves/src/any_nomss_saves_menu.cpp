#include "menus/menu_nomss_saves/include/any_nomss_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AnyNoMssSavesMenu::AnyNoMssSavesMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"after intro", AFTER_INTRO, "just after the intro, at bottom of watchtower"},
                        {"orca", ORCA, "inside orca\'s house, about to do sword tutorial"},
                        {"forest of fairies", FOREST_OF_FAIRIES, "inside forest of fairies, about to rescue tetra"},
                        {"ropes 1", ROPES_1, "inside pirate ship, about to play ropes 1 minigame"},
                        {"early light cycle", EARLY_LIGHTS, "outside ship, before barrel launch cutscene"},
                        {"forsaken fortress 1", FF1, "at start of ff1 after gossip trigger"},
                        {"ff1 interior", FF1_INTERIOR, "ff1 in the rope swing room"},
                        {"windfall", WINDFALL, "at windfall island, just finished talking to korl"},
                        {"bombs swim", BOMBS_SWIM, "at dragon roost island, after wind waker cutscene"},
                        {"ropes 2", ROPES_2, "inside pirate ship, about to play ropes 2 minigame"},
                        {"forest haven swim", FH_SWIM, "at windfall island, about to swim to forest haven"},
                        {"outside forest haven", O_FH, "scaling outside forest haven with door cancel"},
                        {"lip crush cutscene skip", LIP_CRUSH, "inside forest haven at the top, for lip crush"},
                        {"deku tree chin cutscene skip*", DTCS, "inside forest haven at bottom, for normal dtcs"},
                        {"leaf hover*", LEAF_HOVER, "after normal cutscene skip for inside hover"},
                        {"quiver swim", QUIVER_SWIM, "at forest haven, about to swim to thorned fairy island"},
                        {"ff2 swim", FF2_SWIM, "at thorned fairy island, about to swim to ff2"},
                        {"helmaroc skip", HELMAROC_SKIP, "inside ff2 tower, at start of helmaroc king fight"},
                        {"barrier skip", BARRIER_SKIP, "outside hyrule castle, about to do barrier skip"},
                        {"trials skip", TRIALS_SKIP, "inside ganon's tower, about to do trials skip"},
                        {"puppet ganon fight", PG_FIGHT, "inside ganondorf\'s bedroom, at start of puppet ganon fight"},
                        {"hover to ganon", GANON_HOVER,
                         "at the top of the rope in ganondorf\'s bedroom for tuner hover"},
                        {"morth hover*", MORTH_HOVER, "inside ganondorf\'s bedroom after fight, at top of room"},
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
            special(FOREST_OF_FAIRIES, SaveMngSpecial_SetLayer0),
            special(ROPES_1, SaveMngSpecial_SetLayer0),
            special(WINDFALL, SaveMngSpecial_SetLayer0),
            special(BOMBS_SWIM, SaveMngSpecial_BombsSwim_NoMSS),
            special(ROPES_2, SaveMngSpecial_SetLayer2),
            special(FH_SWIM, SaveMngSpecial_SetLayer0),
            special(O_FH, SaveMngSpecial_Outside_FH_NoMSS),
            special(DTCS, SaveMngSpecial_DTCS),
            special(LEAF_HOVER, SaveMngSpecial_LeafHover),
            special(QUIVER_SWIM, SaveMngSpecial_PostLeafHover),
            special(FF2_SWIM, SaveMngSpecial_ExitThornedFairy),
            special(HELMAROC_SKIP, SaveMngSpecial_Helmaroc),
            special(BARRIER_SKIP, SaveMngSpecial_BarrierSkip),
            special(TRIALS_SKIP, SaveMngSpecial_TrialsSkip),
            special(PG_FIGHT, SaveMngSpecial_PuppetGanon),
            special(GANON_HOVER, SaveMngSpecial_GanonHover),
            special(MORTH_HOVER, SaveMngSpecial_MorthHover),
            special(GANONDORF, SaveMngSpecial_Ganondorf),
            special(EARLY_LIGHTS, SaveMngSpecial_EarlyLights_NoMSS),
        };

        SaveManager::triggerLoad(cursor.y, "any_no_mss", AnyNoMssSpecials,
                                 sizeof(AnyNoMssSpecials) / sizeof(AnyNoMssSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}