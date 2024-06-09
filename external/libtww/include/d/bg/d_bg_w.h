#ifndef D_BG_W_H
#define D_BG_W_H

#include "../../SSystem/SComponent/c_bg_w.h"
#include "../../SSystem/SComponent/c_sxyz.h"
#include "../../defines.h"

class dBgS_Acch;
class cM3dGPla;
class dBgS_RoofChk;
class dBgS_SplGrpChk;
class dBgS_SphChk;
class cM3dGTri;
class dBgS_CrrPos;
class cBgS_PolyInfo;
class fopAc_ac_c;
class dBgS_CaptPoly;
class cBgS_GrpPassChk;
class dBgW;
typedef struct _GXColor GXColor;

LIBTWW_DEFINE_FUNC(ChkGrpThrough__4dBgWFiP15cBgS_GrpPassChki,
                  bool, dBgW__ChkGrpThrough, (dBgW*, int, cBgS_GrpPassChk*, int))

class dBgW : public cBgW {
public:
    enum PushPullLabel {
        PP_UNK1_e = 0x01,
        PP_UNK2_e = 0x02,
        PP_UNK4_e = 0x04,
        PP_UNK8_e = 0x08,
    };
    
    typedef void (*dBgW_CrrFunc)(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    typedef void (*dBgW_RideCallBack)(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
    typedef fopAc_ac_c* (*dBgW_PPCallBack)(fopAc_ac_c*, fopAc_ac_c*, s16, dBgW::PushPullLabel);

    void SetCrrFunc(dBgW_CrrFunc func) { m_crr_func = func; }
    void SetRideCallback(dBgW_RideCallBack func) { mpRideCb = func; }
    void SetPushPullCallback(dBgW_PPCallBack func) { mpPushPullCb = func; }

    /* 0xA8 */ dBgW_CrrFunc m_crr_func;
    /* 0xAC */ s16 mOldRotY;
    /* 0xAE */ s16 mRotYDelta;
    /* 0xB0 */ dBgW_RideCallBack mpRideCb;
    /* 0xB4 */ dBgW_PPCallBack mpPushPullCb;
    /* 0xB8 */ u16 mRoomNo;
    /* 0xBA */ u8 mFlag;
    /* 0xBB */ u8 mRoomNo2;
};  // Size: 0xBC

#endif /* D_BG_W_H */
