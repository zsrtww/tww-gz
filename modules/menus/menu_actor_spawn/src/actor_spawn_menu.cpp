#include "menus/menu_actor_spawn/include/actor_spawn_menu.h"
#include <cstdio>
#include "settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/f_op/f_op_actor_mng.h"
#include "libtww/include/f_pc/f_pc_stdcreate_req.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "gz_flags.h"
#include "pos_settings.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "menus/menu_actor_list/include/actor_list_menu.h"
#include "global_data.h"
#include "fs.h"
#include "actor_proc_data.h"

#define CONTROL_TEXT "X/Y"

KEEP_FUNC ActorSpawnMenu::ActorSpawnMenu(ActorSpawnData& data)
    : Menu(data.cursor), mActorID(data.l_actorID), mActorParams(data.l_actorParams), mActorType(data.l_actorType),
      mParamIdx(data.l_paramIdx),
      mParamsSelected(false), lines{
                                  {"actor name:", ACTOR_NAME_INDEX, "Actor Name (Dpad / " CONTROL_TEXT " to scroll)",
                                   false},
                                  {"actor params:", ACTOR_PARAM_INDEX, "Actor Parameters (default: 0)", false},
                                  {"actor subtype:", ACTOR_SUBTYPE_INDEX,
                                   "Actor subtype (default: -1) (Dpad / " CONTROL_TEXT " to scroll)", false},
                                  {"spawn", ACTOR_SPAWN_INDEX, "Spawn actor at current position", false},
                              } {
    loadActorName(mActorID);
}

ActorSpawnMenu::~ActorSpawnMenu() {}

void actorFastCreateAtLink(s16 id, u32 parameters, s8 subtype) {
    fopAcM_prm_class* appen = fopAcM_CreateAppend();
    if (appen != NULL) {
        appen->mParameter = parameters;
        appen->mPos = dComIfGp_getPlayer(0)->current.pos;
        appen->mAngle = dComIfGp_getPlayer(0)->current.angle;
        appen->mEnemyNo = 0xFFFF;
        appen->mSubtype = subtype;
        appen->mRoomNo = dComIfGp_getPlayer(0)->current.roomNo;

        layer_class* curLayer = fpcLy_CurrentLayer();
        fpcSCtRq_Request(curLayer, id, nullptr, nullptr, appen);
    }
}

void ActorSpawnMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (mParamsSelected) {
            cursor.lock_y = false;
            mParamsSelected = false;
        } else {
            g_menuMgr->pop();
            return;
        }
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ACTOR_PARAM_INDEX:
            cursor.lock_y = true;
            mParamsSelected = true;
            break;
        case ACTOR_SPAWN_INDEX:
            actorFastCreateAtLink(mActorID, mActorParams, mActorType);
            break;
        }
    }

    switch (cursor.y) {
    case ACTOR_NAME_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            mActorID++;
            loadActorName(mActorID);
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            mActorID--;
            loadActorName(mActorID);
        } else if (GZ_getButtonRepeat(GZPad::X)) {
            mActorID += 10;
            loadActorName(mActorID);
        } else if (GZ_getButtonRepeat(GZPad::Y)) {
            mActorID -= 10;
            loadActorName(mActorID);
        }
        break;
    case ACTOR_SUBTYPE_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            mActorType++;
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            mActorType--;
        } else if (GZ_getButtonRepeat(GZPad::X)) {
            mActorType += 10;
        } else if (GZ_getButtonRepeat(GZPad::Y)) {
            mActorType -= 10;
        }
        break;
    }

    auto menu_offset = GZ_getSpriteOffset(STNG_SPRITES_MENU);
    float param_offset_x = menu_offset.x + Font::getStrWidth("actor params:  ");
    float param_offset_y = menu_offset.y + 20.0f * (float)(int)ACTOR_PARAM_INDEX;

    char buf[9];
    snprintf(buf, sizeof(buf), "%08X", mActorParams);
    if (mParamsSelected) {
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (mParamIdx == 7) {
                mParamIdx = 0;
            } else if (mParamIdx >= 0 && mParamIdx < 8) {
                mParamIdx++;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (mParamIdx == 0) {
                mParamIdx = 7;
            } else if (mParamIdx >= 0 && mParamIdx < 8) {
                mParamIdx--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            mActorParams += (0x10000000 >> (mParamIdx * 4));
        }
        if (GZ_getButtonRepeat(DPAD_DOWN)) {
            mActorParams -= (0x10000000 >> (mParamIdx * 4));
        }
        GZ_drawSelectChar(buf, param_offset_x, param_offset_y, mParamIdx, 7, 0xFFFFFFFF);
    } else {
        Font::GZ_drawStr(buf, param_offset_x, param_offset_y,
                         (cursor.y == ACTOR_PARAM_INDEX ? CURSOR_RGBA : 0xFFFFFFFF), GZ_checkDropShadows());
    }

    lines[ACTOR_NAME_INDEX].printf("[%04X] <%s>", mActorID, g_procData.procName);
    lines[ACTOR_SUBTYPE_INDEX].printf(" <%d>", mActorType);

    cursor.move(8, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}