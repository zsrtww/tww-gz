#ifndef D_SAVE_D_SAVE_H
#define D_SAVE_D_SAVE_H

#include "../../SSystem/SComponent/c_xyz.h"
#include <stdint.h>

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
    /* 0x00 */ HEART,
    /* 0x01 */ GREEN_RUPEE,
    /* 0x02 */ BLUE_RUPEE,
    /* 0x03 */ YELLOW_RUPEE,
    /* 0x04 */ RED_RUPEE,
    /* 0x05 */ PURPLE_RUPEE,
    /* 0x06 */ ORANGE_RUPEE,
    /* 0x07 */ SILVER_RUPEE,
    /* 0x08 */ S_MAGIC,
    /* 0x09 */ L_MAGIC,
    /* 0x0A */ BOMB_5,
    /* 0x0B */ BOMB_10,
    /* 0x0C */ BOMB_20,
    /* 0x0D */ BOMB_30,
    /* 0x0E */ ARROW_10,
    /* 0x0F */ ARROW_20,
    /* 0x10 */ ARROW_30,
    /* 0x11 */ ARROW_1,
    /* 0x12 */ PACHINKO_SHOT,
    /* 0x13 */ noentry1,
    /* 0x14 */ noentry2,
    /* 0x15 */ noentry3,
    /* 0x16 */ WATER_BOMB_5,
    /* 0x17 */ WATER_BOMB_10,
    /* 0x18 */ WATER_BOMB_20,
    /* 0x19 */ WATER_BOMB_30,
    /* 0x1A */ BOMB_INSECT_5,
    /* 0x1B */ BOMB_INSECT_10,
    /* 0x1C */ BOMB_INSECT_20,
    /* 0x1D */ BOMB_INSECT_30,
    /* 0x1E */ RECOVERY_FAILY,
    /* 0x1F */ TRIPLE_HEART,
    /* 0x20 */ SMALL_KEY,
    /* 0x21 */ KAKERA_HEART,
    /* 0x22 */ UTAWA_HEART,
    /* 0x23 */ MAP,
    /* 0x24 */ COMPUS,
    /* 0x25 */ DUNGEON_EXIT,
    /* 0x26 */ BOSS_KEY,
    /* 0x27 */ DUNGEON_BACK,
    /* 0x28 */ SWORD,
    /* 0x29 */ MASTER_SWORD,
    /* 0x2A */ WOOD_SHIELD,
    /* 0x2B */ SHIELD,
    /* 0x2C */ HYLIA_SHIELD,
    /* 0x2D */ TKS_LETTER,
    /* 0x2E */ WEARS_CASUAL,
    /* 0x2F */ WEAR_KOKIRI,
    /* 0x30 */ ARMOR,
    /* 0x31 */ WEAR_ZORA,
    /* 0x32 */ MAGIC_LV1,
    /* 0x33 */ DUNGEON_EXIT_2,
    /* 0x34 */ WALLET_LV1,
    /* 0x35 */ WALLET_LV2,
    /* 0x36 */ WALLET_LV3,
    /* 0x37 */ noentry4,
    /* 0x38 */ noentry5,
    /* 0x39 */ noentry6,
    /* 0x3A */ noentry7,
    /* 0x3B */ noentry8,
    /* 0x3C */ noentry9,
    /* 0x3D */ ZORAS_JEWEL,
    /* 0x3E */ HAWK_EYE,
    /* 0x3F */ WOOD_STICK,
    /* 0x40 */ BOOMERANG,
    /* 0x41 */ SPINNER,
    /* 0x42 */ IRONBALL,
    /* 0x43 */ BOW,
    /* 0x44 */ HOOKSHOT,
    /* 0x45 */ HVY_BOOTS,
    /* 0x46 */ COPY_ROD,
    /* 0x47 */ W_HOOKSHOT,
    /* 0x48 */ KANTERA,
    /* 0x49 */ LIGHT_SWORD,
    /* 0x4A */ FISHING_ROD_1,
    /* 0x4B */ PACHINKO,
    /* 0x4C */ COPY_ROD_2,
    /* 0x4D */ noentry10,
    /* 0x4E */ noentry11,
    /* 0x4F */ BOMB_BAG_LV2,
    /* 0x50 */ BOMB_BAG_LV1,
    /* 0x51 */ BOMB_IN_BAG,
    /* 0x52 */ noentry12,
    /* 0x53 */ LIGHT_ARROW,
    /* 0x54 */ ARROW_LV1,
    /* 0x55 */ ARROW_LV2,
    /* 0x56 */ ARROW_LV3,
    /* 0x57 */ noentry13,
    /* 0x58 */ LURE_ROD,
    /* 0x59 */ BOMB_ARROW,
    /* 0x5A */ HAWK_ARROW,
    /* 0x5B */ BEE_ROD,
    /* 0x5C */ JEWEL_ROD,
    /* 0x5D */ WORM_ROD,
    /* 0x5E */ JEWEL_BEE_ROD,
    /* 0x5F */ JEWEL_WORM_ROD,
    /* 0x60 */ EMPTY_BOTTLE,
    /* 0x61 */ RED_BOTTLE,
    /* 0x62 */ GREEN_BOTTLE,
    /* 0x63 */ BLUE_BOTTLE,
    /* 0x64 */ MILK_BOTTLE,
    /* 0x65 */ HALF_MILK_BOTTLE,
    /* 0x66 */ OIL_BOTTLE,
    /* 0x67 */ WATER_BOTTLE,
    /* 0x68 */ OIL_BOTTLE_2,
    /* 0x69 */ RED_BOTTLE_2,
    /* 0x6A */ UGLY_SOUP,
    /* 0x6B */ HOT_SPRING,
    /* 0x6C */ FAIRY,
    /* 0x6D */ HOT_SPRING_2,
    /* 0x6E */ OIL2,
    /* 0x6F */ OIL,
    /* 0x70 */ NORMAL_BOMB,
    /* 0x71 */ WATER_BOMB,
    /* 0x72 */ POKE_BOMB,
    /* 0x73 */ FAIRY_DROP,
    /* 0x74 */ WORM,
    /* 0x75 */ DROP_BOTTLE,
    /* 0x76 */ BEE_CHILD,
    /* 0x77 */ CHUCHU_RARE,
    /* 0x78 */ CHUCHU_RED,
    /* 0x79 */ CHUCHU_BLUE,
    /* 0x7A */ CHUCHU_GREEN,
    /* 0x7B */ CHUCHU_YELLOW,
    /* 0x7C */ CHUCHU_PURPLE,
    /* 0x7D */ LV1_SOUP,
    /* 0x7E */ LV2_SOUP,
    /* 0x7F */ LV3_SOUP,
    /* 0x80 */ LETTER,
    /* 0x81 */ BILL,
    /* 0x82 */ WOOD_STATUE,
    /* 0x83 */ IRIAS_PENDANT,
    /* 0x84 */ HORSE_FLUTE,
    /* 0x85 */ noentry14,
    /* 0x86 */ noentry15,
    /* 0x87 */ noentry16,
    /* 0x88 */ noentry17,
    /* 0x89 */ noentry18,
    /* 0x8A */ noentry19,
    /* 0x8B */ noentry20,
    /* 0x8C */ noentry21,
    /* 0x8D */ noentry22,
    /* 0x8E */ noentry23,
    /* 0x8F */ noentry24,
    /* 0x90 */ RAFRELS_MEMO,
    /* 0x91 */ ASHS_SCRIBBLING,
    /* 0x92 */ noentry25,
    /* 0x93 */ noentry26,
    /* 0x94 */ noentry27,
    /* 0x95 */ noentry28,
    /* 0x96 */ noentry29,
    /* 0x97 */ noentry30,
    /* 0x98 */ noentry31,
    /* 0x99 */ noentry32,
    /* 0x9A */ noentry33,
    /* 0x9B */ noentry34,
    /* 0x9C */ CHUCHU_YELLOW2,
    /* 0x9D */ OIL_BOTTLE3,
    /* 0x9E */ SHOP_BEE_CHILD,
    /* 0x9F */ CHUCHU_BLACK,
    /* 0xA0 */ LIGHT_DROP,
    /* 0xA1 */ DROP_CONTAINER,
    /* 0xA2 */ DROP_CONTAINER02,
    /* 0xA3 */ DROP_CONTAINER03,
    /* 0xA4 */ FILLED_CONTAINER,
    /* 0xA5 */ MIRROR_PIECE_2,
    /* 0xA6 */ MIRROR_PIECE_3,
    /* 0xA7 */ MIRROR_PIECE_4,
    /* 0xA8 */ noentry35,
    /* 0xA9 */ noentry36,
    /* 0xAA */ noentry37,
    /* 0xAB */ noentry38,
    /* 0xAC */ noentry39,
    /* 0xAD */ noentry40,
    /* 0xAE */ noentry41,
    /* 0xAF */ noentry42,
    /* 0xB0 */ SMELL_YELIA_POUCH,
    /* 0xB1 */ SMELL_PUMPKIN,
    /* 0xB2 */ SMELL_POH,
    /* 0xB3 */ SMELL_FISH,
    /* 0xB4 */ SMELL_CHILDREN,
    /* 0xB5 */ SMELL_MEDICINE,
    /* 0xB6 */ noentry43,
    /* 0xB7 */ noentry44,
    /* 0xB8 */ noentry45,
    /* 0xB9 */ noentry46,
    /* 0xBA */ noentry47,
    /* 0xBB */ noentry48,
    /* 0xBC */ noentry49,
    /* 0xBD */ noentry50,
    /* 0xBE */ noentry51,
    /* 0xBF */ noentry52,
    /* 0xC0 */ M_BEETLE,
    /* 0xC1 */ F_BEETLE,
    /* 0xC2 */ M_BUTTERFLY,
    /* 0xC3 */ F_BUTTERFLY,
    /* 0xC4 */ M_STAG_BEETLE,
    /* 0xC5 */ F_STAG_BEETLE,
    /* 0xC6 */ M_GRASSHOPPER,
    /* 0xC7 */ F_GRASSHOPPER,
    /* 0xC8 */ M_NANAFUSHI,
    /* 0xC9 */ F_NANAFUSHI,
    /* 0xCA */ M_DANGOMUSHI,
    /* 0xCB */ F_DANGOMUSHI,
    /* 0xCC */ M_MANTIS,
    /* 0xCD */ F_MANTIS,
    /* 0xCE */ M_LADYBUG,
    /* 0xCF */ F_LADYBUG,
    /* 0xD0 */ M_SNAIL,
    /* 0xD1 */ F_SNAIL,
    /* 0xD2 */ M_DRAGONFLY,
    /* 0xD3 */ F_DRAGONFLY,
    /* 0xD4 */ M_ANT,
    /* 0xD5 */ F_ANT,
    /* 0xD6 */ M_MAYFLY,
    /* 0xD7 */ F_MAYFLY,
    /* 0xD8 */ noentry53,
    /* 0xD9 */ noentry54,
    /* 0xDA */ noentry55,
    /* 0xDB */ noentry56,
    /* 0xDC */ noentry57,
    /* 0xDD */ noentry58,
    /* 0xDE */ noentry59,
    /* 0xDF */ noentry60,
    /* 0xE0 */ POU_SPIRIT,
    /* 0xE1 */ noentry61,
    /* 0xE2 */ noentry62,
    /* 0xE3 */ noentry63,
    /* 0xE4 */ noentry64,
    /* 0xE5 */ noentry65,
    /* 0xE6 */ noentry66,
    /* 0xE7 */ noentry67,
    /* 0xE8 */ noentry68,
    /* 0xE9 */ ANCIENT_DOCUMENT,
    /* 0xEA */ AIR_LETTER,
    /* 0xEB */ ANCIENT_DOCUMENT2,
    /* 0xEC */ LV7_DUNGEON_EXIT,
    /* 0xED */ LINKS_SAVINGS,
    /* 0xEE */ SMALL_KEY2,
    /* 0xEF */ POU_FIRE1,
    /* 0xF0 */ POU_FIRE2,
    /* 0xF1 */ POU_FIRE3,
    /* 0xF2 */ POU_FIRE4,
    /* 0xF3 */ BOSSRIDER_KEY,
    /* 0xF4 */ TOMATO_PUREE,
    /* 0xF5 */ TASTE,
    /* 0xF6 */ LV5_BOSS_KEY,
    /* 0xF7 */ SURFBOARD,
    /* 0xF8 */ KANTERA2,
    /* 0xF9 */ L2_KEY_PIECES1,
    /* 0xFA */ L2_KEY_PIECES2,
    /* 0xFB */ L2_KEY_PIECES3,
    /* 0xFC */ KEY_OF_CARAVAN,
    /* 0xFD */ LV2_BOSS_KEY,
    /* 0xFE */ KEY_OF_FILONE,
    /* 0xFF */ NO_ITEM
};

