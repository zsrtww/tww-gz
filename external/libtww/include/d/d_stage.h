#ifndef D_D_STAGE_H
#define D_D_STAGE_H

#include "../addrs.h"
#include "save/d_save.h"
#include "../f_op/f_op_actor.h"
#include "../defines.h"
#include "kankyo/d_kankyo.h"
#include <string.h>

class JKRExpHeap;

class stage_vrbox_info_class {
public:
    /* 0x00 */ u32 field_0x00;
    /* 0x04 */ u32 field_0x04;
    /* 0x08 */ u32 field_0x08;
    /* 0x0C */ u32 field_0x0c;
    /* 0x10 */ GXColor mKumoColor;
    /* 0x14 */ GXColor mKumoCenterColor;
    /* 0x18 */ color_RGB_class mSkyColor;
    /* 0x1B */ color_RGB_class mUsoUmiColor;
    /* 0x1E */ color_RGB_class mKasumiMaeColor;
};

class stage_tresure_data_class {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ u32 mParameter;
    /* 0x0C */ cXyz mSpawnPos;
    /* 0x18 */ csXyz mAngle;
    /* 0x1E */ u16 mSetId;
};  // Size: 0x20

class stage_tresure_class {
public:
    /* 0x00 */ int num;
    /* 0x04 */ stage_tresure_data_class* m_entries;
};

struct stage_stag_info_class {
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ u8 mCameraType;
    /* 0x09 */ u8 field_0x09;
    /* 0x0A */ u16 field_0x0a;
    /* 0x0C */ u32 field_0x0c;
    /* 0x10 */ u32 field_0x10;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ u32 field_0x18;
    /* 0x1C */ u32 field_0x1c;
};

struct stage_scls_info_class {
    /* 0x0 */ char mStage[8];
    /* 0x8 */ u8 mStart;
    /* 0x9 */ u8 mRoom;
    /* 0xA */ u8 mWipe;
    /* 0xB */ u8 field_0xb;
};

struct stage_scls_info_dummy_class {
    /* 0x00 */ int num;
    /* 0x04 */ stage_scls_info_class* m_entries;
};

class stage_lightvec_info_class {
public:
    /* 0x00 */ Vec mPos;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ u8 field_0x18[0x1B - 0x18];
    /* 0x1B */ u8 mFluctuation;
};

class stage_pselect_info_class {
public:
    /* 0x0 */ u8 mPalIdx[8];
    /* 0x8 */ f32 mChangeRate;
};

struct stage_plight_info_class {
    /* 0x00 */ Vec mPos;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ u8 mColorR;
    /* 0x19 */ u8 mColorG;
    /* 0x1A */ u8 mColorB;
    /* 0x1B */ u8 mFluctuation;
};

class stage_palet_info_class {
public:
    /* 0x00 */ color_RGB_class mActor_C0;
    /* 0x03 */ color_RGB_class mActor_K0;
    /* 0x06 */ color_RGB_class mBG0_C0;
    /* 0x09 */ color_RGB_class mBG0_K0;
    /* 0x0C */ color_RGB_class mBG1_C0;
    /* 0x0F */ color_RGB_class mBG1_K0;
    /* 0x12 */ color_RGB_class mBG2_C0;
    /* 0x15 */ color_RGB_class mBG2_K0;
    /* 0x18 */ color_RGB_class mBG3_C0;
    /* 0x1B */ color_RGB_class mBG3_K0;
    /* 0x1E */ color_RGB_class mFog;
    /* 0x21 */ u8 mVirtIdx;
    /* 0x24 */ f32 mFogStartZ;
    /* 0x28 */ f32 mFogEndZ;
};

class stage_map_info_class {
public:
    /* 0x00 */ u8 field_0x00[0x35 - 0x00];
    /* 0x35 */ u8 field_0x35;
    /* 0x36 */ u8 mOceanXZ;
    /* 0x37 */ u8 field_0x37[0x38 - 0x37];
};

struct stage_map_info_dummy_class {
    int num;
    stage_map_info_class* m_entries;
};

class stage_envr_info_class {
public:
    /* 0x0 */ u8 mPselIdx[8];
};

struct stage_camera2_data_class {
    /* 0x00 */ int field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xc;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
};  // Size: 0x18

struct stage_camera_class {
    /* 0x0 */ int num;
    /* 0x4 */ stage_camera2_data_class* m_entries;
};

struct stage_arrow_data_class {
    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ csXyz mAngle;
};  // Size: 0x14

struct stage_arrow_class {
    /* 0x00 */ int num;
    /* 0x04 */ stage_arrow_data_class* m_entries;
};

class stage_actor_data_class {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ u32 mParameter;
    /* 0x0C */ cXyz mSpawnPos;
    /* 0x18 */ csXyz mAngle;
    /* 0x1E */ u16 mSetId;
};  // Size: 0x20

class stage_actor_class {
public:
    /* 0x0 */ int num;
    /* 0x4 */ stage_actor_data_class* m_entries;
};

class stage_tgsc_data_class : public stage_actor_data_class {
public:
    u8 mScale[3];
};  // Size: 0x24

