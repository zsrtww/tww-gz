#include "utils/card.h"
#include "math.h"
#include "menus/settings_menu.h"
#include "libtww/MSL_C/math/s_ceil.h"
#include "libtww/MSL_C/string.h"
#include "libtww/SSystem/SComponent/c_malloc.h"
#include "libtww/SSystem/SComponent/c_counter.h"

/**
 * @brief Like CARDWrite, but allows for arbitrary sizes and offsets.
 */
s32 GZ_storageWrite(Storage* storage, void* data, s32 size, s32 offset, s32 sector_size) {
    u8* buf = (u8*)tww_memalign(-32, sector_size);
    s32 result = Ready;
    s32 read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        s32 rem_size = sector_size - (offset & (sector_size - 1));
        tww_memcpy(buf + (offset & (sector_size - 1)), (void*)((u32)data + read_bytes),
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
s32 GZ_storageRead(Storage* storage, void* data, s32 size, s32 offset, s32 sector_size) {
    u8* buf = (u8*)tww_memalign(-32, sector_size);
    s32 result = Ready;
    s32 read_bytes = 0;

    while (result == Ready && size > 0) {
        StorageRead(*storage, buf, sector_size, (offset & ~(sector_size - 1)));
        if (result != Ready) {
            break;
        }
        s32 rem_size = sector_size - (offset & (sector_size - 1));
        tww_memcpy((void*)((u32)data + read_bytes), buf + (offset & (sector_size - 1)),
                   MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tww_free(buf);
    return result;
}

void GZ_storeSaveLayout(GZSaveLayout& save_layout) {
    tww_memcpy(save_layout.mCheats, g_cheats, sizeof(g_cheats));
    tww_memcpy(save_layout.mTools, g_tools, sizeof(g_tools));
    tww_memcpy(save_layout.mCommandStates, g_commandStates, sizeof(g_commandStates));
    tww_memcpy(save_layout.mWatches, g_watches, sizeof(g_watches));

    save_layout.mDropShadows = g_dropShadows;
    save_layout.mCursorColType = g_cursorColorType;
    save_layout.mFontType = g_fontType;
}

void GZ_loadSaveLayout(GZSaveLayout& save_layout) {
    tww_memcpy(g_cheats, save_layout.mCheats, sizeof(g_cheats));
    tww_memcpy(g_tools, save_layout.mTools, sizeof(g_tools));
    tww_memcpy(g_commandStates, save_layout.mCommandStates, sizeof(g_commandStates));
    tww_memcpy(g_watches, save_layout.mWatches, sizeof(g_watches));

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

    set_entry(SV_CHEATS_INDEX, mCheats);
    set_entry(SV_TOOLS_INDEX, mTools);
    set_entry(SV_WATCHES_INDEX, mWatches);
    set_entry(SV_COMMANDS_INDEX, mCommandStates);
    set_entry(SV_CURSOR_COLOR_INDEX, mCursorColType);
    set_entry(SV_FONT_INDEX, mFontType);
    set_entry(SV_DROP_SHADOW_INDEX, mDropShadows);
#undef set_entry
}

s32 GZ_readSaveFile(Storage* storage, GZSaveFile& save_file, s32 sector_size) {
    s32 result = Ready;
#define assert_result(stmt)                                                                        \
    if ((result = (stmt)) != Ready) {                                                              \
        return result;                                                                             \
    }

    u32 pos = 0;
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

    assert_read_entry(SV_CHEATS_INDEX, save_file.data.mCheats, sizeof(save_file.data.mCheats));
    assert_read_entry(SV_TOOLS_INDEX, save_file.data.mTools, sizeof(save_file.data.mTools));
    assert_read_entry(SV_WATCHES_INDEX, save_file.data.mWatches, sizeof(save_file.data.mWatches));
    assert_read_entry(SV_COMMANDS_INDEX, save_file.data.mCommandStates,
                      sizeof(save_file.data.mCommandStates));
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

    u32 file_size =
        (u32)(ceil((double)sizeof(save_file) / (double)storage.sector_size) * storage.sector_size);

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

#define FRAME_COUNT 200
#define FILE_NAME "twwgz01"

void GZ_loadGZSave(bool& card_load) {
    u8 frame_count = cCt_getFrameCount();

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
    }
}