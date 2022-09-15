#include "utils/card.h"
#include "math.h"
#include "menus/settings_menu.h"
#include "libtww/MSL_C/math/s_ceil.h"

/**
 * @brief Like CARDWrite, but allows for arbitrary sizes and offsets.
 */
int32_t GZ_storageWrite(Storage* storage, void* data, int32_t size, int32_t offset,
                        int32_t sector_size) {
    uint8_t* buf = (uint8_t*)tww_memalign(-32, sector_size);
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        tww_memcpy(buf + (offset & (sector_size - 1)), (void*)((uint32_t)data + read_bytes),
                  MIN(rem_size, size));
        StorageWrite(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tww_free(buf);
    return result;
}

/**
 * @brief Like CARDRead, but allows for arbitrary sizes and offsets.
 */
int32_t GZ_storageRead(Storage* storage, void* data, int32_t size, int32_t offset,
                       int32_t sector_size) {
    uint8_t* buf = (uint8_t*)tww_memalign(-32, sector_size);
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        tww_memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (sector_size - 1)),
                  MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tww_free(buf);
    return result;
}

void GZ_storeSaveLayout(GZSaveLayout& save_layout) {
    save_layout.mDropShadows = g_dropShadows;
    save_layout.mCursorColType = g_cursorColorType;
    save_layout.mFontType = g_fontType;
}

void GZ_loadSaveLayout(GZSaveLayout& save_layout) {
    g_dropShadows = save_layout.mDropShadows;
    g_cursorColorType = save_layout.mCursorColType;
    g_fontType = save_layout.mFontType;
}

void GZ_setupSaveFile(GZSaveFile& save_file) {
    save_file.header.version = GZ_SAVE_VERSION_NUMBER;
    save_file.header.entries = GZ_SAVE_ENTRIES_AMNT;
    save_file.header.offsetsLoc = offsetof(GZSaveFile, offsets);
    save_file.header.sizesLoc = offsetof(GZSaveFile, sizes);
#define set_entry(idx, attr)                                                                       \
    save_file.offsets[idx] = offsetof(GZSaveFile, data) + offsetof(GZSaveLayout, attr);            \
    save_file.sizes[idx] = sizeof(save_file.data.attr)

    set_entry(SV_CURSOR_COLOR_INDEX, mCursorColType);
    set_entry(SV_FONT_INDEX, mFontType);
    set_entry(SV_DROP_SHADOW_INDEX, mDropShadows);
#undef set_entry
}

int32_t GZ_readSaveFile(Storage* storage, GZSaveFile& save_file, int32_t sector_size) {
    int32_t result = Ready;
#define assert_result(stmt)                                                                        \
    if ((result = (stmt)) != Ready) {                                                              \
        return result;                                                                             \
    }

    uint32_t pos = 0;
    assert_result(
        GZ_storageRead(storage, &save_file.header, sizeof(save_file.header), pos, sector_size));
    pos += sizeof(save_file.header);
    if (save_file.header.version != GZ_SAVE_VERSION_NUMBER) {
        return -30;  // Custom error code for "Version" (means a mismatch in the version number).
    }
    assert_result(GZ_storageRead(storage, save_file.offsets,
                                 save_file.header.entries * sizeof(save_file.offsets[0]),
                                 save_file.header.offsetsLoc, sector_size));
    assert_result(GZ_storageRead(storage, save_file.sizes,
                                 save_file.header.entries * sizeof(save_file.sizes[0]),
                                 save_file.header.sizesLoc, sector_size));

#define assert_read_entry(idx, ptr, size)                                                          \
    if (idx < save_file.header.entries) {                                                          \
        assert_result(GZ_storageRead(storage, ptr, MIN(size, save_file.sizes[idx]),                \
                                     save_file.offsets[idx], sector_size));                        \
    }

    assert_read_entry(SV_CURSOR_COLOR_INDEX, &save_file.data.mCursorColType,
                      sizeof(save_file.data.mCursorColType));
    assert_read_entry(SV_FONT_INDEX, &save_file.data.mFontType, sizeof(save_file.data.mFontType));
    assert_read_entry(SV_DROP_SHADOW_INDEX, &save_file.data.mDropShadows,
                      sizeof(save_file.data.mDropShadows));
#undef assert_read_entry
#undef assert_result

    return result;
}