class stage_tgsc_class {
public:
    /* 0x00 */ int num;
    /* 0x04 */ stage_tgsc_data_class* m_entries;
};

struct roomRead_data_class {
    /* 0x0 */ u8 mRoomCount;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x4 */ u8* mpRooms;
};

struct roomRead_class {
    /* 0x0 */ int num;
    /* 0x4 */ roomRead_data_class** m_entries;
};

struct dStage_MemoryMap_c {
    /* 0x0 */ int num;
    /* 0x4 */ u32* m_entries;
};

struct dPath;
struct dStage_dPath_c {
    /* 0x0 */ int num;
    /* 0x4 */ dPath* m_path;
};

struct dStage_Mult_info {
    /* 0x0 */ f32 mTransX;
    /* 0x4 */ f32 mTransY;
    /* 0x8 */ s16 mAngle;
    /* 0xA */ u8 mRoomNo;
    /* 0xB */ u8 mWaveMax;
};  // Size: 0xC

class dStage_Multi_c {
public:
    /* 0x0 */ int num;
    /* 0x4 */ dStage_Mult_info* m_entries;
};

struct stage_sound_data {
    /* 0x00 */ char field_0x0[8];
    /* 0x08 */ Vec field_0x8;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
};  // Size: 0x1C

struct dStage_SoundInfo_c {
    /* 0x0 */ int num;
    /* 0x4 */ stage_sound_data* m_entries;
};

class dStage_FileList_dt_c {
public:
    /* 0x0 */ u32 mParam;
    /* 0x4 */ f32 mSeaLevel;
};

struct dStage_dPnt_c {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ cXyz m_position;
};  // Size: 0x10

struct dStage_FloorInfo_c {};

struct dStage_Lbnk_c {
    /* 0x00 */ u32 m_num;
    /* 0x04 */ u8 * m_bank;
};

struct dStage_MemoryConfig_data {
    /* 0x0 */ u8 m_roomNo;
    /* 0x1 */ u8 m_blockID;
};  // Size: 0x2

struct dStage_MemoryConfig_c {
    /* 0x0 */ int num;
    /* 0x4 */ dStage_MemoryConfig_data* m_entries;
};

struct dStage_DMap_c {};

struct dStage_EventInfo_c {
    /* 0x0 */ int field_0x0;
    /* 0x1 */ char* mName;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
}; // Size: 0x18

struct dStage_Ship_data {
    /* 0x0 */ cXyz m_pos;
    /* 0xC */ s16 m_angle;
    /* 0xE */ u8 field_0xe;
    /* 0xF */ u8 field_0xf;
};

class dStage_Ship_c {
public:
    /* 0x0 */ int num;
    /* 0x4 */ dStage_Ship_data* m_entries;
};

struct FuncTable;

class dStage_dt_c {
public:
    /* 0x00 */ void* vtable;
};

class dStage_EventInfo_c;

class dStage_stageDt_c : public dStage_dt_c {
public:
    /* 0x04 */ stage_camera_class* mpCamera;
    /* 0x08 */ stage_arrow_class* mpArrow;
    /* 0x0C */ stage_actor_class* mpPlayer;
    /* 0x10 */ roomRead_class* mpRoomReads;
    /* 0x14 */ stage_map_info_class* mpMapInfo;
    /* 0x18 */ stage_map_info_dummy_class* mpMapInfoBase;
    /* 0x1C */ stage_palet_info_class* mpPaletInfo;
    /* 0x20 */ stage_pselect_info_class* mpPselectInfo;
    /* 0x24 */ stage_envr_info_class* mpEnvrInfo;
    /* 0x28 */ stage_vrbox_info_class* mpVrboxInfo;
    /* 0x2C */ stage_plight_info_class* mpPlightInfo;
    /* 0x30 */ int mPaletInfoNum;
    /* 0x34 */ int mPselectInfoNum;
    /* 0x38 */ int mEnvrInfoNum;
    /* 0x3C */ int mVrboxInfoNum;
    /* 0x40 */ int mPlightInfoNum;
    /* 0x44 */ u16 mPlayerNum;
    /* 0x48 */ stage_stag_info_class* mpStagInfo;
    /* 0x4C */ stage_scls_info_dummy_class* mpScls;
    /* 0x50 */ dStage_dPnt_c* mpPnt;
    /* 0x54 */ dStage_dPath_c* mpPath;
    /* 0x58 */ dStage_dPnt_c* mpPnt2;
    /* 0x5C */ dStage_dPath_c* mpPath2;
    /* 0x60 */ dStage_SoundInfo_c* mpSoundInfo;
    /* 0x64 */ dStage_EventInfo_c* mpEventInfo;
    /* 0x68 */ dStage_FloorInfo_c* mpFloorInfo;
    /* 0x6C */ dStage_MemoryConfig_c* mpMemoryConfig;
    /* 0x70 */ dStage_MemoryMap_c* mpMemoryMap;
    /* 0x74 */ dStage_Multi_c* mpMulti;
    /* 0x78 */ stage_tresure_class* mpTresure;
    /* 0x7C */ dStage_DMap_c* mpDMap;
    /* 0x80 */ stage_tgsc_class* mpDrTg;
};
static_assert(sizeof(dStage_stageDt_c) == 0x84);

