#include "menus/menu_actor_spawn/include/actor_spawn_menu.h"
#include <cstdio>
#include "settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/f_op/f_op_actor_mng.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "gz_flags.h"
#include "pos_settings.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "menus/menu_actor_list/include/actor_list_menu.h"
#include "global_data.h"
#include "fs.h"

#define CONTROL_TEXT "X/Y"

/**
 * @brief Used for storing entries from procs.bin
 */
procBinData l_procData;

KEEP_FUNC ActorSpawnMenu::ActorSpawnMenu(ActorSpawnData& data)
    : Menu(data.cursor), l_actorID(data.l_actorID), l_actorParams(data.l_actorParams), l_actorType(data.l_actorType),
      l_paramIdx(data.l_paramIdx),
      l_paramsSelected(false), lines{
                                   {"actor name:", ACTOR_NAME_INDEX, "Actor Name (Dpad / " CONTROL_TEXT " to scroll)",
                                    false},
                                   {"actor params:", ACTOR_PARAM_INDEX, "Actor Parameters (default: 0)", false},
                                   {"actor subtype:", ACTOR_SUBTYPE_INDEX,
                                    "Actor subtype (default: -1) (Dpad / " CONTROL_TEXT " to scroll)", false},
                                   {"spawn", ACTOR_SPAWN_INDEX, "Spawn actor at current position", false},
                               } {
    loadActorName(l_actorID);
}

ActorSpawnMenu::~ActorSpawnMenu() {}

void actorFastCreateAtLink(short id, uint32_t parameters, int8_t subtype) {
    fopAcM_create(id, parameters, &dComIfGp_getPlayer(0)->current.pos, dComIfGp_getPlayer(0)->current.roomNo,
                  &dComIfGp_getPlayer(0)->current.angle, nullptr, subtype, nullptr);
}

void ActorSpawnMenu::loadActorName(s16& i_procName) {
    if (i_procName < 0) {
        i_procName = 501;
    }

    if (i_procName > 501) {
        i_procName = 0;
    }

    int offset = i_procName * 32;
    loadFile("twwgz/procs.bin", &l_procData, sizeof(l_procData), offset);
}

void ActorSpawnMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (l_paramsSelected) {
            cursor.lock_y = false;
            l_paramsSelected = false;
        } else {
            g_menuMgr->pop();
            return;
        }
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        switch (cursor.y) {
        case ACTOR_PARAM_INDEX:
            cursor.lock_y = true;
            l_paramsSelected = true;
            break;
        case ACTOR_SPAWN_INDEX:
            actorFastCreateAtLink(l_actorID, l_actorParams, l_actorType);
            break;
        }
    }

    switch (cursor.y) {
    case ACTOR_NAME_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            l_actorID++;
            loadActorName(l_actorID);
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            l_actorID--;
            loadActorName(l_actorID);
        } else if (GZ_getButtonRepeat(GZPad::X)) {
            l_actorID += 10;
            loadActorName(l_actorID);
        } else if (GZ_getButtonRepeat(GZPad::Y)) {
            l_actorID -= 10;
            loadActorName(l_actorID);
        }
        break;
    case ACTOR_SUBTYPE_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            l_actorType++;
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            l_actorType--;
        } else if (GZ_getButtonRepeat(GZPad::X)) {
            l_actorType += 10;
        } else if (GZ_getButtonRepeat(GZPad::Y)) {
            l_actorType -= 10;
        }
        break;
    }

    auto menu_offset = g_spriteOffsets[SPR_MENU_INDEX];
    float param_offset_x = menu_offset.x + Font::getStrWidth("actor params:  ");
    float param_offset_y = menu_offset.y + 20.0f * (float)(int)ACTOR_PARAM_INDEX;

    char buf[9];
    snprintf(buf, sizeof(buf), "%08X", l_actorParams);
    if (l_paramsSelected) {
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            if (l_paramIdx == 7) {
                l_paramIdx = 0;
            } else if (l_paramIdx >= 0 && l_paramIdx < 8) {
                l_paramIdx++;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            if (l_paramIdx == 0) {
                l_paramIdx = 7;
            } else if (l_paramIdx >= 0 && l_paramIdx < 8) {
                l_paramIdx--;
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            l_actorParams += (0x10000000 >> (l_paramIdx * 4));
        }
        if (GZ_getButtonRepeat(DPAD_DOWN)) {
            l_actorParams -= (0x10000000 >> (l_paramIdx * 4));
        }
        GZ_drawSelectChar(buf, param_offset_x, param_offset_y, l_paramIdx, 7, 0xFFFFFFFF);
    } else {
        Font::GZ_drawStr(buf, param_offset_x, param_offset_y,
                         (cursor.y == ACTOR_PARAM_INDEX ? CURSOR_RGBA : 0xFFFFFFFF), GZ_checkDropShadows());
    }

    lines[ACTOR_NAME_INDEX].printf("[%04X] <%s>", l_actorID, l_procData.procName);
    lines[ACTOR_SUBTYPE_INDEX].printf(" <%d>", l_actorType);

    cursor.move(8, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}