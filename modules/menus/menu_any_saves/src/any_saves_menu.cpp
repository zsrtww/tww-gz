#include "menus/menu_any_saves/include/any_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AnySavesMenu::AnySavesMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"manual superswim", MSS, "just after the intro, at bottom of watchtower"},
                        {"post manual superswim", POST_MSS, "after mss at DRI"},
                        {"ff1 exterior", FF1O, "at FF1 after leaving jail cell"},
                        {"forsest haven swim", BOMBS_ANY, "at windfall island, post FF1 cutscene"},
                        {"ropes 2", ROPES_2_ANY, "inside pirate ship, ropes 2 minigame state"},
                        {"forest haven swim", FH_SWIM_ANY, "at windfall island post bombs for swim to forest haven"},
                        {"deku tree cutscene skip", DTCS_ANY, "inside forest haven for first time, for dtcs"},
                        {"leaf hover", LEAF_HOVER, "inside forest haven, after dtcs with leaf spawned"},
                        {"quiver swim", QUIVER_FF2, "outside forest haven, quiver swim"},
                        {"ff2 swim", FF2_SWIM_ANY, "at thorned fairy island, ff2 swim assuming you got quiver"},
                        {"helmaroc skip", HELM_SKIP, "inside ff2 tower, at start of helmaroc king fight"},
                        {"barrier skip", BARRIER_SKIP_ANY, "outside hyrule castle, about to do barrier skip"},
                        {"trials skip", TRIALS_SKIP_ANY, "inside ganon's tower, in trials room for trials skip"},
                        {"puppet ganon fight", PG_FIGHT_ANY,
                         "bottom of ganondorf\'s bedroom, at start of puppet ganon fight"},
                        {"morth hover", MORTH_HOVER_ANY, "inside ganondorf\'s bedroom after fight, at top of room"},
                        {"ganondorf", GANONDORF_ANY, "on top of ganondorf\'s tower, at start of ganondorf fight"},
                    } {}

AnySavesMenu::~AnySavesMenu() {}

void AnySavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special AnySpecials[] = {
            special(BOMBS_ANY, SaveMngSpecial_SetLayer0),
            special(ROPES_2_ANY, SaveMngSpecial_SetLayer2),
            special(DTCS_ANY, SaveMngSpecial_DTCS),
            special(LEAF_HOVER, SaveMngSpecial_LeafHover),
            special(QUIVER_FF2, SaveMngSpecial_PostLeafHover),
            special(FF2_SWIM_ANY, SaveMngSpecial_ExitThornedFairy),
            special(HELM_SKIP, SaveMngSpecial_Helmaroc),
            special(BARRIER_SKIP_ANY, SaveMngSpecial_BarrierSkip),
            special(TRIALS_SKIP_ANY, SaveMngSpecial_TrialsSkip),
            special(PG_FIGHT_ANY, SaveMngSpecial_PuppetGanon),
            special(MORTH_HOVER_ANY, SaveMngSpecial_MorthHover),
            special(GANONDORF_ANY, SaveMngSpecial_Ganondorf),
        };

        SaveManager::triggerLoad(cursor.y, "any_percent", AnySpecials, sizeof(AnySpecials) / sizeof(AnySpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}