class dSv_player_status_a_c {
public:
    uint16_t& getMaxLife() { return mMaxLife; }
    uint16_t& getLife() { return mLife; }
    uint16_t& getRupee() { return mRupee; }
    uint8_t getSelectEquip(int item) const { return mSelectEquip[item]; }

    void setMagic(uint8_t magic) { mMagic = magic; }
    void setMaxMagic(uint8_t max) { mMaxMagic = max; }
    void setRupee(uint16_t rupees) { mRupee = rupees; }
    void setLife(uint16_t life) { mLife = life; }
    void setMaxLife(uint8_t max) { mMaxLife = max; }
    void setSelectEquip(int item_index, uint8_t item) { mSelectEquip[item_index] = item; }

    /* 0x00 */ uint16_t mMaxLife;
    /* 0x02 */ uint16_t mLife;
    /* 0x04 */ uint16_t mRupee;
    /* 0x06 */ uint8_t field_0x6[3];
    /* 0x09 */ uint8_t mSelectItem[3];
    /* 0x0C */ uint8_t field_0xc[2];
    /* 0x0E */ uint8_t mSelectEquip[4];
    /* 0x12 */ uint8_t mWalletSize;
    /* 0x13 */ uint8_t mMaxMagic;
    /* 0x14 */ uint8_t mMagic;
};  // Size: 0x18

