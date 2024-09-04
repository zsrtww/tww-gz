#ifndef D_SAVE_D_SAVE_H
#define D_SAVE_D_SAVE_H

#include "../../SSystem/SComponent/c_xyz.h"
#include "../../dolphin/gctypes.h"

enum SelectEquipIndex {
    SWORD_INDEX = 0,
    SHIELD_INDEX = 1,
    POWER_BRACELETS_INDEX = 2
};

enum CollectItemIndex {
    SWORD_OWNED_INDEX = 0,
    SHIELD_OWNED_INDEX = 1,
    POWER_BRACELETS_OWNED_INDEX = 2,
    PIRATES_CHARM_OWNED_INDEX = 3,
    HEROS_CHARM_OWNED_INDEX = 4
};

enum ItemSlots {
    /* 0x00 */ SLOT_TELESCOPE,
    /* 0x01 */ SLOT_SAIL,
    /* 0x02 */ SLOT_WIND_WAKER,
    /* 0x03 */ SLOT_ROPE,
    /* 0x04 */ SLOT_SPOILS_BAG,
    /* 0x05 */ SLOT_BOOMERANG,
    /* 0x06 */ SLOT_DEKU_LEAF,
    /* 0x07 */ SLOT_TUNER,
    /* 0x08 */ SLOT_CAMERA,
    /* 0x09 */ SLOT_IRON_BOOTS,
    /* 0x0A */ SLOT_MAGIC_ARMOR,
    /* 0x0B */ SLOT_BAIT_BAG,
    /* 0x0C */ SLOT_BOW,
    /* 0x0D */ SLOT_BOMB,
    /* 0x0E */ SLOT_BOTTLE,
    /* 0x12 */ SLOT_TRADE_ITEM = 18,
    /* 0x13 */ SLOT_HOOKSHOT,
    /* 0x14 */ SLOT_HAMMER,
};

enum ItemTable {
    HEART_DROP = 0x00,
    GREEN_RUPEE_DROP = 0x01,
    BLUE_RUPEE_DROP = 0x02,
    YELLOW_RUPEE_DROP = 0x03,
    RED_RUPEE_DROP = 0x04,
    PURPLE_RUPEE_DROP = 0x05,
    ORANGE_RUPEE_DROP = 0x06,
    HEART_PIECE = 0x07,
    HEART_CONTAINER = 0x08,
    SMALL_MAGIC_DROP = 0x09,
    LARGE_MAGIC_DROP = 0x0A,
    BOMB_DROP = 0x0B,
    SILVER_RUPEE_DROP = 0x0F,
    SINGLE_ARROW_DROP = 0x10,
    DOUBLE_ARROW_DROP = 0x11,
    TRIPLE_ARROW_DROP = 0x12,
    KEY_DROP = 0x15,
    FAIRY_DROP = 0x16,
    TRIPLE_HEART_DROP = 0x1E,
    JOY_PENDANT = 0x1F,
    TELESCOPE = 0x20,
    TINGLE_TUNER = 0x21,
    WIND_WAKER = 0x22,
    PICTO_BOX = 0x23,
    SPOILS_BAG = 0x24,
    GRAPPLING_HOOK = 0x25,
    DELUXE_PICTO_BOX = 0x26,
    BOW = 0x27,
    POWER_BRACELETS = 0x28,
    IRON_BOOTS = 0x29,
    MAGIC_ARMOR = 0x2A,
    WATER_BOOTS = 0x2B,
    BAIT_BAG = 0x2C,
    BOOMERANG = 0x2D,
    HOOKSHOT = 0x2F,
    DELIVERY_BAG = 0x30,
    BOMBS = 0x31,
    TUNIC = 0x32,
    SKULL_HAMMER = 0x33,
    DEKU_LEAF = 0x34,
    BOW_WITH_FIRE_AND_ICE_ARROWS = 0x35,
    BOW_WITH_LIGHT_ARROWS = 0x36,
    HEROS_SWORD = 0x38,
    UNCHARGED_MASTER_SWORD = 0x39,
    HALF_CHARGED_MASTER_SWORD = 0x3A,
    HEROS_SHIELD = 0x3B,
    MIRROR_SHIELD = 0x3C,
    FULLY_CHARGED_MASTER_SWORD = 0x3E,
    PIRATES_CHARM = 0x42,
    HEROS_CHARM = 0x43,
    SKULL_NECKLACE = 0x45,
    BOKO_BABA_SEED = 0x46,
    GOLDEN_FEATHER = 0x47,
    KNIGHTS_CREST = 0x48,
    RED_CHU_JELLY = 0x49,
    GREEN_CHU_JELLY = 0x4A,
    BLUE_CHU_JELLY = 0x4B,
    MAP = 0x4C,
    COMPASS = 0x4D,
    BIG_KEY = 0x4E,
    EMPTY_BOTTLE = 0x50,
    RED_POTION = 0x51,
    GREEN_POTION = 0x52,
    BLUE_POTION = 0x53,
    ELIXIR_SOUP_HALF = 0x54,
    ELIXIR_SOUP = 0x55,
    WATER = 0x56,
    FAIRY = 0x57,
    FOREST_FIREFLY = 0x58,
    FOREST_WATER = 0x59,
    TRIFORCE_PIECE_1 = 0x61,
    TRIFORCE_PIECE_2 = 0x62,
    TRIFORCE_PIECE_3 = 0x63,
    TRIFORCE_PIECE_4 = 0x64,
    TRIFORCE_PIECE_5 = 0x65,
    TRIFORCE_PIECE_6 = 0x66,
    TRIFORCE_PIECE_7 = 0x67,
    TRIFORCE_PIECE_8 = 0x68,
    NAYRUS_PEARL = 0x69,
    DINS_PEARL = 0x6A,
    FARORES_PEARL = 0x6B,
    SAIL = 0x78,
    TRIFORCE_CHART = 0x79,
    ALL_PURPOSE_BAIT = 0x82,
    HYOI_PEAR = 0x83,
    TOWN_FLOWER = 0x8C,
    SEA_FLOWER = 0x8D,
    EXOTIC_FLOWER = 0x8E,
    HEROS_FLAG = 0x8F,
    BIG_CATCH_FLAG = 0x90,
    BIG_SALE_FLAG = 0x91,
    PINWHEEL = 0x92,
    SICKLE_MOON_FLAG = 0x93,
    SKULL_TOWER_IDOL = 0x94,
    FOUNTAIN_IDOL = 0x95,
    POSTMAN_STATUE = 0x96,
    SHOP_GURU_STATUE = 0x97,
    FATHERS_LETTER = 0x98,
    NOTE_TO_MOM = 0x99,
    MAGGIES_LETTER = 0x9A,
    MOBLINS_LETTER = 0x9B,
    CABANA_DEED = 0x9C,
    COMPLIMENTARY_ID = 0x9D,
    FILL_UP_COUPON = 0x9E,
    GOLDEN_TINGLE_HEAD = 0xA3,
    NO_ITEM = 0xFF
};

