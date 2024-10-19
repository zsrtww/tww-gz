#include "utils/cursor.h"
#include "controller.h"
#include "settings.h"
#include "rels/include/defines.h"

KEEP_VAR bool g_cursorEnabled = false;

KEEP_FUNC void Cursor::move(int max_x, int max_y) {
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

KEEP_FUNC void Cursor::reset() {
    mode = MODE_SINGLE_COLUMN;
    x = 0;
    y = 0;
    lock_x = false;
    lock_y = false;
}

KEEP_FUNC void Cursor::lock(bool x, bool y) {
    lock_x = x;
    lock_y = y;
}

KEEP_FUNC void Cursor::setMode(uint8_t m) {
    mode = m;
}

#include "libtww/include/d/com/d_com_inf_game.h"
#include "geometry_draw.h"

uint32_t l_cursorMapping[] = {0x00CC00FF, 0x0080FFFF, 0xCC0000FF, 0xEE8000FF, 0xFFCC00FF, 0x6600CCFF};

KEEP_FUNC void GZ_setCursorColor() {
    uint32_t colorId = GZStng_getData(STNG_CURSOR_COLOR, 0);
    if (colorId < ARRAY_COUNT(l_cursorMapping)) {
        g_cursorColor = l_cursorMapping[colorId];
    }
}
