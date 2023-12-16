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
    /* 0x00 */ dTimer_c* mTimerPtr;
    /* 0x04 */ s32 mTimerNowTimeMs;
    /* 0x08 */ s32 mTimerLimitTimeMs;
    /* 0x0C */ s32 mTimerMode;
    /* 0x10 */ u16 mTimerType;
};

struct camera_class;

class dComIfG_camera_info_class {
public:
    /* 0x00 */ camera_class* mpCamera;
    /* 0x04 */ u8 mDlstWindowIdx;
    /* 0x05 */ u8 mCamIdx;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ u32 mCameraAttentionStatus;
    /* 0x0C */ f32 mCameraZoomScale;
    /* 0x10 */ f32 mCameraZoomForcus;
    /* 0x14 */ char* mCameraParamFileName;
    /* 0x18 */ cXyz mCameraPos;
    /* 0x24 */ cXyz mCameraTarget;
    /* 0x30 */ f32 field_0x30;
};

static_assert(sizeof(dComIfG_camera_info_class) == 0x34);

class JKRArchive;
class dPa_control_c;
class dDemo_manager_c;
class dMagma_packet_c;
class dGrass_packet_c;
class dTree_packet_c;
class dWood__Packet_c;
class dFlower_packet_c;
class daPy_py_c;
class daPy_lk_c;
class daPy_npc_c;
class daShip_c;
class daAgb_c;
class J2DOrthoGraph;

struct dADM {
    int mBlockCount;
    void* mpData;
    u8 mCharTbl[0x90];
    void* vtable;
};

class dComIfG_play_c {
public:
    void setItemTimeCount(s32 oxygen) { mItemTimeCount = oxygen; }

    BOOL checkCameraAttentionStatus(int idx, u32 flag) {
        return mCameraInfo[idx].mCameraAttentionStatus & flag;
    }

    dStage_roomControl_c* getRoomControl() { return &mRoomCtrl; }
    dStage_stageDt_c& getStage() { return mStageData; }
    dEvt_control_c& getEvent() { return mEvtCtrl; }
    dEvent_manager_c& getEvtManager() { return mEvtManager; }
    dPa_control_c* getParticle() { return mParticle; }
    dVibration_c& getVibration() { return mVibration; }
    dAttention_c& getAttention() { return mAttention; }
    dDetect_c& getDetect() { return mDetect; }
    dDemo_manager_c* getDemo() { return mDemo; }
    camera_class* getCamera(int idx) { return mCameraInfo[idx].mpCamera; }
    f32 getCamZoomForcus(int idx) { return mCameraInfo[idx].mCameraZoomForcus; }

    dMagma_packet_c* getMagma() { return mpMagmaPacket; }
    dGrass_packet_c* getGrass() { return mpGrassPacket; }
    dTree_packet_c* getTree() { return mpTreePacket; }
    dFlower_packet_c* getFlower() { return mpFlowerPacket; }

    const char* getStartStageName() { return mStartStage.getName(); }
    s8 getStartStageRoomNo() { return mStartStage.getRoomNo(); }
    s8 getStartStageLayer() { return mStartStage.getLayer(); }
    s16 getStartStagePoint() { return mStartStage.getPoint(); }
    void setStartStageLayer(s8 layer) { mStartStage.setLayer(layer); }
    void setStartStage(dStage_startStage_c* i_startStage) { mStartStage = *i_startStage; }
    dStage_startStage_c* getStartStage() { return &mStartStage; }

    const char* getNextStageName() { return mNextStage.getName(); }
    dStage_startStage_c* getNextStartStage() { return &mNextStage; }
    s8 getNextStageRoomNo() { return mNextStage.getRoomNo(); }
    s8 getNextStageLayer() { return mNextStage.getLayer(); }
    s16 getNextStagePoint() { return mNextStage.getPoint(); }
    s8 getNextStageWipe() { return mNextStage.getWipe(); }
    bool isEnableNextStage() { return mNextStage.isEnable(); }
    void offEnableNextStage() { mNextStage.offEnable(); }

    u8 getNowStageNum() { return mPlacenameIndex; }
    u8 checkStageName() { return mPlacenameState; }
    void setStageNameOn(u8 idx) {
        mPlacenameIndex = idx;
        mPlacenameState = 2;
    }
    void setStageNameOff() { mPlacenameState = 1; }

    fopAc_ac_c* getPlayerPtr(int idx) { return (fopAc_ac_c*)mpPlayerPtr[idx]; }
    fopAc_ac_c* getPlayer(int idx) { return (fopAc_ac_c*)mpPlayer[idx]; }
    void setPlayer(int idx, fopAc_ac_c* player) { mpPlayer[idx] = (daPy_py_c*)player; }
    void setPlayerPtr(int idx, fopAc_ac_c* playerPtr) { mpPlayerPtr[idx] = playerPtr; }
    s8 getPlayerCameraID(int idx) { return mCurCamera[idx]; }

    int getItemRupeeCount() { return mItemRupeeCount; }
    void setItemRupeeCount(s32 count) { mItemRupeeCount += count; }
    void setMessageCountNumber(s16 num) { mMsgCountNumber = num; }

    s16 getMiniGameRupee() { return mMiniGameRupee; }
    void plusMiniGameRupee(s16 count) { 
        if(mMiniGameRupee + count > 0) {
            mMiniGameRupee += count;
        }
        else {
            mMiniGameRupee = 0;
        }
    }

    void setLkDemoAnmArchive(JKRArchive* i_arc) { mpLkDArc = i_arc; }
    void setStatus(u16 status) { mStatus = status; }
    void onStatus(u16 status) { mStatus |= status; }
    s32 checkStatus(u16 flags) { return flags & mStatus; }

    void setShipId(u8 i_id) { mShipId = i_id; }
    void setShipRoomId(u8 i_id) { mShipRoomId = i_id; }
    u8 getShipId() { return mShipId; }
    u8 getShipRoomId() { return mShipRoomId; }

    u8* getPlayerInfoBuffer() { return mPlayerInfoBuffer; }
    void setPlayerInfoBufferStageNo(u8 i_stageno) { mPlayerInfoBufferStageNo = i_stageno; }
    u8 getPlayerInfoBufferStageNo() { return mPlayerInfoBufferStageNo; }

    void setAgb(fopAc_ac_c* i_agb) { mpAgb = (daAgb_c*)i_agb; }
    daAgb_c* getAgb() { return mpAgb; }

    void setIkadaShipBeforePos(Vec& i_pos) { mIkadaLinkPos = i_pos; }
    void setIkadaShipId(u8 i_id) { mIkadaShipId = i_id; }
    void setIkadaShipBeforeRoomId(u8 i_roomId) { mIkadaShipBeforeRoomId = i_roomId; }
    u8 getIkadaShipId() { return mIkadaShipId; }
    u8 getIkadaShipBeforeRoomId() { return mIkadaShipBeforeRoomId; }

    dTimer_c* getTimerPtr() { return mTimerInfo.mTimerPtr; }
    s32 getTimerMode() { return mTimerInfo.mTimerMode; }
    
    s16 getItemMagicCount() { return mItemMagicCount; }
    void setItemMagicCount(s16 magic) { mItemMagicCount += magic; }
    s16 getItemMaxMagicCount() { return mItemMaxMagicCount; }
    void setItemMaxMagicCount(s16 magic) { mItemMaxMagicCount += magic; }

    void setItemBombNumCount(s16 num) { mItemBombNumCount += num; }

    f32 getItemLifeCount() { return mItemLifeCount; }
    void setItemLifeCount(f32 num) { mItemLifeCount += num; }
    
    s16 getItemMaxLifeCount() { return mItemMaxLifeCount; }
    void setItemMaxLifeCount(s16 num) { mItemMaxLifeCount += num; }
    
    s16 getItemArrowNumCount() { return mItemArrowNumCount; }
    void setItemArrowNumCount(s16 num) { mItemArrowNumCount += num; }

    void setItemKeyNumCount(s16 num) { mItemKeyNumCount += num; }

    void setItemBeastNumCount(int i_idx, s16 num) { mItemBeastNumCounts[i_idx] += num; }