class dSv_player_status_a_c {
public:
    u8 getSelectItem(int i_no) { return mSelectItem[i_no]; }
    void setSelectItem(int i_no, u8 i_invIdx) { mSelectItem[i_no] = i_invIdx; }
    u8 getSelectEquip(int i_no) { return mSelectEquip[i_no]; }
    void setSelectEquip(int i_no, u8 i_itemNo) { mSelectEquip[i_no] = i_itemNo; }
    u8 getWalletSize() { return mWalletSize; }
    void setWalletSize(u8 size) { mWalletSize = size; }
    int getRupee() { return mRupee; }
    void setRupee(u16 rupee) { mRupee = rupee; }
    u8 getMagic() { return mMagic; }
    void setMagic(u8 magic) { mMagic = magic;}
    u8 getMaxMagic() { return mMaxMagic; }
    void setMaxMagic(u8 magic) { mMaxMagic = magic; }
    u16 getLife() { return mLife; }
    void setLife(u16 life) { mLife = life; }
    u16 getMaxLife() { return mMaxLife; }
    void setMaxLife(u16 life) { mMaxLife = life; }

    /* 0x00 */ u16 mMaxLife;
    /* 0x02 */ u16 mLife;
    /* 0x04 */ u16 mRupee;
    /* 0x06 */ u16 field_0x6;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 mSelectItem[5];   // X, Y, Z button
    /* 0x0E */ u8 mSelectEquip[4];  // Sword, Shield, Bracelet, ?
    /* 0x12 */ u8 mWalletSize;
    /* 0x13 */ u8 mMaxMagic;
    /* 0x14 */ u8 mMagic;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
};  // Size: 0x18

static_assert(sizeof(dSv_player_status_a_c) == 0x18);

class dSv_player_status_b_c {
public:
    void setDateIpl(s64 i_time) { mDateIPL = i_time; }
    u16 getDate() { return mDate; }
    f32 getTime() { return mTime; }
    void setDate(u16 i_date) { mDate = i_date; }
    void setTime(f32 i_time) { mTime = i_time; }
    s64 getDateIpl() { return mDateIPL; }
    s16 getWindY() { return mTactWindAngleY; }
    s16 getWindX() { return mTactWindAngleX; }
    void setWindY(s16 i_windY) { mTactWindAngleY = i_windY; }
    void setWindX(s16 i_windX) { mTactWindAngleX = i_windX; }

    /* 0x00 */ u64 mDateIPL;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 mTime;
    /* 0x10 */ u16 mDate;
    /* 0x12 */ s16 mTactWindAngleX;
    /* 0x14 */ s16 mTactWindAngleY;
};  // Size: 0x18

static_assert(sizeof(dSv_player_status_b_c) == 0x18);

class dSv_player_return_place_c {
public:
    s8 getRoomNo() { return mRoomNo; }
    u8 getPoint() { return mPoint; }
    char* getName() { return mName; }

    /* 0x00 */ char mName[8];
    /* 0x08 */ s8 mRoomNo;
    /* 0x09 */ u8 mPoint;
    /* 0x0A */ u8 unk_0xa;
    /* 0x0B */ u8 unk_0xb;
};  // Size: 0xC

static_assert(sizeof(dSv_player_return_place_c) == 0xC);

class dSv_player_item_c {
public:
    u8 getItem(int i_idx) { return mItems[i_idx]; }
    void setItem(int i_idx, u8 i_itemNo) { mItems[i_idx] = i_itemNo; }

    /* 0x00 */ u8 mItems[21];
};  // Size: 0x15

static_assert(sizeof(dSv_player_item_c) == 0x15);

class dSv_player_get_item_c {
public:
    void offItem(int i_field, u8 i_item) { mItemFlags[i_field] &= ~(u8)(1 << i_item); }

