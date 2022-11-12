#include "libtww/JSystem/JUtility/JUTGamePad.h"
#include "controller.h"
#include "libtww/SSystem/SComponent/c_counter.h"
#include "menu.h"

void setGamepadButtons(u32 buttons) {
    tww_mPadButton.mButton = buttons;
}

void setGamepadTrig(u32 buttons) {
    tww_mPadButton.mTrigger = buttons;
}

#define BUTTON_STATES 12
#define REPEAT_TIME 4
#define REPEAT_DELAY 5

#define buttonStatus (tww_mPadStatus.button)

static u16 sButtonsLastFrame = 0;
static u16 sButtons = 0;
static u16 sButtonsPressed = 0;
static u16 sCursorEnableDelay = 0;

struct ButtonState {
    u16 button;
    u32 pressed_frame;
    bool is_down;
};

static ButtonState buttonStates[BUTTON_STATES] = {
    {CButton::DPAD_LEFT, 0xFFFFFFFF, false}, {CButton::DPAD_RIGHT, 0xFFFFFFFF, false},
    {CButton::DPAD_DOWN, 0xFFFFFFFF, false}, {CButton::DPAD_UP, 0xFFFFFFFF, false},
    {CButton::Z, 0xFFFFFFFF, false},         {CButton::R, 0xFFFFFFFF, false},
    {CButton::L, 0xFFFFFFFF, false},         {CButton::A, 0xFFFFFFFF, false},
    {CButton::B, 0xFFFFFFFF, false},         {CButton::X, 0xFFFFFFFF, false},
    {CButton::Y, 0xFFFFFFFF, false},         {CButton::START, 0xFFFFFFFF, false},
};

void GZ_readController() {
    sButtonsLastFrame = sButtons;
    sButtons = buttonStatus;
    sButtonsPressed = sButtons & (0xFFFF ^ sButtonsLastFrame);

    for (u8 idx = 0; idx < BUTTON_STATES; idx++) {
        buttonStates[idx].is_down = (buttonStates[idx].button & sButtons) != 0;
        if ((buttonStates[idx].button & sButtonsPressed) != 0) {
            buttonStates[idx].pressed_frame = cCt_getFrameCount() + 1;
        }
    }

    // GZ_applyCheats();
    if (GZ_checkMenuOpen() == true) {
        u16 current_input = GZ_getButtonStatus();

        // prevent accidentally moving cursor down when opening menu
        if (!g_cursorEnabled) {
            if (current_input & CButton::DPAD_UP) {
                g_cursorEnabled = true;
            } else if (current_input & (CButton::L | CButton::R)) {
                sCursorEnableDelay = 0;
            } else if (sCursorEnableDelay < 1) {
                sCursorEnableDelay = 1;
            }

            if (sCursorEnableDelay >= 4) {
                g_cursorEnabled = true;
            } else if (sCursorEnableDelay > 0) {
                sCursorEnableDelay++;
            }
        }
        g_cursorEnabled = true;

        setGamepadButtons(0);
        setGamepadTrig(0);

        buttonStatus = 0x0;
        tww_mPadButton.mRepeat = 0x0;
    } else {
        g_cursorEnabled = false;
        sCursorEnableDelay = 0;
        // GZCmd_processInputs();
    }
}

bool GZ_getButtonPressed(int idx) {
    return buttonStates[idx].is_down;
}

bool GZ_getButtonRepeat(int idx, u16 repeat_time) {
    auto delta = cCt_getFrameCount() - buttonStates[idx].pressed_frame;
    auto just_clicked = delta == 0;
    auto held_down_long_enough = delta > REPEAT_DELAY;
    auto is_repeat_frame = held_down_long_enough && delta % repeat_time == 0;
    auto down = GZ_getButtonPressed(idx);
    return down && (just_clicked || is_repeat_frame);
}

bool GZ_getButtonRepeat(int idx) {
    return GZ_getButtonRepeat(idx, REPEAT_TIME);
}

u16 GZ_getButtonStatus() {
    return buttonStatus;
}

bool GZ_getButtonTrig(int idx) {
    auto delta = cCt_getFrameCount() - buttonStates[idx].pressed_frame;
    auto just_clicked = delta == 0;

    auto down = GZ_getButtonPressed(idx);
    return down && just_clicked;
}

bool GZ_getButtonHold(int idx, int phase) {
    u32 delta;
    if (phase == /* POST_GAME_LOOP */ 1) {
        delta = cCt_getFrameCount() - buttonStates[idx].pressed_frame;
    } else {
        delta = cCt_getFrameCount() - buttonStates[idx].pressed_frame + 1;
    }

    if (delta != 0) {
        return true;
    } else {
        return false;
    }
}