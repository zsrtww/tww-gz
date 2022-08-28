#ifndef JUTGAMEPAD_H
#define JUTGAMEPAD_H

#include <stdint.h>
#include "../../dolphin/mtx/vec.h"
#include "../../dolphin/pad/pad.h"
#include "../../addrs.h"
#include "../JKernel/JKRDisposer.h"
#include "../../SSystem/SComponent/c_API_controller_pad.h"

typedef void (*callbackFn)(int, void*);

namespace CButton {
enum {
    DPAD_LEFT = 0x0001,
    DPAD_RIGHT = 0x0002,
    DPAD_DOWN = 0x0004,
    DPAD_UP = 0x0008,
    Z = 0x0010,
    R = 0x0020,
    L = 0x0040,
    A = 0x0100,
    B = 0x0200,
    X = 0x0400,
    Y = 0x0800,
    START = 0x1000,
};
}

struct JUTGamePad : public JKRDisposer {
public:
    enum EStickMode {};
    enum EWhichStick {};
    enum EPadPort {
        Port_Unknown = -1,  // used by JUTException
        Port_1,
        Port_2,
        Port_3,
        Port_4,
    };

    uint32_t getButton() const { return mButton.mButton; }

    uint32_t getTrigger() const { return mButton.mTrigger; }

    float getMainStickX() const { return mMainStick.mPosX; }

    float getMainStickY() const { return mMainStick.mPosY; }

    float getMainStickValue() const { return mMainStick.mValue; }

    int16_t getMainStickAngle() const { return mMainStick.mAngle; }

    float getSubStickX() const { return mSubStick.mPosX; }

    float getSubStickY() const { return mSubStick.mPosY; }

    float getSubStickValue() const { return mSubStick.mValue; }

    int16_t getSubStickAngle() const { return mSubStick.mAngle; }

    uint8_t getAnalogA() const { return mButton.mAnalogA; }

    uint8_t getAnalogB() const { return mButton.mAnalogB; }

    uint8_t getAnalogL() const { return mButton.mAnalogL; }

    uint8_t getAnalogR() const { return mButton.mAnalogR; }

    int8_t getErrorStatus() const { return mErrorStatus; }

    uint32_t testTrigger(uint32_t button) const { return mButton.mTrigger & button; }

    bool isPushing3ButtonReset() const {
        bool isPushingReset = false;

        if (mPortNum != -1 && mButtonReset.mReset != false) {
            isPushingReset = true;
        }
        return isPushingReset;
    }

    struct CButton {
        /* 0x00 */ uint32_t mButton;
        /* 0x04 */ uint32_t mTrigger;  // Pressed Buttons
        /* 0x08 */ uint32_t mRelease;  // Released Buttons
        /* 0x0C */ uint8_t mAnalogA;
        /* 0x0D */ uint8_t mAnalogB;
        /* 0x0E */ uint8_t mAnalogL;
        /* 0x0F */ uint8_t mAnalogR;
        /* 0x10 */ float mAnalogLf;
        /* 0x14 */ float mAnalogRf;
        /* 0x18 */ uint32_t mRepeat;
        /* 0x1C */ uint32_t field_0x1c;
        /* 0x20 */ uint32_t field_0x20;
        /* 0x24 */ uint32_t field_0x24;
        /* 0x28 */ uint32_t field_0x28;
        /* 0x2C */ uint32_t field_0x2c;
    };  // Size: 0x30

    struct C3ButtonReset {
        /* 0x0 */ bool mReset;
    };  // Size: 0x4

    struct CStick {
        /* 0x0 */ float mPosX;
        /* 0x4 */ float mPosY;
        /* 0x8 */ float mValue;
        /* 0xC */ int16_t mAngle;
        /* 0xE */ int8_t field_0xe;
        /* 0xF */ int8_t field_0xf;
    };  // Size: 0x10

    struct CRumble {
        enum ERumble {
            VAL_0 = 0,
            VAL_1 = 1,
            VAL_2 = 2,
        };

        /* 0x00 */ uint32_t field_0x0;
        /* 0x04 */ uint32_t field_0x4;
        /* 0x08 */ uint8_t* field_0x8;
        /* 0x0C */ uint32_t field_0xc;
    };  // Size: 0x10

    /* 0x18 */ CButton mButton;
    /* 0x48 */ CStick mMainStick;
    /* 0x58 */ CStick mSubStick;
    /* 0x68 */ CRumble mRumble;
    /* 0x78 */ int16_t mPortNum;
    /* 0x7A */ int8_t mErrorStatus;
    /* 0x7C */ JSULink<JUTGamePad> mLink;
    /* 0x8C */ uint32_t mPadRecord;
    /* 0x90 */ uint32_t mPadReplay;
    /* 0x94 */ C3ButtonReset mButtonReset;
    /* 0x98 */ uint8_t field_0x9c[4];
    /* 0xA0 */ int64_t mResetTime;
};

#define tww_mPadStatus (*(PADStatus*)tww_mPadStatus_addr)
#define tww_mPadButton (*(JUTGamePad::CButton*)tww_mPadButton_addr)
#define tww_mPadMStick (*(JUTGamePad::CStick*)tww_mPadMStick_addr)
#define tww_mPadSStick (*(JUTGamePad::CStick*)tww_mPadSStick_addr)
#define g_mDoCPd_cpadInfo ((interface_of_controller_pad*)g_mDoCPd_cpadInfo_addr)

/* typedef void (*tww_JUTGamePadRead_t)(void);
#define tww_JUTGamePadRead ((tww_JUTGamePadRead_t)tww_JUTGamePadRead_addr) */

#endif /* JUTGAMEPAD_H */