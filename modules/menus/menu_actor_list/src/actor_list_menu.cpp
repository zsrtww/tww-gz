#include <cstdio>
#include "menus/menu_actor_list/include/actor_list_menu.h"
#include "memory_editor.h"
#include "settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/d_meter.h"
#include "libtww/include/f_op/f_op_actor_mng.h"
#include "libtww/include/d/d_procname.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "fs.h"
#include "global_data.h"
#include "actor_proc_data.h"

#define MEM_TEXT "Z"
#define SLOW_INC_TEXT "X"
#define FAST_INC_TEXT "Y"
#define DELETE_TEXT "START"

// This needs to be figured out after d_menu_windows is decompiled
/**
 * @brief Checks and closes any menu that's currently open.
 *
 * @details This function is used to close any menu that's currently open.
 * It stores the current menu status and then closes the menu by setting the status to none and running the currently
 * open menu's closer function via move_proc function table.
 *
 */

/*
void ActorListMenu::checkAndCloseMenu() {
    if (g_meter2_info.mMenuWindowClass) {
        switch (g_meter2_info.mMenuWindowClass->mMenuStatus) {
        case dMw_c::NO_MENU:
            g_dComIfG_gameInfo.play.mPauseFlag = false;
            break;
        default:
            l_menuStatus = g_meter2_info.mMenuWindowClass->mMenuStatus;
            l_windowStatus = g_meter2_info.mWindowStatus;
            g_meter2_info.offMenuInForce(g_meter2_info.mMenuWindowClass->mMenuStatus);
            g_meter2_info.mMenuWindowClass->mMenuStatus = dMw_c::NO_MENU;
            g_meter2_info.mWindowStatus = dMw_c::NO_MENU;
            g_dComIfG_gameInfo.play.mPauseFlag = false;
            break;
        }
    }
}
*/

/**
 * @brief Checks and restores any menu that was previously open.
 *
 * @details This function is used to restore any menu that was previously open.
 * It restores the menu by setting the status to the stored status and setting the currently stored menu status's
 * corresponding window status.
 *
 * @note There doesn't seem to be the need to run the opener function like there is with the checkAndCloseMenu function.
 * Just restoring the menu status and window status seems to be enough.
 *
 */
/*
void ActorListMenu::checkAndRestoreMenu() {
    if (l_menuStatus != dMw_c::NO_MENU) {
        g_dComIfG_gameInfo.play.mPauseFlag = true;

        switch (l_menuStatus) {
        case dMw_c::RING_MOVE:
        case dMw_c::COLLECT_MOVE:
        case dMw_c::FMAP_MOVE:
        case dMw_c::SAVE_MOVE:
        case dMw_c::OPTIONS_MOVE:
        case dMw_c::LETTER_MOVE:
        case dMw_c::FISHING_MOVE:
        case dMw_c::SKILL_MOVE:
        case dMw_c::INSECT_MOVE:
        case dMw_c::INSECT_AGITHA_MOVE:
        case dMw_c::DMAP_MOVE:
            g_meter2_info.mWindowStatus = l_windowStatus;
            g_meter2_info.mMenuWindowClass->mMenuStatus = l_menuStatus;
            break;
        }
    }
}
*/

