#include "buffer_button.h"
#include "rels/include/defines.h"
#include "controller.h"
#include <string.h>

KEEP_FUNC void Buffer_Buttons_enum_to_str(char* buttonStr, int bufferButton) {
    switch (bufferButton) {
    case A_BUTTON:
        strncpy(buttonStr, "A", 2);
        break;
    case B_BUTTON:
        strncpy(buttonStr, "B", 2);
        break;
    case X_BUTTON:
        strncpy(buttonStr, "X", 2);
        break;
    case Y_BUTTON:
        strncpy(buttonStr, "Y", 2);
        break;
    case Z_BUTTON:
        strncpy(buttonStr, "Z", 2);
        break;
    case START_BUTTON:
        strncpy(buttonStr, "Start", 6);
        break;
    default:
        break;
    }
}

KEEP_FUNC int Buffer_Buttons_enum_to_GZPad_enum(int bufferButton) {
    switch (bufferButton) {
    case A_BUTTON:
        return GZPad::A;
        break;
    case B_BUTTON:
        return GZPad::B;
        break;
    case X_BUTTON:
        return GZPad::X;
        break;
    case Y_BUTTON:
        return GZPad::Y;
        break;
    case Z_BUTTON:
        return GZPad::Z;
        break;
    case START_BUTTON:
        return GZPad::START;
        break;
    default:
        break;
    }
    return GZPad::B;
}