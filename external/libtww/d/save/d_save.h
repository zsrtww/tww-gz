#ifndef D_SAVE_D_SAVE_H
#define D_SAVE_D_SAVE_H

#include "../../SSystem/SComponent/c_xyz.h"
#include "../../dolphin/gctypes.h"

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
    u16& getMaxLife() { return mMaxLife; }
    u8& getMaxMagic() { return mMaxMagic; }
    u16& getLife() { return mLife; }
    u8& getMagic() { return mMagic; }
    u16& getRupee() { return mRupee; }
    u8 getSelectEquip(int item) const { return mSelectEquip[item]; }

    void setMagic(u8 magic) { mMagic = magic; }
    void setMaxMagic(u8 max) { mMaxMagic = max; }
    void setRupee(u16 rupees) { mRupee = rupees; }
    void setLife(u16 life) { mLife = life; }
    void setMaxLife(u16 max) { mMaxLife = max; }
    void setSelectEquip(int item_index, u8 item) { mSelectEquip[item_index] = item; }

    /* 0x00 */ u16 mMaxLife;
    /* 0x02 */ u16 mLife;
    /* 0x04 */ u16 mRupee;
    /* 0x06 */ u8 field_0x6[3];
    /* 0x09 */ u8 mSelectItem[3];
    /* 0x0C */ u8 field_0xc[2];
    /* 0x0E */ u8 mSelectEquip[4];
    /* 0x12 */ u8 mWalletSize;
    /* 0x13 */ u8 mMaxMagic;
    /* 0x14 */ u8 mMagic;
};  // Size: 0x18

class dSv_player_status_b_c {
public:
    void setTime(float pTime) { mTime = pTime; }
    float getTime() const { return mTime; }

    /* 0x00 */ int64_t mDateIpl;
    /* 0x08 */ u8 field_0x8[4];
    /* 0x0C */ float mTime;
    /* 0x10 */ u16 mDate;
    /* 0x12 */ s16 mTactWindAngleX;
    /* 0x14 */ s16 mTactWindAngleY;
};  // Size: 0x18

class dSv_player_return_place_c {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ s8 mRoomNo;
    /* 0x09 */ u8 mPlayerStatus;
    /* 0x0A */ u8 unk10;
    /* 0x0B */ u8 unk11;
};  // Size: 0xC

class dSv_player_item_c {
public:
    u8 getItemSlot(u8 index) { return mItemSlots[index]; }
    void setItemSlot(u8 index, u8 item_id) { mItemSlots[index] = item_id; }

    /* 0x0 */ u8 mItemSlots[21];
};  // Size: 0x15

class dSv_player_get_item_c {
public:
    /* 0x0 */ u8 mItemFlags[21];
};  // Size: 0x15

class dSv_player_item_record_c {
public:
    u8 getArrowNum() { return mArrowNum; }
    u8 getBombNum() { return mBombNum; }

    void setArrowNum(u8 amount) { mArrowNum = amount; }
    void setBombNum(u8 amount) { mBombNum = amount; }

    /* 0x0 */ u16 mTimer;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 mArrowNum;
    /* 0x4 */ u8 mBombNum;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 mBottleNum;
};  // Size: 0x8

class dSv_player_item_max_c {
public:
    /* 0x0 */ u8 mItemMax[8];
};  // Size: 0x8

class dSv_player_bag_item_c {
public:
    /* 0x0 */ u8 field_0x0[24];
};  // Size: 0x1A

class dSv_player_get_bag_item_c {
public:
    /* 0x0 */ u8 field_0x0[12];
};  // Size: 0xC

class dSv_player_bag_item_record_c {
public:
    /* 0x0 */ u8 field_0x0[24];
};  // Size: 0x18

class dSv_player_collect_c {
public:
    /* 0x0 */ u8 mItem[8];
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 mTact;
    /* 0xA */ u8 mTriforce;
    /* 0xB */ u8 mSymbol;
    /* 0xC */ u8 field_0xc;
    /* 0xD */ u8 padding[3];
};  // Size: 0x10

class dSv_player_map_c {
public:
    /* 0x0 */ u8 field_0x0[0x84];
};  // Size: 0x84

class dSv_player_info_c {
public:
    char* getLinkName() { return (char*)mPlayerName; }