    u8 checkMesgCancelButton() { return field_0x4949; }

    void setPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] |= flag; }
    void clearPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] &= ~flag; }
    bool checkPlayerStatus(int param_0, int i, u32 flag) { return flag & mPlayerStatus[param_0][i]; }

    u8 getSelectItem(int idx) { return mSelectItem[idx]; }
    void setSelectItem(int idx, u8 itemNo) { mSelectItem[idx] = itemNo; }
    void setSelectEquip(int idx, u8 itemNo) { mSelectEquip[idx] = itemNo; }
    
    void setItem(u8 slot, u8 i_itemNo) {
        field_0x493d = slot;
        field_0x493e = i_itemNo;
    }

    void setAStatus(u8 status) { mCurrButtonBAction = status; }
    void setDoStatus(u8 status) { mCurrButtonAAction = status; }
    void setRStatusForce(u8 status) { field_0x4930 = status; }

    u8 getScopeType() { return mbCamOverrideFarPlane; }
    void setScopeType(u8 v) { mbCamOverrideFarPlane = v; }
    void setCurrentGrafPort(J2DOrthoGraph* i_graf) { mCurrentGrafPort = i_graf; }
    void setCurrentWindow(dDlst_window_c* i_window) { mCurrentWindow = i_window; }
    void setCurrentView(view_class* i_view) { mCurrentView = i_view; }
    void setCurrentViewport(view_port_class* i_viewport) { mCurrentViewport = i_viewport; }
    s32 getWindowNum() { return mDlstWindowNum; }
    void setWindowNum(u8 num) { mDlstWindowNum = num; }
    dDlst_window_c * getWindow(int idx) { return &mDlstWindow[idx]; }

    J2DOrthoGraph* getCurrentGrafPort() { return mCurrentGrafPort; }

    JKRExpHeap * getExpHeap2D() { return mpExpHeap2D; }

    inline u8 getHeapLockFlag() { return mHeapLockFlag; }
    inline void setHeapLockFlag(u8 flag) { mHeapLockFlag = flag; }
    inline void offHeapLockFlag() { mHeapLockFlag = 0; }

public:
    /* 0x0000 */ dBgS mBgS;
    /* 0x1404 */ dCcS mCcS;
    /* 0x3DF8 */ dADM mADM;
    /* 0x3E94 */ dStage_startStage_c mStartStage;
    /* 0x3EA0 */ dStage_nextStage_c mNextStage;
    /* 0x3EAE */ u8 field_0x3EAE[0x3EB0 - 0x3EAE];
    /* 0x3EB0 */ dStage_stageDt_c mStageData;
    /* 0x3F34 */ dStage_roomControl_c mRoomCtrl;
    /* 0x3F38 */ dEvt_control_c mEvtCtrl;
    /* 0x402C */ dEvent_manager_c mEvtManager;
    /* 0x4568 */ dAttention_c mAttention;
    /* 0x46F8 */ u8 field_0x46F8[0x4700 - 0x46F8];
    /* 0x4700 */ dVibration_c mVibration;
    /* 0x4784 */ dDetect_c mDetect;
    /* 0x4798 */ JKRArchive* mpMsgArchive;
    /* 0x479C */ JKRArchive* mpDmsgArchive;
    /* 0x47A0 */ JKRArchive* mpTmsgArchive;
    /* 0x47A4 */ JKRArchive* mpMenuArchive;
    /* 0x47A8 */ JKRArchive* mpFont0Archive;
    /* 0x47AC */ JKRArchive* mpFont1Archive;
    /* 0x47B0 */ JKRArchive* mpAnmArchive;
    /* 0x47B4 */ JKRArchive* mpLkDArc;
    /* 0x47B8 */ JKRArchive* mpFmapArchive;
    /* 0x47BC */ JKRArchive* mpItemResArchive;
    /* 0x47C0 */ JKRArchive* mpClctResArchive;
    /* 0x47C4 */ JKRArchive* mpFmapResArchive;
    /* 0x47C8 */ JKRArchive* mpDmapResArchive;
    /* 0x47CC */ JKRArchive* mpOptResArchive;
    /* 0x47D0 */ JKRArchive* mpClothResArchive;
    /* 0x47D4 */ JKRArchive* mpSaveResArchive;
    /* 0x47D8 */ JKRArchive* mpItemIconArchive;
    /* 0x47DC */ JKRArchive* mpNameResArchive;
    /* 0x47E0 */ JKRArchive* mpErrorResArchive;
    /* 0x47E4 */ JKRArchive* mpActionIconArchive;
    /* 0x47E8 */ JKRArchive* mpScopeResArchive;
    /* 0x47EC */ JKRArchive* mpCamResArchive;
    /* 0x47F0 */ JKRArchive* mpSwimResArchive;
    /* 0x47F4 */ JKRArchive* mpWindResArchive;

#ifdef NTSCU
    /* 0x47F8 */ JKRArchive* mpEnglishTextArchive;
#endif

    /* 0x47FC */ JKRArchive* mpHyruleTextArchive;

#ifdef NTSCU
    /* 0x4800 */ u8 field_0x4800[0x4824 - 0x4800];
#endif

#ifdef NTSCJ
    /* 0x4800 */ u8 field_0x47fc[0x4818 - 0x47FC];
#endif

    /* 0x4824 */ dPa_control_c* mParticle;
    /* 0x4828 */ dDemo_manager_c* mDemo;
    /* 0x482C */ dMagma_packet_c* mpMagmaPacket;
    /* 0x4830 */ dGrass_packet_c* mpGrassPacket;
    /* 0x4834 */ dTree_packet_c* mpTreePacket;
    /* 0x4838 */ dWood__Packet_c* mpWoodPacket;
    /* 0x483C */ dFlower_packet_c* mpFlowerPacket;
    /* 0x4840 */ s8 mLkDArcIdx;
    /* 0x4841 */ u8 mDlstWindowNum;
    /* 0x4842 */ u16 mStatus;
    /* 0x4844 */ dDlst_window_c mDlstWindow[1];
    /* 0x4870 */ dComIfG_camera_info_class mCameraInfo[1];
    /* 0x48A4 */ daPy_py_c* mpPlayer[1];
    /* 0x48A8 */ s8 mCurCamera[1];
    /* 0x48AC */ fopAc_ac_c* mpPlayerPtr[3];  // 0: Link, 1: Partner, 2: Ship
    /* 0x48B8 */ f32 field_0x48b8;
    /* 0x48BC */ f32 mItemLifeCount;
    /* 0x48C0 */ int mItemRupeeCount;
    /* 0x48C4 */ int mItemTimeCount;
    /* 0x48C8 */ int field_0x48c8;
    /* 0x48CC */ int mNpcNameMessageID;
    /* 0x48D0 */ int mItemNameMessageID;
    /* 0x48D4 */ s16 mItemKeyNumCount;
    /* 0x48D6 */ s16 mItemMaxLifeCount;
    /* 0x48D8 */ s16 mItemMagicCount;
    /* 0x48DA */ s16 field_0x48da;
    /* 0x48DC */ s16 mItemMaxMagicCount;
    /* 0x48DE */ s16 field_0x48de;
    /* 0x48E0 */ s16 mItemArrowNumCount;
    /* 0x48E2 */ s16 field_0x48e2;
    /* 0x48E4 */ s16 mItemBombNumCount;
    /* 0x48E6 */ s16 field_0x48e6;
    /* 0x48E8 */ s16 mItemBeastNumCounts[8];
    /* 0x48F8 */ u8 field_0x48F8[0x4918 - 0x48F8];
    /* 0x4918 */ u16 mMsgCountNumber;
    /* 0x491A */ s16 field_0x491a;
    /* 0x491C */ s16 field_0x491c;
    /* 0x491E */ s16 field_0x491e;
    /* 0x4920 */ s16 field_0x4920;
    /* 0x4922 */ s16 field_0x4922;
    /* 0x4924 */ s16 mCurrHP;
    /* 0x4926 */ s16 mRupyCountDisplay;
    /* 0x4928 */ u8 field_0x4928;
    /* 0x4929 */ u8 field_0x4929;
    /* 0x492A */ u8 field_0x492a;
    /* 0x492B */ u8 mbCamOverrideFarPlane;
    /* 0x492C */ u8 field_0x492c;
    /* 0x492D */ u8 field_0x492d;
    /* 0x492E */ u8 mCurrButtonBAction;
    /* 0x492F */ u8 mCurrButtonAAction;
    /* 0x4930 */ u8 field_0x4930;
    /* 0x4931 */ u8 field_0x4931;
    /* 0x4932 */ u8 field_0x4932;
    /* 0x4933 */ u8 mSelectItem[4];
    /* 0x4937 */ u8 mSelectEquip[4];
    /* 0x493B */ u8 mMesgAnime;
    /* 0x493C */ u8 mMesgAnimeTagInfo;
    /* 0x493D */ u8 field_0x493d;
    /* 0x493E */ u8 field_0x493e;
    /* 0x493F */ u8 field_0x493f;
    /* 0x4940 */ u8 field_0x4940;
    /* 0x4941 */ u8 field_0x4941;
    /* 0x4942 */ u8 field_0x4942;
    /* 0x4943 */ u8 field_0x4943;
    /* 0x4944 */ u8 field_0x4944;
    /* 0x4945 */ u8 field_0x4945;
    /* 0x4946 */ u8 field_0x4946;
    /* 0x4947 */ u8 field_0x4947;
    /* 0x4948 */ u8 field_0x4948;
    /* 0x4949 */ u8 field_0x4949;
    /* 0x494A */ u8 field_0x494a[6];
    /* 0x4950 */ u8 mTactMode;
    /* 0x4951 */ u8 field_0x4951;
    /* 0x4952 */ u8 field_0x4952;
    /* 0x4953 */ u8 field_0x4953;
    /* 0x4954 */ u8 field_0x4954;
    /* 0x4955 */ u8 field_0x4955;
    /* 0x4956 */ u8 field_0x4956;
    /* 0x4957 */ u8 mPlacenameIndex;
    /* 0x4958 */ u8 mPlacenameState;
    /* 0x4959 */ u8 field_0x4959;
    /* 0x495A */ u8 field_0x495a;
    /* 0x495B */ u8 field_0x495b;
    /* 0x495C */ u8 field_0x495c;
    /* 0x495D */ u8 field_0x495d;
    /* 0x495E */ u8 field_0x495e;
    /* 0x495F */ u8 field_0x495f;
    /* 0x4960 */ u8 field_0x4960;
    /* 0x4961 */ u8 field_0x4961;
    /* 0x4962 */ u8 mHeapLockFlag;
    /* 0x4963 */ u8 field_0x4963;
