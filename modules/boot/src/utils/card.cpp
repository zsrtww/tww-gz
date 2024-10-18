#include <cstdio>
#include <numeric>
#include "utils/card.h"
#include "libtww/include/MSL_C/math.h"
#include "libtww/include/MSL_C/string.h"
#include "libtww/include/SSystem/SComponent/c_malloc.h"
#include "libtww/include/SSystem/SComponent/c_counter.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "fifo_queue.h"
#include "rels/include/defines.h"
#include "rels/include/cxx.h"
#include "menus/utils/menu_mgr.h"
#include "rels/include/defines.h"
#include "boot/include/commands.h"
#include "boot/include/equip_priority.h"
#include "menus/menu_settings/include/settings_menu.h"

/**
 * @brief Like CARDWrite, but allows for arbitrary sizes and offsets.
 */
int32_t GZ_storageWrite(Storage* storage, void* data, int32_t size, int32_t offset, int32_t sector_size) {
    uint8_t* buf = new (-32) uint8_t[sector_size];
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        memcpy(buf + (offset & (sector_size - 1)), (void*)((uint32_t)data + read_bytes), MIN(rem_size, size));
        StorageWrite(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    delete[] buf;
    return result;
}

/**
 * @brief Like CARDRead, but allows for arbitrary sizes and offsets.
 */
int32_t GZ_storageRead(Storage* storage, void* data, int32_t size, int32_t offset, int32_t sector_size) {
    uint8_t* buf = new (-32) uint8_t[sector_size];
    int32_t result = Ready;
    int32_t read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        int32_t rem_size = sector_size - (offset & (sector_size - 1));
        memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (sector_size - 1)), MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    delete[] buf;
    return result;
}

/**
 * @brief Stores the settings in a new buffer.
 * @param save_file The save file to fetch the metadata from.
 * @return The buffer containing the settings.
 */
void GZ_storeSettings(GZSaveFile& save_file, void* data) {
    if (save_file.header.data_size == 0) {
        return;
    }
    uint32_t pos = 0;
    for (auto& entry : g_settings) {
        memcpy((void*)((uint32_t)data + pos), &entry->id, sizeof(GZSettingID));
        pos += sizeof(GZSettingID);
        memcpy((void*)((uint32_t)data + pos), &entry->size, sizeof(size_t));
        pos += sizeof(size_t);
        if (entry->size > 0 && entry->data) {
            memcpy((void*)((uint32_t)data + pos), entry->data, entry->size);
        }
        pos += entry->size;
    }
}

/**
 * @brief Loads the settings from a buffer.
 * @param save_file The save file to fetch the metadata from.
 * @param data The buffer containing the settings.
 */
void GZ_loadSettings(GZSaveFile save_file, void* data) {
    uint32_t pos = 0;
    for (uint32_t i = 0; i < save_file.header.entries; i++) {
        GZSettingID id;
        size_t size;
        memcpy(&id, (void*)((uint32_t)data + pos), sizeof(GZSettingID));
        pos += sizeof(GZSettingID);
        memcpy(&size, (void*)((uint32_t)data + pos), sizeof(size_t));
        pos += sizeof(size_t);
        GZSettingEntry* entry = GZStng_get(id);
        if (entry == nullptr) {
            entry = new GZSettingEntry{id, size, size > 0 ? new uint8_t[size] : nullptr};
            g_settings.push_back(entry);
        } else {
            void* old_data = entry->data;
            if (old_data) {
                delete[] (uint8_t*)old_data;
            }
            entry->data = size > 0 ? new uint8_t[size] : nullptr;
            entry->size = size;
        }
        memcpy(entry->data, (void*)((uint32_t)data + pos), size);
        pos += size;
    }
}

/**
 * @brief Setup the save file header.
 * @param save_file The save file to setup.
 */