    /* 0x0 */ u8 mItemFlags[21];
};  // Size: 0x15

static_assert(sizeof(dSv_player_get_item_c) == 0x15);

class dSv_player_item_record_c {
public:
    u8 getArrowNum() { return mArrowNum; }
    u8 getBombNum() { return mBombNum; }
    u8 getPictureNum() { return mPictureNum; }

    void setArrowNum(u8 amount) { mArrowNum = amount; }
    void setBombNum(u8 amount) { mBombNum = amount; }
    void setTimer(u16 timer) { mTimer = timer; }

    /* 0x0 */ u16 mTimer;
    /* 0x2 */ u8 mPictureNum;
    /* 0x3 */ u8 mArrowNum;
    /* 0x4 */ u8 mBombNum;
    /* 0x5 */ u8 mBottleNum[3];
};  // Size: 0x8

static_assert(sizeof(dSv_player_item_record_c) == 0x8);

class dSv_player_item_max_c {
public:
    u8 getArrowNum() { return mArrowNum; }
    u8 getBombNum() { return mBombNum; }

    void setArrowNum(u8 amount) { mArrowNum = amount; }
    void setBombNum(u8 amount) { mBombNum = amount; }

    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 mArrowNum;
    /* 0x2 */ u8 mBombNum;
    /* 0x3 */ u8 field_0x3[5];
};  // Size: 0x8

static_assert(sizeof(dSv_player_item_max_c) == 0x8);

class dSv_player_bag_item_c {
public:
    u8 getBeast(int i_idx) { return mBeast[i_idx]; }
    void setBeast(int i_idx, u8 i_itemNo) { mBeast[i_idx] = i_itemNo; }
    u8 getBait(int i_idx) { return mBait[i_idx]; }
    void setBait(int i_idx, u8 i_itemNo) { mBait[i_idx] = i_itemNo; }
    u8 getReserve(int i_idx) { return mReserve[i_idx]; }
    void setReserve(int i_idx, u8 i_itemNo) { mReserve[i_idx] = i_itemNo; }

    /* 0x00 */ u8 mBeast[8];
    /* 0x08 */ u8 mBait[8];
    /* 0x10 */ u8 mReserve[8];
};  // Size: 0x18

static_assert(sizeof(dSv_player_bag_item_c) == 0x18);

class dSv_player_get_bag_item_c {
public:
    u8 getSpoilFlag(u8 index) { return mBeastFlags; }
    void setSpoilFlag(u8 collected_item) { mBeastFlags |= (1 << collected_item); }

    /* 0x0 */ u32 mReserveFlags;
    /* 0x4 */ u8 mBeastFlags;
    /* 0x5 */ u8 mBaitFlags;
    /* 0x6 */ u8 unk_0x6[0xC - 0x6];
};  // Size: 0xC

static_assert(sizeof(dSv_player_get_bag_item_c) == 0xC);

class dSv_player_bag_item_record_c {
public:
    u8 getBeastNum(int i_idx) { return mBeastNum[i_idx]; }
    void setBeastNum(int i_idx, u8 num) { mBeastNum[i_idx] = num; }
    u8 getBaitNum(int i_idx) { return mBaitNum[i_idx]; }
    void setBaitNum(int i_idx, u8 num) { mBaitNum[i_idx] = num; }
    u8 getReserveNum(int i_idx) { return mReserveNum[i_idx]; }
    void setReserveNum(int i_idx, u8 num) { mReserveNum[i_idx] = num; }

    /* 0x00 */ u8 mBeastNum[8];
    /* 0x08 */ u8 mBaitNum[8];
    /* 0x10 */ u8 mReserveNum[8];
};  // Size: 0x18

static_assert(sizeof(dSv_player_bag_item_record_c) == 0x18);

class dSv_player_collect_c {
public:
    void setCollect(int idx, u8 byte) { mCollect[idx] = byte; }
    u8 checkCollect(int idx) { return mCollect[idx]; }

    void offTact(u8 i_no) { mTact &= ~(u8)(1 << i_no); }
    void offTriforce(u8 i_no) { mTriforce &= ~(u8)(1 << i_no); }
    void offSymbol(u8 i_no) { mSymbol &= ~(u8)(1 << i_no); }

    /* u8 getItemOwned(u8 index) { return mCollect[index]; }
    u8 getSongsOwned() { return mTact; }
    u8 getTriforceOwned() { return mTriforce; }
    u8 getPearlsOwned() { return mSymbol; }

    void setItemOwned(u8 index, u8 has_item) { mCollect[index] = has_item; }
    void setSongsOwned(u8 songs_owned) { mTact = songs_owned; }
    void setTriforceOwned(u8 triforce_owned) { mTriforce = triforce_owned; }
    void setPearlsOwned(u8 pearls_owned) { mSymbol = pearls_owned; } */

    /* 0x0 */ u8 mCollect[8];
    /* 0x8 */ u8 field_0x8;
    /* 0x9 */ u8 mTact;
    /* 0xA */ u8 mTriforce;
    /* 0xB */ u8 mSymbol;
    /* 0xC */ u8 field_0xc;
};  // Size: 0xD

static_assert(sizeof(dSv_player_collect_c) == 0xD);

