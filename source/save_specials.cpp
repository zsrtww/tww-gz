#include "libtww/d/com/d_com_inf_game.h"

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

void SaveMngSpecial_HelmarocKing() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(3);
}

void SaveMngSpecial_Hyrule2_BarrierSkip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName("Hyrule");
    g_dComIfG_gameInfo.play.mNextStage.setPoint(3);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(2);
}

void SaveMngSpecial_PuppetGanon() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
    l_equipped_arrow_type = 3;
}

void SaveMngSpecial_MorthHover_during() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(2);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
    l_equipped_arrow_type = 3;
}

void SaveMngSpecial_MorthHover_after() {
    gSaveManager.injectDefault_after();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(1);
}

void SaveMngSpecial_Ganondorf() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
}