    /* 0x00 */ u8 field_0x0[0x14];
    /* 0x14 */ u8 mPlayerName[16];
    /* 0x24 */ u8 field_0x24;
    /* 0x25 */ u8 field_0x25[16];
    /* 0x35 */ u8 field_0x35;
    /* 0x36 */ u8 field_0x36[16];
    /* 0x47 */ u8 field_0x47;
    /* 0x48 */ u8 field_0x48[0x58 - 0x48];
    /* 0x58 */ u8 mNumGamesCompleted;
    /* 0x59 */ u8 mFmapIdx;
};  // Size: 0x5C

class dSv_player_config_c {
public:
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 mSoundMode;
    /* 0x2 */ u8 mAttentionType;  // Lock-On Type; 0 : hold, 1 : switch
    /* 0x3 */ u8 mVibration;      // Rumble status
    /* 0x4 */ u8 unk4;
};  // Size: 0x5

class dSv_player_priest_c {
public:
    /* 0x0 */ cXyz field_0x0;
    /* 0xC */ s16 field_0xc;
    /* 0xE */ s8 field_0xe;
    /* 0xF */ u8 field_0xf;
};  // Size: 0x10

class dSv_player_status_c_c {
public:
    /* 0x0 */ u8 field_0x0[0x18];
};  // Size: 0x18

class dSv_player_c {
public:
    dSv_player_info_c& getPlayerInfo() { return mPlayerInfo; }
    dSv_player_status_a_c& getPlayerStatusA() { return mPlayerStatusA; }
    dSv_player_status_b_c& getPlayerStatusB() { return mPlayerStatusB; }
    dSv_player_item_c& getItem() { return mItem; }
    dSv_player_collect_c& getCollect() { return mCollect; }
    dSv_player_item_record_c& getItemRecord() { return mItemRecord; }
    dSv_player_item_max_c& getItemMax() { return mItemMax; }
    dSv_player_return_place_c& getPlayerReturnPlace() { return mPlayerReturnPlace; }
    dSv_player_get_item_c& getGetItem() { return mGetItem; }
    dSv_player_config_c& getConfig() { return mConfig; }

    /* 0x000 */ dSv_player_status_a_c mPlayerStatusA;
    /* 0x018 */ dSv_player_status_b_c mPlayerStatusB;
    /* 0x030 */ dSv_player_return_place_c mPlayerReturnPlace;
    /* 0x03C */ dSv_player_item_c mItem;
    /* 0x051 */ dSv_player_get_item_c mGetItem;
    /* 0x066 */ dSv_player_item_record_c mItemRecord;
    /* 0x06E */ dSv_player_item_max_c mItemMax;
    /* 0x076 */ dSv_player_bag_item_c mBagItem;
    /* 0x08E */ u8 field_0x8e[2];
    /* 0x090 */ dSv_player_get_bag_item_c mGetBagItem;
    /* 0x09C */ dSv_player_bag_item_record_c mBagItemRecord;
    /* 0x0B4 */ dSv_player_collect_c mCollect;
    /* 0x0C4 */ dSv_player_map_c mMap;
    /* 0x148 */ dSv_player_info_c mPlayerInfo;
    /* 0x1A4 */ dSv_player_config_c mConfig;
    /* 0x1AC */ dSv_player_priest_c mPriest;
    /* 0x1BC */ dSv_player_status_c_c mPlayerStatusC;
};  // Size: 0x1D4

class dSv_memBit_c {
public:
    /* 0x00 */ u32 mTbox[1];
    /* 0x04 */ u32 mSwitch[4];
    /* 0x14 */ u32 mItem[1];
    /* 0x18 */ u32 mVisitedRoom[2];
    /* 0x20 */ u8 mKeyNum;
    /* 0x21 */ u8 mDungeonItem;
};  // Size: 0x24

class dSv_event_c {
public:
    /* 0x0 */ u8 mEvent[256];
};  // Size: 0x100

class dSv_memory_c {
public:
    dSv_memBit_c& getBit() { return mBit; }
    const dSv_memBit_c& getBit() const { return mBit; }

    /* 0x0 */ dSv_memBit_c mBit;
};  // Size: 0x20

