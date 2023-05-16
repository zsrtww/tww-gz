#ifndef D_COM_D_COM_INF_GAME_H
#define D_COM_D_COM_INF_GAME_H

#include "../../addrs.h"
#include "../save/d_save.h"
#include "../bg/d_bg_s.h"
#include "../cc/d_cc_s.h"
#include "../d_stage.h"
#include "../event/d_event.h"
#include "../event/d_event_manager.h"
#include "../d_attention.h"
#include "../d_vibration.h"
#include "../d_detect.h"
#include "../d_drawlist.h"
#include "../a/d_a_player.h"

struct dTimer_c;

struct J2DGrafContext;

class __d_timer_info_c {
public:
    dTimer_c* mTimerPtr;
    s32 mTimerNowTimeMs;
    s32 mTimerLimitTimeMs;
    s32 mTimerMode;
    u8 mTimerType;
};

struct camera_class;

class dComIfG_camera_info_class {
public:
    /* 0x00 */ camera_class* mCamera;
    /* 0x04 */ u8 mDlstWindowIdx;
    /* 0x05 */ u8 mCamIdx;
    /* 0x08 */ u32 mCameraAttentionStatus;
    /* 0x0C */ float mCameraZoomScale;
    /* 0x10 */ float mCameraZoomForcus;
    /* 0x14 */ char* mCameraParamFileName;
    /* 0x18 */ cXyz mCameraPos;
    /* 0x24 */ cXyz mCameraTarget;
    /* 0x30 */ float field_0x30;
};

class JKRArchive;
class dPa_control_c;
class dDemo_manager_c;
class dMagma_packet_c;
class dGrass_packet_c;
class dTree_packet_c;
class Packet_c;
class dFlower_packet_c;
class daPy_py_c;
class daPy_lk_c;
class daPy_npc_c;
class daShip_c;

struct dADM {
    int mBlockCount;
    void* mpData;
    u8 mCharTbl[0x90];
    void* vtable;
};

class dComIfG_play_c {
public:
    void setOxygen(int oxygen) { mOxygen = oxygen; }

public:
    /* 0x00000 */ dBgS mBgS;
    /* 0x01404 */ dCcS mCcS;
    /* 0x03DF8 */ dADM mADM;
    /* 0x03E94 */ dStage_startStage_c mStartStage;
    /* 0x03EA0 */ dStage_nextStage_c mNextStage;
    /* 0x03EB0 */ dStage_stageDt_c mStageData;
    /* 0x03F34 */ dStage_roomControl_c mRoomControl;
    /* 0x03F38 */ dEvt_control_c mEvent;
    /* 0x0402C */ dEvent_manager_c mEvtManager;
    /* 0x04568 */ dAttention_c mAttention;
    /* 0x046F8 */ u8 field_0x46f8[0x4700 - 0x46F8];
    /* 0x04700 */ dVibration_c mVibration;
    /* 0x04784 */ dDetect_c mDetect;
    /* 0x04798 */ JKRArchive* mMsgArchive;
    /* 0x0479C */ JKRArchive* mpDmsgArchive;
    /* 0x047A0 */ JKRArchive* mpTmsgArchive;
    /* 0x047A4 */ JKRArchive* mpMenuArchive;
    /* 0x047A8 */ JKRArchive* mFontArchive;
    /* 0x047AC */ JKRArchive* field_0x47ac;
    /* 0x047B0 */ JKRArchive* mAnmArchive;
    /* 0x047B4 */ JKRArchive* mpLkDArc;
    /* 0x047B8 */ JKRArchive* mpFMapArchive;
    /* 0x047BC */ JKRArchive* mpItemResArchive;
    /* 0x047C0 */ JKRArchive* mCollectResArchive;
    /* 0x047C4 */ JKRArchive* mFmapResArchive;
    /* 0x047C8 */ JKRArchive* mDmapResArchive;
    /* 0x047CC */ JKRArchive* mOptionResArchive;
    /* 0x047D0 */ JKRArchive* mpClothResArchive;
    /* 0x047D4 */ JKRArchive* mpSaveResArchive;
    /* 0x047D8 */ JKRArchive* mItemIconArchive;
    /* 0x047DC */ JKRArchive* mNameResArchive;
    /* 0x047E0 */ JKRArchive* mErrorResArchive;
    /* 0x047E4 */ JKRArchive* mpActionIconArchive;
    /* 0x047E8 */ JKRArchive* mpScopeResArchive;
    /* 0x047EC */ JKRArchive* mpCamResArchive;
    /* 0x047F0 */ JKRArchive* mpSwimResArchive;
    /* 0x047F4 */ JKRArchive* mpWindResArchive;

#ifdef NTSCU
    /* 0x047F8 */ JKRArchive* mpEnglishTextArchive;
#endif

