#include "font.h"
#include "gcn_c/include/storage.h"
#include "menu.h"

int32_t GZ_storageWrite(Storage* info, void* data, int32_t size, int32_t offset,
                        int32_t sector_size);
int32_t GZ_storageRead(Storage* info, void* data, int32_t size, int32_t offset,
                       int32_t sector_size);
void GZ_storeMemCard(Storage& card);
void GZ_storeMemfile(Storage& card);
void GZ_deleteMemCard(Storage& card);
void GZ_deleteMemfile(Storage& card);
void GZ_loadMemCard(Storage& card);
void GZ_loadMemfile(Storage& card);
void GZ_loadGZSave(bool& card_load);

#define GZ_SAVE_VERSION_NUMBER 0
#define GZ_SAVE_ENTRIES_AMNT 3

// These numbers can only change when we change the GZ_SAVE_VERSION_NUMBER,
// otherwise, only new entries can be added.
enum GZSaveIndex {
    SV_CURSOR_COLOR_INDEX = 0,
    SV_FONT_INDEX = 1,
    SV_DROP_SHADOW_INDEX = 2,
};

struct GZSaveHeader {
    uint32_t version;
    uint32_t entries;
    uint32_t offsetsLoc;
    uint32_t sizesLoc;
};

struct GZSaveLayout {
    bool mDropShadows;
    int mCursorColType;
    int mFontType;
};

struct GZSaveFile {
    GZSaveHeader header;
    uint32_t offsets[GZ_SAVE_ENTRIES_AMNT];
    uint32_t sizes[GZ_SAVE_ENTRIES_AMNT];
    GZSaveLayout data;
};