class dSv_player_map_c {
public:
    void setChartOwned(u32 indx1, u8 indx2) { mCharts[1][indx2] = indx1; }
    void setChartOpened(u32 indx1, u8 indx2) { mCharts[2][indx2] = indx1; }
    void setChartCompleted(u32 indx1, u8 indx2) { mCharts[3][indx2] = indx1; }
    void setChartDeciphered(u8 indx1) { mDecipheredCharts = indx1; }

    u32 getChartOwned(u8 indx1) { return mCharts[1][indx1]; }
    u32 getChartOpened(u8 indx1) { return mCharts[2][indx1]; }
    u32 getChartCompleted(u8 indx1) { return mCharts[3][indx1]; }
    u8 getChartDeciphered() { return mDecipheredCharts; }
    /* 0x00 */ u32 mCharts[4][4];
    /* 0x40 */ u8 field_0x40[49];
    /* 0x71 */ u8 field_0x71[16];
    /* 0x81 */ u8 mDecipheredCharts;
    /* 0x82 */ u8 field_0x82[0x84 - 0x82];
};  // Size: 0x84

static_assert(sizeof(dSv_player_map_c) == 0x84);

class dSv_player_info_c {
public:
    const char* getPlayerName() const { return mPlayerName; }

    u8 getChartSet() { return mFmapIdx; }
    void setChartSet(u8 index) { mFmapIdx = index; }

    /* 0x00 */ u8 field_0x0[0x10];
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ char mPlayerName[17];
    /* 0x25 */ char field_0x25[17];
    /* 0x36 */ char field_0x36[17];
    /* 0x47 */ char field_0x47[17];
    /* 0x58 */ u8 mClearCount;
    /* 0x59 */ u8 mFmapIdx;
    /* 0x5A */ u8 field_0x5a[0x5c - 0x5a];
};  // Size: 0x5C

static_assert(sizeof(dSv_player_info_c) == 0x5C);

class dSv_player_config_c {
public:
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 mSoundMode;
    /* 0x2 */ u8 mAttentionType;
    /* 0x3 */ u8 mVibration;
    /* 0x4 */ u8 field_0x4;
};  // Size: 0x5

static_assert(sizeof(dSv_player_config_c) == 0x5);

class dSv_player_priest_c {
public:
    
    u8 getFlag() { return field_0xf; }
    cXyz& getPos() { return field_0x0; }
    s16 getRotate() { return field_0xc; }
    s8 getRoomNo() { return field_0xe; }

    /* 0x0 */ cXyz field_0x0;
    /* 0xC */ s16 field_0xc;
    /* 0xE */ s8 field_0xe;
    /* 0xF */ u8 field_0xf;
};  // Size: 0x10

static_assert(sizeof(dSv_player_priest_c) == 0x10);

class dSv_player_status_c_c {
public:
    /* 0x00 */ dSv_player_status_a_c mRecollectStatusA;
    /* 0x18 */ dSv_player_item_c mRecollectItem;
    /* 0x2D */ u8 mRecollectItemRecord[3];
    /* 0x30 */ u8 mRecollectItemMax[3];
    /* 0x33 */ dSv_player_bag_item_c mRecollectBagItem;
    /* 0x4B */ dSv_player_bag_item_record_c mRecollectBagItemRecord;
    /* 0x63 */ u8 mRecollectCollect[13];
};  // Size: 0x70

static_assert(sizeof(dSv_player_status_c_c) == 0x70);

class dSv_player_c {
public:
    dSv_player_status_a_c& getPlayerStatusA() { return mPlayerStatusA; }
    dSv_player_status_a_c* getpPlayerStatusA() { return &mPlayerStatusA; }

    dSv_player_status_b_c& getPlayerStatusB() { return mPlayerStatusB; }
    dSv_player_status_b_c* getpPlayerStatusB() { return &mPlayerStatusB; }
    
    dSv_player_return_place_c& getPlayerReturnPlace() { return mReturnPlace; }
    dSv_player_return_place_c* getpPlayerReturnPlace() { return &mReturnPlace; }
    
    dSv_player_item_c& getItem() { return mPlayerItem; }
    dSv_player_item_c* getpItem() { return &mPlayerItem; }

    dSv_player_get_item_c& getGetItem() { return mGetItem; }
    dSv_player_get_item_c* getpGetItem() { return &mGetItem; }
    
    dSv_player_item_record_c& getItemRecord() { return mItemRecord; }
    dSv_player_item_record_c* getpItemRecord() { return &mItemRecord; }
    
    dSv_player_item_max_c& getItemMax() { return mItemMax; }
    dSv_player_item_max_c* getpItemMax() { return &mItemMax; }
    
    dSv_player_bag_item_c& getBagItem() { return mBagItem; }
    dSv_player_bag_item_c* getpBagItem() { return &mBagItem; }
    
    dSv_player_get_bag_item_c& getGetBagItem() { return mGetBagItem; }
    dSv_player_get_bag_item_c* getpGetBagItem() { return &mGetBagItem; }
    
    dSv_player_bag_item_record_c& getBagItemRecord() { return mBagItemRecord; }
    dSv_player_bag_item_record_c* getpBagItemRecord() { return &mBagItemRecord; }
    
    dSv_player_collect_c& getCollect() { return mCollect; }
    dSv_player_collect_c* getpCollect() { return &mCollect; }
    
    dSv_player_map_c& getMap() { return mMap; }
    dSv_player_map_c* getpMap() { return &mMap; }
    
