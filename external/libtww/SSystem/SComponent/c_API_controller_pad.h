#ifndef C_API_CONTROLLER_PAD_
#define C_API_CONTROLLER_PAD_

#include "../../dolphin/gctypes.h"

struct interface_of_controller_pad {
    /* 0x00 */ float mMainStickPosX;
    /* 0x04 */ float mMainStickPosY;
    /* 0x08 */ float mMainStickValue;
    /* 0x0C */ s16 mMainStickAngle;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ float mCStickPosX;
    /* 0x14 */ float mCStickPosY;
    /* 0x18 */ float mCStickValue;
    /* 0x1C */ s16 mCStickAngle;
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ u8 field_0x1f;
    /* 0x20 */ float mAnalogA;
    /* 0x24 */ float mAnalogB;
    /* 0x28 */ float mTriggerLeft;
    /* 0x2C */ float mTriggerRight;
    /* 0x30 */ u16 mButtonFlags;
    /* 0x32 */ u16 mPressedButtonFlags;
    /* 0x34 */ s8 mGamepadErrorFlags;
    /* 0x35 */ u8 mHoldLockL;
    /* 0x36 */ u8 mTrigLockL;
    /* 0x37 */ u8 mHoldLockR;
    /* 0x38 */ u8 mTrigLockR;
    /* 0x39 */ u8 field_0x39;
    /* 0x3A */ u8 field_0x3a;
    /* 0x3B */ u8 field_0x3b;
};

#endif /* C_API_CONTROLLER_PAD_ */