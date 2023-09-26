#ifndef D_KANKYO_H_
#define D_KANKYO_H_

#include "../../dolphin/gctypes.h"
#include "../../SSystem/SComponent/c_xyz.h"
#include "../../dolphin/gx/gx.h"

struct LIGHT_INFLUENCE {
    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ GXColorS10 mColor;
    /* 0x14 */ f32 mPow;
    /* 0x18 */ f32 mFluctuation;
    /* 0x1C */ int mIndex;
};

struct WIND_INFLUENCE {
    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ cXyz mDirection;
    /* 0x18 */ f32 mRadius;
    /* 0x1C */ f32 mStrength;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ int field_0x24;
    /* 0x28 */ u8 mConstant;
    /* 0x29 */ u8 field_0x29;
};

struct WIND_INF_ENTITY {
    /* 0x00 */ u8 mInUse;
    /* 0x04 */ f32 mMinRadius;
    /* 0x08 */ f32 mSpeed;
    /* 0x0C */ f32 mStrengthMaxVel;
    /* 0x10 */ WIND_INFLUENCE mInfluence;
};  // Size: 0x3C

class stage_palette_info_class;
class stage_pselect_info_class;
class stage_envr_info_class;
class stage_vrbox_info_class;
class dKyd_lightSchejule;
class stage_plight_info_class;

class dKankyo_sun_Packet;
class dKankyo_sunlenz_Packet;
class dKankyo_rain_Packet;
class dKankyo_snow_Packet;
class dKankyo_star_Packet;
class dKankyo_housi_Packet;
class dKankyo_cloud_Packet;
class dKankyo_vrkumo_Packet;
class dKankyo_wave_Packet;
class dKyr__wind_Packet;
class dKankyo_wave__INFLUENCE;

class dKy_tevstr_c {
public:
    u8 mLightObj[0x74];
    cXyz mLightPosWorld;
    GXColorS10 mColorC0;
    GXColor mColorK0;
    GXColor mColorK1;
    GXColorS10 mFogColor;
    float mFogStartZ;
    float mFogEndZ;
    float mColpatBlend;
    u8 mInitTimer;
    u8 mEnvrIdxCurr;
    u8 mEnvrIdxPrev;
    u8 mColpatCurr;
    u8 mColpatPrev;
    u8 mRoomNo;
    u8 mEnvrIdxOverride;
    u8 mLightMode;
    u8 mInitType;
};

