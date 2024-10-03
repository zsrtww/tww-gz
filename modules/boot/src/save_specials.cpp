#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/com/d_com_static.h"

#include "flags.h"
#include "save_manager.h"
#include "save_specials.h"
#include "libtww/include/d/d_procname.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "rels/include/defines.h"
#include "commands.h"

// =================== UTILITIES ===================

void SaveMngSpecial_SetActorPos(fopAc_ac_c* actor, f32 x, f32 y, f32 z) {
    actor->current.pos.set(x, y, z);

    if (actor->mBase.mProcName == PROC_PLAYER) {
        l_debug_keep_pos.x = x;
        l_debug_keep_pos.y = y;
        l_debug_keep_pos.z = z;
    }
}

inline void SaveMngSpecial_SetActorYaw(fopAc_ac_c* actor, s16 yRot) {
    actor->current.angle.y = actor->shape_angle.y = yRot;

    if (actor->mBase.mProcName == PROC_PLAYER) {
        l_debug_current_angle.y = l_debug_shape_angle.y = yRot;
    }
}

inline void SaveMngSpecial_SetActorRot(fopAc_ac_c* actor, s16 xRot, s16 yRot, s16 zRot) {
    actor->current.angle.set(xRot, yRot, zRot);
    actor->shape_angle.set(xRot, yRot, zRot);

    if (actor->mBase.mProcName == PROC_PLAYER) {
        l_debug_current_angle.set(xRot, yRot, zRot);
        l_debug_shape_angle.set(xRot, yRot, zRot);
    }
}

inline void SaveMngSpecial_SetHealth(u16 health) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(health);
}

inline void SaveMngSpecial_SetMagic(u8 magic) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(magic);
}

inline void SaveMngSpecial_SetBombCount(u8 bombs) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(bombs);
}

inline void SaveMngSpecial_ChestStorage(fopAc_ac_c* actor) {
    u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr = (*collision_ptr & (0xFFFF ^ 0x4000)) | 0x4;
}

inline void SaveMngSpecial_DoorCancel(fopAc_ac_c* actor) {
    u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr |= 0x4004;
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
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

KEEP_FUNC void SaveMngSpecial_LeafHover() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(6);

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetBombCount(20);
        SaveMngSpecial_SetHealth(1);
    });
}

KEEP_FUNC void SaveMngSpecial_PostLeafHover() {
    gSaveManager.modifySave([]() { SaveMngSpecial_SetBombCount(19); });
}

KEEP_FUNC void SaveMngSpecial_ExitThornedFairy() {
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
    daArrow_c__m_keep_type = 1;

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

KEEP_FUNC void SaveMngSpecial_Helmaroc() {
    SaveMngSpecial_SetLayer3();

    gSaveManager.modifyActor(PROC_PLAYER, [](fopAc_ac_c* actor) {
        SaveMngSpecial_SetActorPos(actor, 4258.2119f, 9064.7334f, -4360.8140f);
        SaveMngSpecial_SetActorYaw(actor, 0xA72A);
    });
}

KEEP_FUNC void SaveMngSpecial_Outside_FH_DC() {
    gSaveManager.modifyActor(PROC_PLAYER, [](fopAc_ac_c* actor) { SaveMngSpecial_DoorCancel(actor); });
}

// =================== ANY% FUNCTIONS ===================

KEEP_FUNC void SaveMngSpecial_TrialsSkipAny() {
    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_LightArrowSkip_Any() {
    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(1);
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

    gSaveManager.modifyActor(PROC_SHIP, [](fopAc_ac_c* actor) {
        SaveMngSpecial_SetActorPos(actor, 196459.0f, 0.0f, -199693.0f);
        SaveMngSpecial_SetActorYaw(actor, 0x623E);
    });
}

KEEP_FUNC void SaveMngSpecial_GanonHover() {
    gSaveManager.modifyActor(PROC_PLAYER, [](fopAc_ac_c* actor) {
        SaveMngSpecial_SetActorPos(actor, 546.4542f, 4476.6108f, -1.1532f);
        SaveMngSpecial_SetActorYaw(actor, 0x3FE1);
    });

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_EarlyLights_NoMSS() {
    dComIfGs_offEventBit(0x2D01);
}

// =================== ALL DUNGEONS FUNCTIONS ===================

KEEP_FUNC void SaveMngSpecial_FF1CS_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"majroom");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(4);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);
}

