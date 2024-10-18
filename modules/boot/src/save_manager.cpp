#include <cstdio>
#include "fs.h"
#include "libtww/include/dolphin/os/OSCache.h"
#include "settings.h"
#include "save_manager.h"
#include "menu.h"
#include "utils/card.h"
#include "fifo_queue.h"
#include "practice.h"
#include "equip_priority.h"
#include "menus/utils/menu_mgr.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/d/com/d_com_static.h"
#include "libtww/include/f_op/f_op_scene_req.h"
#include "libtww/include/m_Do/m_Do_printf.h"

static char l_filename[128];
SaveManager gSaveManager;

bool SaveManager::s_injectSave = false;

void SaveManager::injectSave(void* src) {
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mPlayerStatusA, src, 0x18);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mPlayerStatusB, (char*)src + 0x18, 0x18);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mReturnPlace, (char*)src + 0x30, 0xc);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mPlayerItem, (char*)src + 0x3c, 0x15);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mGetItem, (char*)src + 0x51, 0x15);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mItemRecord, (char*)src + 0x66, 8);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mItemMax, (char*)src + 0x6e, 8);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mBagItem, (char*)src + 0x76, 0x18);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mGetBagItem, (char*)src + 0x8e, 0xc);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mBagItemRecord, (char*)src + 0x9a, 0x18);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mCollect, (char*)src + 0xb2, 0xd);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mMap, (char*)src + 0xbf, 0x84);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mInfo, (char*)src + 0x143, 0x5c);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mConfig, (char*)src + 0x19f, 5);
    memcpy((void*)&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mPriest, (char*)src + 0x1a4, 0x10);
    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mPlayer.mStatusC, (char*)src + 0x1b4, 0x1c0);

    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mSave, (char*)src + 0x374, 0x240);

    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mOcean, (char*)src + 0x5b4, 0x64);

    memcpy(&g_dComIfG_gameInfo.info.mSavedata.mEvent, (char*)src + 0x618, 0x100);

    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
}

void SaveManager::injectDefault_before() {
    g_dComIfG_gameInfo.play.mNextStage.mWipe = 0;
}

void SaveManager::injectDefault_during() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(-1);
}

void SaveManager::injectDefault_after() {}

void SaveManager::defaultLoad() {
    gSaveManager.mPracticeFileOpts.inject_options_during_load = SaveManager::injectDefault_during;
    gSaveManager.mPracticeFileOpts.inject_options_after_load = SaveManager::injectDefault_after;
    g_fifoVisible = true;
    g_menuMgr->hide();
}

void SaveManager::loadSave(uint32_t id, const char* category, special i_specials[], int size) {
    SaveManager::injectDefault_before();

    // Load the corresponding file path and properties
    snprintf(l_filename, sizeof(l_filename), "twwgz/save_files/%s.bin", category);
    loadFile(l_filename, &gSaveManager.mPracticeSaveInfo, sizeof(gSaveManager.mPracticeSaveInfo),
             id * sizeof(gSaveManager.mPracticeSaveInfo));

    snprintf(l_filename, sizeof(l_filename), "twwgz/save_files/%s/%s.bin", category,
             gSaveManager.mPracticeSaveInfo.filename);

    SaveManager::defaultLoad();

    if (gSaveManager.mPracticeSaveInfo.requirements) {
        gSaveManager.mPracticeFileOpts.inject_options_after_counter = gSaveManager.mPracticeSaveInfo.counter;
    }

    // If the selected file was a special, run the special callbacks
    if (i_specials) {
        for (int i = 0; i < size; ++i) {
            if (id == i_specials[i].idx) {
                if (i_specials[i].loadingCallback) {
                    gSaveManager.mPracticeFileOpts.inject_options_during_load = i_specials[i].loadingCallback;
                }
                break;
            }
        }
    }
}

void SaveManager::loadSavefile(const char* l_filename) {
    loadFile(l_filename, MEMFILE_BUF, sizeof(dSv_save_c), 0);
}

KEEP_FUNC void SaveManager::triggerLoad(uint32_t id, const char* category, special i_specials[], int size) {
    loadSave(id, category, i_specials, size);

    SaveManager::loadSavefile(l_filename);
    dSv_save_c* save = (dSv_save_c*)MEMFILE_BUF;

    // Default to normal arrow. The special callbacks will handle other cases.
    daArrow_c__m_keep_type = 0;

    int state = tww_getLayerNo(save->getPlayer().mReturnPlace.mName, save->getPlayer().mReturnPlace.mRoomNo, 0xFF);

    g_dComIfG_gameInfo.play.mNextStage.mRoomNo = save->getPlayer().mReturnPlace.mRoomNo;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = save->getPlayer().mReturnPlace.mPoint;
    strcpy(g_dComIfG_gameInfo.play.mNextStage.mName, save->getPlayer().mReturnPlace.mName);
    g_dComIfG_gameInfo.play.mNextStage.mLayer = state;

    g_dComIfG_gameInfo.info.getRestart().mLastMode = 0;
    g_dComIfG_gameInfo.play.mNextStage.mEnable = true;

    // inject options after initial stage set since some options change stage location
    if (gSaveManager.mPracticeFileOpts.inject_options_during_load) {
        gSaveManager.mPracticeFileOpts.inject_options_during_load();
    }

    s_injectSave = true;
}

