#ifndef D_EVENT_D_EVENT_H
#define D_EVENT_D_EVENT_H

#include "../d_stage.h"
#include "../save/d_save.h"

class dEvt_order_c {
public:
    /*  0x00 */ u16 mEventType;
    /*  0x02 */ u16 mFlag;
    /*  0x04 */ s16 field_0x04;
    /*  0x08 */ fopAc_ac_c* mActor1;
    /*  0x0C */ fopAc_ac_c* mActor2;
    /*  0x10 */ s16 mEventId;
    /*  0x12 */ s16 mPriority;
    /*  0x14 */ u8 mNextOrderIdx;
    /*  0x15 */ u8 mEventInfoIdx;
};  // Size = 0x18
static_assert(sizeof(dEvt_order_c) == 0x18);

typedef int (*SkipFunc)(void*, int);

class dEvt_control_c {
public:
    /* 0x000 */ dEvt_order_c mOrder[8];
    /* 0x0C0 */ u8 mNum;
    /* 0x0C1 */ u8 mFirstOrderIdx;
    /* 0x0C2 */ u8 mMode;
    /* 0x0C3 */ u8 mHalt;
    /* 0x0C4 */ u32 mPt1;
    /* 0x0C8 */ u32 mPt2;
    /* 0x0CC */ u32 mPtTalk;
    /* 0x0D0 */ u32 mPtItem;
    /* 0x0D4 */ u8 mCurStaffId;
    /* 0x0D6 */ u16 field_0xd6;
    /* 0x0D8 */ u16 mEventID;
    /* 0x0DA */ u8 mEventEndSound;
    /* 0x0DB */ u8 field_0xdb[0xE0 - 0xDB];
    /* 0x0E0 */ u8 mTalkButton;
    /* 0x0E1 */ u8 mItemNo;
    /* 0x0E2 */ u8 mbInPhoto;
    /* 0x0E4 */ float mCullFarClipRatio;
    /* 0x0E8 */ u16 mStateFlags;
    /* 0x0EA */ u8 mTactFreeMStick[4];
    /* 0x0EE */ u8 mTactFreeCStick[4];
};

static_assert(sizeof(dEvt_control_c) == 0xF4);

#endif /* D_EVENT_D_EVENT_H */