KEEP_FUNC ActorListMenu::ActorListMenu(Cursor& cursor, ActorListData& data)
    : Menu(cursor), l_index(data.l_index),
      lines{
          {"", ACTOR_PROC_NAME_INDEX, "A: freeze actor, " DELETE_TEXT ": delete actor, " MEM_TEXT " view memory",
           false},
          {"", ACTOR_OBJECT_NAME_INDEX, "current actor's object name", false},
          {"", ACTOR_PROC_ID_INDEX, "current actor's process ID", false},
          {"", ACTOR_GROUP_INDEX, "current actor's group name", false},
          {"", ACTOR_PARAMS_INDEX, "current actor parameters", false},
          {"", ACTOR_ADDRESS_INDEX, "current actor address", false},
          {"", ACTOR_POSITION_X_INDEX,
           "dpad: +/-100.0, " SLOW_INC_TEXT "+dpad: +/-1.0, " FAST_INC_TEXT "+dpad: +/-1000.0", false},
          {"", ACTOR_POSITION_Y_INDEX,
           "dpad: +/-100.0, " SLOW_INC_TEXT "+dpad: +/-1.0, " FAST_INC_TEXT "+dpad: +/-1000.0", false},
          {"", ACTOR_POSITION_Z_INDEX,
           "dpad: +/-100.0, " SLOW_INC_TEXT "+dpad: +/-1.0, " FAST_INC_TEXT "+dpad: +/-1000.0", false},
          {"", ACTOR_ANGLE_X_INDEX, "dpad: +/-100, " SLOW_INC_TEXT "+dpad: +/-1, " FAST_INC_TEXT "+dpad: +/-1000",
           false},
          {"", ACTOR_ANGLE_Y_INDEX, "dpad: +/-100, " SLOW_INC_TEXT "+dpad: +/-1, " FAST_INC_TEXT "+dpad: +/-1000",
           false},
          {"", ACTOR_ANGLE_Z_INDEX, "dpad: +/-100, " SLOW_INC_TEXT "+dpad: +/-1, " FAST_INC_TEXT "+dpad: +/-1000",
           false},
      } {
    // store camera position and target
    l_cameraPos = g_dComIfG_gameInfo.play.mCameraInfo->mCameraPos;
    l_cameraTarget = g_dComIfG_gameInfo.play.mCameraInfo->mCameraTarget;

    // remove any currently open menus
    // checkAndCloseMenu();

    // initial data load from procs.bin
    updateActorData();
    loadActorName();
}

ActorListMenu::~ActorListMenu() {
    // restore any previously open menu
    // checkAndRestoreMenu();

    // restore camera position and target
    g_dComIfG_gameInfo.play.mCameraInfo->mCameraPos = l_cameraPos;
    g_dComIfG_gameInfo.play.mCameraInfo->mCameraTarget = l_cameraTarget;

    dComIfGp_getPEvtManager()->mCameraPlay = 0;
    g_meterHIO.field_0x18 = 1.0f;
}

template <typename T>
void ActorListMenu::updateValue(T* value, bool increase) {
    if (value != NULL) {
        f32 change;
        GZ_getButtonPressed(GZPad::Y) ? change = 1000.0f :
        GZ_getButtonPressed(GZPad::X) ? change = 1.0f :
                                        change = 100.0f;

        *value += (increase ? 1 : -1) * change;
    }
}

void ActorListMenu::updateActorData() {
    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = NULL;

    for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
        if (i == l_index && node != NULL) {
            create_tag_class* tag = (create_tag_class*)node;
            actorData = (fopAc_ac_c*)tag->mpTagData;
            break;
        }

        node = node->mpNextNode;
    }

    g_currentActor = actorData;
}

const char* ActorListMenu::getGroup(fopAc_ac_c* actor) {
    const char* group = "";

    if (actor != nullptr) {
        switch (actor->mGroup) {
        case 0:
            group = "ACTOR";
            break;
        case 1:
            group = "PLAYER";
            break;
        case 2:
            group = "ENEMY";
            break;
        case 3:
            group = "ENV";
            break;
        case 4:
            group = "NPC";
            break;
        }
    }
    return group;
}

const char* ActorListMenu::getObjectName(fopAc_ac_c* actor) {
    const char* object = "";

    if (actor != nullptr) {
        object = fopAcM_getProcNameString(actor);

        // Check for the error message of "誰？" or "who?", to translate it.
        // strcmp with the japanese text doesnt work because of encoding issues.
        if (object[0] == 0x92 && object[1] == 0x4E) {
            object = "n/a";
        }
    }

    return object;
}