class dScnKy_env_light_c {
public:
    /* 0x000 */ void* vtable;
    /* 0x004 */ stage_palette_info_class* mpDmPalet;
    /* 0x008 */ stage_pselect_info_class* mpDmPselect;
    /* 0x00C */ stage_envr_info_class* mpDmEnvr;
    /* 0x010 */ stage_vrbox_info_class* mpDmVrbox;
    /* 0x014 */ dKyd_lightSchejule* mpSchedule;
    /* 0x018 */ LIGHT_INFLUENCE mBaseLightInfluence;
    /* 0x038 */ LIGHT_INFLUENCE mLightInfluence[30];
    /* 0x3F8 */ LIGHT_INFLUENCE* mPointLight[200];
    /* 0x718 */ LIGHT_INFLUENCE* mEfPLight[10];
    /* 0x740 */ u8 field_0x740[0x764 - 0x740];
    /* 0x764 */ u8 mSwordState;
    /* 0x765 */ u8 mSwordFrame;
    /* 0x768 */ int mSwordLightType;
    /* 0x76C */ LIGHT_INFLUENCE mSwordLight;
    /* 0x78C */ stage_plight_info_class* mpPlightInfo;
    /* 0x790 */ WIND_INFLUENCE* mpWindInfluence[30];
    /* 0x808 */ WIND_INF_ENTITY mWindInfluenceEntity[5];
    /* 0x934 */ u8 field_0x934[0x94c - 0x934];
    /* 0x94C */ f32 field_0x94c;
    /* 0x950 */ f32 field_0x950;
    /* 0x954 */ f32 field_0x954;
    /* 0x958 */ f32 mWaveSpeed;
    /* 0x95C */ f32 mWaveSpawnDist;
    /* 0x960 */ f32 mWaveSpawnRadius;
    /* 0x964 */ f32 mWaveScale;
    /* 0x968 */ f32 mWaveScaleRand;
    /* 0x96C */ f32 mWaveCounterSpeedScale;
    /* 0x970 */ f32 mWaveScaleBottom;
    /* 0x974 */ f32 mWaveFlatInter;
    /* 0x978 */ s16 mWaveCount;
    /* 0x97A */ u8 mWaveReset;
    /* 0x97C */ Vec mWindVec;
    /* 0x988 */ Vec* mpWindVecOverride;
    /* 0x98C */ u8 field_0x98c[0x998 - 0x98c];
    /* 0x998 */ f32 mWindPower;
    /* 0x99C */ f32 mWindStrengthOverride;
    /* 0x9A0 */ f32 mCustomWindPower;
    /* 0x9A4 */ s16 mTactWindAngleX;
    /* 0x9A6 */ s16 mTactWindAngleY;
    /* 0x9A8 */ s16 mEvtWindAngleX;
    /* 0x9AA */ s16 mEvtWindAngleY;
    /* 0x9AC */ u8 mTactWindAngleFlags;
    /* 0x9AD */ u8 mEvtWindSet;
    /* 0x9AE */ u8 mTeachWindExist;
    /* 0x9AF */ u8 field_0x9af;
    /* 0x9B0 */ bool mSunInitialized;
    /* 0x9B4 */ dKankyo_sun_Packet* mpSunPacket;
    /* 0x9B8 */ dKankyo_sunlenz_Packet* mpSunLenzPacket;
    /* 0x9BC */ bool mRainInitialized;
    /* 0x9C0 */ int mRainCount;
    /* 0x9C4 */ dKankyo_rain_Packet* mpRainPacket;
    /* 0x9C8 */ bool mSnowInitialized;
    /* 0x9CC */ int mSnowCount;
    /* 0x9D0 */ dKankyo_snow_Packet* mpSnowPacket;
    /* 0x9D4 */ bool mStarInitialized;
    /* 0x9D8 */ int mStarCount;
    /* 0x9DC */ f32 mStarCountTarget;
    /* 0x9E0 */ dKankyo_star_Packet* mpStarPacket;
    /* 0x9E4 */ u8 field_0x9e4[0x9f0 - 0x9e4];
    /* 0x9F0 */ bool mHousiInitialized;
    /* 0x9F4 */ int mHousiCount;
    /* 0x9F8 */ dKankyo_housi_Packet* mpHousiPacket;
    /* 0x9FC */ u8 mCloudInitialized;
    /* 0x9FD */ u8 mMoyaMode;
    /* 0xA00 */ int mMoyaCount;
    /* 0xA04 */ dKankyo_cloud_Packet* mpCloudPacket;
    /* 0xA08 */ u8 mVrkumoStatus;
    /* 0xA0C */ int mVrkumoCount;
    /* 0xA10 */ f32 mVrkumoStrength;
    /* 0xA14 */ dKankyo_vrkumo_Packet* mpVrkumoPacket;
    /* 0xA18 */ u8 mWaveInitialized;
    /* 0xA19 */ u8 field_0xa19[0xa20 - 0xa19];
    /* 0xA20 */ dKankyo_wave_Packet* mpWavePacket;
    /* 0xA24 */ u8 mbWindlineInitialized;
    /* 0xA28 */ int mWindlineCount;
    /* 0xA2C */ dKyr__wind_Packet* mpWind;
    /* 0xA30 */ u8 mbThunderActive;
    /* 0xA31 */ u8 mThunderStateTimer;
    /* 0xA34 */ int mThunderMode;
    /* 0xA38 */ f32 mThunderFlashTimer;
    /* 0xA3C */ u8 field_0xa3c[0xa48 - 0xa3c];
    /* 0xA48 */ LIGHT_INFLUENCE mThunderLightInfluence;
    /* 0xA68 */ dKankyo_wave__INFLUENCE* mpWaveInfl;
    /* 0xA6C */ u8 field_0xa6c[0xa90 - 0xa6c];
    /* 0xA90 */ cXyz mLightDir;
    /* 0xA9C */ cXyz mSunPos2;
    /* 0xAA8 */ cXyz mPLightNearPos;
    /* 0xAB4 */ cXyz mSunPos;
    /* 0xAC0 */ cXyz mMoonPos;
    /* 0xACC */ GXFogAdjTable mXFogTbl;
    /* 0xAE0 */ GXColorS10 mVrSkyColor;
    /* 0xAE8 */ GXColorS10 mVrUsoUmiColor;
    /* 0xAF0 */ GXColorS10 mVrkumoColor;
    /* 0xAF8 */ GXColorS10 mVrkumoCenterColor;
    /* 0xB00 */ GXColorS10 mVrKasumiMaeColor;
    /* 0xB08 */ GXColorS10 mC0;
    /* 0xB10 */ GXColorS10 mK0;
    /* 0xB18 */ GXColorS10 mActorC0;
    /* 0xB20 */ GXColorS10 mActorK0;
    /* 0xB28 */ GXColorS10 mBG0_C0;
    /* 0xB30 */ GXColorS10 mBG0_K0;
    /* 0xB38 */ GXColorS10 mBG1_C0;
    /* 0xB40 */ GXColorS10 mBG1_K0;
    /* 0xB48 */ GXColorS10 mBG2_C0;
    /* 0xB50 */ GXColorS10 mBG2_K0;
    /* 0xB58 */ GXColorS10 mBG3_C0;
    /* 0xB60 */ GXColorS10 mBG3_K0;
    /* 0xB68 */ GXColorS10 mFogColor;
    /* 0xB70 */ GXColorS10 mActorAddColAmb;
    /* 0xB78 */ GXColorS10 mActorAddColDif;
    /* 0xB80 */ GXColorS10 mBgAddColAmb;
    /* 0xB88 */ GXColorS10 mBgAddColDif;
    /* 0xB90 */ GXColorS10 mBg1AddColAmb;
    /* 0xB98 */ GXColorS10 mBg1AddColDif;
    /* 0xBA0 */ GXColorS10 mBg2AddColAmb;
    /* 0xBA8 */ GXColorS10 mBg2AddColDif;
    /* 0xBB0 */ GXColorS10 mBg3AddColAmb;
    /* 0xBB8 */ GXColorS10 mBg3AddColDif;
    /* 0xBC0 */ GXColorS10 mAddColFog;
    /* 0xBC8 */ GXColorS10 mVrboxAddColSky0;
    /* 0xBD0 */ GXColorS10 mVrboxAddColKasumi;
    /* 0xBD8 */ f32 mDiceWeatherChangeTime;
    /* 0xBDC */ f32 mDiceWeatherTime;
    /* 0xBE0 */ f32 mColPatBlend;
    /* 0xBE4 */ f32 mColPatBlendGather;
    /* 0xBE8 */ f32 mFogNear;
    /* 0xBEC */ f32 mFogFar;
    /* 0xBF0 */ f32 mFogStartZ;
    /* 0xBF4 */ f32 mFogEndZ;
    /* 0xBF8 */ f32 mFogRatio;
    /* 0xBFC */ f32 mColAllcolRatio;
    /* 0xC00 */ f32 mColActColRatio;
    /* 0xC04 */ f32 mColBgColRatio;
    /* 0xC08 */ f32 mColFogColRatio;
    /* 0xC0C */ f32 mColVrboxSoraColRatio;
    /* 0xC10 */ f32 mColVrboxKumocolRatio;
    /* 0xC14 */ f32 mGatherAllcolRatio;
    /* 0xC18 */ f32 mGatherActcolRatio;
    /* 0xC1C */ f32 mGatherBgcolRatio;
    /* 0xC20 */ f32 mGatherFogcolRatio;
    /* 0xC24 */ f32 mGatherVrboxSoracolRatio;
    /* 0xC28 */ f32 mGatherVrboxKumocolRatio;
    /* 0xC2C */ f32 field_0xc2c;
    /* 0xC30 */ f32 field_0xc30;
    /* 0xC34 */ f32 field_0xc34;
    /* 0xC38 */ f32 mCurTime;
    /* 0xC3C */ f32 mNextTime;
    /* 0xC40 */ f32 mTimeSpeed;
    /* 0xC44 */ u8 field_0xc44[0xc50 - 0xc44];
    /* 0xC50 */ u32 mMoyaSE;
    /* 0xC64 */ u8 field_0xc54[0xc60 - 0xc54];
    /* 0xC60 */ int mDiceWeatherCounter;
    /* 0xC64 */ int mRainCountOrig;
    /* 0xC68 */ int field_0x12a0;
    /* 0xC6C */ int mPlayerPLightIdx;
    /* 0xC70 */ int mPlayerEfLightIdx;
    /* 0xC74 */ u8 field_0xc74[4];
    /* 0xC78 */ int field_0xc78;
    /* 0xC7C */ int mSchbitTimer;
    /* 0xC80 */ u16 mFogAdjCenter;
    /* 0xC82 */ u16 mDate;
    /* 0xC84 */ u8 mColPatPrev;
    /* 0xC85 */ u8 mColPatCurr;
    /* 0xC86 */ u8 mColpatPrevGather;
    /* 0xC87 */ u8 mColpatCurrGather;
    /* 0xC88 */ u8 mEnvrIdxPrev;
    /* 0xC89 */ u8 mEnvrIdxCurr;
    /* 0xC8A */ u8 mColpatWeather;
    /* 0xC8B */ u8 mDiceWeatherMode;
    /* 0xC8C */ u8 mDiceWeatherState;
    /* 0xC8D */ u8 mDiceWeatherCurrPattern;
    /* 0xC8E */ u8 field_0xc8e;
    /* 0xC8F */ u8 mColPatMode;
    /* 0xC90 */ u8 mColPatModeGather;
    /* 0xC91 */ u8 mFogAdjEnable;
    /* 0xC92 */ u8 mFogAdjTableType;
    /* 0xC93 */ u8 mItemGetCol_chg;
    /* 0xC94 */ u8 mInitAnmTimer;
    /* 0xC95 */ u8 mSchBit;
    /* 0xC96 */ bool mVrboxInvisible;
    /* 0xC97 */ u8 mContrastFlag;
    /* 0xC98 */ u8 field_0xc98;
    /* 0xC99 */ u8 mbDayNightTactStop;
};  // Size: 0xC9C

static_assert(sizeof(dScnKy_env_light_c) == 0xC9C);

#define g_env_light (*(dScnKy_env_light_c*)g_env_light_addr)

typedef int (*dKy_getdaytime_minute)();
#define dKy_getdaytime_minute ((dKy_getdaytime_minute) dKy_getdaytime_minute_addr)

typedef int (*dKy_getdaytime_hour)();
#define dKy_getdaytime_hour ((dKy_getdaytime_hour) dKy_getdaytime_hour_addr)

typedef int (*dKy_moon_type_chk)();
#define dKy_moon_type_chk ((dKy_moon_type_chk) dKy_moon_type_chk_addr)

inline s16 dkankyo_getWindDir() {
    return g_env_light.mTactWindAngleY;
}

inline void dkankyo_setWindDir(s16 dir) {
    g_env_light.mTactWindAngleY = dir;
}

#endif