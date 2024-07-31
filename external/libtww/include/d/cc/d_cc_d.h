#ifndef D_CC_D_CC_D_H
#define D_CC_D_CC_D_H

#include "../../SSystem/SComponent/c_cc_d.h"

enum dCcD_hitSe {};

enum dCcG_At_Spl {};

enum dCcG_Tg_Spl {};

struct dCcD_SrcTri {};

struct dCcD_SrcSph {};

struct dCcD_SrcGObjTg {};

struct dCcD_SrcGObjInf {};

struct dCcD_SrcGObjAt {};

struct dCcD_SrcGAtTgCoCommonBase {};

struct dCcD_SrcCyl {};

struct dCcD_SrcCps {};

class dCcD_GStts : public cCcD_GStts {
public:
    void ClrAt() { mAtSpl = 0; }
    void ClrTg() { mTgSpl = 0; }
    void SetAtApid(unsigned int id) { mAtApid = id; }
    void SetTgApid(unsigned int id) { mTgApid = id; }
    u8 GetRoomId() { return mRoomId; }
    void SetRoomId(int id) { mRoomId = id; }
    unsigned int GetAtOldApid() { return mAtOldApid; }
    unsigned int GetTgOldApid() { return mTgOldApid; }
    bool ChkNoActor() { return field_0x1C & 1; }
    bool ChkNoneActorPerfTblId() { return field_0x08 == 0xFFFF; }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mAtSpl; }
    void SetAtSpl(dCcG_At_Spl spl) { mAtSpl = spl; }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mTgSpl; }
    void SetTgSpl(dCcG_Tg_Spl spl) { mTgSpl = spl; }
    void OnNoActor() { field_0x1C |= 1; }

    /* 0x04 */ u8 mAtSpl;
    /* 0x05 */ u8 mTgSpl;
    /* 0x06 */ u8 mRoomId;
    /* 0x08 */ u16 field_0x08;
    /* 0x0C */ int mAtApid;
    /* 0x10 */ int mAtOldApid;
    /* 0x14 */ int mTgApid;
    /* 0x18 */ int mTgOldApid;
    /* 0x1C */ int field_0x1C;
};  // Size = 0x20

class dCcD_Stts : public cCcD_Stts, public dCcD_GStts {
public:
};  // Size = 0x3C

static_assert(sizeof(dCcD_Stts) == 0x3C);

class dCcD_GObjInf;
typedef void (*dCcD_HitCallback)(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);

class dCcD_GAtTgCoCommonBase {
public:
    /* 0x00 */ u32 mSPrm;
    /* 0x04 */ u32 mRPrm;
    /* 0x08 */ dCcD_HitCallback mHitCallback;
    /* 0x0C */ u32 mApid;
    /* 0x10 */ fopAc_ac_c* mAc;
    /* 0x14 */ s8 mEffCounter;
    /* 0x15 */ u8 field_0x15[3];
    /* 0x18 */ void* vtable;

    void ClrEffCounter() { mEffCounter = 0; }
    u32 GetSPrm() const { return mSPrm; }
    u32 GetRPrm() const { return mRPrm; }
    u32 MskSPrm(u32 mask) const { return mSPrm & mask; }
    u32 MskRPrm(u32 mask) const { return mRPrm & mask; }
    bool ChkSPrm(u32 mask) const { return MskSPrm(mask); }
    void OnSPrm(u32 flag) { mSPrm |= flag; }
    void OnRPrm(u32 flag) { mRPrm |= flag; }
    void OffSPrm(u32 flag) { mSPrm &= ~flag; }
    void OffRPrm(u32 flag) { mRPrm &= ~flag; }
    bool ChkRPrm(u32 flag) const { return MskRPrm(flag); }
    void SetHitCallback(dCcD_HitCallback callback) { mHitCallback = callback; }
    dCcD_HitCallback GetHitCallback() { return mHitCallback; }
};  // Size = 0x1C

class dCcD_GObjAt : public dCcD_GAtTgCoCommonBase {
public:
    void SetVec(cXyz& vec) { mVec = vec; }
    cXyz& GetVec() { return mVec; }
    cXyz* GetVecP() { return &mVec; }
    void SetHitMark(u8 mark) { mHitMark = mark; }
    void SetSe(u8 se) { mSe = se; }
    void SetMtrl(u8 mtrl) { mMtrl = mtrl; }
    void SetAtSpl(dCcG_At_Spl spl) { mSpl = spl; }
    u8 GetSe() { return mSe; }
    u8 GetSpl() { return mSpl; }
    u8 GetMtrl() { return mMtrl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }
    cXyz* GetHitPosP() { return &mHitPos; }

    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl;
    /* 0x1E */ u8 mHitMark;
    /* 0x1F */ u8 mSpl;
    /* 0x20 */ cXyz mHitPos;
    /* 0x2C */ cXyz mVec;
    /* 0x38 */ cXyz mRVec;
};  // Size = 0x44

