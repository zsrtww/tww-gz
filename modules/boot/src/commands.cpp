#include "commands.h"
#include "controller.h"
#include "global_data.h"
#include "fs.h"
#include "boot.h"
#include "libtww/include/JSystem/JUtility/JUTGamePad.h"
#include "settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/a/d_a_player_main.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "libtww/include/d/save/d_save.h"
#include "utils/hook.h"

bool g_commandStates[COMMANDS_AMNT];
bool g_timer_reset = false;
bool g_counterToggle = false;
bool g_medli_room = false;
bool g_makar_room = false;

static Vec sSavePlayerPos = {0.0f, 0.0f, 0.0f};
static int16_t sSavePlayerAngle = 0;
/* static Vec sSaveCamPos = {0.0f, 0.0f, 0.0f};
static Vec sSaveCamTarget = {0.0f, 0.0f, 0.0f}; */

static int sLastInputs;
static int sCurInputs;

bool GZCmd_checkTrig(int combo) {
    if (sCurInputs == combo && sLastInputs != combo) {
        return true;
    }
    return false;
}

void GZCmd_storePosition() {
    if (dComIfGp_getPlayer(0)) {
        sSavePlayerPos = dComIfGp_getPlayer(0)->current.pos;
        sSavePlayerAngle = dComIfGp_getPlayer(0)->shape_angle.y;
    }
}

void GZCmd_loadPosition() {
    if (dComIfGp_getPlayer(0)) {
        dComIfGp_getPlayer(0)->current.pos = sSavePlayerPos;
        dComIfGp_getPlayer(0)->current.angle.y = sSavePlayerAngle;
        l_debug_keep_pos = sSavePlayerPos;
        l_debug_current_angle.y = sSavePlayerAngle;
        l_debug_shape_angle.y = sSavePlayerAngle;
    }
}

void GZCmd_moonJump() {
    if (dComIfGp_getPlayer(0)) {
        dComIfGp_getPlayer(0)->speed.y = 56.0f;
    }
}

void GZCmd_storage() {
    g_dComIfG_gameInfo.play.getEvent().mbEndProc = 1;
}

void GZCmd_quarterHeart() {
    dComIfGs_setLife(2);
    dComIfGp_setItemLifeCount(-1);
}
void GZCmd_hoverBoots() {
    if (dComIfGp_getPlayer(0)) {
        daPy_getPlayerLinkActorClass()->setHoverBoots(5 * 30);
    }
}

/*Temporary functions to fix bug with collision codes from inline function*/
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
    daPy_lk_c* player_p = (daPy_lk_c*)dComIfGp_getPlayer(0);

    if (player_p != nullptr) {
        if (player_p->mCurProcID == daPy_lk_c::PROC_SWIM_UP_e || player_p->mCurProcID == daPy_lk_c::PROC_SWIM_WAIT_e ||
            player_p->mCurProcID == daPy_lk_c::PROC_SWIM_MOVE_e) {
            player_p->mVelocity = GZStng_getData<float>(STNG_WATER_SPEED, DEFAULT_WATER_SPEED);
        } else {
            player_p->mVelocity = GZStng_getData<float>(STNG_LAND_SPEED, DEFAULT_LAND_SPEED);
        }
    }
}

void GZCmd_upcharge() {
    daPy_lk_c* player_p = (daPy_lk_c*)dComIfGp_getPlayer(0);

    if (player_p != nullptr) {
        player_p->mVelocity = -550.0f;
    }
}

void GZCmd_areaReload() {
    const char* stage = g_dComIfG_gameInfo.play.mStartStage.getName();
    s16 entrance = g_dComIfG_gameInfo.play.mStartStage.getPoint();
    s8 room = g_dComIfG_gameInfo.play.mStartStage.getRoomNo();
    s8 layer = g_dComIfG_gameInfo.play.mStartStage.getLayer();

    g_dComIfG_gameInfo.play.mNextStage.setName(stage);
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(room);
    if (entrance == -1) {
        g_dComIfG_gameInfo.play.mNextStage.setPoint(g_lastValidPoint);
    } else {
        g_dComIfG_gameInfo.play.mNextStage.setPoint(entrance);
    }
    g_dComIfG_gameInfo.play.mNextStage.setLayer(layer);
    g_dComIfG_gameInfo.play.mNextStage.setEnabled(true);
    g_dComIfG_gameInfo.play.mNextStage.setWipe(0);
}

void GZCmd_full_health() {
    u16 max_life = dComIfGs_getMaxLife();
    u16 life = max_life - dComIfGs_getLife();
    dComIfGs_setLife((max_life));
    dComIfGp_setItemLifeCount(static_cast<f32>(life));
}

void GZCmd_full_magic() {
    u8 max_magic = dComIfGs_getMaxMagic();
    dComIfGs_setMagic(max_magic);
}

void GZCmd_toggleTimer() {
    if (GZCmd_checkTrig(CButton::DPAD_RIGHT | CButton::R | CButton::L)) {
        g_counterToggle = !g_counterToggle;
    }
}

void GZCmd_resetTimer() {
    g_timer_reset = !g_timer_reset;
}

void GZCmd_void() {
    const char* stage_partner = g_dComIfG_gameInfo.play.mStartStage.getName();

    daPy_getPlayerLinkActorClass()->set_void(0, 0xC9, 0.0f, 0);

    if (g_medli_room && strcmp(stage_partner, "M_Dai") == 0) {
        dComIfGs_getpPriest()->set_partner_room(2, dComIfGp_getPlayer(0)->current.pos,
                                                dComIfGp_getPlayer(0)->current.angle.y,
                                                g_dComIfG_gameInfo.play.mNextStage.getRoomNo());
    }

    if (g_makar_room && strcmp(stage_partner, "kaze") == 0) {
        dComIfGs_getpPriest()->set_partner_room(1, dComIfGp_getPlayer(0)->current.pos,
                                                dComIfGp_getPlayer(0)->current.angle.y,
                                                g_dComIfG_gameInfo.play.mNextStage.getRoomNo());
    }
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
    {g_commandStates[CMD_TOGGLE_TIMER], (CButton::DPAD_RIGHT | CButton::R | CButton::L), GZCmd_toggleTimer},
    {g_commandStates[CMD_RESET_TIMER], (CButton::DPAD_LEFT | CButton::R | CButton::L), GZCmd_resetTimer},
    {g_commandStates[CMD_VOID], (CButton::L | CButton::R | CButton::B | CButton::START), GZCmd_void},
    {g_commandStates[CMD_HOVER_BOOTS], (CButton::L | CButton::DPAD_LEFT), GZCmd_hoverBoots}

};

void GZCmd_processInputs() {
    sCurInputs = GZ_getButtonStatus();
    for (auto c : sCommands) {
        if (c.active && GZ_getButtonStatus() == c.buttons) {
            c.command();
            setGamepadButtons(0x0);
            setGamepadTrig(0x0);
            mPadButton.mRepeat = 0x0;
            mPadStatus.button = 0x0;
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
