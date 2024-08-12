#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/com/d_com_static.h"

#include "flags.h"
#include "save_manager.h"
#include "save_specials.h"
#include "rels/include/defines.h"

// =================== UTILITIES ===================

inline void SaveMngSpecial_SetHealth(u16 health) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(health);
}

inline void SaveMngSpecial_SetMagic(u8 magic) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(magic);
}

inline void SaveMngSpecial_SetBombCount(u8 bombs) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(bombs);
}

// =================== GENERIC FUNCTIONS ===================

KEEP_FUNC void SaveMngSpecial_SetLayer0() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(0);
}

KEEP_FUNC void SaveMngSpecial_SetLayer1() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
}

KEEP_FUNC void SaveMngSpecial_SetLayer2() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(2);
}

KEEP_FUNC void SaveMngSpecial_SetLayer3() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(3);
}

// =================== SHARED FUNCTIONS ===================

KEEP_FUNC void SaveMngSpecial_DTCS() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

KEEP_FUNC void SaveMngSpecial_LeafHover() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(6);

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetBombCount(20);
        SaveMngSpecial_SetHealth(1);
    });
}

KEEP_FUNC void SaveMngSpecial_PostLeafHover() {
    gSaveManager.injectDefault_after();

    gSaveManager.modifySave([]() { SaveMngSpecial_SetBombCount(19); });
}

KEEP_FUNC void SaveMngSpecial_ExitThornedFairy() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetBombCount(19); });
}

KEEP_FUNC void SaveMngSpecial_BarrierSkip() {
    SaveMngSpecial_SetLayer2();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"Hyrule");
    g_dComIfG_gameInfo.play.mNextStage.setPoint(3);

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(6);
        SaveMngSpecial_SetBombCount(19);
    });
}

KEEP_FUNC void SaveMngSpecial_TrialsSkip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(1);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(6);
        SaveMngSpecial_SetBombCount(17);
    });
}

KEEP_FUNC void SaveMngSpecial_PuppetGanon() {
    SaveMngSpecial_SetLayer1();
    daArrow_c__m_keep_type = 3;

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(10);
        SaveMngSpecial_SetBombCount(17);
    });
}

KEEP_FUNC void SaveMngSpecial_MorthHover() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(2);
    SaveMngSpecial_SetLayer1();
    daArrow_c__m_keep_type = 3;

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(1);
        SaveMngSpecial_SetMagic(8);
        SaveMngSpecial_SetBombCount(12);
    });
}

KEEP_FUNC void SaveMngSpecial_Ganondorf() {
    SaveMngSpecial_SetLayer1();

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(4);
        SaveMngSpecial_SetBombCount(10);
    });
}

// =================== ANY% FUNCTIONS ===================

KEEP_FUNC void SaveMngSpecial_LightArrowSkip_Any() {
    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetBombCount(17);
        SaveMngSpecial_SetHealth(6);
        SaveMngSpecial_SetMagic(6);
    });
}

KEEP_FUNC void SaveMngSpecial_PGCutsceneSkip_Any() {
    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetBombCount(16);
        SaveMngSpecial_SetHealth(6);
        SaveMngSpecial_SetMagic(10);
    });
}

KEEP_FUNC void SaveMngSpecial_PGSkip_Any() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(8);

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetBombCount(15);
        SaveMngSpecial_SetHealth(1);
        SaveMngSpecial_SetMagic(13);
    });
}

// =================== ANY% NO MSS FUNCTIONS ===================

KEEP_FUNC void SaveMngSpecial_BombsSwim_NoMSS() {
    SaveMngSpecial_SetLayer0();

    // TODO replace with actor mod system later when it exists
    fopAc_ac_c* ship_p = g_dComIfG_gameInfo.play.mpPlayerPtr[2];

    if (ship_p != nullptr) {
        // set KorL's pos and angle to be the same as when the Wind Waker cutscene ends
        ship_p->current.pos.set(196459.0f, 0.0f, -199693.0f);
        ship_p->current.angle.y = ship_p->shape_angle.y = 0x623E;
    }
}

// =================== ALL DUNGEONS FUNCTIONS ===================

KEEP_FUNC void SaveMngSpecial_FF1CS_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"majroom");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(4);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

KEEP_FUNC void SaveMngSpecial_EarlyLeafHover_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(4); });
}

KEEP_FUNC void SaveMngSpecial_DTCS_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

KEEP_FUNC void SaveMngSpecial_KalleDemos_AD() {
    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(7);
        SaveMngSpecial_SetMagic(16);
    });
}

KEEP_FUNC void SaveMngSpecial_EnterDRC_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetBombCount(15);
        SaveMngSpecial_SetHealth(6);
        SaveMngSpecial_SetMagic(16);
    });
}

KEEP_FUNC void SaveMngSpecial_DRCMiniboss_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"M_Dra09");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(9);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

KEEP_FUNC void SaveMngSpecial_DRCBossKeySkip_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(10);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_NayrusPearl_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(212);
}

KEEP_FUNC void SaveMngSpecial_EnterTOTG_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(9);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(10); });
}

KEEP_FUNC void SaveMngSpecial_TOTG_AD() {
    gSaveManager.injectDefault_during();
    SaveMngSpecial_SetHealth(10);
}

KEEP_FUNC void SaveMngSpecial_Darknut_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"SirenMB");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(23);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_AfterStatue2_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(8);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetMagic(8); });
}

KEEP_FUNC void SaveMngSpecial_HyruleEscape_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"Hyroom");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(0);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(2);
}

KEEP_FUNC void SaveMngSpecial_BarrierSkip_AD() {
    SaveMngSpecial_SetLayer0();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"Hyrule");
    g_dComIfG_gameInfo.play.mNextStage.setPoint(3);
}

KEEP_FUNC void SaveMngSpecial_BoomerangSkip_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_PhantomGanon_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(15);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(6); });
}

KEEP_FUNC void SaveMngSpecial_EnterHelmaroc_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(15);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(2); });
}

KEEP_FUNC void SaveMngSpecial_Hyrule2Skip_AD() {
    SaveMngSpecial_SetLayer3();

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(2); });
}

KEEP_FUNC void SaveMngSpecial_FireMountain_AD() {
    gSaveManager.injectDefault_during();
    daArrow_c__m_keep_type = 2;
}

KEEP_FUNC void SaveMngSpecial_EarlyET_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
    daArrow_c__m_keep_type = 2;
}

KEEP_FUNC void SaveMngSpecial_ET_AD() {
    gSaveManager.injectDefault_during();
    daArrow_c__m_keep_type = 2;
}

KEEP_FUNC void SaveMngSpecial_SongstoneSkip_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(9);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(11);
    daArrow_c__m_keep_type = 3;
}

KEEP_FUNC void SaveMngSpecial_Jalhalla_AD() {
    gSaveManager.injectDefault_during();
    daArrow_c__m_keep_type = 3;
}

KEEP_FUNC void SaveMngSpecial_IceRing_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
    daArrow_c__m_keep_type = 3;

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(2); });
}

KEEP_FUNC void SaveMngSpecial_Makar_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_EnterWT_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(9);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_WT_AD() {
    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_Wizzrobe_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"kazeMB");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(6);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_AfterHS_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(2);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(20);
}

KEEP_FUNC void SaveMngSpecial_Swim2FCP_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"sea");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(4);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

KEEP_FUNC void SaveMngSpecial_TrialsSkip_AD() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(1);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_PGSkip_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(8);
}