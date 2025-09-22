#include "menus/menu_pst_saves/include/pst_saves_menu.h"
#include "gz_flags.h"
#include "save_specials.h"
#include "save_manager.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC PSTSavesMenu::PSTSavesMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"manual superswim", MSS_PST, "after intro at bottom of tower"},
          {"early diamond steppe", EARLY_DIAMOND_STEPPE_PST, "after mss at bottom of tower at outset"},
          {"forsaken fortress 1 swim", FF1_SWIM_PST, "outside diamond steppe, about to swim to nfi submarine"},
          {"forsaken fortress 1 chest storage", FF1_CS_PST, "ff1 in yellow rupee chest room"},
          {"greatfish swim", GREATFISH_SWIM_PST, "at windfall after getting sail for swim to greatfish"},
          {"wallet swim", WALLET_PST, "at greatfish after the cutscene for swim to nfi"},
          {"ropes 2", ROPES_2_PST, "in pirate ship, ropes 2 state"},
          {"forest haven swim", FH_SWIM_PST, "at windfall for swim to forest haven"},
          {"early leaf hover", EARLY_LEAF_HOVER_PST, "outside forest haven for hover to higher entrance"},
          {"deku tree cutscene skip", DEKU_TREE_CS_PST, "inside forest haven upper spawn for cutscene skip"},
          {"forbidden woods", FORBIDDEN_WOODS_PST, "start of forbidden woods"},
          {"kalle demos", KALLE_DEMOS_PST, "kalle demos boss fight"},
          {"enter dragon roost cavern", ENTER_DRC_PST, "outside forest haven for swim to eti/dri"},
          {"dragon roost cavern", DRC_PST, "start of drc"},
          {"dragon roost cavern miniboss", DRC_MB_PST, "outside area of drc"},
          {"gohma", GOHMA_BOSS_PST, "gohma boss fight"},
          {"bird\'s peak rock", BPR_PST, "at dri after pearl cutscene for swim to bpr"},
          {"ghost ship 1", GHOST_SHIP_1_PST, "at windfall for swim to crescent moon ghost ship"},
          {"placing din\'s pearl, islet swim, golden gunboat", NTI_IOS_GOLDEN_BOAT_PST,
           "at windfall for swim to nti/ios/golden gunboat"},
          {"nayru's pearl", NAYRUS_PEARL_PST, "at needle rock isle for swim to outset for nayru's pearl"},
          {"enter tower of the gods", ENTER_TOTG_PST, "outside jabun's cave for swim to sti"},
          {"tower of the gods", TOTG_PST, "start of totg"},
          {"darnut", DARKNUT_PST, "totg darknut miniboss"},
          {"gohdan", GOHDAN_BOSS_PST, "gohdan boss fight"},
          {"puzzle skip", PUZZLE_SKIP_PST, "inside hyrule castle for puzzle skip"},
          {"hyrule escape", HYRULE_ESCAPE_PST, "inside hyrule castle after master sword for hyrule escape"},
          {"cyclos", CYCLOS_PST, "outside totg for sail to nti for cyclos"},
          {"forsaken fortress 2 swim", FF_SWIM_PST, "at tingle island near tingle for swim to ff2"},
          {"phantom ganon", PHANTOM_GANON_PST, "phantom ganon fight miniboss"},
          {"enter helmaroc", ENTER_HELM_PST, "after phantom ganon fight for chest storage climb"},
          {"helmaroc skip", HELM_SKIP_PST, "in helmaroc boss fight for helmaroc skip"},
          {"early wind god\'s aria", EARLY_WGA_PST, "inside mother and child after hyrule 2 for early wga"},
          {"power bracelets", POWER_BRACELETS_PST, "at gale isle for swim to fire mountain"},
          {"earth god's lyrics", EGL_PST, "at shark isle for swim to headstone"},
          {"stonewatcher", STONEWATCHER_PST, "at headstone for swim to stonewatcher"},
          {"ghost ship 2", GHOST_SHIP_2_PST, "at stonewatcher for swim to diamond steppe ghost ship"},
          {"needle rock chart", NEEDLE_ROCK_PST, "in diamond steppe quadrant for sailing to needle rock"},
          {"medli", MEDLI_PST, "at dri for chest storage to medli"},
          {"eastern triangle island swim", EFI_GREATFISH_PST, "ar dri after getting medli for swim to efi/greatfish"},
          {"earth temple swim", ET_SWIM_PST, "at greatfish for swim to earth temple"},
          {"earth temple", EARTH_TEMPLE_PST, "start of earth temple"},
          {"mirror shield", MIROR_SHIELD_PST, "in earth temple in the shortcut room for zh to miniboss"},
          {"song stone skip", SONGSTONE_SKIP_PST, "in earth temple in song stone room"},
          {"jalhalla", JALHALLA_PST, "jalhalla boss fight"},
          {"makar", MAKAR_PST, "at headstone, about to get makar"},
          {"iron boots", ICE_RING_PST, "at forest haven after getting makar for swim to ice ring"},
          {"wind temple", WT_PST, "start of wind temple"},
          {"wizzrobe miniboss", WIZZROBE_PST, "wizzrobe miniboss fight"},
          {"after hookshot", AFTER_HS_PST, "in wind temple after miniboss"},
          {"molgera", MOLGERA_PST, "molgera boss fight"},
          {"overlook", OVERLOOK_PST, "at gale isle for swim to overlook"},
          {"private oasis", PRIVATE_OASIS_PST, "at private oasis for chets storage early cabana"},
          {"gale isle", GALE_ISLE_PST, "at tingle island for swim to gale isle"},
          {"savage labyrinth", SAVAGE_PST, "start of savage labyrinth"},
          {"savage labyrinth floor 10", SAVAGE_10_PST, "in first savage labyrinth break floor"},
          {"savage labyrinth floor 20", SAVAGE_20_PST, "in second savage labyrinth break floor"},
          {"triforce", TRIFORCE_PST, "at tingle island for salvaging the last 3 triforce shards"},
          {"hyrule darknuts", HYRULE_DARKNUTS_PST, "in master sword chamber for darknut fight"},
          {"barrier cutscene skip", BARRIER_CS_PST, "outside hyrule castle for barrier cutscene skip"},
          {"trials skip", TRIALS_SKIP_PST, "inside ganon's tower, in trials room for trials skip"},
          {"puppet ganon", PUPPET_GANON_PST, "puppet ganon boss fight"},
          {"ganondorf", GANONDORF_PST, "ganondorf boss fight"},

      } {}

