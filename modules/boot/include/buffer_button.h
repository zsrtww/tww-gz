#pragma once

#include "libtww/include/dolphin/gctypes.h"

enum Buffer_Buttons {
    A_BUTTON, 
    B_BUTTON,
    X_BUTTON, 
    Y_BUTTON, 
    Z_BUTTON,
    START_BUTTON
};

void Buffer_Buttons_enum_to_str(char* buttonStr, int bufferButton);
int Buffer_Buttons_enum_to_GZPad_enum(int bufferButton);