#include "font.h"
#include "gcn_c/include/storage.h"
#include "settings.h"
#include "equip_priority.h"
#include "cheats.h"
#include "tools.h"
#include "commands.h"
#include "watches.h"
#include "pos_settings.h"
#include "menu.h"

static_assert(sizeof(CARDFileInfo) == 0x14);
static_assert(sizeof(CARDStat) == 0x6C);
static_assert(sizeof(CARDDir) == 0x40);
static_assert(sizeof(CARDControl) == 0x110);

#define GZ_SAVE_VERSION_NUMBER 0
#define GZ_SAVE_ENTRIES_AMNT 9

// These numbers can only change when we change the GZ_SAVE_VERSION_NUMBER,
// otherwise, only new entries can be added.
enum GZSaveIndex {
    SV_CHEATS_INDEX = 0,
    SV_ITEM_EQUIP_INDEX = 1,
    SV_TOOLS_INDEX = 2,
    SV_WATCHES_INDEX = 3,
    SV_COMMANDS = 4,
    SV_DROP_SHADOW_INDEX = 5,
    SV_CURSOR_COLOR_INDEX = 6,
    SV_FONT_INDEX = 7,
    SV_SPRITES_INDEX = 8,
};

struct GZSaveHeader {
    uint32_t version;
    uint32_t entries;
    uint32_t offsetsLoc;
    uint32_t sizesLoc;
};

struct GZSaveLayout {
    Cheat mCheats[CHEAT_AMNT];
    ItemEquipSettings mItemEquipSettings[NUM_EQUIPPABLE_ITEMS];
    Tool mTools[TOOLS_COUNT];
    MemoryWatch mWatches[MAX_WATCHES];
    bool mCommandStates[COMMANDS_AMNT];
    bool mDropShadows;
    int mCursorColType;
    int mFontType;
    Vec2 mSpriteOffsets[SPRITES_AMNT];
};

struct GZSaveFile {
    GZSaveHeader header;
    uint32_t offsets[GZ_SAVE_ENTRIES_AMNT];
    uint32_t sizes[GZ_SAVE_ENTRIES_AMNT];
    GZSaveLayout data;
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
