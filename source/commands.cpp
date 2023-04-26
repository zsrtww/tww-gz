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

void GZCmd_storage() {
    dComIfGs_setStorage();
}

void GZCmd_quarterHeart() {
    dComIfGs_setLife(1);
}

void GZCmd_normalCollision() {
    u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr &= 0xFFFF ^ 0x4004;
}

void GZCmd_chestStorage() {
    u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr = (*collision_ptr & (0xFFFF ^ 0x4000)) | 0x4;
}

void GZCmd_doorCancel() {
    u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr |= 0x4004;
}

void GZCmd_fastMovement() {
    u32 link_state = dComIfGs_getLinkState();
    if (link_state >= 53 && link_state <= 55) dComIfGs_setSpeed(2000);
    else dComIfGs_setSpeed(150);
}

static Command sCommands[COMMANDS_AMNT] = {
    {g_commandStates[CMD_STORE_POSITION], (CButton::DPAD_UP | CButton::R), GZCmd_storePosition},
    {g_commandStates[CMD_LOAD_POSITION], (CButton::DPAD_DOWN | CButton::R), GZCmd_loadPosition},
    {g_commandStates[CMD_MOON_JUMP], (CButton::R | CButton::A), GZCmd_moonJump},
    {g_commandStates[CMD_STORAGE], (CButton::DPAD_RIGHT), GZCmd_storage},
    {g_commandStates[CMD_NORMAL_COLLISION], (CButton::L | CButton::DPAD_DOWN), GZCmd_normalCollision},
    {g_commandStates[CMD_CHEST_STORAGE], (CButton::L | CButton::DPAD_RIGHT), GZCmd_chestStorage},
    {g_commandStates[CMD_DOOR_CANCEL], (CButton::L | CButton::DPAD_LEFT), GZCmd_doorCancel},
    {g_commandStates[CMD_QUARTER_HEART], (CButton::R | CButton::DPAD_LEFT), GZCmd_quarterHeart},
    {g_commandStates[CMD_FAST_MOVEMENT], (CButton::DPAD_LEFT), GZCmd_fastMovement}
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