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
    void setStorage() { mbEndProc = 1; }

    u8 getTalkXYBtn() { return mTalkButton; }
    bool chkTalkXY() { return mTalkButton == 1 || mTalkButton == 2 || mTalkButton == 3; }
    void setPtI_Id(u32 id) { mPtItem = id; }
    void setGtItm(u8 itemNo) { mGetItemNo = itemNo; }
    u8 getGtItm() { return mGetItemNo; }
    u8 getPreItemNo() { return mItemNo; }
    
    f32 getCullRate() { return mCullFarClipRatio; }
    void setCullRate(f32 ratio) { mCullFarClipRatio = ratio; }
    
    u16 chkEventFlag(u16 flag) { return flag & mEventFlag; }
    void onEventFlag(u16 flag) { mEventFlag |= flag; }
    void offEventFlag(u16 flag) { mEventFlag &= ~flag; }
    void reset() { onEventFlag(8); }

    bool runCheck() { return mMode != 0; }

    /* 0x00 */ dEvt_order_c mOrder[8];
    /* 0xC0 */ u8 mOrderCount;
    /* 0xC1 */ u8 mFirstOrderIdx;
    /* 0xC2 */ u8 mMode;
    /* 0xC3 */ u8 mbEndProc;
    /* 0xC4 */ u32 mPt1;
    /* 0xC8 */ u32 mPt2;
    /* 0xCC */ int mPtTalk;
    /* 0xD0 */ u32 mPtItem;
    /* 0xD4 */ u8 mGetItemNo;
    /* 0xD5 */ u8 field_0xD5[0xD6 - 0xD5];
    /* 0xD6 */ s16 field_0xd6;
    /* 0xD8 */ s16 mEventId;
    /* 0xDA */ u8 mEventEndSound;
    /* 0xDB */ u8 field_0xdb;
    /* 0xDC */ u8 field_0xdc;
    /* 0xDD */ u8 field_0xDD[0xDE - 0xDD];
    /* 0xDE */ u8 field_0xde;
    /* 0xDF */ u8 field_0xdf;
    /* 0xE0 */ u8 mTalkButton;
    /* 0xE1 */ u8 mItemNo;
    /* 0xE2 */ u8 mbInPhoto;
    /* 0xE3 */ u8 field_0xE3[0xE4 - 0xE3];
    /* 0xE4 */ f32 mCullFarClipRatio;
    /* 0xE8 */ u16 mEventFlag;
    /* 0xEA */ u8 mTactFreeMStick[4];
    /* 0xEE */ u8 mTactFreeCStick[4];
};

static_assert(sizeof(dEvt_control_c) == 0xF4);

#endif /* D_EVENT_D_EVENT_H */