    dSv_player_info_c& getPlayerInfo() { return mInfo; }
    dSv_player_info_c* getpPlayerInfo() { return &mInfo; }
    
    dSv_player_config_c& getConfig() { return mConfig; }
    dSv_player_config_c* getpConfig() { return &mConfig; }
    
    dSv_player_priest_c& getPriest() { return mPriest; }
    dSv_player_priest_c* getpPriest() { return &mPriest; }

    dSv_player_status_c_c* getpPlayerStatusC(int i_idx) { return &mStatusC[i_idx]; }

    /* 0x000 */ dSv_player_status_a_c mPlayerStatusA;
    /* 0x018 */ dSv_player_status_b_c mPlayerStatusB;
    /* 0x030 */ dSv_player_return_place_c mReturnPlace;
    /* 0x03C */ dSv_player_item_c mPlayerItem;
    /* 0x051 */ dSv_player_get_item_c mGetItem;
    /* 0x066 */ dSv_player_item_record_c mItemRecord;
    /* 0x06E */ dSv_player_item_max_c mItemMax;
    /* 0x076 */ dSv_player_bag_item_c mBagItem;
    /* 0x090 */ dSv_player_get_bag_item_c mGetBagItem;
    /* 0x09C */ dSv_player_bag_item_record_c mBagItemRecord;
    /* 0x0B4 */ dSv_player_collect_c mCollect;
    /* 0x0C4 */ dSv_player_map_c mMap;
    /* 0x148 */ dSv_player_info_c mInfo;
    /* 0x1A4 */ dSv_player_config_c mConfig;
    /* 0x1AC */ dSv_player_priest_c mPriest;
    /* 0x1BC */ dSv_player_status_c_c mStatusC[4];
};  // Size: 0x380

static_assert(sizeof(dSv_player_c) == 0x380);

typedef bool (*dSv_memBit_c__isDungeonItem_t)(void* addr, int);
#define dSv_memBit_c__isDungeonItem ((dSv_memBit_c__isDungeonItem_t) dSv_memBit_c__isDungeonItem_addr)

typedef void (*dSv_memBit_c__onDungeonItem_t)(void* addr, int);
#define dSv_memBit_c__onDungeonItem ((dSv_memBit_c__onDungeonItem_t) dSv_memBit_c__onDungeonItem_addr)

class dSv_memBit_c {
public:
    enum {
        /* 0x0 */ MAP,
        /* 0x1 */ COMPASS,
        /* 0x2 */ BOSS_KEY,
        /* 0x3 */ STAGE_BOSS_ENEMY,
        /* 0x4 */ STAGE_LIFE,
        /* 0x5 */ STAGE_BOSS_DEMO,
        /* 0x7 */ STAGE_BOSS_ENEMY_2 = 7
    };

    void offDungeonItem(int flag) { mDungeonItem &= ~(1 << flag); }
    u8 getKeyNum() { return mKeyNum; }
    void setKeyNum(u8 i_keyNum) { mKeyNum = i_keyNum; }
    void onDungeonItemMap() { dSv_memBit_c__onDungeonItem(this, MAP); }
    BOOL isDungeonItemMap() { return dSv_memBit_c__isDungeonItem(this, MAP); }
    void onDungeonItemCompass() { dSv_memBit_c__onDungeonItem(this, COMPASS); }
    BOOL isDungeonItemCompass() { return dSv_memBit_c__isDungeonItem(this, COMPASS); }
    void onDungeonItemBossKey() { dSv_memBit_c__onDungeonItem(this, BOSS_KEY); }
    BOOL isDungeonItemBossKey() { return dSv_memBit_c__isDungeonItem(this, BOSS_KEY); }
    void onStageBossEnemy() { dSv_memBit_c__onDungeonItem(this, STAGE_BOSS_ENEMY); }
    BOOL isStageBossEnemy() { return dSv_memBit_c__isDungeonItem(this, STAGE_BOSS_ENEMY); }
    BOOL isStageBossEnemy2() { return dSv_memBit_c__isDungeonItem(this, STAGE_BOSS_ENEMY_2); }
    void onStageLife() { dSv_memBit_c__onDungeonItem(this, STAGE_LIFE); }
    BOOL isStageLife() { return dSv_memBit_c__isDungeonItem(this, STAGE_LIFE); }
 
    /* 0x00 */ u32 mTbox;
    /* 0x04 */ u32 mSwitch[4];
    /* 0x14 */ u32 mItem;
    /* 0x18 */ u32 mVisitedRoom[2];
    /* 0x20 */ u8 mKeyNum;
    /* 0x21 */ u8 mDungeonItem;
};  // Size: 0x24

static_assert(sizeof(dSv_memBit_c) == 0x24);

class dSv_event_c {
public:
    /* 0x0 */ u8 mEvent[256];
};  // Size: 0x100

static_assert(sizeof(dSv_event_c) == 0x100);

class dSv_reserve_c {
public:
    /* 0x0 */ u8 field_0x0[0x50];
};  // Size: 0x50

class dSv_memory_c {
public:
    dSv_memBit_c& getBit() { return mBit; }
    const dSv_memBit_c& getBit() const { return mBit; }

    /* 0x0 */ dSv_memBit_c mBit;
};  // Size: 0x24

static_assert(sizeof(dSv_memory_c) == 0x24);

