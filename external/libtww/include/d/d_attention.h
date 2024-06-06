#ifndef D_D_ATTENTION_H
#define D_D_ATTENTION_H

#include "../SSystem/SComponent/c_angle.h"
#include "save/d_save.h"
#include "../f_op/f_op_actor.h"

class mDoExt_McaMorf;
class J3DAnmColor;
class J3DMatColorAnm;
class dAttDraw_c {
public:
    /* 0x0 */ mDoExt_McaMorf* anm;
    /* 0x4 */ J3DAnmColor* mpAnmClr;
    /* 0x8 */ J3DMatColorAnm* mpAnmMatClr;
};

class dAttHint_c {
public:
    /* 0x0 */ u32 mHintActorID;
    /* 0x4 */ int mPriority;
    /* 0x8 */ u32 field_0x8;
};

class dAttCatch_c {
public:
    /* 0x00 */ u32 field_0x0;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ u8 field_0xc;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ u32 mCatghTargetID;
    /* 0x14 */ u8 mChangeItem;
};  // Size = 0x18

class dAttParam_c {
public:
    /* 0x00 */ u16 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ void* vtable;
};  // Size = 0x20

class dAttLook_c {
public:
    u32 field_0x0;
    u32 field_0x4;
    f32 field_0x8;
    u32 mLookTargetID;
};  // Size = 0x10

class dAttList_c {
public:
    /* 0x0 */ f32 mWeight;
    /* 0x4 */ f32 mDistance;
    /* 0x8 */ u32 mType;
    /* 0xC */ u32 mActorID;
};  // Size = 0x10

class JKRSolidHeap;

// size is right but members are off, fix later
class dAttention_c {
public:
    /* 0x000 */ fopAc_ac_c* mpPlayer;
    /* 0x004 */ int mLockOnTargetBsPcID;
    /* 0x008 */ void* mCallBack;
    /* 0x00C */ int mPlayerNo;
    /* 0x010 */ u32 mFlagMask;
    /* 0x014 */ u8 field_0x014[0x018 - 0x014];
    /* 0x018 */ u8 mLockOnState;
    /* 0x019 */ u8 field_0x019;
    /* 0x01A */ u8 field_0x01a;
    /* 0x01B */ u8 field_0x01b;
    /* 0x01C */ s16 field_0x01c;
    /* 0x01E */ u8 field_0x01E[0x020 - 0x01E];
    /* 0x020 */ u32 mFlags;
    /* 0x024 */ JKRSolidHeap* heap;
    /* 0x028 */ s8 field_0x028;
    /* 0x02C */ cXyz field_0x02c;
    /* 0x038 */ dAttDraw_c draw[2];
    /* 0x050 */ u32 field_0x050;
    /* 0x054 */ dAttList_c mLockOnList[8];
    /* 0x0D4 */ int mLockOnNum;
    /* 0x0D8 */ int mLockOnOffs;
    /* 0x0DC */ dAttList_c mActionList[4];
    /* 0x11C */ int mActionNum;
    /* 0x120 */ int mActionOffs;
    /* 0x124 */ dAttHint_c mHint;
    /* 0x130 */ dAttCatch_c mCatch;
    /* 0x148 */ dAttLook_c mLook[2];
    /* 0x168 */ int mEnemyBsPcId;
    /* 0x16C */ f32 mEnemyDistance;
    /* 0x170 */ dAttParam_c mAttParam;
};  // Size = 0x190

static_assert(sizeof(dAttention_c) == 0x190);

#endif /* D_D_ATTENTION_H */
