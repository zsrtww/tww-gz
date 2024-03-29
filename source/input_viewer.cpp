#include "input_viewer.h"
#include "controller.h"
#include "font.h"
#include "menus/settings_menu.h"
#include "utils/draw.h"
#include "libtww/MSL_C/string.h"
#include "libtww/MSL_C/math.h"
#include "menus/tools_menu.h"
#include "color.h"

#define OUTLINE_WIDTH 0x10

void drawEllipse(uint32_t color, Vec2 center, Vec2 dim) {
    constexpr const size_t n_points = 4;
    float dx[n_points] = {0};
    float dy[n_points] = {0};
    float tmp;
    for (size_t i = 0; i < n_points; ++i) {
        dx[i] = tww_cos(i * M_PI / 2.0 / n_points);
        dy[i] = tww_sin(i * M_PI / 2.0 / n_points);
    }
    Draw::begin(4 * n_points, GX_TRIANGLEFAN);
    for (uint8_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < n_points; ++j) {
            Draw::add_vertex(color, {center.x + dim.x / 2 * dx[j], center.y + dim.y / 2 * dy[j]},
                             {0.5f + dx[j], 0.5f + dy[j]});
            tmp = dx[j];
            dx[j] = -dy[j];
            dy[j] = tmp;
        }
    }
    Draw::end();
}

void drawEllipseOutline(uint32_t color, Vec2 center, Vec2 dim, uint8_t line_width) {
    constexpr const size_t n_points = 4;
    float dx[n_points] = {0};
    float dy[n_points] = {0};
    float tmp;
    for (size_t i = 0; i < n_points; ++i) {
        dx[i] = tww_cos(i * M_PI / 2.0 / n_points);
        dy[i] = tww_sin(i * M_PI / 2.0 / n_points);
    }
    Draw::begin_outline(4 * n_points + 1, line_width);
    for (uint8_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < n_points; ++j) {
            Draw::add_vertex(color, {center.x + dim.x / 2 * dx[j], center.y + dim.y / 2 * dy[j]},
                             {0.5f + dx[j], 0.5f + dy[j]});
            tmp = dx[j];
            dx[j] = -dy[j];
            dy[j] = tmp;
        }
    }
    Draw::add_vertex(color, {center.x + dim.x / 2 * dx[0], center.y + dim.y / 2 * dy[0]},
                     {0.5f + dx[0], 0.5f + dy[0]});
    Draw::end();
}

void drawStickOutline(uint32_t color, Vec2 pos, float size) {
    float s2 = size / 2;
    float dx1 = 0;
    float dy1 = -1.0f;
    float dx2 = 0.7071f;
    float dy2 = -0.7071f;
    float tmp;
    Draw::begin_outline(9, OUTLINE_WIDTH);
    for (uint8_t i = 0; i < 4; ++i) {
        Draw::add_vertex(color, {pos.x + s2 * dx1, pos.y + s2 * dy1}, {0.5f + dx1, 0.5f + dy1});
        Draw::add_vertex(color, {pos.x + s2 * dx2, pos.y + s2 * dy2}, {0.5f + dx2, 0.5f + dy2});
        tmp = dx1;
        dx1 = -dy1;
        dy1 = tmp;
        tmp = dx2;
        dx2 = -dy2;
        dy2 = tmp;
    }
    Draw::add_vertex(color, {pos.x + s2 * dx1, pos.y + s2 * dy1}, {0.5f + dx1, 0.5f + dy1});
    Draw::end();
}

void drawButton(GZPad button, char c, uint32_t color, Vec2 pos, Vec2 dim, float char_size) {
    bool is_button_down = GZ_getButtonPressed(button);
    Draw::drawRectOutline(color, {pos.x, pos.y}, dim, OUTLINE_WIDTH);
    if (is_button_down) {
        Draw::drawRect(color, {pos.x, pos.y}, dim);
    }
    float width = Font::getCharWidth(c, char_size);
    Font::GZ_drawChar(c, pos.x + (dim.x - width) / 2, pos.y + (dim.y + char_size / 2) / 2,
                      is_button_down ? 0x00000060 : color, false, char_size);
}