class dCcD_GObjTg : public dCcD_GAtTgCoCommonBase {
public:
    void SetSe(u8 se) { mSe = se; }
    void SetVec(cXyz& vec) { mVec = vec; }
    cXyz& GetVec() { return mVec; }
    void SetShieldFrontRangeYAngle(s16* angle) { mShieldFrontRangeYAngle = angle; }
    void SetMtrl(u8 mtrl) { mMtrl = mtrl; }
    u8 GetMtrl() { return mMtrl; }
    void SetHitMark(CcG_Tg_HitMark mark) { mHitMark = mark; }
    s16* GetShieldFrontRangeYAngle() { return mShieldFrontRangeYAngle; }
    u8 GetSpl() { return mSpl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    cXyz* GetVecP() { return &mVec; }
    cXyz* GetRVecP() { return &mRVec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }
    cXyz* GetHitPosP() { return &mHitPos; }

    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl;
    /* 0x1E */ u8 mHitMark;
    /* 0x1F */ u8 mSpl;
    /* 0x20 */ cXyz mVec;
    /* 0x2C */ cXyz mRVec;
    /* 0x38 */ cXyz mHitPos;
    /* 0x44 */ s16* mShieldFrontRangeYAngle;
};  // Size = 0x48

class dCcD_GObjCo : public dCcD_GAtTgCoCommonBase {
public:
};  // Size = 0x1C

class dCcD_GObjInf : public cCcD_GObjInf {
public:
    void SetAtVec(cXyz& vec) { mGObjAt.SetVec(vec); }
    void SetTgVec(cXyz& vec) { mGObjTg.SetVec(vec); }
    bool ChkAtNoMass() const { return mGObjAt.ChkSPrm(8); }
    void OnAtNoHitMark() { mGObjAt.OnSPrm(2); }
    void OffAtNoHitMark() { mGObjAt.OffSPrm(2); }
    void OnTgNoHitMark() { mGObjTg.OnSPrm(4); }
    void OffTgNoHitMark() { mGObjTg.OffSPrm(4); }
    void OnAtNoConHit() { mGObjAt.OnSPrm(1); }
    void OffAtNoConHit() { mGObjAt.OffSPrm(1); }
    void OnTgNoConHit() { mGObjTg.OnSPrm(2); }
    void SetAtHitMark(u8 mark) { mGObjAt.SetHitMark(mark); }
    void SetAtSe(u8 se) { mGObjAt.SetSe(se); }
    void SetTgSe(u8 se) { mGObjTg.SetSe(se); }
    void SetAtMtrl(u8 mtrl) { mGObjAt.SetMtrl(mtrl); }
    void SetTgMtrl(u8 mtrl) { mGObjTg.SetMtrl(mtrl); }
    cXyz* GetAtVecP() { return mGObjAt.GetVecP(); }
    cXyz* GetTgVecP() { return mGObjTg.GetVecP(); }
    cXyz* GetTgRVecP() { return mGObjTg.GetRVecP(); }
    void SetAtSpl(dCcG_At_Spl spl) { mGObjAt.SetAtSpl(spl); }
    void SetAtHitCallback(dCcD_HitCallback callback) { mGObjAt.SetHitCallback(callback); }
    void SetTgHitCallback(dCcD_HitCallback callback) { mGObjTg.SetHitCallback(callback); }
    void SetCoHitCallback(dCcD_HitCallback callback) { mGObjCo.SetHitCallback(callback); }
    u8 GetAtSe() { return mGObjAt.GetSe(); }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mGObjAt.GetSpl(); }
    u8 GetAtMtrl() { return mGObjAt.GetMtrl(); }
    u8 GetTgMtrl() { return mGObjTg.GetMtrl(); }
    void SetTgShieldFrontRangeYAngle(s16* angle) { mGObjTg.SetShieldFrontRangeYAngle(angle); }
    void SetTgHitMark(CcG_Tg_HitMark mark) { mGObjTg.SetHitMark(mark); }
    void OnTgShield() { mGObjTg.OnSPrm(0x1); }
    void OffTgShield() { mGObjTg.OffSPrm(0x1); }
    void OnTgShieldFrontRange() { mGObjTg.OnSPrm(0x8); }
    void OffTgShieldFrontRange() { mGObjTg.OffSPrm(0x8); }
    bool ChkTgIronBallRebound() { return mGObjTg.ChkSPrm(0x100); }
    s16* GetTgShieldFrontRangeYAngle() { return mGObjTg.GetShieldFrontRangeYAngle(); }
    bool ChkTgShield() { return mGObjTg.ChkSPrm(1); }
    bool ChkTgSpShield() { return mGObjTg.ChkSPrm(0x40); }
    bool ChkTgSmallShield() { return mGObjTg.ChkSPrm(0x10); }
    bool ChkTgShieldFrontRange() { return mGObjTg.ChkSPrm(8); }
    bool ChkAtNoConHit() { return mGObjAt.ChkSPrm(1); }
    bool ChkAtStopNoConHit() { return mGObjAt.ChkSPrm(0x4); }
    bool ChkTgNoConHit() { return mGObjTg.ChkSPrm(2); }
    bool ChkTgStopNoConHit() { return mGObjTg.ChkSPrm(0x2000); }
    bool ChkCoAtLasso() { return mGObjCo.ChkSPrm(1); }
    bool ChkCoTgLasso() { return mGObjCo.ChkSPrm(2); }
    dCcD_HitCallback GetCoHitCallback() { return mGObjCo.GetHitCallback(); }
    dCcD_HitCallback GetAtHitCallback() { return mGObjAt.GetHitCallback(); }
    dCcD_HitCallback GetTgHitCallback() { return mGObjTg.GetHitCallback(); }
    void OnCoHitNoActor() { mGObjCo.OnRPrm(1); }
    void OffCoHitNoActor() { mGObjCo.OffRPrm(1); }
    void OnAtHitNoActor() { mGObjAt.OnRPrm(2); }
    void OffAtHitNoActor() { mGObjAt.OffRPrm(2); }
    void OnTgHitNoActor() { mGObjTg.OnRPrm(1); }
    void OffTgHitNoActor() { mGObjTg.OffRPrm(1); }
    bool ChkCoHitNoActor() const { return mGObjCo.ChkRPrm(1); }
    bool ChkAtHitNoActor() const { return mGObjAt.ChkRPrm(2); }
    bool ChkTgHitNoActor() const { return mGObjTg.ChkRPrm(1); }
    bool ChkAtNoHitMark() { return mGObjAt.ChkSPrm(2); }
    bool ChkTgNoHitMark() { return mGObjTg.ChkSPrm(4); }
    bool ChkTgHookShotNoHitMark() { return mGObjTg.ChkSPrm(0x400); }
    bool ChkTgArrowNoHitMark() { return mGObjTg.ChkSPrm(0x1000); }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mGObjTg.GetSpl(); }
    int GetTgHitMark() { return mGObjTg.GetHitMark(); }
    int GetAtHitMark() { return mGObjAt.GetHitMark(); }
    void ClrAtEffCounter() { mGObjAt.ClrEffCounter(); }
    void ClrTgEffCounter() { mGObjTg.ClrEffCounter(); }
    void ClrCoEffCounter() { mGObjCo.ClrEffCounter(); }
    void OnTgShieldHit() { mGObjTg.OnRPrm(2); }
    void OffTgShieldHit() { mGObjTg.OffRPrm(2); }
    bool ChkTgShieldHit() { return mGObjTg.ChkRPrm(2); }
    void OnAtShieldHit() { mGObjAt.OnRPrm(1); }
    void OffAtShieldHit() { mGObjAt.OffRPrm(1); }
    bool ChkAtShieldHit() { return mGObjAt.ChkRPrm(1); }
    void SetTgRVec(cXyz& vec) { mGObjTg.SetRVec(vec); }
    void SetAtRVec(cXyz& vec) { mGObjAt.SetRVec(vec); }
    void SetTgHitPos(cXyz& pos) { mGObjTg.SetHitPos(pos); }
    void SetAtHitPos(cXyz& pos) { mGObjAt.SetHitPos(pos); }
    cXyz* GetAtHitPosP() { return mGObjAt.GetHitPosP(); }
    cXyz* GetTgHitPosP() { return mGObjTg.GetHitPosP(); }

    /* 0x050 */ dCcD_GObjAt mGObjAt;
    /* 0x094 */ dCcD_GObjTg mGObjTg;
    /* 0x0DC */ dCcD_GObjCo mGObjCo;
};  // Size = 0xF8

