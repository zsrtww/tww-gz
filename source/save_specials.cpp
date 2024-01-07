#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/com/d_com_static.h"

#include "flags.h"
#include "save_manager.h"
#include "save_specials.h"

void SaveMngSpecial_ForestOfFairies_FirstVisit() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(0);
}

void SaveMngSpecial_Ropes1() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(0);
}

void SaveMngSpecial_Ropes2() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(2);
}

void SaveMngSpecial_FF1_PirateShip_Night() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(-1);
}

void SaveMngSpecial_Windfall_Day0() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(0);
}

void SaveMngSpecial_DTCS() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

void SaveMngSpecial_ExitThornedFairy() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

void SaveMngSpecial_HelmarocKing() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(3);
}

void SaveMngSpecial_Hyrule2_BarrierSkip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "Hyrule");
    g_dComIfG_gameInfo.play.mNextStage.setPoint(3);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(2);
}

void SaveMngSpecial_Hyrule2_BarrierSkip_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(6);
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(19);
}


void SaveMngSpecial_TrialsSkip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(1);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

void SaveMngSpecial_TrialsSkip_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(6);
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(17);
}

void SaveMngSpecial_PuppetGanon() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
    daArrow_c__m_keep_type = 3;
}

void SaveMngSpecial_PuppetGanon_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(10);
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(17);
}

void SaveMngSpecial_MorthHover_during() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(2);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
    daArrow_c__m_keep_type = 3;
}

void SaveMngSpecial_MorthHover_after() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(1);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(8);
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(12);
}

void SaveMngSpecial_Ganondorf() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
}

void SaveMngSpecial_Ganondorf_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(4);
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(10);
}

void SaveMngSpecial_LeafHover() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(6);
}

void SaveMngSpecial_LeafHover_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(20);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(1);
}

void SaveMngSpecial_QuiverAny_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(19);
}

void SaveMngSpecial_LightArrowSkip_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(17);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(6);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(6);
}

void SaveMngSpecial_PGCutsceneSkip_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(16);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(6);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(10);
}

void SaveMngSpecial_PGSkip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(8);
}

void SaveMngSpecial_PGSkip_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(15);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(1);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(13);
}

void SaveMngSpecial_FF1_CS_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "majroom");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(4);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

void SaveMngSpecial_Early_Leaf_Hover_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

void SaveMngSpecial_Early_Leaf_Hover_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(4);
}

void SaveMngSpecial_Deku_Tree_CS_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

void SaveMngSpecial_Kalle_Demons_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(7);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(16);
}

void SaveMngSpecial_Enter_DRC_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

void SaveMngSpecial_Enter_DRC_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(15);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(6);
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(16);
}

void SaveMngSpecial_DRC_MB_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "M_Dra09");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(9);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

void SaveMngSpecial_DRC_BKS_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(10);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

void SaveMngSpecial_Nayrus_Pearl_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(212);
}

void SaveMngSpecial_Enter_TOTG_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(9);
}

void SaveMngSpecial_Enter_TOTG_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(10);
}

void SaveMngSpecial_TOTG_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(10);
}

void SaveMngSpecial_Darknut_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "SirenMB");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(23);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

void SaveMngSpecial_After_Statue2_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(8);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

void SaveMngSpecial_After_Statue2_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(8);
}

void SaveMngSpecial_Hyrule_Escape_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "Hyroom");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(0);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(2);
}

void SaveMngSpecial_Hyrule1_BarrierSkip_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "Hyrule");
    g_dComIfG_gameInfo.play.mNextStage.setPoint(3);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(0);
}

void SaveMngSpecial_Boomerang_Skip_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

void SaveMngSpecial_Phantom_Ganon_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(15);
}

void SaveMngSpecial_Phantom_Ganon_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(6);
}

void SaveMngSpecial_Enter_Helm_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(2);
}

void SaveMngSpecial_Hyrule2_Skip_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(2);
}

void SaveMngSpecial_FireMountain_AD() {
    gSaveManager.injectDefault_during();
    daArrow_c__m_keep_type = 2;
}

void SaveMngSpecial_Early_ET_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
    daArrow_c__m_keep_type = 2;
}

void SaveMngSpecial_ET_AD() {
    gSaveManager.injectDefault_during();
    daArrow_c__m_keep_type = 2;
}

void SaveMngSpecial_Songstone_Skip_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(9);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(11);
    daArrow_c__m_keep_type = 3;
}

void SaveMngSpecial_Jalhalla_AD() {
    gSaveManager.injectDefault_during();
    daArrow_c__m_keep_type = 3;
}

void SaveMngSpecial_IceRing_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
    daArrow_c__m_keep_type = 3;
}

void SaveMngSpecial_IceRing_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(2);
}

void SaveMngSpecial_Makar_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

void SaveMngSpecial_Makar_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(1);
}

void SaveMngSpecial_Enter_WT_AD_During() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(9);
}

void SaveMngSpecial_Enter_WT_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(1);
}

void SaveMngSpecial_WT_AD_After() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(1);
}

void SaveMngSpecial_Wizzrobe_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "kazeMB");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(6);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

void SaveMngSpecial_After_HS_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(2);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(20);
}

void SaveMngSpecial_Swim_2_FCP_AD() {
    gSaveManager.injectDefault_during();
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*) "sea");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(4);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}