void drawButtonEllipse(GZPad button, char c, uint32_t color, Vec2 pos, Vec2 dim, float char_size) {
    bool is_button_down = GZ_getButtonPressed(button);
    drawEllipseOutline(color, {pos.x + dim.x / 2, pos.y + dim.y / 2}, dim, OUTLINE_WIDTH);
    if (is_button_down) {
        drawEllipse(color, {pos.x + dim.x / 2, pos.y + dim.y / 2}, dim);
    }
    float width = Font::getCharWidth(c, char_size);
    Font::GZ_drawChar(c, pos.x + (dim.x - width) / 2, pos.y + (dim.y + char_size / 2) / 2,
                      is_button_down ? 0x00000060 : color, false, char_size);
}

void drawCross(uint32_t color, Vec2 pos, float size) {
    float branch_width = 3.f * size / 11.f;
    float branch_length = 4.f * size / 11.f;
    drawButton(GZPad::DPAD_LEFT, '-', color, {pos.x, pos.y + branch_length},
               {branch_length, branch_width}, 8 * size / 25);
    drawButton(GZPad::DPAD_UP, '|', color, {pos.x + branch_length, pos.y},
               {branch_width, branch_length}, 4 * size / 25);
    drawButton(GZPad::DPAD_RIGHT, '-', color,
               {pos.x + branch_length + branch_width, pos.y + branch_length},
               {branch_length, branch_width}, 8 * size / 25);
    drawButton(GZPad::DPAD_DOWN, '|', color,
               {pos.x + branch_length, pos.y + branch_length + branch_width},
               {branch_width, branch_length}, 4 * size / 25);
}

bool stickInRectRange(s8 xmin, s8 ymin, s8 xmax, s8 ymax) {
    return ((tww_mPadStatus.stick_x <= xmax) && (tww_mPadStatus.stick_y <= ymax) && (tww_mPadStatus.stick_x >= xmin) && (tww_mPadStatus.stick_y >= ymin));
}