void GZ_storeMemCard(Storage& storage) {
    GZSaveFile save_file;
    GZ_setupSaveFile(save_file);
    GZ_storeSaveLayout(save_file.data);

    uint32_t file_size = (uint32_t)(
        ceil((double)sizeof(save_file) / (double)storage.sector_size) * storage.sector_size);

    storage.result = StorageDelete(0, storage.file_name_buffer);
    storage.result = StorageCreate(0, storage.file_name_buffer, file_size, &storage.info);

    if (storage.result == Ready || storage.result == Exist) {
        storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);

        if (storage.result == Ready) {
            storage.result =
                GZ_storageWrite(&storage, &save_file, sizeof(save_file), 0, storage.sector_size);

            storage.result = StorageClose(&storage.info);
        }
    }
}

/* void GZ_storeMemfile(Storage& storage) {
    PositionData posData;
    posData.link = dComIfGp_getPlayer()->mCurrent.mPosition;
    posData.cam.target = tp_matrixInfo.matrix_info->target;
    posData.cam.pos = tp_matrixInfo.matrix_info->pos;
    posData.angle = dComIfGp_getPlayer()->mCollisionRot.mY;
    uint32_t file_size = (uint32_t)(
        tp_ceil((double)sizeof(dSv_info_c) / (double)storage.sector_size) * storage.sector_size);

    storage.result = StorageDelete(0, storage.file_name_buffer);
    storage.result = StorageCreate(0, storage.file_name_buffer, file_size, &storage.info);

    if (storage.result == Ready || storage.result == Exist) {
        storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
        if (storage.result == Ready) {
            dComIfGs_putSave(g_dComIfG_gameInfo.info.mDan.mStageNo);

            setReturnPlace(g_dComIfG_gameInfo.play.mStartStage.mStage,
                           g_dComIfG_gameInfo.play.mEvent.field_0x12c, 0);

            storage.result = GZ_storageWrite(&storage, &g_dComIfG_gameInfo, sizeof(dSv_info_c), 0,
                                             storage.sector_size);
            storage.result = GZ_storageWrite(&storage, &posData, sizeof(posData),
                                             sizeof(dSv_info_c) + 1, storage.sector_size);
            if (storage.result == Ready) {
                FIFOQueue::push("saved memfile!", Queue);
            } else {
                char buff[32];
                tp_sprintf(buff, "failed to save: %d", storage.result);
                FIFOQueue::push(buff, Queue);
            }
            storage.result = StorageClose(&storage.info);
        }
    }
} */

void GZ_deleteMemCard(Storage& storage) {
    storage.result = StorageDelete(0, storage.file_name_buffer);
}

void GZ_loadMemCard(Storage& storage) {
    storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);

    if (storage.result == Ready) {
        GZSaveFile save_file;
        GZ_storeSaveLayout(save_file.data);
        storage.result = GZ_readSaveFile(&storage, save_file, storage.sector_size);

        if (storage.result == Ready) {
            GZ_loadSaveLayout(save_file.data);
            SettingsMenu::initFont();
        }

        storage.result = StorageClose(&storage.info);
    }
}

/* void GZ_loadMemfile(Storage& storage) {
    storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);

    if (storage.result == Ready) {
        PositionData posData;
        storage.result = GZ_readMemfile(&storage, posData, storage.sector_size);
        if (storage.result == Ready) {
            FIFOQueue::push("loaded memfile!", Queue);
            g_injectMemfile = true;
            SaveManager::injectDefault_before();
            SaveManager::injectMemfile((void*)sTmpBuf);
            SaveManager::injectDefault_during();
            SaveManager::injectDefault_after();
            GZ_loadPositionData(posData);
            set_position_data = true;
            g_injectSave = true;
            g_fifoVisible = true;
            GZ_setMenu(MN_NONE_INDEX);
        } else {
            char buff[32];
            tp_sprintf(buff, "failed to load: %d", storage.result);
            FIFOQueue::push(buff, Queue);
        }
        storage.result = StorageClose(&storage.info);
    }
} */

#define FRAME_COUNT 200
#define FILE_NAME "twwgz01"

void GZ_loadGZSave(bool& card_load) {
    // uint8_t frame_count = cCt_getFrameCount();
    static uint8_t frame_count = 0;

    if (card_load && frame_count > FRAME_COUNT) {
        static Storage storage;
        storage.file_name = FILE_NAME;
        storage.sector_size = SECTOR_SIZE;
        tww_sprintf(storage.file_name_buffer, (char*)storage.file_name);
        storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
        if (storage.result == Ready) {
            GZ_loadMemCard(storage);
        }

        card_load = false;
    } else {
        frame_count++;
    }
}