class dSv_danBit_c {
public:
    u8 getGbaRupeeCount() { return mGbaRupeeCount; }
    void incGbaRupeeCount() { mGbaRupeeCount++; }

    /* 0x0 */ s8 mStageNo;
    /* 0x1 */ u8 mGbaRupeeCount;
    /* 0x4 */ u32 mSwitch[2];
};  // Size: 0xC

static_assert(sizeof(dSv_danBit_c) == 0xC);

class dSv_zoneBit_c {
public:
    /* 0x0 */ u16 mSwitch[3];
    /* 0x6 */ u16 mItem;
};  // Size: 0x8

static_assert(sizeof(dSv_zoneBit_c) == 0x8);

class dSv_zoneActor_c {
public:
    /* 0x00 */ u32 mActorFlags[16];
};  // Size: 0x40

static_assert(sizeof(dSv_zoneActor_c) == 0x40);

class dSv_zone_c {
public:
    dSv_zoneBit_c& getZoneBit() { return mZoneBit; }
    const dSv_zoneBit_c& getBit() const { return mZoneBit; }
    dSv_zoneActor_c& getActor() { return mZoneActor; }
    const dSv_zoneActor_c& getActor() const { return mZoneActor; }

    s8 getRoomNo() { return mRoomNo; }

    /* 0x00 */ s8 mRoomNo;
    /* 0x02 */ dSv_zoneBit_c mZoneBit;
    /* 0x0C */ dSv_zoneActor_c mZoneActor;
};  // Size: 0x4C

static_assert(sizeof(dSv_zone_c) == 0x4C);

class dSv_ocean_c {
public:
    /* 0x0 */ u16 mBits[50];
};  // Size: 0x64

static_assert(sizeof(dSv_ocean_c) == 0x64);

class dSv_restart_c {
public:
    void setRoomParam(u32 param) { mRestartParam = param; }
    void setStartPoint(s16 point) { mStartCode = point; }
    void setLastSceneInfo(f32 speed, u32 mode) {
        mLastSpeedF = speed;
        mLastMode = mode;
    }

    s16 getStartPoint() { return mStartCode; }
    u32 getLastMode() { return mLastMode; }
    f32 getLastSpeedF() { return mLastSpeedF; }
    s8 getRoomNo() { return mRestartRoom; }
    u32 getRoomParam() { return mRestartParam; }
    cXyz& getRoomPos() { return mRestartPos; }
    s16 getRoomAngleY() { return mRestartAngle; }
    s8 getRestartOption() { return mOption; }
    s8 getRestartOptionRoomNo() { return mOptionRoomNo; }
    s16 getRestartOptionPoint() { return mOptionPoint; }
    s16 getRestartOptionAngleY() { return mOptionRoomAngleY; }
    cXyz& getRestartOptionPos() { return mOptionRoomPos; }

    /* 0x00 */ s8 mRestartRoom;
    /* 0x01 */ u8 mOption;
    /* 0x02 */ s8 mOptionRoomNo;
    /* 0x04 */ s16 mOptionPoint;
    /* 0x06 */ s16 mOptionRoomAngleY;
    /* 0x08 */ cXyz mOptionRoomPos;
    /* 0x14 */ s16 mStartCode;
    /* 0x16 */ s16 mRestartAngle;
    /* 0x18 */ cXyz mRestartPos;
    /* 0x24 */ u32 mRestartParam;
    /* 0x28 */ f32 mLastSpeedF;
    /* 0x2C */ u32 mLastMode;
};  // Size: 0x30

static_assert(sizeof(dSv_restart_c) == 0x30);

class dSv_turnRestart_c {
public:
    u32 getParam() { return mParam; }
    cXyz& getPos() { return mPosition; }
    s16 getAngleY() { return mAngleY; }
    s8 getRoomNo() { return mRoomNo; }
    cXyz& getShipPos() { return mShipPos; }
    s16 getShipAngleY() { return mShipAngleY; }

    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ u32 mParam;
    /* 0x10 */ s16 mAngleY;
    /* 0x12 */ s8 mRoomNo;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14[0x24 - 0x14];
    /* 0x24 */ cXyz mShipPos;
    /* 0x30 */ s16 mShipAngleY;
    /* 0x34 */ int field_0x34;
};  // Size: 0x38

static_assert(sizeof(dSv_turnRestart_c) == 0x38);

class dSv_save_c {
public:
    dSv_player_c& getPlayer() { return mPlayer; }
    dSv_event_c& getEvent() { return mEvent; }
    dSv_ocean_c& getOcean() { return mOcean; }
    dSv_memory_c& getSave(int i_stageNo) { return mSave[i_stageNo]; }
    void putSave(int i_stageNo, dSv_memory_c mem) { mSave[i_stageNo] = mem; }

    static const int STAGE_MAX = 16; 

    /* 0x000 */ dSv_player_c mPlayer;
    /* 0x380 */ dSv_memory_c mSave[STAGE_MAX];
    /* 0x5C0 */ dSv_ocean_c mOcean;
    /* 0x624 */ dSv_event_c mEvent;
};  // Size: 0x724

