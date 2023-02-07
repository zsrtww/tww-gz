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