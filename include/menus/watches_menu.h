#pragma once

#include "menu.h"

#define MAX_WATCHES 10

enum MemoryType {
    MEMTYPE_u8,
    MEMTYPE_s8,
    MEMTYPE_u16,
    MEMTYPE_s16,
    MEMTYPE_u32,
    MEMTYPE_s32,
    MEMTYPE_f32,
    MEMTYPE_string,
};

enum MemoryColumns { WatchAddress, WatchX, WatchY, WatchHex, WatchType, WatchOffset };

struct MemoryWatch {
    uint32_t address = 0x80000000;
    float x = 400.0f;
    float y = 100.0f;
    bool hex = false;
    uint8_t type = MEMTYPE_string;
    uint16_t offset = 0x0000;
    uint32_t value;
    bool visible = false;
    bool line_selected = false;
    bool value_selected = false;
};

extern MemoryWatch g_watches[MAX_WATCHES];

class WatchesMenu : public Menu {
public:
    WatchesMenu() : Menu() {}
    static void draw();
    static void drawMemoryLines();
    static void drawWatches();

    static Cursor cursor;
};