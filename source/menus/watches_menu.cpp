#include "libtww/MSL_C/string.h"
#include "menus/memory_editor_menu.h"
#include "menus/watches_menu.h"
#include "menus/settings_menu.h"

#define WATCH_COLUMNS 6
#define WATCH_ADDRESS_X_OFFSET 25.0f
#define WHITE_RGBA 0xFFFFFFFF
#define SPEED_THRESHOLD 30

Cursor WatchesMenu::cursor;

uint8_t button_held_counter = 0;
float l_scrollSpeed = 1.0f;
uint8_t l_addrIdx = 3;
uint8_t l_offsetIdx = 2;

MemoryWatch g_watches[MAX_WATCHES] = {};

void WatchesMenu::drawMemoryLines() {
    const float watch_x_pos_x_offset =
        WATCH_ADDRESS_X_OFFSET + maxF(GZ_getTextWidth("Address"), GZ_getTextWidth("0x80000000")) +
        5.0f;
    const float watch_y_pos_x_offset =
        watch_x_pos_x_offset + maxF(GZ_getTextWidth("X"), GZ_getTextWidth("<000>")) + 5.0f;
    const float watch_hex_x_offset =
        watch_y_pos_x_offset + maxF(GZ_getTextWidth("Y"), GZ_getTextWidth("<000>")) + 5.0f;
    const float watch_type_x_offset =
        watch_hex_x_offset + maxF(GZ_getTextWidth("Hex"), GZ_getTextWidth("<false>")) + 5.0f;
    const float watch_offset_x_offset =
        watch_type_x_offset + maxF(GZ_getTextWidth("Type"), GZ_getTextWidth("<u32>")) + 5.0f;
    const float watch_visible_x_offset =
        watch_offset_x_offset + maxF(GZ_getTextWidth("Offset"), GZ_getTextWidth("0x0000")) + 5.0f;

    Font::GZ_drawStr("Address", WATCH_ADDRESS_X_OFFSET, 60.0f, WHITE_RGBA, g_dropShadows);
    Font::GZ_drawStr("X", watch_x_pos_x_offset, 60.0f, WHITE_RGBA, g_dropShadows);
    Font::GZ_drawStr("Y", watch_y_pos_x_offset, 60.0f, WHITE_RGBA, g_dropShadows);
    Font::GZ_drawStr("Hex", watch_hex_x_offset, 60.0f, WHITE_RGBA, g_dropShadows);
    Font::GZ_drawStr("Type", watch_type_x_offset, 60.0f, WHITE_RGBA, g_dropShadows);
    Font::GZ_drawStr("Offset", watch_offset_x_offset, 60.0f, WHITE_RGBA, g_dropShadows);
    Font::GZ_drawStr("Visible", watch_visible_x_offset, 60.0f, WHITE_RGBA, g_dropShadows);

    for (int i = 0; i < MAX_WATCHES; i++) {
        const float line_y_offset = (80.0f + (i * 20.0f));
        char watch_address[11];
        char watch_x[8];
        char watch_y[8];
        char watch_hex[8];
        char watch_type[6];
        char watch_offset[7];
        char watch_visible[4];

        tww_sprintf(watch_address, "0x%08X", g_watches[i].address);
        tww_sprintf(watch_x, "%.0f", g_watches[i].x);
        tww_sprintf(watch_y, "%.0f", g_watches[i].y);
        tww_sprintf(watch_hex, "%s", g_watches[i].hex ? "true" : "false");

        switch (g_watches[i].type) {
        case MEMTYPE_u8:
            tww_sprintf(watch_type, "u8");
            break;
        case MEMTYPE_u16:
            tww_sprintf(watch_type, "u16");
            break;
        case MEMTYPE_u32:
            tww_sprintf(watch_type, "u32");
            break;
        case MEMTYPE_s8:
            tww_sprintf(watch_type, "s8");
            break;
        case MEMTYPE_s16:
            tww_sprintf(watch_type, "s16");
            break;
        case MEMTYPE_s32:
            tww_sprintf(watch_type, "s32");
            break;
        case MEMTYPE_f32:
            tww_sprintf(watch_type, "f32");
            break;
        case MEMTYPE_string:
            tww_sprintf(watch_type, "str");
            break;
        }
        tww_sprintf(watch_offset, "0x%04X", g_watches[i].offset);
        tww_sprintf(watch_visible, "%s", g_watches[i].visible ? "[X]" : "[ ]");

        if (g_watches[i].line_selected) {
            switch (cursor.x) {
            case WatchAddress:
                if (g_watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (l_addrIdx == 9) {
                            l_addrIdx = 3;
                        } else if (l_addrIdx >= 3 && l_addrIdx < 9) {
                            l_addrIdx++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (l_addrIdx == 3) {
                            l_addrIdx = 9;
                        } else if (l_addrIdx > 3 && l_addrIdx <= 9) {
                            l_addrIdx--;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
                        if (l_addrIdx == 3) {
                            g_watches[i].address = 0x81FFFFFF;
                        }
                        if (l_addrIdx <= 9 && l_addrIdx > 3) {
                            g_watches[i].address += 1 << ((9 - l_addrIdx) * 4);
                        }
                        if (g_watches[i].address > 0x81FFFFFF) {
                            g_watches[i].address = 0x81FFFFFF;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
                        if (l_addrIdx <= 9 && l_addrIdx >= 3) {
                            g_watches[i].address -= 1 << ((9 - l_addrIdx) * 4);
                        }
                        if (g_watches[i].address < 0x80000000) {
                            g_watches[i].address = 0x80000000;
                        }
                    }

                    GZ_drawSelectChar(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset,
                                      l_addrIdx, 9, WHITE_RGBA);
                } else {
                    Font::GZ_drawStr(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                }
                Font::GZ_drawStr(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                break;
            case WatchX:
                if (g_watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (g_watches[i].x >= 0.0f && g_watches[i].x < 600.0f) {
                            g_watches[i].x += l_scrollSpeed;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (g_watches[i].x > 0.0f && g_watches[i].x <= 600.0f) {
                            g_watches[i].x -= l_scrollSpeed;
                        }
                    }
                    if (g_watches[i].x < 0) {
                        g_watches[i].x = 0;
                    }
                    if (g_watches[i].x > 600) {
                        g_watches[i].x = 600;
                    }
                    tww_sprintf(watch_x, "<%.0f>", g_watches[i].x);
                    Font::GZ_drawStr(watch_x, watch_x_pos_x_offset - 8.0f, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(watch_x, watch_x_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                }
                Font::GZ_drawStr(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                break;
            case WatchY:
                if (g_watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (g_watches[i].y >= 0.0f && g_watches[i].y < 500.0f) {
                            g_watches[i].y += l_scrollSpeed;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (g_watches[i].y > 0.0f && g_watches[i].y <= 500.0f) {
                            g_watches[i].y -= l_scrollSpeed;
                        }
                    }
                    if (g_watches[i].y < 0) {
                        g_watches[i].y = 0;
                    }
                    if (g_watches[i].y > 500) {
                        g_watches[i].y = 500;
                    }
                    tww_sprintf(watch_y, "<%.0f>", g_watches[i].y);
                    Font::GZ_drawStr(watch_y, watch_y_pos_x_offset - 8.0f, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(watch_y, watch_y_pos_x_offset, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                }
                Font::GZ_drawStr(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);

                break;
            case WatchHex:
                if (g_watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        g_watches[i].hex = !g_watches[i].hex;
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        g_watches[i].hex = !g_watches[i].hex;
                    }
                    tww_sprintf(watch_hex, "<%s>", g_watches[i].hex ? "true" : "false");
                    Font::GZ_drawStr(watch_hex, watch_hex_x_offset - 8.0f, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(watch_hex, watch_hex_x_offset, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                }
                Font::GZ_drawStr(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                break;
            case WatchType:
                if (g_watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (g_watches[i].type == MEMTYPE_string) {
                            g_watches[i].type = MEMTYPE_u8;
                        } else if (g_watches[i].type >= MEMTYPE_u8 &&
                                   g_watches[i].type < MEMTYPE_string) {
                            g_watches[i].type++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (g_watches[i].type == MEMTYPE_u8) {
                            g_watches[i].type = MEMTYPE_string;
                        } else if (g_watches[i].type > MEMTYPE_u8 &&
                                   g_watches[i].type <= MEMTYPE_string) {
                            g_watches[i].type--;
                        }
                    }
                    switch (g_watches[i].type) {
                    case MEMTYPE_u8:
                        tww_sprintf(watch_type, "<u8>");
                        break;
                    case MEMTYPE_u16:
                        tww_sprintf(watch_type, "<u16>");
                        break;
                    case MEMTYPE_u32:
                        tww_sprintf(watch_type, "<u32>");
                        break;
                    case MEMTYPE_s8:
                        tww_sprintf(watch_type, "<s8>");
                        break;
                    case MEMTYPE_s16:
                        tww_sprintf(watch_type, "<s16>");
                        break;
                    case MEMTYPE_s32:
                        tww_sprintf(watch_type, "<s32>");
                        break;
                    case MEMTYPE_f32:
                        tww_sprintf(watch_type, "<f32>");
                        break;
                    case MEMTYPE_string:
                        tww_sprintf(watch_type, "<str>");
                    }
                    Font::GZ_drawStr(watch_type, watch_type_x_offset - 8.0f, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                } else {
                    Font::GZ_drawStr(watch_type, watch_type_x_offset, line_y_offset, CURSOR_RGBA,
                                     g_dropShadows);
                }
                Font::GZ_drawStr(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_offset, watch_offset_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                break;
            case WatchOffset:
                if (g_watches[i].value_selected) {
                    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
                        if (l_offsetIdx == 5) {
                            l_offsetIdx = 2;
                        } else if (l_offsetIdx >= 2 && l_offsetIdx < 5) {
                            l_offsetIdx++;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
                        if (l_offsetIdx == 2) {
                            l_offsetIdx = 5;
                        } else if (l_offsetIdx > 2 && l_offsetIdx <= 5) {
                            l_offsetIdx--;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
                        switch (l_offsetIdx) {
                        case 2: {
                            g_watches[i].offset += 0x1000;
                            break;
                        }
                        case 3: {
                            g_watches[i].offset += 0x100;
                            break;
                        }
                        case 4: {
                            g_watches[i].offset += 0x10;
                            break;
                        }
                        case 5: {
                            g_watches[i].offset += 0x1;
                            break;
                        }
                        }
                        if (g_watches[i].offset > 0xFFFF) {
                            g_watches[i].offset = 0xFFFF;
                        }
                    }
                    if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
                        switch (l_offsetIdx) {
                        case 2: {
                            g_watches[i].offset -= 0x1000;
                            break;
                        }
                        case 3: {
                            g_watches[i].offset -= 0x100;
                            break;
                        }
                        case 4: {
                            g_watches[i].offset -= 0x10;
                            break;
                        }
                        case 5: {
                            g_watches[i].offset -= 0x1;
                            break;
                        }
                        }
                        if (g_watches[i].offset < 0x0000) {
                            g_watches[i].offset = 0x0000;
                        }
                    }
                    GZ_drawSelectChar(watch_offset, watch_offset_x_offset, line_y_offset,
                                      l_offsetIdx, 5, WHITE_RGBA);
                } else {
                    Font::GZ_drawStr(watch_offset, watch_offset_x_offset, line_y_offset,
                                     CURSOR_RGBA, g_dropShadows);
                }
                Font::GZ_drawStr(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_x, watch_x_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_y, watch_y_pos_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_hex, watch_hex_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_type, watch_type_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                Font::GZ_drawStr(watch_visible, watch_visible_x_offset, line_y_offset, WHITE_RGBA,
                                 g_dropShadows);
                break;
            }
        } else {
            int y = cursor.y;
            Font::GZ_drawStr(watch_address, WATCH_ADDRESS_X_OFFSET, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
            Font::GZ_drawStr(watch_x, watch_x_pos_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
            Font::GZ_drawStr(watch_y, watch_y_pos_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
            Font::GZ_drawStr(watch_hex, watch_hex_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
            Font::GZ_drawStr(watch_type, watch_type_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
            Font::GZ_drawStr(watch_offset, watch_offset_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
            Font::GZ_drawStr(watch_visible, watch_visible_x_offset, line_y_offset,
                             (y == i ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        }
    }
}

bool checkMemLineSelected() {
    bool return_value = false;
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (g_watches[i].line_selected) {
            return_value = true;
        }
    }
    return return_value;
}

bool checkLineValSelected() {
    bool return_value = false;
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (g_watches[i].value_selected) {
            return_value = true;
        }
    }

    return return_value;
}

void WatchesMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(GZPad::B)) {
        if (checkLineValSelected()) {
            for (int i = 0; i < MAX_WATCHES; i++) {
                g_watches[i].value_selected = false;
            }
            g_watches[cursor.y].value_selected = false;
            cursor.lock_x = false;
        } else if (checkMemLineSelected()) {
            for (int i = 0; i < MAX_WATCHES; i++) {
                g_watches[i].line_selected = false;
            }
            g_watches[cursor.y].line_selected = false;
            cursor.lock_y = false;
        } else {
            GZ_setMenu(GZ_MEMORY_MENU);
            return;
        }
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        if (g_watches[cursor.y].value_selected) {
            g_watches[cursor.y].value_selected = false;
            cursor.lock_x = false;
        } else if (g_watches[cursor.y].line_selected) {
            g_watches[cursor.y].value_selected = true;
            cursor.lock_x = true;
        } else {
            g_watches[cursor.y].line_selected = true;
            cursor.lock_y = true;
        }
    }

    if (GZ_getButtonTrig(GZPad::Z)) {
        g_watches[cursor.y].visible = !g_watches[cursor.y].visible;
    }

    if (GZ_getButtonTrig(GZPad::Y)) {
        if (g_watches[cursor.y].offset > 0 && *(uint32_t*)g_watches[cursor.y].address != 0) {
            MemoryEditorMenu::mAddressIndex =
                *(uint32_t*)g_watches[cursor.y].address + g_watches[cursor.y].offset;
        } else {
            MemoryEditorMenu::mAddressIndex = g_watches[cursor.y].address;
        }
        GZ_setMenu(GZ_MEM_EDITOR_MENU);
    }

    if (GZ_getButtonPressed(GZPad::DPAD_RIGHT) || GZ_getButtonPressed(GZPad::DPAD_LEFT)) {
        if (l_scrollSpeed < 20.0f) {
            l_scrollSpeed += 1.0f;
        }
        if (l_scrollSpeed > 20.0f) {
            l_scrollSpeed = 20.0f;
        }
    } else {
        l_scrollSpeed = 1.0f;
    }

    cursor.move(WATCH_COLUMNS, MAX_WATCHES);
    Font::GZ_drawStr("Press Z to enable/disable watch. Y to jump to editor address", 25.0f, 440.f,
                     WHITE_RGBA, g_dropShadows);
    drawMemoryLines();
}

void WatchesMenu::drawWatches() {
    for (int i = 0; i < MAX_WATCHES; i++) {
        if (g_watches[i].visible) {
            char rendered_value[8];
            switch (g_watches[i].type) {
            case MEMTYPE_u32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(
                        rendered_value, g_watches[i].hex ? "%08X" : "%u",
                        *(uint32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, g_watches[i].hex ? "%08X" : "%u",
                                *(uint32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case MEMTYPE_u16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(
                        rendered_value, g_watches[i].hex ? "%04X" : "%u",
                        *(uint16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, g_watches[i].hex ? "%04X" : "%u",
                                *(uint16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case MEMTYPE_u8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(
                        rendered_value, g_watches[i].hex ? "%02X" : "%u",
                        *(uint8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, g_watches[i].hex ? "%02X" : "%u",
                                *(uint8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case MEMTYPE_s32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(
                        rendered_value, g_watches[i].hex ? "%08X" : "%i",
                        *(int32_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, g_watches[i].hex ? "%08X" : "%i",
                                *(int32_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case MEMTYPE_s16:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(
                        rendered_value, g_watches[i].hex ? "%04X" : "%i",
                        *(int16_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, g_watches[i].hex ? "%04X" : "%i",
                                *(int16_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case MEMTYPE_s8:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(rendered_value, g_watches[i].hex ? "%02X" : "%i",
                                *(int8_t*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, g_watches[i].hex ? "%02X" : "%i",
                                *(int8_t*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case MEMTYPE_f32:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(rendered_value, "%.2f",
                                *(float*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, "%.2f", *(float*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            case MEMTYPE_string:
                if (g_watches[i].offset > 0x0000 && *(uint32_t*)g_watches[i].address != 0) {
                    tww_sprintf(rendered_value, "%s",
                                (char*)(*(uint32_t*)g_watches[i].address + g_watches[i].offset));
                } else {
                    tww_sprintf(rendered_value, "%s", (char*)g_watches[i].address);
                }
                Font::GZ_drawStr(rendered_value, g_watches[i].x, g_watches[i].y, 0xFFFFFFFF,
                                 g_dropShadows);
                break;
            }
        }
    }
}