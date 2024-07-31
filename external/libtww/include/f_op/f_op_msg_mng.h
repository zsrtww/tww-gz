#ifndef F_F_OP_MSG_MNG_H_
#define F_F_OP_MSG_MNG_H_

#include "f_op_msg.h"

class JKRExpHeap;
class JKRHeap;
class fopAc_ac_c;
class msg_class;
class J2DPane;
class J2DScreen;

struct msg_process_profile_definition {
    /* 0x00 */ leaf_process_profile_definition base;
    /* 0x24 */ msg_method_class* sub_method;  // Subclass methods
};

struct fopMsg_prm_class {
    /* 0x00 */ fopAc_ac_c* mpActor;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ u32 mMsgNo;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ int field_0x18;
};  // Size: 0x1C

struct fopMsg_prm_timer : public fopMsg_prm_class {
    /* 0x1C */ int mTimerMode;
    /* 0x20 */ u16 mLimitTimeMs;
    /* 0x22 */ u8 mShowType;
    /* 0x23 */ u8 mIconType;
    /* 0x24 */ cXy mTimerPos;
    /* 0x2C */ cXy mRupeePos;
};  // Size: 0x34

class J2DScreen;

struct fopMsgM_pane_class {
    /* 0x00 */ J2DPane* pane;
    /* 0x04 */ cXy mPosTopLeftOrig;
    /* 0x0C */ cXy mPosTopLeft;
    /* 0x14 */ cXy mPosCenterOrig;
    /* 0x1C */ cXy mPosCenter;
    /* 0x24 */ cXy mSizeOrig;
    /* 0x2C */ cXy mSize;
    /* 0x34 */ u8 mInitAlpha;
    /* 0x35 */ u8 mNowAlpha;
    /* 0x36 */ s16 mUserArea;
};

struct fopMsgM_pane_alpha_class {
    /* 0x00 */ J2DPane* pane;
    /* 0x04 */ u8 mInitAlpha;
    /* 0x05 */ u8 mNowAlpha;
};

typedef int (*fopMsgCreateFunc)(void*);

#endif
