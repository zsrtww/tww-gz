#include "menus/menu_ad_saves/include/all_dungeons_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC AllDungeonsSavesMenu::AllDungeonsSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"manual superswim", MSS_AD, "after intro at bottom of tower"},
          {"post manual superswim", PMSS_AD, "after mss at dri"},
          {"forsaken fortress 1 chest storage", FF1_CS_AD, "ff1 in yellow rupee chest room"},
          {"windfall", WINDFALL_AD, "at windfall, after ff1 cutscene for sail/tuner/gfcs"},
          {"ropes 2", ROPES_2_AD, "in pirate ship, ropes 2 state"},
          {"forest haven swim", FH_SWIM_AD, "at windfall for swim to forest haven"},
          {"early leaf hover", EARLY_LEAF_HOVER_AD, "outside forest haven for hover to higher entrance"},
          {"deku tree cutscene skip", DEKU_TREE_CS_AD, "inside forest haven upper spawn for cutscene skip"},
          {"forbidden woods", FORBIDDEN_WOODS_AD, "start of forbidden woods"},
          {"kalle demos", KALLE_DEMOS_AD, "kalle demos boss fight"},
          {"enter dragon roost cavern", ENTER_DRC_AD, "outside forest haven for swim to eti/dri"},
          {"dragon roost cavern", DRC_AD, "start of drc"},
          {"drc miniboss", DRC_MB_AD, "outside area of drc"},
          {"drc boss key skip", DRC_BKS_AD, "inside drc in boss door room for bk skip"},
          {"gohma", GOHMA_BOSS_AD, "gohma boss fight"},
          {"nayru's pearl", NAYRUS_PEARL_AD, "at dri after drc for balloon swim to outset"},
          {"enter tower of the gods", ENTER_TOTG_AD, "outside jabuun's cave for swim to sti/nti"},
          {"tower of the gods", TOTG_AD, "start of totg"},
          {"darknut", DARKNUT_AD, "darknut miniboss"},
          {"totg third statue", TOTG_AFTER_STATUE2_AD, "totg after returning second statue"},
          {"gohdan", GOHDAN_BOSS_AD, "gohdan boss fight"},
          {"puzzle skip", PUZZLE_SKIP_AD, "inside hyrule castle for puzzle skip"},
          {"hyrule escape", HYRULE_ESCAPE_AD, "inside hyrule castle after master sword for hyrule escape"},
          {"barrier skip", BARRIER_SKIP_AD, "outside hyrule castle for barrier skip"},
          {"trial skip", TRIAL_SKIP_AD, "inside ganon's tower, in trials room for trials skip"},
          {"boomerang skip", BOOMERANG_SKIP_AD, "in phantom ganon's room for boomerang skip"},
          {"phantom ganon", PHANTOM_GANON_AD, "phantom ganon fight miniboss"},
          {"enter helmaroc", ENTER_HELM_AD, "after phantom ganon fight for chest storage climb"},
          {"hyrule 2 skip", HYRULE2_SKIP_AD, "in helm boss fight for ems cutscene skip"},
          {"early wind god's aria", EARLY_WGA_AD, "at windfall after ff2 for swim to gale isle"},
          {"power bracelets", FIRE_MOUNTAIN_AD, "at fire mountain for power braclets"},
          {"early earth temple", EARLY_ET_AD, "at headstone for early earth temple"},
          {"earth temple", ET_AD, "start of earth temple"},
          {"song stone skip", SONGTONE_SKIP_AD, "in earth temple in song stone room"},
          {"jalhalla", JALHALLA_AD, "jalhalla boss fight"},
          {"iron boots", ICE_RING_AD, "at headstone for swim to ice ring for iron boots"},
          {"makar", MAKAR_AD, "at ice ring for swim to forest haven for makar"},
          {"enter wind temple", ENTER_WT_AD, "at forest haven for balloon swim to gale isle"},
          {"wind temple", WT_AD, "start of wind temple"},
          {"wizzrobe", WIZZROBE_AD, "wizzrobe miniboss"},
          {"after hookshot", AFTER_HS_AD, "wind temple after hookshot"},
          {"molgera", MOLGERA_AD, "molgera boss fight"},
          {"swim to flight control platform", SWIM_2_FCP_AD, "at gale isle for swim to flight control platform"},
          {"fcp layer manip", FCP_LAYER_MANIP_AD, "at flight control platform for layer manip dark portal"},
          {"puppet ganon cutscene skip", PG_CS_AD, "in grand staircase for puppet ganon cutscene skip"},
          {"puppet ganon skip", PG_SKIP_AD, "in puppet ganon room on layer 8 for puppet ganon skip"},
          {"puppet ganon", PUPPET_GANON_AD, "puppet ganon fight if not doing pg skip"},
          {"ganondorf", GANONDORF_AD, "ganondorf boss fight"},
      } {}