static_assert(sizeof(dCcD_GObjInf) == 0xF8);

class dCcD_Cyl {
public:
    dCcD_GObjInf mGObjInf;
    cCcD_CylAttr mCylAttr;
};  // Size = 0x130
static_assert(sizeof(dCcD_Cyl) == 0x130);

extern "C" cCcD_GObjInf__vtbl_t __vt__8dCcD_Cyl;
#define dCcD_Cyl_vtable __vt__8dCcD_Cyl

class dCcD_Sph {
public:
    dCcD_GObjInf mGObjInf;
    cCcD_SphAttr mSphAttr;
};  // Size = 0x12C
static_assert(sizeof(dCcD_Sph) == 0x12C);

extern "C" cCcD_GObjInf__vtbl_t __vt__8dCcD_Sph;
#define dCcD_Sph_vtable __vt__8dCcD_Sph

class dCcD_Cps {
public:
    dCcD_GObjInf mGObjInf;
    cCcD_CpsAttr mCpsAttr;
};  // Size = 0x138
static_assert(sizeof(dCcD_Cps) == 0x138);

extern "C" cCcD_GObjInf__vtbl_t __vt__8dCcD_Cps;
#define dCcD_Cps_vtable __vt__8dCcD_Cps

class dCcD_Tri {
public:
    dCcD_GObjInf mGObjInf;
    cCcD_TriAttr mTriAttr;
};

#endif /* D_CC_D_CC_D_H */
