#include "gcn_c/include/storage.h"
#include "menu.h"

static_assert(sizeof(CARDFileInfo) == 0x14);
static_assert(sizeof(CARDStat) == 0x6C);
static_assert(sizeof(CARDDir) == 0x40);
static_assert(sizeof(CARDControl) == 0x110);

#define GZ_SAVE_VERSION_NUMBER 1

struct GZSaveHeader {
    uint32_t version;
    size_t data_size;
    uint32_t entries;
};

struct GZSaveFile {
    GZSaveHeader header;
};

int32_t GZ_storageWrite(Storage* info, void* data, int32_t size, int32_t offset, int32_t sector_size);
int32_t GZ_storageRead(Storage* info, void* data, int32_t size, int32_t offset, int32_t sector_size);
void GZ_storeMemCard(Storage& card);
void GZ_storeMemfile(Storage& card);
void GZ_deleteMemCard(Storage& card);
void GZ_deleteMemfile(Storage& card);
void GZ_loadMemCard(Storage& card);
void GZ_loadMemfile(Storage& card);
void GZ_loadGZSave(bool& card_load);