class dSv_player_status_b_c {
public:
    void setTime(float pTime) { mTime = pTime; }
    float getTime() const { return mTime; }

    /* 0x00 */ int64_t mDateIpl;
    /* 0x08 */ uint8_t field_0x8[4];
    /* 0x0C */ float mTime;
    /* 0x10 */ uint16_t mDate;
    /* 0x12 */ int16_t mTactWindAngleX;
    /* 0x14 */ int16_t mTactWindAngleY;
};  // Size: 0x18

class dSv_player_return_place_c {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ int8_t mRoomNo;
    /* 0x09 */ uint8_t mPlayerStatus;
    /* 0x0A */ uint8_t unk10;
    /* 0x0B */ uint8_t unk11;
};  // Size: 0xC

class dSv_player_item_c {
public:
    /* 0x0 */ uint8_t mItemSlots[21];
};  // Size: 0x15

class dSv_player_get_item_c {
public:
    /* 0x0 */ uint8_t mItemFlags[21];
};  // Size: 0x15

class dSv_player_item_record_c {
public:
    void setArrowNum(uint8_t amount) { mArrowNum = amount; }
    uint8_t getArrowNum() { return mArrowNum; }

    /* 0x0 */ uint16_t mTimer;
    /* 0x2 */ uint8_t field_0x2;
    /* 0x3 */ uint8_t mArrowNum;
    /* 0x4 */ uint8_t mBombNum;
    /* 0x5 */ uint8_t field_0x5;
    /* 0x6 */ uint8_t mBottleNum;
};  // Size: 0x8

