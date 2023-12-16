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
    if (dComIfGp_getPlayer(0)) {
        sSavePlayerPos = dComIfGp_getPlayer(0)->current.mPosition;
        sSavePlayerAngle = dComIfGp_getPlayer(0)->current.mAngle;
    }
}

void GZCmd_loadPosition() {
    if (dComIfGp_getPlayer(0)) {
        dComIfGp_getPlayer(0)->current.mPosition = sSavePlayerPos;
        dComIfGp_getPlayer(0)->current.mAngle = sSavePlayerAngle;
        l_debug_keep_pos = sSavePlayerPos;
        l_debug_current_angle = sSavePlayerAngle;
        l_debug_shape_angle = sSavePlayerAngle;
    }
}

void GZCmd_moonJump() {
    if (dComIfGp_getPlayer(0)) {
        dComIfGp_getPlayer(0)->speed.y = 56.0f;
    }
}

void GZCmd_storage() {
    // dComIfGs_setStorage();
}

void GZCmd_quarterHeart() {
    dComIfGs_setLife(1);
}

void GZCmd_normalCollision() {
    /* u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr &= 0xFFFF ^ 0x4004; */
}

void GZCmd_chestStorage() {
    /* u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr = (*collision_ptr & (0xFFFF ^ 0x4000)) | 0x4; */
}

void GZCmd_doorCancel() {
    /* u16* collision_ptr = dComIfGs_getCollision();
    *collision_ptr |= 0x4004; */
}

void GZCmd_fastMovement() {
    /* u32 link_state = dComIfGs_getLinkState();
    if (link_state >= 53 && link_state <= 55) dComIfGs_setSpeed(2000);
    else dComIfGs_setSpeed(150); */
}

void GZCmd_upcharge() {
    /* dComIfGs_setSpeed(-550); */
}

void GZCmd_areaReload() {
    const char* stage = g_dComIfG_gameInfo.play.mStartStage.getName();
    s16 entrance = g_dComIfG_gameInfo.play.mStartStage.getPoint();
    s8 room = g_dComIfG_gameInfo.play.mStartStage.getRoomNo();
    s8 layer = g_dComIfG_gameInfo.play.mStartStage.getLayer();

    g_dComIfG_gameInfo.play.mNextStage.setName(stage);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(entrance);
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(room);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(layer);
    g_dComIfG_gameInfo.play.mNextStage.setEnabled(true);
    g_dComIfG_gameInfo.play.mNextStage.setWipe(0);
}

void GZCmd_full_health() {
    u16 max_life = dComIfGs_getMaxLife();
    dComIfGs_setLife(max_life);
}

void GZCmd_full_magic() {
    u8 max_magic = dComIfGs_getMaxMagic();
    dComIfGs_setMagic(max_magic);
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
    {g_commandStates[CMD_FAST_MOVEMENT], (CButton::DPAD_LEFT), GZCmd_fastMovement},
    {g_commandStates[CMD_UPCHARGE], (CButton::X | CButton::Z), GZCmd_upcharge},
    {g_commandStates[CMD_AREA_RELOAD], (CButton::L | CButton::R | CButton::A | CButton::START), GZCmd_areaReload},
    {g_commandStates[CMD_REFILL_HEALTH], (CButton::R | CButton::DPAD_RIGHT), GZCmd_full_health},
    {g_commandStates[CMD_REFILL_MAGIC], (CButton::L | CButton::DPAD_UP), GZCmd_full_magic},
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