#ifdef NTSCU
    /* 0x4964 */ u8 mGameLanguage;
#endif
    /* 0x4965 */ u8 field_0x4965;
    /* 0x4966 */ char field_0x4966[1];
    /* 0x4967 */ u8 field_0x4967[0x4977 - 0x4967];
    /* 0x4977 */ u8 field_0x4977;
    /* 0x4978 */ u8 field_0x4978;
    /* 0x4979 */ u8 field_0x4979;
    /* 0x497A */ u8 field_0x497a;
    /* 0x497B */ u8 field_0x497B[0x497C - 0x497B];
    /* 0x497C */ JKRExpHeap* mpExpHeap2D;
    /* 0x4980 */ int mMesgCameraTagInfo;
    /* 0x4984 */ int field_0x4984;
    /* 0x4988 */ int field_0x4988[10];
    /* 0x49B0 */ u8 mPlayerInfoBuffer[0x4A20 - 0x49B0];
    /* 0x4A20 */ u8 mPlayerInfoBufferStageNo;
    /* 0x4A24 */ daAgb_c* mpAgb;
    /* 0x4A28 */ u32 mPlayerStatus[2][2];
    /* 0x4A38 */ u8 field_0x4A38[0x4A3A - 0x4A38];
    /* 0x4A3A */ u8 mMiniGameType;
    /* 0x4A3C */ s16 mMiniGameRupee;
    /* 0x4A3D */ u8 field_0x4A3E[0x4A40 - 0x4A3E];
    /* 0x4A40 */ __d_timer_info_c mTimerInfo;
    /* 0x4A54 */ dDlst_window_c* mCurrentWindow;
    /* 0x4A58 */ view_class* mCurrentView;
    /* 0x4A5C */ view_port_class* mCurrentViewport;
    /* 0x4A60 */ J2DOrthoGraph* mCurrentGrafPort;
    /* 0x4A64 */ u8 mShipId;
    /* 0x4A65 */ u8 mShipRoomId;
    /* 0x4A66 */ u8 mIkadaShipBeforeRoomId;
    /* 0x4A67 */ u8 mIkadaShipId;
    /* 0x4A68 */ cXyz mIkadaLinkPos;
    /* 0x4A74 */ void* mpItemTable;
    /* 0x4A78 */ void* mpFmapData;
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
    /* 0x05D1C */ u8 field_0x5d1c[0x174A8];
};

#ifdef NTSCJ
static_assert(sizeof(dComIfG_inf_c) == 0x1d1b8);
#endif

#ifdef NTSCU
static_assert(sizeof(dComIfG_inf_c) == 0x1d1c8);
#endif

#define g_dComIfG_gameInfo (*(dComIfG_inf_c*)(g_dComIfG_gameInfo_addr))

typedef int (*tww_getLayerNo)(const char* stageName, int roomId, int layerOverride);
#define tww_getLayerNo ((tww_getLayerNo)tww_getLayerNo_addr)

inline u8 dComIfGs_getSelectEquip(int i_no) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(i_no);
}

inline u8 dComIfGs_getWalletSize() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();
}

inline void dComIfGs_setWalletSize(u8 size) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setWalletSize(size);
}

inline int dComIfGs_getRupee() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getRupee();
}

inline void dComIfGs_setRupee(u16 rupee) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(rupee);
}

inline u8 dComIfGs_getItemBeast(int param_0) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItem().getBeast(param_0);
}

inline void dComIfGs_setItemBeast(int i_idx, u8 i_itemNo) {
    g_dComIfG_gameInfo.info.getPlayer().getBagItem().setBeast(i_idx, i_itemNo);
}

inline u8 dComIfGs_getItemBait(int param_0) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItem().getBait(param_0);
}

inline void dComIfGs_setItemBait(int i_idx, u8 i_itemNo) {
    g_dComIfG_gameInfo.info.getPlayer().getBagItem().setBait(i_idx, i_itemNo);
}

inline u8 dComIfGs_getItemReserve(int param_0) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItem().getReserve(param_0);
}

inline void dComIfGs_setItemReserve(int i_idx, u8 i_itemNo) {
    g_dComIfG_gameInfo.info.getPlayer().getBagItem().setReserve(i_idx, i_itemNo);
}

inline s64 dComIfGs_getDateIpl() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().getDateIpl();
}

/**
 * Returns which item is in a specific inventory slot.
 * @param i_invIdx The index of the inventory slot.
 * @return The item number of the item in that slot, or 0xFF for no item.
 */
inline u8 dComIfGs_getItem(int i_invIdx) {
    if (i_invIdx < 0x15) {
        return g_dComIfG_gameInfo.info.getPlayer().getItem().getItem(i_invIdx);
    } else if (i_invIdx < 0x18) {
        return 0xFF;
    } else if (i_invIdx < 0x18 + 8) {
        return dComIfGs_getItemBeast(i_invIdx - 0x18);
    } else if (i_invIdx < 0x24) {
        return 0xFF;
    } else if (i_invIdx < 0x24 + 8) {
        return dComIfGs_getItemBait(i_invIdx - 0x24);
    } else if (i_invIdx < 0x30) {
        return 0xFF;
    } else if (i_invIdx < 0x30 + 8) {
        return dComIfGs_getItemReserve(i_invIdx - 0x30);
    } else {
        return 0xFF;
    }
}

/**
 * Sets a specific inventory slot to contain a particular item.
 * @param i_invIdx The index of the inventory slot.
 * @param i_itemNo The item number of the item to place in that slot, or 0xFF for no item.
 */