class dSv_player_item_max_c {
public:
    /* 0x0 */ uint8_t mItemMax[8];
};  // Size: 0x8

class dSv_player_bag_item_c {
public:
    /* 0x0 */ uint8_t field_0x0[24];
};  // Size: 0x1A

class dSv_player_get_bag_item_c {
public:
    /* 0x0 */ uint8_t field_0x0[12];
};  // Size: 0xC

class dSv_player_bag_item_record_c {
public:
    /* 0x0 */ uint8_t field_0x0[24];
};  // Size: 0x18

class dSv_player_collect_c {
public:
    /* 0x0 */ uint8_t mItem[8];
    /* 0x8 */ uint8_t unk8;
    /* 0x9 */ uint8_t mTact;
    /* 0xA */ uint8_t mTriforce;
    /* 0xB */ uint8_t mSymbol;
    /* 0xC */ uint8_t field_0xc;
    /* 0xD */ uint8_t padding[3];
};  // Size: 0x10

class dSv_player_map_c {
public:
    /* 0x0 */ uint8_t field_0x0[0x84];
};  // Size: 0x84

class dSv_player_info_c {
public:
    char* getLinkName() { return (char*)mPlayerName; }

    /* 0x00 */ uint8_t field_0x0[0x14];
    /* 0x14 */ uint8_t mPlayerName[16];
    /* 0x24 */ uint8_t field_0x24;
    /* 0x25 */ uint8_t field_0x25[16];
    /* 0x35 */ uint8_t field_0x35;
    /* 0x36 */ uint8_t field_0x36[16];
    /* 0x47 */ uint8_t field_0x47;
    /* 0x48 */ uint8_t field_0x48[0x58 - 0x48];
    /* 0x58 */ uint8_t mNumGamesCompleted;
    /* 0x59 */ uint8_t mFmapIdx;
};  // Size: 0x5C

class dSv_player_config_c {
public:
    /* 0x0 */ uint8_t unk0;
    /* 0x1 */ uint8_t mSoundMode;
    /* 0x2 */ uint8_t mAttentionType;  // Lock-On Type; 0 : hold, 1 : switch
    /* 0x3 */ uint8_t mVibration;      // Rumble status
    /* 0x4 */ uint8_t unk4;
}; // Size: 0x5

class dSv_player_priest_c {
public:
    /* 0x0 */ cXyz field_0x0;
    /* 0xC */ s16 field_0xc;
    /* 0xE */ s8 field_0xe;
    /* 0xF */ u8 field_0xf;
};  // Size: 0x10

