#ifndef D_D_ATTENTION_H
#define D_D_ATTENTION_H

#include "../SSystem/SComponent/c_angle.h"
#include "save/d_save.h"
#include "../f_op/f_op_actor.h"

class dAttHint_c {
public:
    u32 mHintActorBsPcID;
    u32 mBestPriority;
    u32 field_0x8;
};

class dAttCatch_c {
public:
    void* field_0x0;
    u32 field_0x4;
    float field_0x8;
    u8 field_0xc;
    u8 field_0xd;
    u8 field_0xe;
    u8 field_0xf;
    u32 field_0x10;
    u8 mChangeItem;
};  // Size = 0x18

class dAttParam_c {
public:
    /* 0x00 */ u16 mFlag;
    /* 0x04 */ float field_0x4;
    /* 0x08 */ float field_0x8;
    /* 0x0C */ float field_0xc;
    /* 0x10 */ float field_0x10;
    /* 0x14 */ float field_0x14;
    /* 0x18 */ float field_0x18;
    /* 0x1C */ void* vtable;
};  // Size = 0x20

class dAttLook_c {
public:
    u32 field_0x0;
    u32 field_0x4;
    float field_0x8;
    u32 field_0xc;
};  // Size = 0x10

class dAttList_c {
public:
    float mWeight;
    float mDistance;
    int mType;
    int mPcId;
};  // Size = 0x10

class JKRHeap;

// size is right but members are off, fix later
class dAttention_c {
public:
    /* 0x000 */ fopAc_ac_c* mpPlayer;
    /* 0x004 */ u32 mLockOnTargetBsPcID;
    /* 0x008 */ u8 field_0x8[4];
    /* 0x00C */ int mPlayerNo;
    /* 0x010 */ u32 mFlagMask;
    /* 0x014 */ u8 field_0x14[4];
    /* 0x018 */ u8 mLockOnState;
    /* 0x018 */ u8 field_0x19;
    /* 0x01A */ u8 field_0x1a;
    /* 0x01B */ u8 field_0x1b;
    /* 0x01C */ u16 field_0x1c;
    /* 0x020 */ u32 mFlags;
    /* 0x024 */ JKRHeap* mpHeap;
    /* 0x028 */ u8 field_0x28[0x54 - 0x28];
    /* 0x054 */ dAttList_c mLockOnList[8];
    /* 0x0D4 */ int mLockonCount;
    /* 0x0D8 */ int mLockOnOffs;
    /* 0x0DC */ dAttList_c mActionList[4];
    /* 0x11C */ int mActionCount;
    /* 0x120 */ int mActionOffs;
    /* 0x124 */ dAttHint_c mHint;
    /* 0x130 */ dAttCatch_c mCatch;
    /* 0x148 */ dAttLook_c field_0x148;
    /* 0x158 */ dAttLook_c field_0x158;
    /* 0x168 */ int mEnemyBsPcId;
    /* 0x16C */ float mEnemyDistance;
    /* 0x170 */ dAttParam_c mAttParam;
};  // Size = 0x190

static_assert(sizeof(dAttention_c) == 0x190);

#endif /* D_D_ATTENTION_H */