inline void dComIfGs_setItem(int i_invIdx, u8 i_itemNo) {
    if (i_invIdx < 0x15) {
        g_dComIfG_gameInfo.info.getPlayer().getItem().setItem(i_invIdx, i_itemNo);
    } else if (i_invIdx < 0x18) {
        return;
    } else if (i_invIdx < 0x18 + 8) {
        dComIfGs_setItemBeast(i_invIdx - 0x18, i_itemNo);
    } else if (i_invIdx < 0x24) {
        return;
    } else if (i_invIdx < 0x24 + 8) {
        dComIfGs_setItemBait(i_invIdx - 0x24, i_itemNo);
    } else if (i_invIdx < 0x30) {
        return;
    } else if (i_invIdx < 0x30 + 8) {
        dComIfGs_setItemReserve(i_invIdx - 0x30, i_itemNo);
    } else {
        return;
    }
}

inline u8 dComIfGs_getBeast(int i_idx) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItem().getBeast(i_idx);
}

inline void dComIfGs_setBeastItem(u8 i_itemNo) {
    dSv_player_bag_item_c__setBeastItem(&g_dComIfG_gameInfo.info.getPlayer().getBagItem(), i_itemNo);
}

inline u8 dComIfGs_getBait(int i_idx) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItem().getBait(i_idx);
}

inline void dComIfGs_setBaitItem(u8 i_itemNo) {
    dSv_player_bag_item_c__setBaitItem(&g_dComIfG_gameInfo.info.getPlayer().getBagItem(), i_itemNo);
}

inline u8 dComIfGs_getReserve(int i_idx) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItem().getReserve(i_idx);
}

inline BOOL dComIfGs_isGetCollectMap(int i_no) {
    return dSv_player_map_c__isGetMap(&g_dComIfG_gameInfo.info.getPlayer().getMap(), i_no - 1);
}

inline void dComIfGs_onGetCollectMap(int i_no) {
    dSv_player_map_c__onGetMap(&g_dComIfG_gameInfo.info.getPlayer().getMap(), i_no - 1);
}

inline u8 dComIfGs_getArrowNum() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemRecord().getArrowNum();
}

inline void dComIfGs_setArrowNum(u8 num) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setArrowNum(num);
}

inline u8 dComIfGs_getBombNum() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemRecord().getBombNum();
}

inline void dComIfGs_setBombNum(u8 num) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setBombNum(num);
}

inline u8 dComIfGs_getPictureNum() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemRecord().getPictureNum();
}

inline u8 dComIfGs_getBeastNum(int i_idx) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItemRecord().getBeastNum(i_idx);
}

inline void dComIfGs_setBeastNum(int i_idx, u8 num) {
    g_dComIfG_gameInfo.info.getPlayer().getBagItemRecord().setBeastNum(i_idx, num);
}

inline u8 dComIfGs_getBaitNum(int i_idx) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItemRecord().getBaitNum(i_idx);
}

inline void dComIfGs_setBaitNum(int i_idx, u8 num) {
    g_dComIfG_gameInfo.info.getPlayer().getBagItemRecord().setBaitNum(i_idx, num);
}

inline u8 dComIfGs_getReserveNum(int i_idx) {
    return g_dComIfG_gameInfo.info.getPlayer().getBagItemRecord().getReserveNum(i_idx);
}

inline void dComIfGs_setReserveNum(int i_idx, u8 num) {
    g_dComIfG_gameInfo.info.getPlayer().getBagItemRecord().setReserveNum(i_idx, num);
}

inline void dComIfGs_setEventReg(u16 i_reg, u8 i_no) {
    dSv_event_c__setEventReg(&g_dComIfG_gameInfo.info.getEvent(), i_reg, i_no);
}

inline u8 dComIfGs_getEventReg(u16 i_reg) {
    return dSv_event_c__getEventReg(&g_dComIfG_gameInfo.info.getEvent(), i_reg);
}

inline BOOL dComIfGs_isEventBit(u16 flag) {
    return dSv_event_c__isEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_onEventBit(u16 flag) {
    dSv_event_c__onEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_offEventBit(u16 flag) {
    dSv_event_c__offEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_onTmpBit(u16 flag) {
    dSv_event_c__onEventBit(&g_dComIfG_gameInfo.info.getTmp(), flag);
}

inline void dComIfGs_offTmpBit(u16 flag) {
    dSv_event_c__offEventBit(&g_dComIfG_gameInfo.info.getTmp(), flag);
}

inline void dComIfGs_setRestartRoomParam(u32 i_param) {
    g_dComIfG_gameInfo.info.getRestart().setRoomParam(i_param);
}

inline s8 dComIfGs_getRestartRoomNo() {
    return g_dComIfG_gameInfo.info.getRestart().getRoomNo();
}

inline s8 dComIfGs_getRestartOption() {
    return g_dComIfG_gameInfo.info.getRestart().getRestartOption();
}

inline s16 dComIfGs_getRestartOptionPoint() {
    return g_dComIfG_gameInfo.info.getRestart().getRestartOptionPoint();
}

inline s8 dComIfGs_getRestartOptionRoomNo() {
    return g_dComIfG_gameInfo.info.getRestart().getRestartOptionRoomNo();
}

inline cXyz& dComIfGs_getRestartOptionPos() {
    return g_dComIfG_gameInfo.info.getRestart().getRestartOptionPos();
}

inline s16 dComIfGs_getRestartOptionAngleY() {
    return g_dComIfG_gameInfo.info.getRestart().getRestartOptionAngleY();
}

inline u32 dComIfGs_getLastSceneMode() {
    return g_dComIfG_gameInfo.info.getRestart().getLastMode();
}

inline u32 dComIfGs_getRestartRoomParam() {
    return g_dComIfG_gameInfo.info.getRestart().getRoomParam();
}

inline cXyz& dComIfGs_getRestartRoomPos() {
    return g_dComIfG_gameInfo.info.getRestart().getRoomPos();
}

inline s16 dComIfGs_getRestartRoomAngleY() {
    return g_dComIfG_gameInfo.info.getRestart().getRoomAngleY();
}

inline void dComIfGs_setStartPoint(s16 i_point) {
    g_dComIfG_gameInfo.info.getRestart().setStartPoint(i_point);
}

inline s8 dComIfGs_getTurnRestartRoomNo() {
    return g_dComIfG_gameInfo.info.getTurnRestart().getRoomNo();
}

inline u32 dComIfGs_getTurnRestartParam() {
    return g_dComIfG_gameInfo.info.getTurnRestart().getParam();
}

inline cXyz& dComIfGs_getTurnRestartPos() {
    return g_dComIfG_gameInfo.info.getTurnRestart().getPos();
}

inline cXyz& dComIfGs_getTurnRestartShipPos() {
    return g_dComIfG_gameInfo.info.getTurnRestart().getShipPos();
}

inline s16 dComIfGs_getTurnRestartAngleY() {
    return g_dComIfG_gameInfo.info.getTurnRestart().getAngleY();
}

inline s16 dComIfGs_getTurnRestartShipAngleY() {
    return g_dComIfG_gameInfo.info.getTurnRestart().getShipAngleY();
}

inline u8 dComIfGs_getPlayerPriestFlag() {
    return g_dComIfG_gameInfo.info.getPlayer().getPriest().getFlag();
}

inline cXyz& dComIfGs_getPlayerPriestPos() {
    return g_dComIfG_gameInfo.info.getPlayer().getPriest().getPos();
}

inline s16 dComIfGs_getPlayerPriestRotate() {
    return g_dComIfG_gameInfo.info.getPlayer().getPriest().getRotate();
}

inline s8 dComIfGs_getPlayerPriestRoomNo() {
    return g_dComIfG_gameInfo.info.getPlayer().getPriest().getRoomNo();
}

inline int dComIfGs_getTriforceNum() {
    return dSv_player_collect_c__getTriforceNum(&g_dComIfG_gameInfo.info.getPlayer().getCollect());
}

inline BOOL dComIfGs_isTbox(int i_no) {
    return dSv_memBit_c__isTbox(&g_dComIfG_gameInfo.info.getMemory().getBit(), i_no);
}

inline BOOL dComIfGs_isSaveTbox(int i_stageNo, int i_no) {
    return dSv_memBit_c__isTbox(&g_dComIfG_gameInfo.info.getSavedata().getSave(i_stageNo).getBit(), i_no);
}

inline void dComIfGs_onTbox(int i_no) {
    dSv_memBit_c__onTbox(&g_dComIfG_gameInfo.info.getMemory().getBit(), i_no);
}

inline void dComIfGs_onSaveTbox(int i_stageNo, int i_no) {
    dSv_memBit_c__onTbox(&g_dComIfG_gameInfo.info.getSavedata().getSave(i_stageNo).getBit(), i_no);
}

/**
 * This does not appear in the demo debug maps, but it likely existed and was simply unused until the
 * final release based on the fact that dComIfGs_onSaveSwitch does appear in the maps.
 */
inline BOOL dComIfGs_isSaveSwitch(int i_stageNo, int i_no) {
    return dSv_memBit_c__isSwitch(&g_dComIfG_gameInfo.info.getSavedata().getSave(i_stageNo).getBit(), i_no);
}

inline void dComIfGs_onSaveSwitch(int i_stageNo, int i_no) {
    dSv_memBit_c__onSwitch(&g_dComIfG_gameInfo.info.getSavedata().getSave(i_stageNo).getBit(), i_no);
}

inline BOOL dComIfGs_isStageBossEnemy() {
    return g_dComIfG_gameInfo.info.getMemory().getBit().isStageBossEnemy();
}

inline void dComIfGs_onStageLife() {
    g_dComIfG_gameInfo.info.getMemory().getBit().onStageLife();
}

inline BOOL dComIfGs_isStageLife() {
    return g_dComIfG_gameInfo.info.getMemory().getBit().isStageLife();
}

inline BOOL dComIfGs_isCollect(int i_idx, u8 i_item) {
    return dSv_player_collect_c__isCollect(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_idx, i_item);
}

inline void dComIfGs_onCollect(int i_idx, u8 i_item) {
    dSv_player_collect_c__onCollect(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_idx, i_item);
}

inline void dComIfGs_offCollect(int i_idx, u8 i_item) {
    dSv_player_collect_c__offCollect(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_idx, i_item);
}

inline u8 dComIfGs_checkCollect(int no) {
    return g_dComIfG_gameInfo.info.getPlayer().getCollect().checkCollect(no);
}

inline void dComIfGs_setCollect(int idx, u8 byte) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().setCollect(idx, byte);
}

inline BOOL dComIfGs_isTact(u8 i_no) {
    return dSv_player_collect_c__isTact(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_no);
}

inline void dComIfGs_onTact(u8 i_no) {
    dSv_player_collect_c__onTact(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_no);
}

inline void dComIfGs_offTact(u8 i_no) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().offTact(i_no);
}

inline BOOL dComIfGs_isTriforce(u8 i_no) {
    return dSv_player_collect_c__isTriforce(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_no);
}

inline void dComIfGs_onTriforce(u8 i_no) {
    dSv_player_collect_c__onTriforce(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_no);
}

inline void dComIfGs_offTriforce(u8 i_no) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().offTriforce(i_no);
}