class dStage_roomDt_c : public dStage_dt_c {
public:
    /* 0x04 */ stage_lightvec_info_class* mpLightVecInfo;
    /* 0x08 */ int mLightVecInfoNum;
    /* 0x0C */ stage_map_info_class* mpMapInfo;
    /* 0x10 */ stage_map_info_dummy_class* mpMapInfoBase;
    /* 0x14 */ stage_vrbox_info_class* mpVrbox;
    /* 0x18 */ dStage_FileList_dt_c* mpFileList;
    /* 0x1C */ dStage_Ship_c* mpShip;
    /* 0x20 */ stage_actor_class* mpPlayer;
    /* 0x24 */ dStage_dPnt_c* mpPoint2;
    /* 0x28 */ dStage_dPath_c* mpPath2;
    /* 0x2C */ stage_camera_class* mpCamera;
    /* 0x30 */ stage_arrow_class* mpArrow;
    /* 0x34 */ dStage_SoundInfo_c* mpSound;
    /* 0x38 */ stage_scls_info_dummy_class* mpScls;
    /* 0x3C */ dStage_Lbnk_c* mpLbnk;
    /* 0x40 */ stage_tresure_class* mpTresure;
    /* 0x44 */ stage_tgsc_class* mpDrTg;
    /* 0x48 */ dStage_FloorInfo_c* mpFloor;
    /* 0x4C */ s8 mRoomNo;
    /* 0x4D */ u8 field_0x4D[0x4E - 0x4D];
    /* 0x4E */ u16 mPlayerNum;
    /* 0x50 */ int mVrboxNum;
};
static_assert(sizeof(dStage_roomDt_c) == 0x54);

class dStage_darkStatus_c {
public:
    /* 0x00 */ u8 mEnvAlpha;
    /* 0x01 */ u8 mBokoAlpha[2];
    /* 0x04 */ f32 mBokoScale[2];
    /* 0x0C */ int field_0xc;
    /* 0x10 */ f32 field_0x10[2];
    /* 0x18 */ f32 field_0x18[2];

    u8 getEnvAlpha() const { return mEnvAlpha; }
    u8 getBokoAlpha(int i) const { return mBokoAlpha[i]; }
    f32 getBokoScale(int i) const { return mBokoScale[i]; }
};

class dBgW;
class dStage_roomStatus_c {
public:
    /* 0x000 */ dStage_roomDt_c mRoomDt;
    /* 0x054 */ dKy_tevstr_c mTevStr;
    /* 0x104 */ u8 mFlags;
    /* 0x105 */ bool mDraw;
    /* 0x106 */ s8 mZoneCount;
    /* 0x107 */ s8 mZoneNo;
    /* 0x108 */ s8 mMemBlockID;
    /* 0x10C */ int mProcID;
    /* 0x110 */ dBgW* mpBgW;
};  // Size: 0x114

static_assert(sizeof(dStage_roomStatus_c) == 0x114);

class dStage_roomControl_c {
public:
    u8 field_0x0[4];
};

class dStage_startStage_c {
public:
    const char* getName() const { return mName; }
    s16 getPoint() const { return mPoint; }
    int getRoomNo() const { return mRoomNo; }
    s8 getLayer() const { return mLayer; }

    void setName(const char* name) { strcpy(mName, name); }
    void setPoint(s16 point) { mPoint = point; }
    void setRoomNo(s8 room) { mRoomNo = room; }
    void setLayer(s8 layer) { mLayer = layer; }

    /* 0x0 */ char mName[8];
    /* 0x8 */ s16 mPoint;
    /* 0xA */ s8 mRoomNo;
    /* 0xB */ s8 mLayer;
};
static_assert(sizeof(dStage_startStage_c) == 0xC);

class dStage_nextStage_c : public dStage_startStage_c {
public:
    void setEnabled(s8 is_enabled) { mEnable = is_enabled; }
    void setWipe(u8 wipe_type) { mWipe = wipe_type; }
    void offEnable() { mEnable = 0; }
    s8 isEnable() const { return mEnable; }
    s8 getWipe() const { return mWipe; }

    /* 0xC */ s8 mEnable;
    /* 0xD */ s8 mWipe;
};

// unknown name
struct dStage_objectNameInf {
    char mName[8];
    s16 mProcName;
    s8 mSubtype;
};  // Size: 0xC

#define dStage_roomControl_c__mStayNo (*(s8*)(dStage_roomControl_c__mStayNo_addr))
#define dStage_roomControl_c__m_time_pass (*(BOOL*)(dStage_roomControl_c__m_time_pass_addr))

LIBTWW_DEFINE_FUNC(SetTimePass__20dStage_roomControl_cFi,
                  void, dStage_roomControl_c__setTimePass, (int))

#endif /* D_D_STAGE_H */
