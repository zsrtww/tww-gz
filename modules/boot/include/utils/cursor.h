#pragma once

#include <stdint.h>
#include "controller.h"

#define SCROLL_P10_BTN GZPad::X
#define SCROLL_M10_BTN GZPad::Y

struct Cursor {
    enum Mode {
        MODE_SINGLE_COLUMN,
        MODE_LIST,
        MODE_UNRESTRICTED,
    };

    Cursor() { reset(); }

    void move(int max_x, int max_y);

    template <typename T>
    static void moveList(T& index) {
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            index--;
        } else if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            index++;
        } else if (GZ_getButtonRepeat(SCROLL_M10_BTN)) {
            index -= 10;
        } else if (GZ_getButtonRepeat(SCROLL_P10_BTN)) {
            index += 10;
        }
    }

    template <typename T>
    static void moveListSimple(T& index) {
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            index--;
        } else if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            index++;
        }
    }

    void reset();
    void lock(bool x, bool y);
    void setMode(uint8_t m);

    int x = 0;
    int y = 0;
    uint8_t mode = 0;
    bool lock_x = false;
    bool lock_y = false;
};

extern bool g_cursorEnabled;

void GZ_setCursorColor();