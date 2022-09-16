#ifndef D_EVENT_D_EVENT_H
#define D_EVENT_D_EVENT_H

#include "../d_stage.h"
#include "../save/d_save.h"

class dEvt_order_c {
public:
    /*  0x00 */ uint16_t mEventType;
    /*  0x02 */ uint16_t mFlag;
    /*  0x04 */ int16_t field_0x04;
    /*  0x08 */ fopAc_ac_c* mActor1;
    /*  0x0C */ fopAc_ac_c* mActor2;
    /*  0x10 */ int16_t mEventId;
    /*  0x12 */ int16_t mPriority;
    /*  0x14 */ uint8_t mNextOrderIdx;
    /*  0x15 */ uint8_t mEventInfoIdx;
};  // Size = 0x18
static_assert(sizeof(dEvt_order_c) == 0x18);

typedef int (*SkipFunc)(void*, int);

class dEvt_control_c {
public:
    /* 0x000 */ dEvt_order_c mOrder[8];
    /* 0x0C0 */ uint8_t mNum;
    /* 0x0C1 */ uint8_t mFirstOrderIdx;
    /* 0x0C2 */ uint8_t mMode;
    /* 0x0C3 */ uint8_t mHalt;
    /* 0x0C4 */ uint32_t mPt1;
    /* 0x0C8 */ uint32_t mPt2;
    /* 0x0CC */ uint32_t mPtTalk;
    /* 0x0D0 */ uint32_t mPtItem;
    /* 0x0D4 */ uint8_t mCurStaffId;
    /* 0x0D6 */ uint16_t field_0xd6;
    /* 0x0D8 */ uint16_t mEventID;
    /* 0x0DA */ uint8_t mEventEndSound;
    /* 0x0DB */ uint8_t field_0xdb[0xE0 - 0xDB];
    /* 0x0E0 */ uint8_t mTalkButton;
    /* 0x0E1 */ uint8_t mItemNo;
    /* 0x0E2 */ uint8_t mbInPhoto;
    /* 0x0E4 */ float mCullFarClipRatio;
    /* 0x0E8 */ uint16_t mStateFlags;
    /* 0x0EA */ uint8_t mTactFreeMStick[4];
    /* 0x0EE */ uint8_t mTactFreeCStick[4];
};

static_assert(sizeof(dEvt_control_c) == 0xF4);

#endif /* D_EVENT_D_EVENT_H */
