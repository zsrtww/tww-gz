#include "menus/memory_editor_menu.h"
#include "menus/settings_menu.h"
#include "libtww/MSL_C/string.h"
#include "color.h"

#define MAX_DISPLAY_LINES 15
#define WHITE_RGBA ColorPalette::WHITE
#define ADDRESS_RGBA ColorPalette::GRAY
#define LINE_X_OFFSET 20.0f
#define LINE_BYTE_OFFSET 100.0f

Cursor MemoryEditorMenu::cursor;
uint32_t MemoryEditorMenu::mAddressIndex = 0x80000000;

bool l_idxSelected = false;
uint8_t l_idxPlace = 0;
uint8_t l_byteIdx = 0;
uint8_t l_cycleR = 0;
uint8_t l_cycleG = 0;
uint8_t l_cycleB = 0;

void MemoryEditorMenu::drawMemEditor() {
    char index[9];
    tww_sprintf(index, "%08X", mAddressIndex);

    if (l_idxSelected) {
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (l_idxPlace == 7) {
                l_idxPlace = 0;
            } else if (l_idxPlace >= 0 && l_idxPlace < 8) {
                l_idxPlace++;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (l_idxPlace == 0) {
                l_idxPlace = 7;
            } else if (l_idxPlace >= 0 && l_idxPlace < 8) {
                l_idxPlace--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            switch (l_idxPlace) {
            case 0:
                mAddressIndex = 0x81FFFFFF;
                break;
            case 1:
                mAddressIndex += 0x1000000;
                break;
            case 2:
                mAddressIndex += 0x100000;
                break;
            case 3:
                mAddressIndex += 0x10000;
                break;
            case 4:
                mAddressIndex += 0x1000;
                break;
            case 5:
                mAddressIndex += 0x100;
                break;
            case 6:
                mAddressIndex += 0x10;
                break;
            case 7:
                mAddressIndex += 0x1;
                break;
            }
            if (mAddressIndex > 0x81FFFFFF) {
                mAddressIndex = 0x81FFFFFF;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
            switch (l_idxPlace) {
            case 0:
                mAddressIndex -= 0x10000000;
                break;
            case 1:
                mAddressIndex -= 0x1000000;
                break;
            case 2:
                mAddressIndex -= 0x100000;
                break;
            case 3:
                mAddressIndex -= 0x10000;
                break;
            case 4:
                mAddressIndex -= 0x1000;
                break;
            case 5:
                mAddressIndex -= 0x100;
                break;
            case 6:
                mAddressIndex -= 0x10;
                break;
            case 7:
                mAddressIndex -= 0x1;
                break;
            }
            if (mAddressIndex < 0x80000000) {
                mAddressIndex = 0x80000000;
            }
        }
        GZ_drawSelectChar(index, LINE_X_OFFSET, 80.0f, l_idxPlace, 7, WHITE_RGBA);
    } else {
        Font::GZ_drawStr(index, LINE_X_OFFSET, 80.0f, (cursor.y == 0 ? CURSOR_RGBA : WHITE_RGBA),
                         g_dropShadows);
    }

    if (cursor.y > 0 && !cursor.lock_x) {
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (l_byteIdx == 0) {
                l_byteIdx = 7;
            } else if (l_byteIdx >= 0 && l_byteIdx < 8) {
                l_byteIdx--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (l_byteIdx == 7) {
                l_byteIdx = 0;
            } else if (l_byteIdx >= 0 && l_byteIdx < 8) {
                l_byteIdx++;
            }
        }
    }

    for (uint8_t i = 0; i < MAX_DISPLAY_LINES; i++) {
        float y_offset;
        y_offset = ((100.0f) + (i * 20.0f));

        char address[10];
        char b0[3];
        char b1[3];
        char b2[3];
        char b3[3];
        char b4[3];
        char b5[3];
        char b6[3];
        char b7[3];

        tww_sprintf(address, "%08X ", mAddressIndex + (i * 8));
        tww_sprintf(b0, "%02X", *(uint8_t*)(mAddressIndex + (i * 8)));
        tww_sprintf(b1, "%02X", *(uint8_t*)((mAddressIndex + (i * 8)) + 1));
        tww_sprintf(b2, "%02X", *(uint8_t*)((mAddressIndex + (i * 8)) + 2));
        tww_sprintf(b3, "%02X", *(uint8_t*)((mAddressIndex + (i * 8)) + 3));
        tww_sprintf(b4, "%02X", *(uint8_t*)((mAddressIndex + (i * 8)) + 4));
        tww_sprintf(b5, "%02X", *(uint8_t*)((mAddressIndex + (i * 8)) + 5));
        tww_sprintf(b6, "%02X", *(uint8_t*)((mAddressIndex + (i * 8)) + 6));
        tww_sprintf(b7, "%02X", *(uint8_t*)((mAddressIndex + (i * 8)) + 7));

        float address_offset = Font::getStrWidth(address) + LINE_X_OFFSET;
        float b_offset = Font::getStrWidth(" 00");
        if (cursor.y == (i + 1) && cursor.lock_x && cursor.lock_y) {
            if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
                *(uint8_t*)((mAddressIndex + (i * 8)) + l_byteIdx) += 0x1;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
                *(uint8_t*)((mAddressIndex + (i * 8)) + l_byteIdx) -= 0x1;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                *(uint8_t*)((mAddressIndex + (i * 8)) + l_byteIdx) += 0x10;
            }
            if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                *(uint8_t*)((mAddressIndex + (i * 8)) + l_byteIdx) -= 0x10;
            }
        }

        uint32_t mem_cursor_color;
        // cycle cursor color when value selected
        if (cursor.lock_x && cursor.lock_y) {
            if (l_cycleR < 0x00A0 && (l_cycleG == 0x0000 && l_cycleB == 0x0000)) {
                l_cycleR += 0x0001;
            } else if (l_cycleG < 0x00A0 && (l_cycleB == 0x0000 && l_cycleR == 0x00A0)) {
                l_cycleG += 0x0001;
            } else if (l_cycleB < 0x00A0 && (l_cycleG == 0x00A0 && l_cycleR == 0x00A0)) {
                l_cycleB += 0x0001;
            } else if (l_cycleR > 0x0000 && (l_cycleG == 0x00A0 && l_cycleB == 0x00A0)) {
                l_cycleR -= 0x0001;
            } else if (l_cycleG > 0x0000 && (l_cycleB == 0x00A0 && l_cycleR == 0x0000)) {
                l_cycleG -= 0x0001;
            } else {
                l_cycleB -= 0x0001;
            }
            mem_cursor_color = (l_cycleR << 24) | (l_cycleG << 16) | (l_cycleB << 8) | 0xFF;
        } else {
            mem_cursor_color = CURSOR_RGBA;
        }

        Font::GZ_drawStr(address, LINE_X_OFFSET, y_offset,
                         (cursor.y == (i + 1) ? CURSOR_RGBA : ADDRESS_RGBA), g_dropShadows);
        Font::GZ_drawStr(b0, address_offset, y_offset,
                         (l_byteIdx == 0 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
        Font::GZ_drawStr(b1, address_offset + b_offset * 1, y_offset,
                         (l_byteIdx == 1 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
        Font::GZ_drawStr(b2, address_offset + b_offset * 2, y_offset,
                         (l_byteIdx == 2 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
        Font::GZ_drawStr(b3, address_offset + b_offset * 3, y_offset,
                         (l_byteIdx == 3 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
        Font::GZ_drawStr(b4, address_offset + b_offset * 4, y_offset,
                         (l_byteIdx == 4 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
        Font::GZ_drawStr(b5, address_offset + b_offset * 5, y_offset,
                         (l_byteIdx == 5 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
        Font::GZ_drawStr(b6, address_offset + b_offset * 6, y_offset,
                         (l_byteIdx == 6 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
        Font::GZ_drawStr(b7, address_offset + b_offset * 7, y_offset,
                         (l_byteIdx == 7 && cursor.y == (i + 1) ? mem_cursor_color : WHITE_RGBA),
                         g_dropShadows);
    }
}

void MemoryEditorMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(GZPad::B)) {
        if (l_idxSelected) {
            cursor.lock_y = false;
            l_idxSelected = false;
        } else if (cursor.lock_x || cursor.lock_y) {
            cursor.lock_x = false;
            cursor.lock_y = false;
        } else {
            GZ_setMenu(GZ_MEMORY_MENU);
            return;
        }
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case 0:
            cursor.lock_y = true;
            l_idxSelected = true;
            break;
        }

        if (cursor.y > 0) {
            cursor.lock_x = true;
            cursor.lock_y = true;
        }
    }

    cursor.move(8, 1 + MAX_DISPLAY_LINES);
    Font::GZ_drawStr("DPad to move/modify value, A/B to (de)select value", 25.0f, 440.f, WHITE_RGBA,
                     g_dropShadows);
    drawMemEditor();
}