class dSv_info_c {
public:
    dSv_save_c& getSavedata() { return mSavedata; }
    dSv_player_c& getPlayer() { return mSavedata.getPlayer(); }
    dSv_ocean_c& getOcean() { return mSavedata.getOcean(); }
    dSv_event_c& getEvent() { return mSavedata.getEvent(); }
    dSv_restart_c& getRestart() { return mRestart; }
    dSv_event_c& getTmp() { return mTmp; }
    dSv_turnRestart_c& getTurnRestart() { return mTurnRestart; }
    dSv_memory_c& getMemory() { return mMemory; }
    dSv_danBit_c& getDan() { return mDan; }
    dSv_zone_c& getZone(int id) { return mZone[id]; }

    /* 0x0000 */ dSv_save_c mSavedata;
    /* 0x0724 */ u8 unk_0x724[0x50];
    /* 0x0778 */ dSv_memory_c mMemory;
    /* 0x079C */ dSv_danBit_c mDan;
    /* 0x07A8 */ dSv_zone_c mZone[32];
    /* 0x1128 */ dSv_restart_c mRestart;
    /* 0x1158 */ dSv_event_c mTmp;
    /* 0x1258 */ dSv_turnRestart_c mTurnRestart;
    /* 0x1290 */ u8 field_0x1290;
    /* 0x1291 */ u8 field_0x1291;
    /* 0x1292 */ u8 field_0x1292;
    /* 0x1298 */ s64 field_0x1298;
};  // Size: 0x12A0

static_assert(sizeof(dSv_info_c) == 0x12A0);

typedef bool (*dSv_event_c__isEventBit)(void* addr, uint16_t flag);
#define dSv_event_c__isEventBit ((dSv_event_c__isEventBit) dSv_event_c__isEventBit_addr)

typedef void (*dSv_event_c__onEventBit)(void* addr, uint16_t flag);
#define dSv_event_c__onEventBit ((dSv_event_c__onEventBit) dSv_event_c__onEventBit_addr)

typedef void (*dSv_event_c__offEventBit)(void* addr, uint16_t flag);
#define dSv_event_c__offEventBit ((dSv_event_c__offEventBit) dSv_event_c__offEventBit_addr)

typedef void (*dSv_player_return_place_c__set_t)(void* _this, char const* i_name, s8 roomNo,
                                                 s8 pointNo);
#define dSv_player_return_place_c__set                                                             \
    ((dSv_player_return_place_c__set_t)dSv_player_return_place_c__set_addr)

typedef void (*onDungeonItem__12dSv_memBit_cFi)(void* addr, int flag);
#define onDungeonItem__12dSv_memBit_cFi                                                            \
    ((onDungeonItem__12dSv_memBit_cFi) onDungeonItem__12dSv_memBit_cFi_addr)

typedef int (*isDungeonItem__12dSv_memBit_cFi)(void* addr, int flag);
#define isDungeonItem__12dSv_memBit_cFi                                                            \
    ((isDungeonItem__12dSv_memBit_cFi)isDungeonItem__12dSv_memBit_cFi_addr)

typedef void (*tww_getSave)(void* addr, int32_t areaID);
#define tww_getSave ((tww_getSave)tww_getSave_addr)

typedef void (*tww_putSave)(void* addr, int32_t areaID);
#define tww_putSave ((tww_putSave)tww_putSave_addr)



typedef void (*dSv_player_bag_item_c__setBeastItem_t)(void* addr, u8);
#define dSv_player_bag_item_c__setBeastItem ((dSv_player_bag_item_c__setBeastItem_t) dSv_player_bag_item_c__setBeastItem_addr)

typedef void (*dSv_player_bag_item_c__setBaitItem_t)(void* addr, u8);
#define dSv_player_bag_item_c__setBaitItem ((dSv_player_bag_item_c__setBaitItem_t) dSv_player_bag_item_c__setBaitItem_addr)

typedef bool (*dSv_player_map_c__isGetMap_t)(void* addr, int);
#define dSv_player_map_c__isGetMap ((dSv_player_map_c__isGetMap_t) dSv_player_map_c__isGetMap_addr)

typedef void (*dSv_player_map_c__onGetMap_t)(void* addr, int);
#define dSv_player_map_c__onGetMap ((dSv_player_map_c__onGetMap_t) dSv_player_map_c__onGetMap_addr)

typedef void (*dSv_event_c__setEventReg_t)(void* addr, u16 reg, u8 flag);
#define dSv_event_c__setEventReg ((dSv_event_c__setEventReg_t) dSv_event_c__setEventReg_addr)

typedef u8 (*dSv_event_c__getEventReg_t)(void* addr, u16 reg);
#define dSv_event_c__getEventReg ((dSv_event_c__getEventReg_t) dSv_event_c__getEventReg_addr)

typedef int (*dSv_player_collect_c__getTriforceNum_t)(void* addr);
#define dSv_player_collect_c__getTriforceNum ((dSv_player_collect_c__getTriforceNum_t) dSv_player_collect_c__getTriforceNum_addr)

typedef bool (*dSv_memBit_c__isTbox_t)(void* addr, int);
#define dSv_memBit_c__isTbox ((dSv_memBit_c__isTbox_t) dSv_memBit_c__isTbox_addr)

typedef void (*dSv_memBit_c__onTbox_t)(void* addr, int);
#define dSv_memBit_c__onTbox ((dSv_memBit_c__onTbox_t) dSv_memBit_c__onTbox_addr)

typedef bool (*dSv_memBit_c__isSwitch_t)(void* addr, int);
#define dSv_memBit_c__isSwitch ((dSv_memBit_c__isSwitch_t) dSv_memBit_c__isSwitch_addr)

