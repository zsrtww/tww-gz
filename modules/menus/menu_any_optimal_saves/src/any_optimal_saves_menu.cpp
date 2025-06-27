#include "menus/menu_any_optimal_saves/include/any_optimal_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AnyOptimalSavesMenu::AnyOptimalSavesMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"manual superswim", MSS, "just after the intro, at bottom of watchtower"},
                        {"post manual superswim", POST_MSS, "after mss at DRI"},
                        {"ff1 exterior", FF1O, "at FF1 after leaving jail cell"},
                        {"door cancel leaf", DC_LEAF, "at windfall island, post FF1 cutscene"},
                        {"forest haven swim", FH_SWIM, "at windfall outside bomb shop with door cancel"},
                        {"forest haven climb", FH_CLIMB, "outside forest haven with door cancel"},
                        {"deku tree cutscene skip", DTCS, "inside forest haven at top, for dtcs"},
                        {"door cancel ff2", DC_FF2, "at windfall cove after leaf for door cancel ff2"},
                        {"ff2 climb", FF2_CLIMB, "outside ff2 near climbing spot with door cancel"},
                        {"helmaroc skip", HELM_SKIP, "inside ff2 tower, at start of helmaroc king fight"},
                        {"barrier skip", BARRIER_SKIP, "outside hyrule castle, about to do barrier skip"},
                        {"trials skip", TRIAL_SKIP, "inside ganon's tower, in trials room for trials skip"},
                        {"light arrow skip", LA_SKIP, "in phantom ganon room for light arrow skip with tuner"},
                        {"puppet ganon cutscene skip", PGCS, "at grand staircase for puppet ganon cutscene skip"},
                        {"puppet ganon skip", PGS, "inside ganondorf\'s bedroom on layer 8 for pg skip with tuner"},
                        {"ganondorf", GANON, "on top of ganondorf\'s tower, at start of ganondorf fight"},
                    } {}

AnyOptimalSavesMenu::~AnyOptimalSavesMenu() {}

void AnyOptimalSavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special AnyOptimalSpecials[] = {
            special(POST_MSS, SaveMngSpecial_Post_MSS),
            special(FF1O, SaveMngSpecial_FF1_Exterior),
            special(DC_LEAF, SaveMngSpecial_Door_Cancel_Leaf),
            special(FH_SWIM, SaveMngSpecial_FH_Swim),
            special(FH_CLIMB, SaveMngSpecial_Outside_FH_DC),
            special(FF2_CLIMB, SaveMngSpecial_FF2_Climb),
            special(HELM_SKIP, SaveMngSpecial_Helmaroc),
            special(TRIAL_SKIP, SaveMngSpecial_TrialsSkipAny),
            special(LA_SKIP, SaveMngSpecial_LightArrowSkip_Any),
            special(PGS, SaveMngSpecial_PGSkip_Any),
            special(BARRIER_SKIP, SaveMngSpecial_BarrierSkip_Any),
        };

        SaveManager::triggerLoad(cursor.y, "any_optimal", AnyOptimalSpecials,
                                 sizeof(AnyOptimalSpecials) / sizeof(AnyOptimalSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}