void InputViewer::drawViewer(Vec2 pos, float scale, bool is_shadow) {
    drawButton(GZPad::A, 'A', is_shadow ? 0x00000060 : 0x00FF7fFF,
               {pos.x + 130.f * scale, pos.y + 30.f * scale}, {30.f * scale, 30.f * scale},
               8 * scale);
    drawButton(GZPad::B, 'B', is_shadow ? 0x00000060 : 0xFF0000FF,
               {pos.x + 108.5f * scale, pos.y + 45.f * scale}, {13.f * scale, 13.f * scale},
               8 * scale);
    drawButton(GZPad::X, 'X', is_shadow ? 0x00000060 : 0xFFFFFFFF,
               {pos.x + 167.5f * scale, pos.y + 30.f * scale}, {15.f * scale, 30.f * scale},
               8 * scale);
    drawButton(GZPad::Y, 'Y', is_shadow ? 0x00000060 : 0xFFFFFFFF,
               {pos.x + 130.f * scale, pos.y + 7.5f * scale}, {30.f * scale, 15.f * scale},
               8 * scale);
    drawButton(GZPad::Z, 'Z', is_shadow ? 0x00000060 : 0x8A2BE2FF,
               {pos.x + 167.5f * scale, pos.y + 7.5f * scale}, {15.f * scale, 15.f * scale},
               8 * scale);
    drawButton(GZPad::START, ' ', is_shadow ? 0x00000060 : 0xFFFFFFFF,
               {pos.x + 87.5f * scale, pos.y + 40.f * scale}, {10.f * scale, 10.f * scale},
               8 * scale);
    drawCross(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x + 95.f * scale, pos.y + 10.f * scale},
              25.f * scale);

    // analog sticks
    uint32_t col;
    double stickMag;
    stickMag = tww_mPadStatus.stick_x*tww_mPadStatus.stick_x + tww_mPadStatus.stick_y*tww_mPadStatus.stick_y;
    if ((g_tools[ESS_CHECKER_INDEX].active)) {
        if (stickInRectRange(-2, -2, 2, 2)) {
            col = BLACK;
        } else if (stickMag <= 81) {
            col = BLUE;
        } else if (stickMag <= 324) {
            col = GREEN;
        } else if (stickMag <= 729) {
            col = YELLOW;
        } else if (stickMag <= 1296) {
            col = ORANGE;
        } else {
            col = RED;
        }
    } else if (g_tools[DEADZONE_CHECKER_INDEX].active && stickInRectRange(-2, -2, 2, 2)) {
        col = RED;
    } else {
        col = WHITE;
    }
    drawStickOutline(is_shadow ? 0x00000060 : col,
                     {pos.x + 17.5f * scale, pos.y + 30.f * scale}, 35.0f * scale);
    drawEllipse(is_shadow ? 0x00000060 : col,
                {pos.x + (17.5f + tww_mPadMStick.mPosX * 10) * scale,
                 pos.y + (30.f - tww_mPadMStick.mPosY * 10) * scale},
                {20.0f * scale, 20.0f * scale});
    drawStickOutline(is_shadow ? 0x00000060 : 0xFFD138FF,
                     {pos.x + 62.5f * scale, pos.y + 30.f * scale}, 35.0f * scale);
    drawEllipse(is_shadow ? 0x00000060 : 0xFFD138FF,
                {pos.x + (62.5f + tww_mPadSStick.mPosX * 10) * scale,
                 pos.y + (30.f - tww_mPadSStick.mPosY * 10) * scale},
                {20.0f * scale, 20.0f * scale});

    // Analog triggers
    Draw::drawRectOutline(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x, pos.y},
                          {35.f * scale, 7.f * scale}, OUTLINE_WIDTH);
    Draw::drawRect(is_shadow                     ? 0x00000060 :
                   GZ_getButtonPressed(GZPad::L) ? 0x00FF00FF :
                                                   0xFFFFFFFF,
                   {pos.x, pos.y}, {35.f * tww_mPadButton.mAnalogLf * scale, 7.f * scale});
    Draw::drawRectOutline(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x + 45.f * scale, pos.y},
                          {35.f * scale, 7.f * scale}, OUTLINE_WIDTH);
    Draw::drawRect(is_shadow                     ? 0x00000060 :
                   GZ_getButtonPressed(GZPad::R) ? 0x00FF00FF :
                                                   0xFFFFFFFF,
                   {pos.x + (45.f + 35.f * (1 - tww_mPadButton.mAnalogRf)) * scale, pos.y},
                   {35.f * tww_mPadButton.mAnalogRf * scale, 7.f * scale});

    // stick inputs
    char control_x[5];  // control stick x
    char control_y[5];  // control stick y
    char c_x[5];        // c stick x
    char c_y[5];        // c stick y

    tww_sprintf(control_x, "%d", tww_mPadStatus.stick_x);
    tww_sprintf(control_y, "%d", tww_mPadStatus.stick_y);
    tww_sprintf(c_x, "%d", tww_mPadStatus.substick_x);
    tww_sprintf(c_y, "%d", tww_mPadStatus.substick_y);

    Font::GZ_drawStr(control_x, pos.x, pos.y + 65.f * scale, is_shadow ? 0x00000060 : 0xFFFFFFFF,
                     false, 13 * scale);
    Font::GZ_drawStr(control_y, pos.x + 23.f * scale, pos.y + 65.f * scale,
                     is_shadow ? 0x00000060 : 0xFFFFFFFF, false, 13 * scale);
    Font::GZ_drawStr(c_x, pos.x + 45.f * scale, pos.y + 65.f * scale,
                     is_shadow ? 0x00000060 : 0xFFD138FF, false, 13 * scale);
    Font::GZ_drawStr(c_y, pos.x + 70.f * scale, pos.y + 65.f * scale,
                     is_shadow ? 0x00000060 : 0xFFD138FF, false, 13 * scale);
}

void InputViewer::draw() {
    Vec2 pos = {0.f, 0.f};
    pos.x += 220.0f /* g_spriteOffsets[VIEWER_INDEX].x */;
    pos.y += 380.0f /* g_spriteOffsets[VIEWER_INDEX].y */;
    float scale = 1.0f;
    if (g_dropShadows)
        drawViewer({pos.x + 1.f, pos.y + 1.f}, scale, true);
    drawViewer(pos, scale, false);
}