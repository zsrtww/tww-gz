#include "utils/cursor.h"
#include "controller.h"
#include "color.h"

int g_cursorColor;
int g_cursorColorType;
bool g_cursorEnabled = false;

void Cursor::move(int max_x, int max_y) {
    if (!g_cursorEnabled) {
        return;
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
        if (mode != MODE_UNRESTRICTED) {
            x = 0;  // reset so other lines aren't affected
        }

        if (!lock_y) {
            y > 0 ? y-- : y = max_y - 1;
        }
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
        if (mode != MODE_UNRESTRICTED) {
            x = 0;  // reset so other lines aren't affected
        }

        if (!lock_y) {
            y < max_y - 1 ? y++ : y = 0;
        }
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
        // if y and x aren't locked, we must be on a single column menu
        if (mode == MODE_SINGLE_COLUMN) {
            y += 10;
            if (y > max_y - 1) {
                y = max_y - 1;
            }
        } else if (!lock_x) {
            x < max_x - 1 ? x++ : x = 0;
        }
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
        // if y and x aren't locked, we must be on a single column menu
        if (mode == MODE_SINGLE_COLUMN) {
            y -= 10;
            if (y < 0) {
                y = 0;
            }
        } else if (!lock_x) {
            x > 0 ? x-- : x = max_x - 1;
        }
    }
}

void GZ_setCursorColor() {
    switch (g_cursorColorType) {
    case CURSOR_GREEN:
        g_cursorColor = ColorPalette::GREEN;
        break;
    case CURSOR_BLUE:
        g_cursorColor = ColorPalette::BLUE;
        break;
    case CURSOR_RED:
        g_cursorColor = ColorPalette::RED;
        break;
    case CURSOR_ORANGE:
        g_cursorColor = ColorPalette::ORANGE;
        break;
    case CURSOR_YELLOW:
        g_cursorColor = ColorPalette::YELLOW;
        break;
    case CURSOR_PURPLE:
        g_cursorColor = ColorPalette::PURPLE;
        break;
    }
}