typedef void (*dSv_memBit_c__onSwitch_t)(void* addr, int);
#define dSv_memBit_c__onSwitch ((dSv_memBit_c__onSwitch_t) dSv_memBit_c__onSwitch_addr)

typedef void (*dSv_memBit_c__offSwitch_t)(void* addr, int);
#define dSv_memBit_c__offSwitch ((dSv_memBit_c__offSwitch_t) dSv_memBit_c__offSwitch_addr)

typedef bool (*dSv_player_collect_c__isCollect_t)(void* addr, int, u8);
#define dSv_player_collect_c__isCollect ((dSv_player_collect_c__isCollect_t) dSv_player_collect_c__isCollect_addr)

typedef void (*dSv_player_collect_c__onCollect_t)(void* addr, int, u8);
#define dSv_player_collect_c__onCollect ((dSv_player_collect_c__onCollect_t) dSv_player_collect_c__onCollect_addr)

typedef void (*dSv_player_collect_c__offCollect_t)(void* addr, int, u8);
#define dSv_player_collect_c__offCollect ((dSv_player_collect_c__offCollect_t) dSv_player_collect_c__offCollect_addr)

typedef bool (*dSv_player_collect_c__isTact_t)(void* addr, u8);
#define dSv_player_collect_c__isTact ((dSv_player_collect_c__isTact_t) dSv_player_collect_c__isTact_addr)

typedef void (*dSv_player_collect_c__onTact_t)(void* addr, u8);
#define dSv_player_collect_c__onTact ((dSv_player_collect_c__onTact_t) dSv_player_collect_c__onTact_addr)

typedef bool (*dSv_player_collect_c__isTriforce_t)(void* addr, u8);
#define dSv_player_collect_c__isTriforce ((dSv_player_collect_c__isTriforce_t) dSv_player_collect_c__isTriforce_addr)

typedef void (*dSv_player_collect_c__onTriforce_t)(void* addr, u8);
#define dSv_player_collect_c__onTriforce ((dSv_player_collect_c__onTriforce_t) dSv_player_collect_c__onTriforce_addr)

typedef bool (*dSv_player_collect_c__isSymbol_t)(void* addr, u8);
#define dSv_player_collect_c__isSymbol ((dSv_player_collect_c__isSymbol_t) dSv_player_collect_c__isSymbol_addr)

typedef void (*dSv_player_collect_c__onSymbol_t)(void* addr, u8);
#define dSv_player_collect_c__onSymbol ((dSv_player_collect_c__onSymbol_t) dSv_player_collect_c__onSymbol_addr)


typedef void (*dSv_info_c__onSwitch_t)(void* addr, int, int);
#define dSv_info_c__onSwitch ((dSv_info_c__onSwitch_t) dSv_info_c__onSwitch_addr)

typedef void (*dSv_info_c__offSwitch_t)(void* addr, int, int);
#define dSv_info_c__offSwitch ((dSv_info_c__offSwitch_t) dSv_info_c__offSwitch_addr)

typedef bool (*dSv_info_c__isSwitch_t)(void* addr, int, int);
#define dSv_info_c__isSwitch ((dSv_info_c__isSwitch_t) dSv_info_c__isSwitch_addr)

typedef bool (*dSv_info_c__revSwitch_t)(void* addr, int, int);
#define dSv_info_c__revSwitch ((dSv_info_c__revSwitch_t) dSv_info_c__revSwitch_addr)

typedef void (*dSv_info_c__onItem_t)(void* addr, int, int);
#define dSv_info_c__onItem ((dSv_info_c__onItem_t) dSv_info_c__onItem_addr)

typedef bool (*dSv_info_c__isItem_t)(void* addr, int, int);
#define dSv_info_c__isItem ((dSv_info_c__isItem_t) dSv_info_c__isItem_addr)


typedef void (*dSv_player_get_item_c__onItem_t)(void* addr, int, u8);
#define dSv_player_get_item_c__onItem ((dSv_player_get_item_c__onItem_t) dSv_player_get_item_c__onItem_addr)

typedef bool (*dSv_player_get_item_c__isItem_t)(void* addr, int, u8);
#define dSv_player_get_item_c__isItem ((dSv_player_get_item_c__isItem_t) dSv_player_get_item_c__isItem_addr)


typedef void (*dSv_player_get_bag_item_c__onBeast_t)(void* addr, u8);
#define dSv_player_get_bag_item_c__onBeast ((dSv_player_get_bag_item_c__onBeast_t) dSv_player_get_bag_item_c__onBeast_addr)

typedef bool (*dSv_player_get_bag_item_c__isBeast_t)(void* addr, u8);
#define dSv_player_get_bag_item_c__isBeast ((dSv_player_get_bag_item_c__isBeast_t) dSv_player_get_bag_item_c__isBeast_addr)

typedef void (*dSv_player_get_bag_item_c__onBait_t)(void* addr,  u8);
#define dSv_player_get_bag_item_c__onBait ((dSv_player_get_bag_item_c__onBait_t) dSv_player_get_bag_item_c__onBait_addr)

typedef bool (*dSv_player_get_bag_item_c__isBait_t)(void* addr, u8);
#define dSv_player_get_bag_item_c__isBait ((dSv_player_get_bag_item_c__isBait_t) dSv_player_get_bag_item_c__isBait_addr)

#endif /* D_SAVE_D_SAVE_H */