inline BOOL dComIfGs_isSymbol(u8 i_no) {
    return dSv_player_collect_c__isSymbol(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_no);
}

inline void dComIfGs_onSymbol(u8 i_no) {
    dSv_player_collect_c__onSymbol(&g_dComIfG_gameInfo.info.getPlayer().getCollect(), i_no);
}

inline void dComIfGs_offSymbol(u8 i_no) {
    g_dComIfG_gameInfo.info.getPlayer().getCollect().offSymbol(i_no);
}

inline BOOL dComIfGs_isDungeonItemMap() {
    return g_dComIfG_gameInfo.info.getMemory().getBit().isDungeonItemMap();
}

inline void dComIfGs_onDungeonItemMap() {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemMap();
}

inline BOOL dComIfGs_isDungeonItemCompass() {
    return g_dComIfG_gameInfo.info.getMemory().getBit().isDungeonItemCompass();
}

inline void dComIfGs_onDungeonItemCompass() {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemCompass();
}

inline BOOL dComIfGs_isDungeonItemBossKey() {
    return g_dComIfG_gameInfo.info.getMemory().getBit().isDungeonItemBossKey();
}

inline void dComIfGs_onDungeonItemBossKey() {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemBossKey();
}

inline void dComIfGs_onSwitch(int i_no, int i_roomNo) {
    dSv_info_c__onSwitch(&g_dComIfG_gameInfo.info, i_no, i_roomNo);
}

inline void dComIfGs_offSwitch(int i_no, int i_roomNo) {
    dSv_info_c__offSwitch(&g_dComIfG_gameInfo.info, i_no, i_roomNo);
}

inline BOOL dComIfGs_isSwitch(int i_no, int i_roomNo) {
    return dSv_info_c__isSwitch(&g_dComIfG_gameInfo.info, i_no, i_roomNo);
}

inline BOOL dComIfGs_revSwitch(int i_no, int i_roomNo) {
    return dSv_info_c__revSwitch(&g_dComIfG_gameInfo.info, i_no, i_roomNo);
}

inline void dComIfGs_onItem(int bitNo, int roomNo) {
    dSv_info_c__onItem(&g_dComIfG_gameInfo.info, bitNo, roomNo);
}

inline BOOL dComIfGs_isItem(int bitNo, int roomNo) {
    return dSv_info_c__isItem(&g_dComIfG_gameInfo.info, bitNo, roomNo);
}

inline void dComIfGs_getSave(int i_stageNo) {
    tww_getSave(&g_dComIfG_gameInfo.info, i_stageNo);
}

inline void dComIfGs_putSave(int i_stageNo) {
    tww_putSave(&g_dComIfG_gameInfo.info, i_stageNo);
}

inline void dComIfGs_setReturnPlace(const char* stage, s8 roomNo, s8 point) {
    dSv_player_return_place_c__set(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mReturnPlace,
                                   stage, roomNo, point);
}

/**
 * Returns which inventory slot the item equipped on a specific button is located in.
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 * @return The index of the inventory slot for the item equipped on that button, or 0xFF for no item.
 */
inline u8 dComIfGs_getSelectItem(int i_btnIdx) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectItem(i_btnIdx);
}

/**
 * Sets which inventory slot the item equipped on a specific button is located in.
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 * @param i_invIdx The index of the inventory slot, or 0xFF for no item.
 */
inline void dComIfGs_setSelectItem(int i_btnIdx, u8 i_invIdx) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setSelectItem(i_btnIdx, i_invIdx);
}

inline u16 dComIfGs_getDate() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().getDate();
}

inline void dComIfGs_setDate(u16 i_date) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().setDate(i_date);
}

inline f32 dComIfGs_getTime() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().getTime();
}

inline void dComIfGs_setTime(f32 i_time) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().setTime(i_time);
}

inline BOOL dComIfGs_isGetItem(int i_field, u8 i_item) {
    return dSv_player_get_item_c__isItem(&g_dComIfG_gameInfo.info.getPlayer().getGetItem(), i_field, i_item);
}

inline void dComIfGs_onGetItem(int i_field, u8 i_item) {
    dSv_player_get_item_c__onItem(&g_dComIfG_gameInfo.info.getPlayer().getGetItem(), i_field, i_item);
}

inline void dComIfGs_offGetItem(int i_field, u8 i_item) {
    g_dComIfG_gameInfo.info.getPlayer().getGetItem().offItem(i_field, i_item);
}

inline BOOL dComIfGs_isGetItemBeast(u8 i_beast) {
    return dSv_player_get_bag_item_c__isBeast(&g_dComIfG_gameInfo.info.getPlayer().getGetBagItem(), i_beast);
}

inline void dComIfGs_onGetItemBeast(u8 i_beast) {
    dSv_player_get_bag_item_c__onBeast(&g_dComIfG_gameInfo.info.getPlayer().getGetBagItem(), i_beast);
}

inline BOOL dComIfGs_isGetItemBait(u8 i_bait) {
    return dSv_player_get_bag_item_c__isBait(&g_dComIfG_gameInfo.info.getPlayer().getGetBagItem(), i_bait);
}