class dSv_danBit_c {
public:
    /* 0x00 */ s8 mStageNo;
    /* 0x04 */ u32 mSwitch[2];
};  // Size: 0xC

class dSv_zoneBit_c {
public:
    /* 0x00 */ u16 mSwitch[2];
    /* 0x04 */ u16 mRoomSwitch;
    /* 0x06 */ u16 mItem;
};  // Size: 0x8

class dSv_zoneActor_c {
public:
    /* 0x00 */ u32 mActorFlags[16];
};  // Size: 0x10

class dSv_zone_c {
public:
    dSv_zoneBit_c& getZoneBit() { return mBit; }
    const dSv_zoneBit_c& getBit() const { return mBit; }
    dSv_zoneActor_c& getActor() { return mActor; }
    const dSv_zoneActor_c& getActor() const { return mActor; }

    s8& getRoomNo() { return mRoomNo; }

    /* 0x0 */ s8 mRoomNo;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ dSv_zoneBit_c mBit;
    /* 0xC */ dSv_zoneActor_c mActor;
};  // Size: 0x4C

class dSv_restart_c {
public:
    /* 0x00 */ u8 mRestartCode;
    /* 0x01 */ u8 field_0x1;
    /* 0x02 */ s8 mRoomNo;
    /* 0x06 */ s16 mRoomAngleY;
    /* 0x08 */ cXyz mRoomPos;
    /* 0x14 */ u32 mRoomParam;
    /* 0x18 */ cXyz mLinkRestartPos;
    /* 0x24 */ u32 mLinkRestartParam;
};  // Size: 0x28

class dSv_turnRestart_c {
public:
    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ u32 mParam;
    /* 0x10 */ s16 mAngleY;
    /* 0x12 */ s8 mRoomNo;
    /* 0x14 */ u8 field_0x14[0x24 - 0x14];
    /* 0x24 */ cXyz field_0x24;
    /* 0x30 */ s16 field_0x30;
    /* 0x34 */ float field_0x34;
};  // Size: 0x38

class dSv_ocean_c {
public:
    /* 0x0 */ u16 mBits[50];
};  // Size: 0x64

class dSv_save_c {
public:
    dSv_player_c& getPlayer() { return mPlayer; }
    dSv_event_c& getEvent() { return mEvent; }
    dSv_memory_c& getSave(int i_stageNo) { return mSave[i_stageNo]; }
    void putSave(int i_stageNo, dSv_memory_c mem) { mSave[i_stageNo] = mem; }

    static const int STAGE_MAX = 16;

    /* 0x000 */ dSv_player_c mPlayer;
    /* 0x1D4 */ u8 field_0x1d4[0x380 - 0x1D4];
    /* 0x380 */ dSv_memory_c mSave[STAGE_MAX];
    /* 0x5C0 */ dSv_ocean_c mOcean;
    /* 0x624 */ dSv_event_c mEvent;
};  // Size: 0x724

class dSv_info_c {
public:
    dSv_save_c& getSavedata() { return mSavedata; }
    dSv_memory_c& getMemory() { return mMemory; }
    dSv_player_c& getPlayer() { return mSavedata.getPlayer(); }
    dSv_event_c& getTmp() { return mTmp; }

    /* 0x0000 */ dSv_save_c mSavedata;
    /* 0x0778 */ u8 field_0x724[0x778 - 0x724];
    /* 0x0778 */ dSv_memory_c mMemory;
    /* 0x079C */ dSv_danBit_c mDan;
    /* 0x07A8 */ dSv_zone_c mZone[32];
    /* 0x1128 */ dSv_restart_c mRestart;
    /* 0x1150 */ u8 field_0x1150[0x1158 - 0x1150];
    /* 0x1158 */ dSv_event_c mTmp;
    /* 0x1258 */ dSv_turnRestart_c mTurnRestart;
    /* 0x1290 */ u8 field_0x1290[0x10];
};  // Size: 0x12A0

static_assert(sizeof(dSv_info_c) == 0x12A0);

typedef void (*dSv_player_return_place_c__set_t)(void* _this, char const* i_name, s8 roomNo,
                                                 s8 pointNo);
#define dSv_player_return_place_c__set                                                             \
    ((dSv_player_return_place_c__set_t)dSv_player_return_place_c__set_addr)

#endif /* D_SAVE_D_SAVE_H */