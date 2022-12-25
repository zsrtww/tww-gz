#pragma once

#include "libtww/JSystem/JUtility/JUTGamePad.h"

enum GZPad {
    DPAD_LEFT = 0,
    DPAD_RIGHT = 1,
    DPAD_DOWN = 2,
    DPAD_UP = 3,
    Z = 4,
    R = 5,
    L = 6,
    A = 7,
    B = 8,
    X = 9,
    Y = 10,
    START = 11,
};

void setGamepadButtons(u32 buttons);
void setGamepadTrig(u32 buttons);
bool GZ_getButtonRepeat(int idx);
bool GZ_getButtonRepeat(int idx, u16 repeat_time);
bool GZ_getButtonPressed(int idx);
bool GZ_getButtonHold(int idx, int phase = 0);
u16 GZ_getButtonStatus();
void GZ_readController();
bool GZ_getButtonTrig(int idx);
void GZ_readZombieHoverInputs();
u8 GZ_getAPressesPerWindow();
u8 GZ_getBPressesPerWindow();