#ifndef D_CC_D_CC_MASS_S_H
#define D_CC_D_CC_MASS_S_H

#include "../../SSystem/SComponent/c_cc_d.h"

typedef void (*dCcMassS_ObjCallback)(fopAc_ac_c*, cXyz*, uint32_t);

class dCcMassS_Obj {
public:
    /* 0x00 */ cCcD_Obj* mpObj;
    /* 0x04 */ uint8_t mPriority;
    /* 0x08 */ dCcMassS_ObjCallback mpCallback;
    /* 0x0C */ cCcD_DivideInfo mDivideInfo;
    /* 0x14 */ void* vtable;
};  // Size = 0x18

static_assert(sizeof(dCcMassS_Obj) == 0x18);

class dCcMassS_Mng {
public:
    /* 0x0000 */ cCcD_DivideArea mDivideArea;
    /* 0x0040 */ int32_t mMassObjCount;
    /* 0x0044 */ dCcMassS_Obj mMassObjs[5];
    /* 0x00BC */ int32_t mMassAreaCount;
    /* 0x00C0 */ dCcMassS_Obj mMassAreas[2];
    /* 0x00F0 */ cCcD_CylAttr mCylAttr;
    /* 0x0128 */ uint8_t mChkFlag;
    /* 0x0129 */ uint8_t mResultCamBit;
    /* 0x012C */ uint32_t field_0x12c;
    /* 0x0130 */ uint32_t mResultCam;
    /* 0x0134 */ Vec mCamTopPos;
    /* 0x0140 */ float mCamTopDist;
    /* 0x0144 */ Vec mCamBottomPos;
    /* 0x0150 */ float mCamBottomDist;
    /* 0x0154 */ cCcD_CpsAttr mCpsAttr;
    /* 0x0194 */ cCcD_DivideInfo mDivideInfo;
    /* 0x019C */ void* vtable;
};

static_assert(sizeof(dCcMassS_Mng) == 0x1A0);

#endif /* D_CC_D_CC_MASS_S_H */
