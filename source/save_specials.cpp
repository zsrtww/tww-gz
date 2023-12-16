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
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(8);
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

