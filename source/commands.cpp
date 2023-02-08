#include "commands.h"
#include "controller.h"
#include "lib.h"
#include "menus/settings_menu.h"
#include "libtww/d/com/d_com_inf_game.h"

bool g_commandStates[COMMANDS_AMNT];

static Vec sSavePlayerPos = {0.0f, 0.0f, 0.0f};
static SVec sSavePlayerAngle = {0, 0, 0};

static int sLastInputs;
static int sCurInputs;

bool GZCmd_checkTrig(int combo) {
    if (sCurInputs == combo && sLastInputs != combo) {
        return true;
    }
    return false;
}

/* void GZCmd_pauseFrame() {
    if (GZCmd_checkTrig(FRAME_PAUSE_BUTTONS)) {
        g_framePaused = !g_framePaused;
    }
} */

void GZCmd_storePosition() {
    if (dComIfGp_getPlayer()) {
        sSavePlayerPos = dComIfGp_getPlayer()->mCurrent.mPosition;
        sSavePlayerAngle = dComIfGp_getPlayer()->mCurrent.mAngle;
    }
}

void GZCmd_loadPosition() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mCurrent.mPosition = sSavePlayerPos;
        dComIfGp_getPlayer()->mCurrent.mAngle = sSavePlayerAngle;
        l_debug_keep_pos = sSavePlayerPos;
        l_debug_current_angle = sSavePlayerAngle;
        l_debug_shape_angle = sSavePlayerAngle;
    }
}

void GZCmd_moonJump() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mSpeed.y = 56.0f;
    }
}

static Command sCommands[COMMANDS_AMNT] = {
    {g_commandStates[CMD_STORE_POSITION], (CButton::DPAD_UP | CButton::R), GZCmd_storePosition},
    {g_commandStates[CMD_LOAD_POSITION], (CButton::DPAD_DOWN | CButton::R), GZCmd_loadPosition},
    {g_commandStates[CMD_MOON_JUMP], (CButton::R | CButton::A), GZCmd_moonJump},
};

void GZCmd_processInputs() {
    sCurInputs = GZ_getButtonStatus();
    for (auto c : sCommands) {
        if (c.active && GZ_getButtonStatus() == c.buttons) {
            c.command();
            setGamepadButtons(0);
            setGamepadTrig(0);
            tww_mPadButton.mRepeat = 0;
            tww_mPadStatus.button = 0;
        }
    }
    sLastInputs = sCurInputs;
}

void GZCmd_enable(int idx) {
    sCommands[idx].active = true;
}

void GZCmd_disable(int idx) {
    sCommands[idx].active = false;
}