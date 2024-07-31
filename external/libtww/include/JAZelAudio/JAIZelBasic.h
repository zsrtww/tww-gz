#ifndef JAZELAUDIO_JAIZELBASIC_H
#define JAZELAUDIO_JAIZELBASIC_H

#include "../defines.h"
#include "../JSystem/JAudio/JAIBasic.h"

class JAISound;
class JKRSolidHeap;
class JAIZelBasic;

LIBTWW_DEFINE_FUNC(bgmAllMute__11JAIZelBasicFUl,
                  void, JAIZelBasic__bgmAllMute, (JAIZelBasic*, u32))

extern "C" JAIZelBasic* zel_basic__11JAIZelBasic;
#define zel_basic zel_basic__11JAIZelBasic

class JAIZelBasic : public JAIBasic {
public:
    void setHour(s32 i_hour) { mHour = i_hour; }
    void setMinute(s32 i_minute) { mMinute = i_minute; }
    void setWeekday(s32 i_weekday) { mWeekday = i_weekday; }

    f32 calcMainBgmVol() { return field_0x0080 * field_0x0084 * field_0x0088 * field_0x008c * field_0x0090 * field_0x0094 * field_0x0098 * field_0x009c * field_0x00ac; }
    f32 calcSubBgmVol() { return field_0x00a0 * field_0x00a4 * field_0x00a8; }

    void bgmAllMute(u32 param_0) { JAIZelBasic__bgmAllMute(this, param_0); }

    void bgmAllUnmute(u32 param_0) {
        field_0x0080 = 1.0f;

        if (mpMainBgmSound != NULL) {
            mpMainBgmSound->setVolume(calcMainBgmVol(), param_0, 0);
        }
    }

    void subBgmMute(u32 param_0) {
        if (mpSubBgmSound != NULL) {
            mpSubBgmSound->setVolume(0.0f, param_0, 0);
        }
    }

    void subBgmUnmute(u32 param_0) {
        if (mpSubBgmSound != NULL) {
            mpSubBgmSound->setVolume(calcSubBgmVol(), param_0, 0);
        }
    }

    static JAIZelBasic* getInterface() { return zel_basic; }

    struct scene_info_s {
        u16 bgmNum;
        u8 field_0x2;
        u8 field_0x3;
    };
    struct isle_area_s {
        f32 field_0x0;
        f32 field_0x4;
        f32 field_0x8;
        f32 field_0xC;
    };

