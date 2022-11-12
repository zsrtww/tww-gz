#pragma once


#include "controller.h"

enum CURSOR_COLORS {
    CURSOR_GREEN,
    CURSOR_BLUE,
    CURSOR_RED,
    CURSOR_ORANGE,
    CURSOR_YELLOW,
    CURSOR_PURPLE
};

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
        } else if (GZ_getButtonRepeat(GZPad::Y)) {
            index -= 10;
        } else if (GZ_getButtonRepeat(GZPad::X)) {
            index += 10;
        }
    }

    void reset() {
        mode = MODE_SINGLE_COLUMN;
        x = 0;
        y = 0;
        lock_x = false;
        lock_y = false;
    }

    void lock(bool x, bool y) {
        lock_x = x;
        lock_y = y;
    }

    void setMode(u8 m) { mode = m; }

    int x = 0;
    int y = 0;
    u8 mode = 0;
    bool lock_x = false;
    bool lock_y = false;
};

extern bool g_cursorEnabled;
extern int g_cursorColor;
extern int g_cursorColorType;

void GZ_setCursorColor();