inline void dComIfGs_onGetItemBait(u8 i_bait) {
    dSv_player_get_bag_item_c__onBait(&g_dComIfG_gameInfo.info.getPlayer().getGetBagItem(), i_bait);
}

inline BOOL dComIfGs_checkGetBottle() {
    u8 bottleCount = 0;
    for (int i = 0; i < 4; i++) {
        if (dComIfGs_getItem(0xE + i) != 0xFF) {
            bottleCount++;
        }
    }
    return bottleCount != 0;
}

inline s16 dComIfGs_getWindY() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().getWindY();
}

inline s16 dComIfGs_getWindX() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().getWindX();
}

inline void dComIfGs_setWindY(s16 i_windY) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().setWindY(i_windY);
}

inline void dComIfGs_setWindX(s16 i_windX) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().setWindX(i_windX);
}

inline const char* dComIfGs_getPlayerName() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerInfo().getPlayerName();
}

inline u8 dComIfGs_getGbaRupeeCount() {
    return g_dComIfG_gameInfo.info.getDan().getGbaRupeeCount();
}

inline void dComIfGs_incGbaRupeeCount() {
    g_dComIfG_gameInfo.info.getDan().incGbaRupeeCount();
}

inline u8 dComIfGs_getBombMax() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemMax().getBombNum();
}

inline void dComIfGs_setBombMax(u8 num) {
    g_dComIfG_gameInfo.info.getPlayer().getItemMax().setBombNum(num);
}

inline u8 dComIfGs_getArrowMax() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemMax().getArrowNum();
}

inline void dComIfGs_setArrowMax(u8 num) {
    g_dComIfG_gameInfo.info.getPlayer().getItemMax().setArrowNum(num);
}

inline u16 dComIfGs_getLife() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getLife();
}

inline void dComIfGs_setLife(u16 life) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(life);
}

inline u16 dComIfGs_getMaxLife() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMaxLife();
}

inline void dComIfGs_setMaxLife(u8 life) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxLife(life);
}

inline u8 dComIfGs_getMagic() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMagic();
}

inline void dComIfGs_setMagic(u8 magic) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(magic);
}

inline u8 dComIfGs_getMaxMagic() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMaxMagic();
}

inline void dComIfGs_setMaxMagic(u8 magic) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxMagic(magic);
}

inline u8 dComIfGs_getKeyNum() {
    return g_dComIfG_gameInfo.info.getMemory().getBit().getKeyNum();
}

// custom
inline u8 dComIfGs_getSaveKeyNum(int stage) {
    return g_dComIfG_gameInfo.info.mSavedata.mSave[stage].mBit.getKeyNum();
}

// custom
inline void dComIfGs_setSaveKeyNum(int stage, int num) {
    g_dComIfG_gameInfo.info.mSavedata.mSave[stage].mBit.setKeyNum(num);
}

inline void dComIfGs_resetFwaterTimer(u16 timer) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setTimer(timer);
}

inline dSv_player_status_a_c* dComIfGs_getpPlayerStatusA() {
    return g_dComIfG_gameInfo.info.getPlayer().getpPlayerStatusA();
}

inline dSv_player_status_b_c* dComIfGs_getpPlayerStatusB() {
    return g_dComIfG_gameInfo.info.getPlayer().getpPlayerStatusB();
}

inline dSv_player_return_place_c* dComIfGs_getpPlayerReturnPlace() {
    return g_dComIfG_gameInfo.info.getPlayer().getpPlayerReturnPlace();
}

inline dSv_player_item_c* dComIfGs_getpItem() {
    return g_dComIfG_gameInfo.info.getPlayer().getpItem();
}

inline dSv_player_get_item_c* dComIfGs_getpGetItem() {
    return g_dComIfG_gameInfo.info.getPlayer().getpGetItem();
}

inline dSv_player_item_record_c* dComIfGs_getpItemRecord() {
    return g_dComIfG_gameInfo.info.getPlayer().getpItemRecord();
}

inline dSv_player_item_max_c* dComIfGs_getpItemMax() {
    return g_dComIfG_gameInfo.info.getPlayer().getpItemMax();
}

inline dSv_player_bag_item_c* dComIfGs_getpBagItem() {
    return g_dComIfG_gameInfo.info.getPlayer().getpBagItem();
}

inline dSv_player_get_bag_item_c* dComIfGs_getpGetBagItem() {
    return g_dComIfG_gameInfo.info.getPlayer().getpGetBagItem();
}

inline dSv_player_bag_item_record_c* dComIfGs_getpBagItemRecord() {
    return g_dComIfG_gameInfo.info.getPlayer().getpBagItemRecord();
}

inline dSv_player_collect_c* dComIfGs_getpCollect() {
    return g_dComIfG_gameInfo.info.getPlayer().getpCollect();
}

inline dSv_player_map_c* dComIfGs_getpMap() {
    return g_dComIfG_gameInfo.info.getPlayer().getpMap();
}

inline dSv_player_info_c* dComIfGs_getpPlayerInfo() {
    return g_dComIfG_gameInfo.info.getPlayer().getpPlayerInfo();
}

inline dSv_player_config_c* dComIfGs_getpConfig() {
    return g_dComIfG_gameInfo.info.getPlayer().getpConfig();
}

inline dSv_player_priest_c* dComIfGs_getpPriest() {
    return g_dComIfG_gameInfo.info.getPlayer().getpPriest();
}

inline dSv_player_status_c_c* dComIfGs_getpPlayerStatusC(int i_idx) {
    return g_dComIfG_gameInfo.info.getPlayer().getpPlayerStatusC(i_idx);
}

/**
 * === PLAY ===
 */

inline camera_class* dComIfGp_getCamera(int idx) { return g_dComIfG_gameInfo.play.getCamera(idx); }
inline f32 dComIfGp_getCamZoomForcus(int idx) { return g_dComIfG_gameInfo.play.getCamZoomForcus(idx); }

inline const char* dComIfGp_getStartStageName() {
    return g_dComIfG_gameInfo.play.getStartStageName();
}

inline u32 dComIfGp_getNowStageNum() {
    return g_dComIfG_gameInfo.play.getNowStageNum();
}

inline u8 dComIfGp_checkStageName() {
    return g_dComIfG_gameInfo.play.checkStageName();
}

inline void dComIfGp_setStageNameOn(u8 idx) {
    g_dComIfG_gameInfo.play.setStageNameOn(idx);
}

inline void dComIfGp_setStageNameOff() {
    g_dComIfG_gameInfo.play.setStageNameOff();
}

inline int dComIfGp_getStartStageRoomNo() {
    return g_dComIfG_gameInfo.play.getStartStageRoomNo();
}

inline s8 dComIfGp_getStartStageLayer() {
    return g_dComIfG_gameInfo.play.getStartStageLayer();
}

inline s32 dComIfGp_getStartStagePoint() {
    return g_dComIfG_gameInfo.play.getStartStagePoint();
}

inline void dComIfGp_offEnableNextStage() {
    g_dComIfG_gameInfo.play.offEnableNextStage();
}

inline const char* dComIfGp_getNextStageName() {
    return g_dComIfG_gameInfo.play.getNextStageName();
}

inline dStage_startStage_c* dComIfGp_getNextStartStage() {
    return g_dComIfG_gameInfo.play.getNextStartStage();
}

inline dStage_startStage_c* dComIfGp_getStartStage() {
    return g_dComIfG_gameInfo.play.getStartStage();
}

inline void dComIfGp_setStartStage(dStage_startStage_c* p_startStage) {
    g_dComIfG_gameInfo.play.setStartStage(p_startStage);
}

inline s8 dComIfGp_getNextStageRoomNo() {
    return g_dComIfG_gameInfo.play.getNextStageRoomNo();
}

inline s8 dComIfGp_getNextStageLayer() {
    return g_dComIfG_gameInfo.play.getNextStageLayer();
}

inline s32 dComIfGp_getNextStageWipe() {
    return g_dComIfG_gameInfo.play.getNextStageWipe();
}