    /* 0x047FC */ JKRArchive* mpHyruleTextArchive;

#ifdef NTSCU
    /* 0x04800 */ u8 field_0x4800[0x4824 - 0x4800];
#endif

#ifdef NTSCJ
    /* 0x04800 */ u8 field_0x47fc[0x4818 - 0x47FC];
#endif

    /* 0x04824 */ dPa_control_c* mParticle;
    /* 0x04828 */ dDemo_manager_c* mpDemoMgr;
    /* 0x0482C */ dMagma_packet_c* mpMagmaPacket;
    /* 0x04830 */ dGrass_packet_c* mpGrassPacket;
    /* 0x04834 */ dTree_packet_c* mpTreePacket;
    /* 0x04838 */ Packet_c* mpWoodPacket;
    /* 0x0483C */ dFlower_packet_c* mpFlowerPacket;
    /* 0x04840 */ u8 mLkDArcIdx;
    /* 0x04841 */ u8 field_0x4841;
    /* 0x04842 */ u16 mVrboxFlags;
    /* 0x04844 */ dDlst_window_c mWindow[1];
    /* 0x0486C */ u8 mCurCameraInfo;
    /* 0x04870 */ dComIfG_camera_info_class mCameraInfo[1];
    /* 0x048A4 */ daPy_py_c* mPlayer[1];
    /* 0x048A8 */ s8 mCurCamera;
    /* 0x048AC */ daPy_lk_c* mPlayerPtr;
    /* 0x048B0 */ daPy_npc_c* mpPlayerPartnerActor;
    /* 0x048B4 */ daShip_c* mpShip;
    /* 0x048B8 */ u8 field_0x48b8[4];
    /* 0x048BC */ int mItemLifeCount;
    /* 0x048C0 */ int mItemRupeeCount;
    /* 0x048C4 */ int mOxygen;
    /* 0x048C8 */ int field_0x48c8;
    /* 0x048CC */ int mNpcNameMessageID;
    /* 0x048D0 */ int mItemNameMessageID;
    /* 0x048D4 */ u16 field_0x48d4;
    /* 0x048D6 */ u16 mCollectHeartPieceCount;
    /* 0x048D8 */ u8 field_0x48d8[0x4A7C - 0x48D8];
};

#ifdef NTSCJ
static_assert(sizeof(dComIfG_play_c) == 0x4A70);
#endif

#ifdef NTSCU
static_assert(sizeof(dComIfG_play_c) == 0x4A7C);
#endif

class dComIfG_inf_c {
public:
    /* 0x00000 */ dSv_info_c info;
    /* 0x012A0 */ dComIfG_play_c play;
    /* 0x05D20 */ u8 field_0x5D20[0x174A8];
};

#ifdef NTSCJ
static_assert(sizeof(dComIfG_inf_c) == 0x1d1b8);
#endif

#ifdef NTSCU
static_assert(sizeof(dComIfG_inf_c) == 0x1d1c8);
#endif

#define g_dComIfG_gameInfo (*(dComIfG_inf_c*)(g_dComIfG_gameInfo_addr))

inline daPy_lk_c* dComIfGp_getPlayer() {
    return g_dComIfG_gameInfo.play.mPlayerPtr;
}

inline u32 dComIfGs_getLinkState() {
    return l_pointer_base_address[0xC40];
}

inline void dComIfGs_setSpeed(float speed) {
    ((float*) l_pointer_base_address)[0xD39] = speed;
}

inline u16* dComIfGs_getCollision() {
    u16** collision_base_address_ptr = (u16**) &g_dComIfG_gameInfo.play.mCameraInfo->mCameraTarget + 4;
    u16* collision_base_address = *collision_base_address_ptr;
    return &collision_base_address[0x24B];
}

inline void dComIfGs_setStorage() {
    g_dComIfG_gameInfo.play.mEvent.setStorage();
}

inline void dComIfGs_setOxygen(int amount) {
    g_dComIfG_gameInfo.play.setOxygen(amount);
}

inline uint8_t dComIfGs_getSword() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(SWORD_INDEX);
}

inline void dComIfGs_setSword(u8 item_id) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setSelectEquip(SWORD_INDEX, item_id);
}

inline void dComIfGs_setSwordOwned(u8 has_item) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setItemOwned(SWORD_OWNED_INDEX, has_item);
}

inline uint8_t dComIfGs_getShield() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(SHIELD_INDEX);
}

inline void dComIfGs_setShield(u8 item_id) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setSelectEquip(SHIELD_INDEX, item_id);
}

inline void dComIfGs_setShieldOwned(u8 has_item) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setItemOwned(SHIELD_OWNED_INDEX, has_item);
}

inline uint8_t dComIfGs_getPowerBracelets() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(POWER_BRACELETS_INDEX);
}

inline void dComIfGs_setPowerBracelets(u8 item_id) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setSelectEquip(POWER_BRACELETS_INDEX, item_id);
}

