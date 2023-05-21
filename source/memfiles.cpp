#include "memfiles.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/f_op/f_op_scene_req.h"
#include "libtww/defines.h"

KEEP_VAR bool g_injectMemfile;
KEEP_VAR bool set_position_data;
KEEP_VAR PositionData memfile_posdata;

bool l_dataCopied;
cXyz l_tmpPos = g_dComIfG_gameInfo.info.mRestart.mRoomPos;
uint16_t l_tmpAngle = g_dComIfG_gameInfo.info.mRestart.mRoomAngleY;

KEEP_FUNC void GZ_setLinkPosition() {
    static int8_t sLoadDelay = 0;//10;

    //if (fopScnRq.isLoading == 1) {
    //    sLoadDelay--;
    //}

    // respawn pos gets overwritten by default spawn, so reinject respawn info
    if (!l_dataCopied) {
        l_tmpPos = g_dComIfG_gameInfo.info.mRestart.mRoomPos;
        l_tmpAngle = g_dComIfG_gameInfo.info.mRestart.mRoomAngleY;
        l_dataCopied = true;
    }

    if (sLoadDelay == 0) {
        if (dComIfGp_getPlayer() != nullptr) {
            dComIfGp_getPlayer()->mCurrent.mPosition = memfile_posdata.link;
            dComIfGp_getPlayer()->mCollisionRot.sy = memfile_posdata.angle;
            g_dComIfG_gameInfo.info.mRestart.mRoomPos = l_tmpPos;
            g_dComIfG_gameInfo.info.mRestart.mRoomAngleY = l_tmpAngle;
            l_dataCopied = false;
        }
        //sLoadDelay = 10;
    }
}