void GZ_setupSaveFile(GZSaveFile& save_file) {
    save_file.header.version = GZ_SAVE_VERSION_NUMBER;
    save_file.header.entries = g_settings.size();
    save_file.header.data_size =
        std::transform_reduce(g_settings.begin(), g_settings.end(), (size_t)0, std::plus{},
                              [](GZSettingEntry* entry) { return entry->size; }) +
        (sizeof(GZSettingID) + sizeof(size_t)) * g_settings.size();
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
    uint8_t* data = nullptr;
    if (save_file.header.data_size > 0) {
        data = new uint8_t[save_file.header.data_size];
        assert_result(GZ_storageRead(storage, data, save_file.header.data_size, pos, sector_size));
    }

    // Clear the settings before loading the saved ones.
    for (auto& entry : g_settings) {
        delete[] (uint8_t*)entry->data;
        delete entry;
    }

    g_settings.clear();

    GZ_loadSettings(save_file, data);

    if (data != nullptr) {
        delete[] data;
    }

#undef assert_result

    return result;
}

KEEP_FUNC void GZ_storeMemCard(Storage& storage) {
    GZSaveFile save_file;
    GZ_setupSaveFile(save_file);
    uint32_t file_size = sizeof(save_file) + save_file.header.data_size;
    uint8_t* data = new uint8_t[file_size];
    memcpy(data, &save_file.header, sizeof(save_file.header));
    GZ_storeSettings(save_file, &data[sizeof(save_file.header)]);
    // Align the file size to the sector size.
    file_size = (uint32_t)(ceil((double)sizeof(save_file) / (double)storage.sector_size) *
                           storage.sector_size);
    storage.result = StorageDelete(0, storage.file_name_buffer);
    storage.result = StorageCreate(0, storage.file_name_buffer, file_size, &storage.info);
    if (storage.result == Ready || storage.result == Exist) {
        storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
        if (storage.result == Ready) {
            storage.result = GZ_storageWrite(&storage, data, file_size, 0, storage.sector_size);
            if (storage.result == Ready) {
                OSReport("saved card!\n");
                FIFOQueue::push("saved card!", Queue);
            } else {
                OSReport("failed to save\n");
                char buff[32];
                snprintf(buff, sizeof(buff), "failed to save: %d", storage.result);
                FIFOQueue::push(buff, Queue);
            }
            storage.result = StorageClose(&storage.info);
        }
    }
    if (data != nullptr) {
        delete[] (uint8_t*)data;
    }
}

KEEP_FUNC void GZ_deleteMemCard(Storage& storage) {
    storage.result = StorageDelete(0, storage.file_name_buffer);
    if (storage.result == Ready) {
        FIFOQueue::push("deleted card!", Queue);
    } else {
        char buff[32];
        snprintf(buff, sizeof(buff), "failed to delete: %d", storage.result);
        FIFOQueue::push(buff, Queue);
    }
}

KEEP_FUNC void GZ_loadMemCard(Storage& storage) {
    storage.result = StorageOpen(0, storage.file_name_buffer, &storage.info, OPEN_MODE_RW);
    if (storage.result == Ready) {
        GZSaveFile save_file;
        storage.result = GZ_readSaveFile(&storage, save_file, storage.sector_size);
        if (storage.result == Ready) {
            FIFOQueue::push("loaded card!", Queue);
            GZ_initFont();
        } else {
            char buff[32];
            snprintf(buff, sizeof(buff), "failed to load: %d", storage.result);
            FIFOQueue::push(buff, Queue);
        }
        storage.result = StorageClose(&storage.info);
    }
}

#define FRAME_COUNT 200
#define FILE_NAME "twwgz01"

KEEP_FUNC void GZ_loadGZSave(bool& card_load) {
    uint8_t frame_count = cCt_getFrameCount();
    if (card_load && frame_count > FRAME_COUNT) {
        static Storage storage;
        storage.file_name = FILE_NAME;
        storage.sector_size = SECTOR_SIZE;
        snprintf(storage.file_name_buffer, sizeof(storage.file_name_buffer),
                 (char*)storage.file_name);
        storage.result = CARDProbeEx(0, NULL, &storage.sector_size);
        if (storage.result == Ready) {
            GZ_loadMemCard(storage);
        }

        card_load = false;
    }
}