class dSv_player_status_c_c {
public:
    /* 0x0 */ uint8_t field_0x0[0x18];
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
    /* 0x08E */ uint8_t field_0x8e[2];
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
    /* 0x00 */ uint32_t mTbox[1];
    /* 0x04 */ uint32_t mSwitch[4];
    /* 0x14 */ uint32_t mItem[1];
    /* 0x18 */ uint32_t mVisitedRoom[2];
    /* 0x20 */ uint8_t mKeyNum;
    /* 0x21 */ uint8_t mDungeonItem;
};  // Size: 0x24

class dSv_event_c {
public:
    /* 0x0 */ uint8_t mEvent[256];
};  // Size: 0x100

class dSv_memory_c {
public:
    dSv_memBit_c& getBit() { return mBit; }
    const dSv_memBit_c& getBit() const { return mBit; }

    /* 0x0 */ dSv_memBit_c mBit;
};  // Size: 0x20

class dSv_danBit_c {
public:
    /* 0x00 */ int8_t mStageNo;
    /* 0x04 */ uint32_t mSwitch[2];
};  // Size: 0xC

class dSv_zoneBit_c {
public:
    /* 0x00 */ uint16_t mSwitch[2];
    /* 0x04 */ uint16_t mRoomSwitch;
    /* 0x06 */ uint16_t mItem;
};  // Size: 0x8

class dSv_zoneActor_c {
public:
    /* 0x00 */ uint32_t mActorFlags[16];
};  // Size: 0x10

class dSv_zone_c {
public:
    dSv_zoneBit_c& getZoneBit() { return mBit; }
    const dSv_zoneBit_c& getBit() const { return mBit; }
    dSv_zoneActor_c& getActor() { return mActor; }
    const dSv_zoneActor_c& getActor() const { return mActor; }

    int8_t& getRoomNo() { return mRoomNo; }

    /* 0x0 */ int8_t mRoomNo;
    /* 0x1 */ uint8_t unk1;
    /* 0x2 */ dSv_zoneBit_c mBit;
    /* 0xC */ dSv_zoneActor_c mActor;
};  // Size: 0x4C

class dSv_restart_c {
public:
    /* 0x00 */ uint8_t mRestartCode;
    /* 0x01 */ uint8_t field_0x1;
    /* 0x02 */ int8_t mRoomNo;
    /* 0x06 */ int16_t mRoomAngleY;
    /* 0x08 */ cXyz mRoomPos;
    /* 0x14 */ uint32_t mRoomParam;
    /* 0x18 */ cXyz mLinkRestartPos;
    /* 0x24 */ uint32_t mLinkRestartParam;
};  // Size: 0x28

class dSv_turnRestart_c {
public:
    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ uint32_t mParam;
    /* 0x10 */ int16_t mAngleY;
    /* 0x12 */ int8_t mRoomNo;
    /* 0x14 */ uint8_t field_0x14[0x24 - 0x14];
    /* 0x24 */ cXyz field_0x24;
    /* 0x30 */ int16_t field_0x30;
    /* 0x34 */ float field_0x34;
};  // Size: 0x38

class dSv_ocean_c {
public:
    /* 0x0 */ uint16_t mBits[50];
};  // Size: 0x64

class dSv_save_c {
public:
    dSv_player_c& getPlayer() { return mPlayer; }
    dSv_event_c& getEvent() { return mEvent; }
    dSv_memory_c& getSave(int i_stageNo) { return mSave[i_stageNo]; }
    void putSave(int i_stageNo, dSv_memory_c mem) { mSave[i_stageNo] = mem; }

    static const int STAGE_MAX = 16;

    /* 0x000 */ dSv_player_c mPlayer;
    /* 0x1D4 */ uint8_t field_0x1d4[0x380 - 0x1D4];
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
    /* 0x0778 */ uint8_t field_0x724[0x778 - 0x724];
    /* 0x0778 */ dSv_memory_c mMemory;
    /* 0x079C */ dSv_danBit_c mDan;
    /* 0x07A8 */ dSv_zone_c mZone[32];
    /* 0x1128 */ dSv_restart_c mRestart;
    /* 0x1150 */ uint8_t field_0x1150[0x1158 - 0x1150];
    /* 0x1158 */ dSv_event_c mTmp;
    /* 0x1258 */ dSv_turnRestart_c mTurnRestart;
    /* 0x1290 */ uint8_t field_0x1290[0x10];
};  // Size: 0x12A0

static_assert(sizeof(dSv_info_c) == 0x12A0);

#endif /* D_SAVE_D_SAVE_H */