inline bool dComIfGp_isEnableNextStage() {
    return g_dComIfG_gameInfo.play.isEnableNextStage();
}

inline s16 dComIfGp_getNextStagePoint() {
    return g_dComIfG_gameInfo.play.getNextStagePoint();
}

inline fopAc_ac_c* dComIfGp_getPlayer(int idx) {
    return g_dComIfG_gameInfo.play.getPlayer(idx);
}

inline void dComIfGp_setPlayer(int idx, fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayer(idx, player);
}

inline void dComIfGp_setPlayerPtr(int idx, fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(idx, player);
}

inline fopAc_ac_c* dComIfGp_getCb1Player() {
    return g_dComIfG_gameInfo.play.getPlayerPtr(1);
}

inline void dComIfGp_setCb1Player(fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(1, player);
}

inline stage_stag_info_class* dComIfGp_getStageStagInfo() {
    return g_dComIfG_gameInfo.play.getStage().mpStagInfo;
}

inline stage_actor_class* dComIfGp_getStagePlayer() {
    return g_dComIfG_gameInfo.play.getStage().mpPlayer;
}

inline s32 dComIfGp_roomControl_getTimePass() {
    return dStage_roomControl_c__m_time_pass;
}

inline int dComIfGp_roomControl_getStayNo() {
    return dStage_roomControl_c__mStayNo;
}

/* inline dStage_roomDt_c* dComIfGp_roomControl_getStatusRoomDt(int room_no) {
    return g_dComIfG_gameInfo.play.getRoomControl()->getStatusRoomDt(room_no);
} */

inline void dComIfGp_roomControl_setTimePass(int isPassing) {
    dStage_roomControl_c__m_time_pass = isPassing;
}

inline dBgS* dComIfG_Bgsp() {
    return &g_dComIfG_gameInfo.play.mBgS;
}

inline dCcS* dComIfG_Ccsp() {
    return &g_dComIfG_gameInfo.play.mCcS;
}

inline daShip_c* dComIfGp_getShipActor() {
    return (daShip_c*)g_dComIfG_gameInfo.play.getPlayerPtr(2);
}

inline void dComIfGp_setShipActor(fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(2, player);
}

inline void dComIfGp_getIkadaShipBeforePos(Vec* o_pos) {
    *o_pos = g_dComIfG_gameInfo.play.mIkadaLinkPos;
}

inline void dComIfGp_setIkadaShipBeforePos(Vec& i_pos) {
    g_dComIfG_gameInfo.play.setIkadaShipBeforePos(i_pos);
}

inline void dComIfGp_setIkadaShipId(u8 i_id) {
    g_dComIfG_gameInfo.play.setIkadaShipId(i_id);
}

inline void dComIfGp_setIkadaShipBeforeRoomId(u8 i_roomId) {
    g_dComIfG_gameInfo.play.setIkadaShipBeforeRoomId(i_roomId);
}

inline u8 dComIfGp_getIkadaShipId() {
    return g_dComIfG_gameInfo.play.getIkadaShipId();
}

inline u8 dComIfGp_getIkadaShipBeforeRoomId() {
    return g_dComIfG_gameInfo.play.getIkadaShipBeforeRoomId();
}

inline stage_scls_info_dummy_class* dComIfGp_getStageSclsInfo() {
    return g_dComIfG_gameInfo.play.getStage().mpScls;
}

inline dStage_stageDt_c& dComIfGp_getStage() {
    return g_dComIfG_gameInfo.play.getStage();
}

inline dVibration_c& dComIfGp_getVibration() {
    return g_dComIfG_gameInfo.play.getVibration();
}

inline dAttention_c& dComIfGp_getAttention() {
    return g_dComIfG_gameInfo.play.getAttention();
}

inline dDetect_c& dComIfGp_getDetect() {
    return g_dComIfG_gameInfo.play.getDetect();
}

inline void dComIfGp_setStatus(u16 status) {
    g_dComIfG_gameInfo.play.setStatus(status);
}

inline void dComIfGp_onStatus(u16 status) {
    g_dComIfG_gameInfo.play.onStatus(status);
}

inline void dComIfGp_setShipId(u8 i_id) {
    g_dComIfG_gameInfo.play.setShipId(i_id);
}

inline void dComIfGp_setShipRoomId(u8 i_id) {
    g_dComIfG_gameInfo.play.setShipRoomId(i_id);
}

inline u8 dComIfGp_getShipId() {
    return g_dComIfG_gameInfo.play.getShipId();
}

inline u8 dComIfGp_getShipRoomId() {
    return g_dComIfG_gameInfo.play.getShipRoomId();
}

inline u8* dComIfGp_getPlayerInfoBuffer() {
    return g_dComIfG_gameInfo.play.getPlayerInfoBuffer();
}

inline void dComIfGp_setPlayerInfoBufferStageNo(u8 i_stageno) {
    g_dComIfG_gameInfo.play.setPlayerInfoBufferStageNo(i_stageno);
}

inline u8 dComIfGp_getPlayerInfoBufferStageNo() {
    return g_dComIfG_gameInfo.play.getPlayerInfoBufferStageNo();
}

inline void dComIfGp_setAgb(fopAc_ac_c* i_agb) {
    g_dComIfG_gameInfo.play.setAgb(i_agb);
}

inline daAgb_c* dComIfGp_getAgb() {
    return g_dComIfG_gameInfo.play.getAgb();
}

inline daPy_py_c* daPy_getPlayerActorClass() {
    return (daPy_py_c*)dComIfGp_getPlayer(0);
}

inline fopAc_ac_c* dComIfGp_getLinkPlayer() {
    return g_dComIfG_gameInfo.play.getPlayerPtr(0);
}

inline void dComIfGp_setLinkPlayer(fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(0, player);
}

inline daPy_lk_c* daPy_getPlayerLinkActorClass() {
    return (daPy_lk_c*)dComIfGp_getLinkPlayer();
}

inline s8 dComIfGp_getPlayerCameraID(int idx) {
    return g_dComIfG_gameInfo.play.getPlayerCameraID(idx);
}

inline BOOL dComIfGp_checkCameraAttentionStatus(int idx, u32 flag) {
    return g_dComIfG_gameInfo.play.checkCameraAttentionStatus(idx, flag);
}

inline int dComIfGp_getItemRupeeCount() {
    return g_dComIfG_gameInfo.play.getItemRupeeCount();
}

inline void dComIfGp_setItemRupeeCount(s32 count) {
    g_dComIfG_gameInfo.play.setItemRupeeCount(count);
}

inline f32 dComIfGp_getItemLifeCount() {
    return g_dComIfG_gameInfo.play.getItemLifeCount();
}

inline void dComIfGp_setItemLifeCount(f32 amount) {
    g_dComIfG_gameInfo.play.setItemLifeCount(amount);
}

inline s16 dComIfGp_getItemMaxLifeCount() {
    return g_dComIfG_gameInfo.play.getItemMaxLifeCount();
}

inline void dComIfGp_setItemMaxLifeCount(s16 num) {
    g_dComIfG_gameInfo.play.setItemMaxLifeCount(num);
}

inline void dComIfGp_setItemTimeCount(s32 count) {
    g_dComIfG_gameInfo.play.setItemTimeCount(count);
}

inline void dComIfGp_setItemKeyNumCount(s16 num) {
    g_dComIfG_gameInfo.play.setItemKeyNumCount(num);
}

inline void dComIfGp_setMessageCountNumber(s16 num) {
    g_dComIfG_gameInfo.play.setMessageCountNumber(num);
}

inline s32 dComIfGp_checkStatus(u16 flags) {
    return g_dComIfG_gameInfo.play.checkStatus(flags);
}

inline s16 dComIfGp_getItemMagicCount() {
    return g_dComIfG_gameInfo.play.getItemMagicCount();
}

inline void dComIfGp_setItemMagicCount(s16 magic) {
    g_dComIfG_gameInfo.play.setItemMagicCount(magic);
}

inline s16 dComIfGp_getItemMaxMagicCount() {
    return g_dComIfG_gameInfo.play.getItemMaxMagicCount();
}

