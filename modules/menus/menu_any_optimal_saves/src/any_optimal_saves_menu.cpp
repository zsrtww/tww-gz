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
                        {"forest haven climb", FH_CLIMB, "outside forest haven with door cancel"},
                        {"deku tree cutscene skip", DTCS, "inside forest haven at top, for dtcs"},
                        {"greatfish cutscene skip", GFCS, "at windfall cove after leaf for gfcs"},
                        {"sail skip", SAIL_SKIP, "in windfall quadrant in korl, aster gfcs for sail skip"},
                        {"ropes 2", ROPES_2, "inside pirate ship for bombs"},
                        {"door cancel ff2", DC_FF2, "at windfall docks after bombs for door cancel ff2"},
                        {"helmaroc skip", HELM_SKIP, "inside ff2 tower, at start of helmaroc king fight"},
                        {"barrier skip", BARRIER_SKIP, "outside hyrule castle, about to do barrier skip"},
                        {"trials skip", TRIAL_SKIP, "inside ganon's tower, in trials room for trials skip"},
                        {"light arrow skip", LA_SKIP, "in phantom ganon room for light arrow skip with tuner"},
                        {"puppet ganon cutscene skip", PGCS, "at grand staircase for puppet ganon cutscene skip"},
                        {"puppet ganon skip", PGS, "inside ganondorf\'s bedroom on lyaer 8 for pg skip with tuner"},
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
            special(FH_CLIMB, SaveMngSpecial_Outside_FH_DC),   special(HELM_SKIP, SaveMngSpecial_Helmaroc),
            special(TRIAL_SKIP, SaveMngSpecial_TrialsSkipAny), special(LA_SKIP, SaveMngSpecial_LightArrowSkip_Any),
            special(PGS, SaveMngSpecial_PGSkip_Any),
        };

        SaveManager::triggerLoad(cursor.y, "any_optimal", AnyOptimalSpecials,
                                 sizeof(AnyOptimalSpecials) / sizeof(AnyOptimalSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}