inline void dComIfGs_setPowerBraceletsOwned(u8 has_item) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setItemOwned(POWER_BRACELETS_OWNED_INDEX, has_item);
}

inline uint8_t dComIfGs_getPiratesCharmOwned() {
    return g_dComIfG_gameInfo.info.getPlayer().getCollect().getItemOwned(PIRATES_CHARM_OWNED_INDEX);
}

inline void dComIfGs_setPiratesCharmOwned(u8 has_item) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setItemOwned(PIRATES_CHARM_OWNED_INDEX, has_item);
}

inline uint8_t dComIfGs_getHerosCharmOwned() {
    return g_dComIfG_gameInfo.info.getPlayer().getCollect().getItemOwned(HEROS_CHARM_OWNED_INDEX);
}

inline void dComIfGs_setHerosCharmOwned(u8 has_item) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setItemOwned(HEROS_CHARM_OWNED_INDEX, has_item);
}

inline uint8_t dComIfGs_getSongsOwned() {
    return g_dComIfG_gameInfo.info.getPlayer().getCollect().getSongsOwned();
}

inline void dComIfGs_setSongsOwned(u8 songs_owned) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setSongsOwned(songs_owned);
}

inline uint8_t dComIfGs_getTriforceOwned() {
    return g_dComIfG_gameInfo.info.getPlayer().getCollect().getTriforceOwned();
}

inline void dComIfGs_setTriforceOwned(u8 triforce_owned) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setTriforceOwned(triforce_owned);
}

inline uint8_t dComIfGs_getPearlsOwned() {
    return g_dComIfG_gameInfo.info.getPlayer().getCollect().getPearlsOwned();
}

inline void dComIfGs_setPearlsOwned(u8 pearls_owned) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setPearlsOwned(pearls_owned);
}

inline uint16_t dComIfGs_getMaxLife() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMaxLife();
}

inline void dComIfGs_setMaxLife(uint16_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxLife(amount);
}

inline uint16_t dComIfGs_getLife() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getLife();
}

inline void dComIfGs_setLife(uint16_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(amount);
}

inline uint8_t dComIfGs_getMaxMagic() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMaxMagic();
}

inline void dComIfGs_setMaxMagic(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxMagic(amount);
}

inline uint8_t dComIfGs_getMagic() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMagic();
}

inline void dComIfGs_setMagic(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(amount);
}

inline uint16_t dComIfGs_getRupee() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getRupee();
}

inline void dComIfGs_setRupee(uint16_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(amount);
}

inline void dComIfGs_setForestWaterTimer(uint16_t frames) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setForestWaterTimer(frames);
}

inline uint8_t dComIfGs_getArrowNum() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemRecord().getArrowNum();
}

inline void dComIfGs_setArrowNum(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setArrowNum(amount);
}

inline uint8_t dComIfGs_getBombNum() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemRecord().getBombNum();
}

inline void dComIfGs_setBombNum(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(amount);
}

inline uint8_t dComIfGs_getArrowCapacity() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemMax().getArrowCapacity();
}

inline void dComIfGs_setArrowCapacity(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemMax().setArrowCapacity(amount);
}

inline uint8_t dComIfGs_getBombCapacity() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemMax().getBombCapacity();
}

inline void dComIfGs_setBombCapacity(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemMax().setBombCapacity(amount);
}

inline u8 dComIfGs_getItemSlot(u8 index) {
    return g_dComIfG_gameInfo.info.getPlayer().getItem().getItemSlot(index);
}

inline void dComIfGs_setItemSlot(u8 index, u8 item_id) {
    g_dComIfG_gameInfo.info.getPlayer().getItem().setItemSlot(index, item_id);
}

inline u8 dComIfGs_getItemFlag(u8 index) {
    return g_dComIfG_gameInfo.info.getPlayer().getGetItem().getItemFlag(index);
}

inline void dComIfGs_setItemFlag(u8 index, u8 has_item) {
    g_dComIfG_gameInfo.info.getPlayer().getGetItem().setItemFlag(index, has_item);
}

inline void dComIfGs_setReturnPlace(const char* stage, s8 roomNo, s8 point) {
    dSv_player_return_place_c__set(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mPlayerReturnPlace,
                                   stage, roomNo, point);
}

inline const char* dComIfGp_getStartStageName() {
    return g_dComIfG_gameInfo.play.mStartStage.getName();
}

inline s8 dComIfGp_getStartStageRoom() {
    return g_dComIfG_gameInfo.play.mStartStage.mRoomNo;
}

inline s8 dComIfGp_getStartStagePoint() {
    return g_dComIfG_gameInfo.play.mStartStage.mPoint & 0xFF;
}

inline s32 dComIfGp_roomControl_getStayNo() {
    return dStage_roomControl_c__mStayNo;
}

#endif /* D_COM_D_COM_INF_GAME_H */