inline void dComIfGp_setItemMaxMagicCount(s16 magic) {
    g_dComIfG_gameInfo.play.setItemMaxMagicCount(magic);
}

inline void dComIfGp_setItemBombNumCount(s16 num) {
    g_dComIfG_gameInfo.play.setItemBombNumCount(num);
}

inline s16 dComIfGp_getItemArrowNumCount() {
    return g_dComIfG_gameInfo.play.getItemArrowNumCount();
}

inline void dComIfGp_setItemArrowNumCount(s16 num) {
    return g_dComIfG_gameInfo.play.setItemArrowNumCount(num);
}

inline void dComIfGp_setItemBeastNumCount(int i_idx, s16 num) {
    g_dComIfG_gameInfo.play.setItemBeastNumCount(i_idx, num);
}

inline u8 dComIfGp_checkMesgCancelButton() {
    return g_dComIfG_gameInfo.play.checkMesgCancelButton();
}

inline bool dComIfGp_checkPlayerStatus0(int param_0, u32 flag) {
    return g_dComIfG_gameInfo.play.checkPlayerStatus(param_0, 0, flag);
}

inline bool dComIfGp_checkPlayerStatus1(int param_0, u32 flag) {
    return g_dComIfG_gameInfo.play.checkPlayerStatus(param_0, 1, flag);
}

inline void dComIfGp_setPlayerStatus0(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.setPlayerStatus(param_0, 0, flag);
}

inline void dComIfGp_setPlayerStatus1(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.setPlayerStatus(param_0, 1, flag);
}

inline void dComIfGp_clearPlayerStatus0(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.clearPlayerStatus(param_0, 0, flag);
}

inline void dComIfGp_clearPlayerStatus1(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.clearPlayerStatus(param_0, 1, flag);
}

/**
 * Returns which item is on a specific button.
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 * @return The item number of the item in that slot, or 0xFF for no item.
 */
inline u8 dComIfGp_getSelectItem(int i_btnIdx) {
    return g_dComIfG_gameInfo.play.getSelectItem(i_btnIdx);
}

/**
 * Updates which item is on a specific button to match which item is in the inventory slot correspond to that button.
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 */
inline void dComIfGp_setSelectItem(int i_btnIdx) {
    if (dComIfGs_getSelectItem(i_btnIdx) != 0xFF) {
        int invIdx = dComIfGs_getSelectItem(i_btnIdx);
        u8 itemNo = dComIfGs_getItem(invIdx);
        g_dComIfG_gameInfo.play.setSelectItem(i_btnIdx, itemNo);
        
        invIdx = dComIfGs_getSelectItem(i_btnIdx);
        itemNo = dComIfGs_getItem(invIdx);
        if (itemNo == 0xFF) {
            dComIfGs_setSelectItem(i_btnIdx, 0xFF);
        }
    } else {
        g_dComIfG_gameInfo.play.setSelectItem(i_btnIdx, 0xFF);
    }
}

inline void dComIfGp_setSelectEquip(int idx, u8 itemNo) {
    g_dComIfG_gameInfo.play.setSelectEquip(idx, itemNo);
}

inline void dComIfGp_setItem(u8 slot, u8 i_itemNo) {
    g_dComIfG_gameInfo.play.setItem(slot, i_itemNo);
}

inline u8 dComIfGp_getScopeType() { return g_dComIfG_gameInfo.play.getScopeType(); }
inline void dComIfGp_setScopeType(u8 v) { g_dComIfG_gameInfo.play.setScopeType(v); }

inline void dComIfGp_setCurrentGrafPort(J2DOrthoGraph* i_graf) {
    g_dComIfG_gameInfo.play.setCurrentGrafPort(i_graf);
}

inline u8 dComIfGp_getMiniGameType() {
    // TODO add enum for minigame type.
    // 0 for none, 8 for shooting the fishman, 2/6 for orca, 7 for mail sorting, etc
    return g_dComIfG_gameInfo.play.mMiniGameType;
}

inline void dComIfGp_setAStatus(u8 status) {
    g_dComIfG_gameInfo.play.setAStatus(status);
}

inline void dComIfGp_setDoStatus(u8 status) {
    g_dComIfG_gameInfo.play.setDoStatus(status);
}

inline void dComIfGp_setRStatusForce(u8 status) {
    g_dComIfG_gameInfo.play.setRStatusForce(status);
}

inline s16 dComIfGp_getMiniGameRupee() {
    return g_dComIfG_gameInfo.play.getMiniGameRupee();
}

inline void dComIfGp_plusMiniGameRupee(s16 count) { 
    g_dComIfG_gameInfo.play.plusMiniGameRupee(count);
}

inline s32 dComIfGp_getWindowNum() { return g_dComIfG_gameInfo.play.getWindowNum(); }
inline void dComIfGp_setWindowNum(u8 num) { g_dComIfG_gameInfo.play.setWindowNum(num); }
inline dDlst_window_c * dComIfGp_getWindow(int idx) { return g_dComIfG_gameInfo.play.getWindow(idx); }
inline J2DOrthoGraph* dComIfGp_getCurrentGrafPort() { return g_dComIfG_gameInfo.play.getCurrentGrafPort(); }
inline void dComIfGp_setCurrentWindow(dDlst_window_c* window) { return g_dComIfG_gameInfo.play.setCurrentWindow(window); }
inline void dComIfGp_setCurrentView(view_class* view) { return g_dComIfG_gameInfo.play.setCurrentView(view); }
inline void dComIfGp_setCurrentViewport(view_port_class* viewport) { return g_dComIfG_gameInfo.play.setCurrentViewport(viewport); }

inline JKRExpHeap * dComIfGp_getExpHeap2D() {
    return g_dComIfG_gameInfo.play.getExpHeap2D();
}

inline u8 dComIfGp_getHeapLockFlag() {
    return g_dComIfG_gameInfo.play.getHeapLockFlag();
}

inline void dComIfGp_setHeapLockFlag(u8 flag) {
    g_dComIfG_gameInfo.play.setHeapLockFlag(flag);
}

inline void dComIfGp_offHeapLockFlag() {
    g_dComIfG_gameInfo.play.offHeapLockFlag();
}

/**
 * === EVENT ===*/

inline BOOL dComIfGp_event_runCheck() {
    return g_dComIfG_gameInfo.play.getEvent().runCheck();
}

inline dEvent_manager_c* dComIfGp_getPEvtManager() {
    return &g_dComIfG_gameInfo.play.getEvtManager();
}


// remove these later

inline u8 dComIfGs_getChartSet() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerInfo().getChartSet();
}

inline void dComIfGs_setChartSet(u8 set) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerInfo().setChartSet(set);
}

inline void dComIfGs_setChartOwned(u32 indx1, u8 indx2) {
    g_dComIfG_gameInfo.info.getPlayer().mMap.setChartOwned(indx1, indx2);
}

inline void dComIfGs_setChartOpened(u32 indx1, u8 indx2) {
    g_dComIfG_gameInfo.info.getPlayer().mMap.setChartOpened(indx1, indx2);
}

inline void dComIfGs_setChartCompleted(u32 indx1, u8 indx2) {
    g_dComIfG_gameInfo.info.getPlayer().mMap.setChartCompleted(indx1, indx2);
}

inline void dComIfGs_setChartDeciphered(u8 indx1) {
    g_dComIfG_gameInfo.info.getPlayer().mMap.setChartDeciphered(indx1);
}

inline u32 dComIfGs_getChartOwned(u8 indx1) {
    return g_dComIfG_gameInfo.info.getPlayer().mMap.getChartOwned(indx1);
}

inline u32 dComIfGs_getChartOpened(u8 indx1) {
    return g_dComIfG_gameInfo.info.getPlayer().mMap.getChartOpened(indx1);
}

inline u32 dComIfGs_getChartCompleted(u8 indx1) {
    return g_dComIfG_gameInfo.info.getPlayer().mMap.getChartCompleted(indx1);
}

inline u8 dComIfGs_getChartDeciphered() {
    return g_dComIfG_gameInfo.info.getPlayer().mMap.getChartDeciphered();
}

#endif /* D_COM_D_COM_INF_GAME_H */