AllDungeonsSavesMenu::~AllDungeonsSavesMenu() {}

void AllDungeonsSavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special AllDungeonsSpecials[] = {
            special(FF1_CS_AD, SaveMngSpecial_FF1CS_AD),
            special(WINDFALL_AD, SaveMngSpecial_SetLayer0),
            special(ROPES_2_AD, SaveMngSpecial_SetLayer2),
            special(EARLY_LEAF_HOVER_AD, SaveMngSpecial_EarlyLeafHover_AD),
            special(DEKU_TREE_CS_AD, SaveMngSpecial_DTCS_AD),
            special(KALLE_DEMOS_AD, SaveMngSpecial_KalleDemos_AD),
            special(ENTER_DRC_AD, SaveMngSpecial_EnterDRC_AD),
            special(DRC_MB_AD, SaveMngSpecial_DRCMiniboss_AD),
            special(DRC_BKS_AD, SaveMngSpecial_DRCBossKeySkip_AD),
            special(NAYRUS_PEARL_AD, SaveMngSpecial_NayrusPearl_AD),
            special(ENTER_TOTG_AD, SaveMngSpecial_EnterTOTG_AD),
            special(TOTG_AD, SaveMngSpecial_TOTG_AD),
            special(DARKNUT_AD, SaveMngSpecial_Darknut_AD),
            special(TOTG_AFTER_STATUE2_AD, SaveMngSpecial_AfterStatue2_AD),
            special(HYRULE_ESCAPE_AD, SaveMngSpecial_HyruleEscape_AD),
            special(BARRIER_SKIP_AD, SaveMngSpecial_BarrierSkip_AD),
            special(TRIAL_SKIP_AD, SaveMngSpecial_TrialsSkip_AD),
            special(BOOMERANG_SKIP_AD, SaveMngSpecial_BoomerangSkip_AD),
            special(PHANTOM_GANON_AD, SaveMngSpecial_PhantomGanon_AD),
            special(ENTER_HELM_AD, SaveMngSpecial_EnterHelmaroc_AD),
            special(HYRULE2_SKIP_AD, SaveMngSpecial_Hyrule2Skip_AD),
            special(FIRE_MOUNTAIN_AD, SaveMngSpecial_FireMountain_AD),
            special(EARLY_ET_AD, SaveMngSpecial_EarlyET_AD),
            special(ET_AD, SaveMngSpecial_ET_AD),
            special(SONGTONE_SKIP_AD, SaveMngSpecial_SongstoneSkip_AD),
            special(JALHALLA_AD, SaveMngSpecial_Jalhalla_AD),
            special(ICE_RING_AD, SaveMngSpecial_IceRing_AD),
            special(MAKAR_AD, SaveMngSpecial_Makar_AD),
            special(ENTER_WT_AD, SaveMngSpecial_EnterWT_AD),
            special(WT_AD, SaveMngSpecial_WT_AD),
            special(WIZZROBE_AD, SaveMngSpecial_Wizzrobe_AD),
            special(AFTER_HS_AD, SaveMngSpecial_AfterHS_AD),
            special(SWIM_2_FCP_AD, SaveMngSpecial_Swim2FCP_AD),
            special(PG_SKIP_AD, SaveMngSpecial_PGSkip_AD),
            special(PUPPET_GANON_AD, SaveMngSpecial_PuppetGanon),
        };

        SaveManager::triggerLoad(cursor.y, "all_dungeons", AllDungeonsSpecials,
                                 sizeof(AllDungeonsSpecials) / sizeof(AllDungeonsSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}