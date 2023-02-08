#ifndef D_D_STAGE_H
#define D_D_STAGE_H

#include "../addrs.h"
#include "save/d_save.h"
#include "../f_op/f_op_actor.h"

struct stage_vrboxcol_info_class {};

struct stage_vrbox_info_class {};

struct stage_tresure_class {};

struct stage_tgsc_data_class {};

struct stage_tgsc_class {};

struct stage_stag_info_class {};

struct stage_scls_info_dummy_class {};

struct stage_pure_lightvec_info_class {};

struct stage_pselect_info_class {};

struct stage_plight_info_class {};

struct stage_palette_info_class {};

struct stage_map_info_dummy_class {};

struct stage_map_info_class {};

struct stage_envr_info_class {};

struct stage_camera_class {};

struct stage_camera2_data_class {};

struct stage_arrow_class {};

struct stage_actor_data_class {};

struct stage_actor_class {};

struct roomRead_class {};

struct dStage_FileList2_dt_c {};

struct dStage_MemoryMap_c {};

struct dStage_dPath_c {};

struct dStage_Multi_c {};

struct dStage_SoundInfo_c {};

struct dStage_FileList_dt_c {};

struct dStage_dPnt_c {};

struct dStage_FloorInfo_c {};

struct dStage_Lbnk_c {};

struct dStage_Elst_c {};

struct dStage_MemoryConfig_c {};

struct dStage_DMap_c {};

struct dStage_MapEventInfo_c {};

class dStage_dt_c {
public:
    /* 0x00 */ void* vtable;
};

class dStage_EventInfo_c;

class dStage_stageDt_c : public dStage_dt_c {
public:
    /* 0x04 */ stage_camera_class* mCamera;
    /* 0x08 */ stage_arrow_class* mArrow;
    /* 0x0C */ stage_actor_class* mPlayer;
    /* 0x10 */ roomRead_class* mRoom;
    /* 0x14 */ stage_map_info_class* mMapInfo;
    /* 0x18 */ stage_map_info_dummy_class* mMapInfoBase;
    /* 0x1C */ stage_palette_info_class* mPaletteInfo;
    /* 0x20 */ stage_pselect_info_class* mPselectInfo;
    /* 0x24 */ stage_envr_info_class* mEnvrInfo;
    /* 0x28 */ stage_vrbox_info_class* mVrboxInfo;
    /* 0x2C */ stage_plight_info_class* mPlightInfo;
    /* 0x30 */ u8 field_0x30[0x40 - 0x30];
    /* 0x40 */ u32 mPaletteNumInfo;
    /* 0x44 */ u32 mPselectNumInfo;
    /* 0x48 */ stage_stag_info_class* mStagInfo;
    /* 0x4C */ stage_scls_info_dummy_class* mSclsInfo;
    /* 0x50 */ dStage_dPnt_c* mPntInfo;
    /* 0x54 */ dStage_dPath_c* mPathInfo;
    /* 0x58 */ dStage_dPnt_c* mPnt2Inf;
    /* 0x5C */ dStage_dPath_c* mPath2Info;
    /* 0x60 */ u8 field_0x60[4];
    /* 0x64 */ dStage_EventInfo_c* mpEventInfo;
    /* 0x68 */ u8 field_0x68[0x74 - 0x68];
    /* 0x74 */ dStage_Multi_c* mMulti;
    /* 0x78 */ u8 field_0x78[0x84 - 0x78];
};
static_assert(sizeof(dStage_stageDt_c) == 0x84);

class dStage_roomControl_c {
public:
    u8 field_0x0[4];
};

class dStage_startStage_c {
public:
    inline char* getName() { return mStage; }
    s8 getLayer() { return mLayer; }
    void setLayer(s8 layer) { mLayer = layer; }
    void setPoint(s16 point) { mPoint = point; }
    void setRoomNo(s8 room) { mRoomNo = room; }

    /* 0x0 */ char mStage[8];
    /* 0x8 */ s16 mPoint;
    /* 0xA */ s8 mRoomNo;
    /* 0xB */ s8 mLayer;
};
static_assert(sizeof(dStage_startStage_c) == 0xC);

class dStage_nextStage_c : public dStage_startStage_c {
public:
    s8 enabled;
    u8 wipe;
    u8 wipe_speed;
};

// unknown name
struct dStage_objectNameInf {
    char mName[8];
    s16 mProcName;
    s8 mSubtype;
};  // Size: 0xC

#define dStage_roomControl_c__mStayNo (*(s8*)(dStage_roomControl_c__mStayNo_addr))

#endif /* D_D_STAGE_H */
