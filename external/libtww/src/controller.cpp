#include "../include/JSystem/JUtility/JUTGamePad.h"
#include "../include/controller.h"

#define mPad_ (mPadButton)

void setGamepadButtons(u16 buttons) {
    mPad_.mButton = buttons;
}

void setGamepadTrig(u16 buttons) {
    mPad_.mTrigger = buttons;
}