PSTSavesMenu::~PSTSavesMenu() {}

void PSTSavesMenu::draw() {
    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        special PSTSpecials[] = {
            special(GREATFISH_SWIM_PST, SaveMngSpecial_Greatfish_PST),
            special(EARLY_LEAF_HOVER_PST, SaveMngSpecial_EarlyLeafHover),
            special(FORBIDDEN_WOODS_PST, SaveMngSpecial_ForbiddenWoods_PST),
            special(KALLE_DEMOS_PST, SaveMngSpecial_KalleDemos_AD),
            special(ENTER_DRC_PST, SaveMngSpecial_EnterDRC_PST),
            special(DRC_PST, SaveMngSpecial_DRC_PST),
            special(HYRULE_ESCAPE_PST, SaveMngSpecial_HyruleEscape_AD),
            special(FF_SWIM_PST, SaveMngSpecial_Tingle_PST),
            special(PHANTOM_GANON_PST, SaveMngSpecial_PhantomGanon_AD),
            special(ENTER_HELM_PST, SaveMngSpecial_EnterHelmaroc_PST),
            special(HELM_SKIP_PST, SaveMngSpecial_Helmaroc),
            special(MIROR_SHIELD_PST, SaveMngSpecial_MirorShield_PST),
            special(SONGSTONE_SKIP_PST, SaveMngSpecial_SongStoneSkip_PST),
            special(GALE_ISLE_PST, SaveMngSpecial_Tingle_PST),
            special(TRIFORCE_PST, SaveMngSpecial_Tingle_PST),
            special(PUPPET_GANON_PST, SaveMngSpecial_PuppetGanon),
        };

        SaveManager::triggerLoad(cursor.y, "pst", PSTSpecials, sizeof(PSTSpecials) / sizeof(PSTSpecials[0]));
        g_menuMgr->hide();
    }

    cursor.move(0, sizeof(lines) / sizeof(lines[0]));
    GZ_drawMenuLines(lines, cursor.y, sizeof(lines) / sizeof(lines[0]));
}