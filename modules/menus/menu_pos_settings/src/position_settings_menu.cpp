#include "menus/menu_pos_settings/include/position_settings_menu.h"
#include <cstdio>
#include "utils/draw.h"
#include "fifo_queue.h"
#include "libtww/include/SSystem/SComponent/c_counter.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define INITAL_SPEED 1.0f
#define INCREMENT_FACTOR 1.05f
#define MAX_SPEED 20.f

KEEP_FUNC PosSettingsMenu::PosSettingsMenu(Cursor& cursor, PosSettingsData& data)
    : Menu(cursor), init_once(data.init_once), l_cursorSpeed(data.l_cursorSpeed), l_selItem(data.l_selItem),
      lines{{"main menu", SpritesIndex::SPR_MENU_INDEX, "Change main menu position", false},
            {"fifo queue", SpritesIndex::SPR_FIFO_INDEX, "Change fifo queue position", false},
            {"link debug info", SpritesIndex::SPR_DEBUG_INFO_INDEX, "Change link debug info position", false},
            {"time display", SpritesIndex::SPR_TIME_DISP_INDEX, "Change Time Display position", false},
            {"input viewer", SpritesIndex::SPR_VIEWER_INDEX, "Change input viewer position", false},
            {"frame timer", SpritesIndex::SPR_COUNT_INDEX, "Change frame timer position", false},
            {"zombie hover info", SpritesIndex::SPR_ZH_INFO_INDEX, "Change zombie hover info position", false},
            {"stage info", SpritesIndex::SPR_SPRITES_STAGE_INFO_INDEX, "Change stage info position", false}} {}

PosSettingsMenu::~PosSettingsMenu() {}

void drawCursor(Vec2 pos) {
    bool cycle = (cCt_getFrameCount() / 8) % 2;
    if (GZ_checkDropShadows()) {
        Draw::drawRectOutline(DROP_SHADOWS_RGBA, {pos.x - 10 + 1, pos.y + 1}, {20, 0}, 0xA);
        Draw::drawRectOutline(DROP_SHADOWS_RGBA, {pos.x + 1, pos.y - 10 + 1}, {0, 20}, 0xA);
    }
    Draw::drawRectOutline(cycle ? g_cursorColor : 0xFFFFFFFF, {pos.x - 10, pos.y}, {20, 0}, 0xA);
    Draw::drawRectOutline(cycle ? g_cursorColor : 0xFFFFFFFF, {pos.x, pos.y - 10}, {0, 20}, 0xA);
}

void PosSettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (l_selItem != POSITION_SETTINGS_NO_SELECTION) {
            l_selItem = POSITION_SETTINGS_NO_SELECTION;
        } else {
            init_once = false;
            g_menuMgr->pop();
            return;
        }
    }

    if (!init_once) {
        l_selItem = POSITION_SETTINGS_NO_SELECTION;
        init_once = true;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        if (cursor.y < SPRITES_AMNT) {
            l_selItem = l_selItem == cursor.y ? POSITION_SETTINGS_NO_SELECTION : cursor.y;
        }
    }

    if (l_selItem != POSITION_SETTINGS_NO_SELECTION && l_selItem < SPRITES_AMNT) {
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT, 3)) {
            g_spriteOffsets[l_selItem].x += l_cursorSpeed;
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT, 3)) {
            g_spriteOffsets[l_selItem].x -= l_cursorSpeed;
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_UP, 3)) {
            g_spriteOffsets[l_selItem].y -= l_cursorSpeed;
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN, 3)) {
            g_spriteOffsets[l_selItem].y += l_cursorSpeed;
        }

        // Draw visual cursor
        drawCursor(g_spriteOffsets[l_selItem]);
    }

    if (GZ_getButtonPressed(GZPad::DPAD_RIGHT) || GZ_getButtonPressed(GZPad::DPAD_LEFT) ||
        GZ_getButtonPressed(GZPad::DPAD_UP) || GZ_getButtonPressed(GZPad::DPAD_DOWN)) {
        if (l_cursorSpeed < MAX_SPEED) {
            l_cursorSpeed *= INCREMENT_FACTOR;
        }
        if (l_cursorSpeed > MAX_SPEED) {
            l_cursorSpeed = MAX_SPEED;
        }
    } else {
        l_cursorSpeed = INITAL_SPEED;
    }

    cursor.lock_x = l_selItem != POSITION_SETTINGS_NO_SELECTION;
    cursor.lock_y = l_selItem != POSITION_SETTINGS_NO_SELECTION;

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
