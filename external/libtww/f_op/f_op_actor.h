#ifndef F_OP_ACTOR_H_
#define F_OP_ACTOR_H_

#include "../SSystem/SComponent/c_sxyz.h"
#include "../SSystem/SComponent/c_xyz.h"
#include "../dolphin/mtx/mtx.h"
#include "../f_pc/f_pc_leaf.h"
#include "../d/kankyo/d_kankyo.h"

struct JKRSolidHeap;

class dEvt_info_c {
public:
    void setCommand(u16 command) { mCommand = command; }
    void setMapToolId(u8 id) { mMapToolId = id; }
    void setEventId(s16 id) { mEventId = id; }
    void setCondition(u16 condition) { mCondition = condition; }
    void setArchiveName(char* name) { mArchiveName = name; }
    u8 getMapToolId() { return mMapToolId; }
    s16 getEventId() { return mEventId; }
    u8 getIdx() { return mIndex; }
    char* getArchiveName() { return mArchiveName; }
    bool chkCondition(u16 condition) { return mCondition == condition; }

    bool checkCommandTalk() { return mCommand == 1; }
    bool checkCommandItem() { return mCommand == 4; }

public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ u16 mCommand;
    /* 0x06 */ u16 mCondition;
    /* 0x08 */ s16 mEventId;
    /* 0x0A */ u8 mMapToolId;
    /* 0x0B */ u8 mIndex;
    /* 0x0C */ char* mArchiveName;
    /* 0x10 */ void* field_0x10;
    /* 0x14 */ void* field_0x14;
};  // Size = 0x18

struct actor_place {
    cXyz mPosition;
    csXyz mAngle;
    u8 mRoomNo;
};

struct actor_attention_types {
    /* 0x00 */ u32 mDistance1;
    /* 0x04 */ u32 mDistance2;
    /* 0x08 */ cXyz mPosition;
    /* 0x14 */ u32 mFlags;
};  // Size = 0x18

class JntHit_c;
class J3DModel;

class fopAc_ac_c : public leafdraw_class {
public:
    /* 0x0C0 */ int mAcType;
    /* 0x0C4 */ create_tag_class mAcTg;
    /* 0x0D8 */ create_tag_class mDwTg;
    /* 0x0EC */ profile_method_class* mSubMtd;
    /* 0x0F0 */ JKRSolidHeap* mHeap;
    /* 0x0F4 */ dEvt_info_c mEvtInfo;
    /* 0x10C */ dKy_tevstr_c mTevStr;
    /* 0x1BC */ s16 mSetID;
    /* 0x1BE */ u8 mGroup;
    /* 0x1BF */ u8 mCullType;
    /* 0x1C0 */ u8 mDemoActorId;
    /* 0x1C1 */ s8 mSubtype;
    /* 0x1C4 */ u32 mStatus;
    /* 0x1C8 */ u32 mCondition;
    /* 0x1CC */ u32 mParentPcId;
    /* 0x1D0 */ actor_place mOrig;
    /* 0x1E4 */ actor_place mNext;
    /* 0x1F8 */ actor_place mCurrent;
    /* 0x20C */ csXyz mCollisionRot;
    /* 0x214 */ cXyz mScale;
    /* 0x220 */ cXyz mSpeed;
    /* 0x22C */ Mtx* mCullMtx;
    union {
        struct {
            /* 0x230 */ cXyz mMin;
            /* 0x23C */ cXyz mMax;
        } mBox;
        struct {
            /* 0x230 */ cXyz mCenter;
            /* 0x23C */ float mRadius;
        } mSphere;
    } mCull;
    /* 0x248 */ float mCullSizeFar;
    /* 0x24C */ J3DModel* mpGrabbedShadowModel;
    /* 0x250 */ JntHit_c* mpArrowStopJntHit;
    /* 0x254 */ float mSpeedF;
    /* 0x258 */ float mGravity;
    /* 0x25C */ float mMaxFallSpeed;
    /* 0x260 */ cXyz mEyePos;
    /* 0x26C */ actor_attention_types mAttentionInfo;
    /* 0x284 */ u8 mMaxHp;
    /* 0x285 */ u8 mCurrHp;
    /* 0x288 */ s32 mItemTableIdx;
    /* 0x28C */ u8 mItemStealNum;
    /* 0x28D */ u8 mItemStealLeft;

    const cXyz& getPosition() const { return mCurrent.mPosition; }
    const csXyz& getAngle() const { return mCurrent.mAngle; }
};  // Size: 0x290

#endif