    /* 0x0020 */ u8 field_0x0020;
    /* 0x0021 */ u8 field_0x0021;
    /* 0x0022 */ u8 field_0x0022[0x0024 - 0x0022];
    /* 0x0024 */ u8* field_0x0024;
#ifndef NTSCJ
    /* 0x0028 */ int field_0x0028;
#endif
    /* Offsets below are for USA/PAL */
    /* 0x002C */ u8 mHour;
    /* 0x002D */ u8 mMinute;
    /* 0x002E */ u8 mWeekday;
    /* 0x002F */ u8 field_0x002f;
    /* 0x0030 */ u16 field_0x0030;
    /* 0x0032 */ u8 field_0x0032;
    /* 0x0033 */ u8 field_0x0033;
    /* 0x0034 */ int field_0x0034;
    /* 0x0038 */ int field_0x0038;
    /* 0x003C */ f32 field_0x003c;
    /* 0x0040 */ u8 field_0x0040;
    /* 0x0041 */ u8 field_0x0041;
    /* 0x0042 */ u8 field_0x0042;
    /* 0x0043 */ u8 field_0x0043;
    /* 0x0044 */ u8 field_0x0044;
    /* 0x0045 */ u8 field_0x0045;
    /* 0x0046 */ u8 field_0x0046;
    /* 0x0047 */ u8 field_0x0047;
    /* 0x0048 */ Vec field_0x0048;
    /* 0x0054 */ Vec field_0x0054;
    /* 0x0060 */ u8 mbLandingDemoStarted;
    /* 0x0061 */ u8 field_0x0061;
#ifndef NTSCJ
    /* 0x0062 */ u8 field_0x0062;
#endif
    /* 0x0063 */ u8 field_0x0063;
    /* 0x0064 */ u8 field_0x0064;
    /* 0x0065 */ u8 field_0x0065;
    /* 0x0066 */ u8 field_0x0066;
    /* 0x0067 */ u8 field_0x0067[0x0068 - 0x0067];
    /* 0x0068 */ JAISound* mpMainBgmSound;
    /* 0x006C */ JAISound* mpSubBgmSound;
    /* 0x0070 */ JAISound* mpStreamBgmSound;
    /* 0x0074 */ u32 mSubBgmNum;
    /* 0x0078 */ u32 mMainBgmNum;
    /* 0x007C */ u32 mStreamBgmNum;
    /* 0x0080 */ f32 field_0x0080;
    /* 0x0084 */ f32 field_0x0084;
    /* 0x0088 */ f32 field_0x0088;
    /* 0x008C */ f32 field_0x008c;
    /* 0x0090 */ f32 field_0x0090;
    /* 0x0094 */ f32 field_0x0094;
    /* 0x0098 */ f32 field_0x0098;
    /* 0x009C */ f32 field_0x009c;
    /* 0x00A0 */ f32 field_0x00a0;
    /* 0x00A4 */ f32 field_0x00a4;
    /* 0x00A8 */ f32 field_0x00a8;
    /* 0x00AC */ f32 field_0x00ac;
    /* 0x00B0 */ int field_0x00b0;
    /* 0x00B4 */ u8 field_0x00b4;
    /* 0x00B5 */ u8 mSomeSpecialBGMFlag;
    /* 0x00B6 */ u8 mLastMinibossSubBGMType;
    /* 0x00B7 */ u8 field_0x00b7;
    /* 0x00B8 */ u8 field_0x00b8;
    /* 0x00B9 */ u8 field_0x00b9;
    /* 0x00BA */ u8 field_0x00ba;
    /* 0x00BB */ u8 field_0x00bb;
    /* 0x00BC */ u8 field_0x00bc;
    /* 0x00BD */ u8 field_0x00bd;
    /* 0x00BE */ u8 field_0x00be;
#ifndef NTSCJ
    /* 0x00BF */ u8 field_0x00bf;
#endif
    /* 0x00C0 */ u8 field_0x00c0;
    /* 0x00C1 */ s8 field_0x00c1;
    /* 0x00C4 */ int field_0x00c4;
    /* 0x00C8 */ u8 field_0x00c8;
    /* 0x00C9 */ u8 field_0x00c9;
    /* 0x00CA */ u8 field_0x00ca;
    /* 0x00CB */ s8 field_0x00cb;
    /* 0x00CC */ u8 field_0x00cc;
    /* 0x00CD */ u8 field_0x00cd;
    /* 0x00CE */ u8 field_0x00ce;
    /* 0x00CF */ u8 field_0x00CF[0x00D0 - 0x00CF];
    /* 0x00D0 */ int field_0x00d0;
    /* 0x00D4 */ JAISound* field_0x00d4[24];
    /* 0x0134 */ u32 field_0x0134[24];
    /* 0x0194 */ u32 field_0x0194[24];
    /* 0x01F4 */ int field_0x01f4;
    /* 0x01F8 */ u8 field_0x01f8;
    /* 0x01F9 */ u8 field_0x01f9;
    /* 0x01FA */ u8 field_0x01fa;
    /* 0x01FB */ u8 field_0x01fb;
    /* 0x01FC */ u8 field_0x01fc;
    /* 0x01FD */ u8 field_0x01fd;
    /* 0x01FE */ u8 field_0x01fe;
    /* 0x01FF */ u8 field_0x01ff;
    /* 0x0200 */ u8 field_0x0200;
    /* 0x0201 */ u8 field_0x0201;
    /* 0x0202 */ u8 field_0x0202[0x0204 - 0x0202];
    /* 0x0204 */ u8 field_0x0204;
    /* 0x0205 */ u8 field_0x0205;
    /* 0x0206 */ u8 field_0x0206;
    /* 0x0207 */ u8 field_0x0207;
    /* 0x0208 */ u8 field_0x0208;
    /* 0x020C */ int field_0x020c;
    /* 0x0210 */ int field_0x0210;
    /* 0x0214 */ int field_0x0214;
    /* 0x0218 */ u32 field_0x0218;
    /* 0x021C */ u8 mCameraSeaFloorGroupInfo;
    /* 0x021D */ u8 mLinkSeaFloorGroupInfo;
    /* 0x021E */ u8 field_0x021e;
    /* 0x021F */ u8 field_0x021F[0x0220 - 0x021F];
    /* 0x0220 */ s32 field_0x0220;
    /* 0x0224 */ int field_0x0224;
    /* 0x0228 */ u32 mNextSceneBgmId;
    /* 0x022C */ u8 field_0x022c;
    /* 0x022D */ u8 field_0x022d;
    /* 0x022E */ u8 field_0x022e;
    /* 0x022F */ u8 field_0x022f;
    /* 0x0230 */ u8 field_0x0230;
    /* 0x0231 */ u8 field_0x0231;
    /* 0x0232 */ u8 mFirstDynamicSceneWaveIndex;
    /* 0x0233 */ u8 field_0x0233;
    /* 0x0234 */ u8 mSetNum;
    /* 0x0235 */ u8 mSecondDynamicSceneWaveIndex;
    /* 0x0236 */ u8 field_0x0236;
    /* 0x0237 */ u8 field_0x0237;
    /* 0x0238 */ u8 mIslandRoomNo;
    /* 0x0239 */ u8 field_0x0239;
    /* 0x023A */ u8 field_0x023a;
    /* 0x023B */ u8 field_0x023B[0x1B80 - 0x023B];
    /* 0x1B80 */ int field_0x1b80;
    /* 0x1B84 */ u8 field_0x1b84[0x1DD0 - 0x1B84];
    /* 0x1DD0 */ int field_0x1dd0;
    /* 0x1DD4 */ u8 field_0x1dd4;
    /* 0x1DD5 */ u8 field_0x1DD5[0x1E98 - 0x1DD5];
    /* 0x1E98 */ int field_0x1e98;
    /* 0x1E9C */ u8 field_0x1e9c[0x1EC0 - 0x1E9C];
    /* 0x1EC0 */ int field_0x1ec0;
    /* 0x1EC4 */ int field_0x1ec4;
    /* 0x1EC8 */ int field_0x1ec8;
    /* 0x1ECC */ int field_0x1ecc;
    /* 0x1ED0 */ int field_0x1ed0;
    /* 0x1ED4 */ u8 field_0x1ED4[0x1F34 - 0x1ED4];
    /* 0x1F34 */ int field_0x1f34;
    /* 0x1F38 */ JAISound* field_0x1f38;
    /* 0x1F3C */ u8 field_0x1f3c;
    /* 0x1F3D */ u8 mIsSailing;
    /* 0x1F3E */ u8 field_0x1F3E[0x1F40 - 0x1F3E];
    /* 0x1F40 */ f32 field_0x1f40;
    /* 0x1F44 */ int field_0x1f44;
    /* 0x1F48 */ int field_0x1f48;
    /* 0x1F4C */ struct {
        int field_0x00;
        int field_0x04;
     } field_0x1f4c[0x1E];
    /* 0x203C */ u8 field_0x203c;
    /* 0x203D */ u8 field_0x203d;
    /* 0x2040 */ int field_0x2040[4];
    /* 0x2050 */ int field_0x2050[4];
    /* 0x2060 */ JAISound* field_0x2060;
    /* 0x2064 */ int field_0x2064;
    /* 0x2068 */ u8 field_0x2068[0x20F4 - 0x2068];
};

#endif /* JAZELAUDIO_JAIZELBASIC_H */
