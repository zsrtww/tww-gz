#pragma once

#include "font.h"

#define MAX_RENDER_LINES 18

#define MAX_LIST_MEMBER_LENGTH 40
#define MAX_LIST_ITEMS 20
#define MAX_LINE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100

struct ListMember {
    char member[MAX_LIST_MEMBER_LENGTH];
};

struct Line {
    char line[MAX_LINE_LENGTH];
    const int idx;
    char description[MAX_DESCRIPTION_LENGTH];
    bool toggleable = false;
    bool* activation_flag;
    u8 max_y_cursor_options;
    char value[MAX_LINE_LENGTH] = {0};
};

float maxF(float a, float b);
void menu_anim(int idx);
void GZ_drawMenuLines(Line lines[], int cursor, int LINES);
