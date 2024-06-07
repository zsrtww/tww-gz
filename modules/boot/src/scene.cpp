#include "scene.h"
#include "fifo_queue.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/kankyo/d_kankyo.h"
#include "libtww/include/m_Do/m_Do_printf.h"

KEEP_VAR SceneItem g_sceneFlags[SCENE_FLAG_AMNT] = {
    {FREEZE_TIME_INDEX, false}
};