void ActorListMenu::draw() {
    g_actorViewEnabled = true;
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        // disable gadget and close menu
        g_actorViewEnabled = false;
        g_menuMgr->pop();
        return;
    }

    bool rightPressed = GZ_getButtonRepeat(GZPad::DPAD_RIGHT, 1);
    bool leftPressed = GZ_getButtonRepeat(GZPad::DPAD_LEFT, 1);

    switch (cursor.y) {
    case ACTOR_PROC_NAME_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            l_index++;
            if (l_index > g_fopAcTg_Queue.mSize - 1)
                l_index = 0;

            updateActorData();
            loadActorName();
        }

        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            l_index--;
            if (l_index > g_fopAcTg_Queue.mSize - 1)
                l_index = g_fopAcTg_Queue.mSize - 1;

            updateActorData();
            loadActorName();
        }

        if (GZ_getButtonRepeat(GZPad::START)) {
            if (g_currentActor) {
                if (g_currentActor->mBase.mProcName != PROC_PLAYER) {
                    fopAcM_delete(g_currentActor);
                }
            }
        }

        if (GZ_getButtonRepeat(GZPad::A)) {
            if (g_currentActor) {
                g_currentActor->mBase.mPauseFlag = !g_currentActor->mBase.mPauseFlag;
            }
        }

        if (GZ_getButtonTrig(GZPad::Z)) {
            switch (cursor.y) {
            case ACTOR_PROC_NAME_INDEX:
                g_memoryEditor_addressIndex = (uint32_t)g_currentActor;
                g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
                return;
            }
        }

        break;

    case ACTOR_OBJECT_NAME_INDEX:
        break;

    case ACTOR_PROC_ID_INDEX:
        break;

    case ACTOR_GROUP_INDEX:
        break;

    case ACTOR_PARAMS_INDEX:
        break;

    case ACTOR_POSITION_X_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->current.pos.x, rightPressed);
        }
        break;

    case ACTOR_POSITION_Y_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->current.pos.y, rightPressed);
        }
        break;

    case ACTOR_POSITION_Z_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->current.pos.z, rightPressed);
        }
        break;

    case ACTOR_ANGLE_X_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->shape_angle.x, rightPressed);
        }
        break;

    case ACTOR_ANGLE_Y_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->shape_angle.y, rightPressed);
        }
        break;

    case ACTOR_ANGLE_Z_INDEX:
        if (rightPressed || leftPressed) {
            updateValue(&g_currentActor->shape_angle.z, rightPressed);
        }
        break;
    }

    if (g_currentActor) {
        lines[ACTOR_PROC_NAME_INDEX].printf("proc name:  <%s>", g_procData.procName);
        lines[ACTOR_OBJECT_NAME_INDEX].printf("object name: %s", getObjectName(g_currentActor));
        lines[ACTOR_PROC_ID_INDEX].printf("proc id: %d", g_currentActor->mBase.mBsPcId);
        lines[ACTOR_GROUP_INDEX].printf("group: %s", getGroup(g_currentActor));
        lines[ACTOR_PARAMS_INDEX].printf("params:  0x%08X", g_currentActor->mBase.mParameters);
        lines[ACTOR_ADDRESS_INDEX].printf("address: 0x%08X", g_currentActor);
        lines[ACTOR_POSITION_X_INDEX].printf("pos-x: <%.1f>", g_currentActor->current.pos.x);
        lines[ACTOR_POSITION_Y_INDEX].printf("pos-y: <%.1f>", g_currentActor->current.pos.y);
        lines[ACTOR_POSITION_Z_INDEX].printf("pos-z: <%.1f>", g_currentActor->current.pos.z);
        lines[ACTOR_ANGLE_X_INDEX].printf("rot-x: <0x%04X>", static_cast<u16>(g_currentActor->shape_angle.x));
        lines[ACTOR_ANGLE_Y_INDEX].printf("rot-y: <0x%04X>", static_cast<u16>(g_currentActor->shape_angle.y));
        lines[ACTOR_ANGLE_Z_INDEX].printf("rot-z: <0x%04X>", static_cast<u16>(g_currentActor->shape_angle.z));
    }

    cursor.move(0, ACTOR_LIST_LINE_COUNT);
    GZ_drawMenuLines(lines, cursor.y, ACTOR_LIST_LINE_COUNT);
}