GZSettingID l_mapping[] = {
    STNG_ITEM_EQUIP_TELESCOPE,
    STNG_ITEM_EQUIP_SAIL,
    STNG_ITEM_EQUIP_WIND_WAKER,
    STNG_ITEM_EQUIP_GRAPPLING_HOOK,
    STNG_ITEM_EQUIP_BOOMERANG,
    STNG_ITEM_EQUIP_DEKU_LEAF,
    STNG_ITEM_EQUIP_TINGLE_TUNER,
    STNG_ITEM_EQUIP_PROGRESSIVE_PICTO_BOX,
    STNG_ITEM_EQUIP_IRON_BOOTS,
    STNG_ITEM_EQUIP_MAGIC_ARMOR,
    STNG_ITEM_EQUIP_PROGRESSIVE_BOW,
    STNG_ITEM_EQUIP_BOMBS,
    STNG_ITEM_EQUIP_HOOKSHOT,
    STNG_ITEM_EQUIP_SKULL_HAMMER,
};

static const ItemSlots l_slots[] = {
    SLOT_TELESCOPE,
    SLOT_SAIL,
    SLOT_WIND_WAKER,
    SLOT_ROPE,
    SLOT_BOOMERANG,
    SLOT_DEKU_LEAF,
    SLOT_TUNER,
    SLOT_CAMERA,
    SLOT_IRON_BOOTS,
    SLOT_MAGIC_ARMOR,
    SLOT_BOW,
    SLOT_BOMB,
    SLOT_HOOKSHOT,
    SLOT_HAMMER,
};

// runs at the beginning of phase_1 of dScnPly__phase_1 load sequence
KEEP_FUNC void SaveManager::loadData() {
    if (s_injectSave) {
        SaveManager::injectSave(MEMFILE_BUF);

        if (gSaveManager.mPracticeFileOpts.inject_options_after_load) {
            gSaveManager.mPracticeFileOpts.inject_options_after_load();
        }

        if (GZStng_getData<bool>(STNG_EQUIP_PRIORITY, false)) {
            u8 cur_item_x = dComIfGs_getSelectItem(0);
            u8 cur_item_y = dComIfGs_getSelectItem(1);
            u8 cur_item_z = dComIfGs_getSelectItem(2);

            u8 new_items[3] = {NO_ITEM, NO_ITEM, NO_ITEM};

            for (int i = 0; i < NUM_ITEM_EQUIPS; i++) {
                u8 item_slot = l_slots[i];
                auto stng = GZStng_get(l_mapping[i]);
                u8 highest_priority = name_X;
                u8 medium_priority = name_Y;
                if (stng) {
                    highest_priority = static_cast<ItemEquipSettings*>(stng->data)->high_priority;
                    medium_priority = static_cast<ItemEquipSettings*>(stng->data)->medium_priority;
                }

                if (item_slot == NO_ITEM)
                    continue;

                if (item_slot == cur_item_x || item_slot == cur_item_y || item_slot == cur_item_z) {
                    if (new_items[highest_priority] == NO_ITEM) {
                        new_items[highest_priority] = item_slot;
                    } else if (new_items[medium_priority] == NO_ITEM) {
                        new_items[medium_priority] = item_slot;
                    } else {
                        new_items[3 - highest_priority - medium_priority] = item_slot;
                    }
                }
            }

            dComIfGs_setSelectItem(0, new_items[name_X]);
            dComIfGs_setSelectItem(1, new_items[name_Y]);
            dComIfGs_setSelectItem(2, new_items[name_Z]);
        }

        s_injectSave = false;
    }
}

KEEP_FUNC void SaveManager::RemoveActorModRequest(u32 id) {
    for (auto req = mDeque.begin(); req != mDeque.end(); ++req) {
        if (req->id == id) {
            mDeque.erase(req);
        }
    }
}

KEEP_FUNC void SaveManager::ProcessActorModRequests() {
    // Actor modification requests get added as soon as the practice save is selected.
    // To prevent the requests from being processed immediately while the game is still fading out,
    // first `mNextStage.mEnable` is checked.
    // Then on the other side of the load, it is necessary to wait for the scene/stage/room to finish
    // processing, because these creation steps can sometimes modify actors.
    // When `l_fopScnRq_IsUsingOfOverlap` is false, the scene is done loading and the fade in
    // will begin. This gurantees that the stage/room is ready and actors can be modified.

    if (!g_dComIfG_gameInfo.play.mNextStage.mEnable && !l_fopScnRq_IsUsingOfOverlap) {
        for (auto req = mDeque.begin(); req != mDeque.end(); ++req) {
            fopAc_ac_c* actor;

            if (req->judgeFunc != nullptr) {
                // Use the "judge" search function supplied by the request to find a specific actor
                actor = (fopAc_ac_c*)fopAcIt_Judge(req->judgeFunc, nullptr);
            } else {
                // This version of `fopAcM_SearchByName` has an `IsCreating` check which
                // the inline version does not have.
                fopAcM_SearchByName(req->procName, &actor);
            }

            if (actor != nullptr) {
                // Actor was found, process the modification request
                req->callback(actor);
                RemoveActorModRequest(req->id);
            } else {
                // Actor not found, try again next frame
                req->attempts++;

                // Dont allow attempts to last longer than 5 seconds
                if (req->attempts >= 150) {
                    OSReport("Couldn't find actor:%d, deleting req:%d\n", req->procName, req->id);
                    RemoveActorModRequest(req->id);
                }
            }
        }
    }
}