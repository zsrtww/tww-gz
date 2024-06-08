#include "scene.h"
#include "fifo_queue.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/kankyo/d_kankyo.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "libtww/include/JAZelAudio/JAIZelBasic.h"

KEEP_VAR SceneItem g_sceneFlags[SCENE_FLAG_AMNT] = {
    {MUTE_BGM_INDEX, false},
    {FREEZE_TIME_INDEX, false},
};

void GZ_enableBGM() {
    JAIZelBasic::getInterface()->bgmAllUnmute(0);
    JAIZelBasic::getInterface()->subBgmUnmute(0);
}

void GZ_disableBGM() {
    JAIZelBasic::getInterface()->bgmAllMute(0);
    JAIZelBasic::getInterface()->subBgmMute(0);
}