KEEP_FUNC void SaveMngSpecial_EarlyLeafHover_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_DTCS_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

KEEP_FUNC void SaveMngSpecial_KalleDemos_AD() {
    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetHealth(7);
        SaveMngSpecial_SetMagic(16);
    });
}

KEEP_FUNC void SaveMngSpecial_EnterDRC_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(5);

    gSaveManager.modifySave([]() {
        SaveMngSpecial_SetBombCount(15);
        SaveMngSpecial_SetHealth(6);
        SaveMngSpecial_SetMagic(16);
    });
}

KEEP_FUNC void SaveMngSpecial_DRCMiniboss_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"M_Dra09");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(9);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

KEEP_FUNC void SaveMngSpecial_DRCBossKeySkip_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(10);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_NayrusPearl_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(212);
}

KEEP_FUNC void SaveMngSpecial_EnterTOTG_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(9);

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(10); });
}

KEEP_FUNC void SaveMngSpecial_TOTG_AD() {
    SaveMngSpecial_SetHealth(10);
}

KEEP_FUNC void SaveMngSpecial_Darknut_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"SirenMB");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(23);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_AfterStatue2_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(8);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
    gSaveManager.modifySave([]() { SaveMngSpecial_SetMagic(8); });
}

KEEP_FUNC void SaveMngSpecial_HyruleEscape_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"Hyroom");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(0);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(2);

    gSaveManager.modifyActor(PROC_PLAYER, [](fopAc_ac_c* actor) {
        SaveMngSpecial_SetActorPos(actor, 349.2255f, -1549.8273f, -1697.4833f);
        SaveMngSpecial_SetActorYaw(actor, 0xD000);
    });
}

KEEP_FUNC void SaveMngSpecial_BarrierSkip_AD() {
    SaveMngSpecial_SetLayer0();
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"Hyrule");
    g_dComIfG_gameInfo.play.mNextStage.setPoint(3);
}

KEEP_FUNC void SaveMngSpecial_BoomerangSkip_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"GanonM");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(0);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_PhantomGanon_AD() {
    SaveMngSpecial_SetLayer1();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(15);
    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(6); });
}

KEEP_FUNC void SaveMngSpecial_EnterHelmaroc_AD() {
    SaveMngSpecial_SetLayer1();
    g_dComIfG_gameInfo.play.mNextStage.setPoint(15);
    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(2); });
}

KEEP_FUNC void SaveMngSpecial_Hyrule2Skip_AD() {
    SaveMngSpecial_SetLayer3();

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(2); });

    gSaveManager.modifyActor(PROC_PLAYER, [](fopAc_ac_c* actor) {
        SaveMngSpecial_SetActorPos(actor, 4258.2119f, 9064.7334f, -4360.8140f);
        SaveMngSpecial_SetActorYaw(actor, 0xA72A);
    });
}

KEEP_FUNC void SaveMngSpecial_FireMountain_AD() {
    daArrow_c__m_keep_type = 2;
}

KEEP_FUNC void SaveMngSpecial_EarlyET_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
    daArrow_c__m_keep_type = 2;
}

KEEP_FUNC void SaveMngSpecial_ET_AD() {
    daArrow_c__m_keep_type = 2;
}

KEEP_FUNC void SaveMngSpecial_SongstoneSkip_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(9);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(11);
    daArrow_c__m_keep_type = 3;
}

KEEP_FUNC void SaveMngSpecial_Jalhalla_AD() {
    daArrow_c__m_keep_type = 3;
}

KEEP_FUNC void SaveMngSpecial_IceRing_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
    daArrow_c__m_keep_type = 3;

    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(2); });
}

KEEP_FUNC void SaveMngSpecial_Makar_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_EnterWT_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_WT_AD() {
    gSaveManager.modifySave([]() { SaveMngSpecial_SetHealth(1); });
}

KEEP_FUNC void SaveMngSpecial_Wizzrobe_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"kazeMB");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(6);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_AfterHS_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(2);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(20);
}

KEEP_FUNC void SaveMngSpecial_Swim2FCP_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"sea");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(4);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(1);
}

KEEP_FUNC void SaveMngSpecial_TrialsSkip_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setName((char*)"GanonA");
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(1);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

KEEP_FUNC void SaveMngSpecial_PGSkip_AD() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(8);
}


