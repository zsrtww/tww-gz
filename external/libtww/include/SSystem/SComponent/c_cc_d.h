#ifndef C_CC_D_H
#define C_CC_D_H

#include "c_m3d_g_aab.h"
#include "c_m3d_g_cps.h"
#include "c_m3d_g_cyl.h"
#include "c_m3d_g_sph.h"
#include "c_m3d_g_tri.h"
#include "../../f_op/f_op_actor.h"

enum CcG_Tg_HitMark {
    CcG_Tg_UNK_MARK_6 = 6,
    CcG_Tg_UNK_MARK_8 = 8,
};

enum cCcD_ObjAtType {
    /* 0x00000002 */ AT_TYPE_SWORD          = (1 << 1),
    /* 0x00000020 */ AT_TYPE_BOMB           = (1 << 5),
    /* 0x00000040 */ AT_TYPE_BOOMERANG      = (1 << 6),
    /* 0x00000080 */ AT_TYPE_BOKO_STICK     = (1 << 7),
    /* 0x00000100 */ AT_TYPE_WATER          = (1 << 8),
    /* 0x00000200 */ AT_TYPE_FIRE           = (1 << 9),
    /* 0x00000400 */ AT_TYPE_MACHETE        = (1 << 10),
    /* 0x00000800 */ AT_TYPE_UNK800         = (1 << 11),
    /* 0x00001000 */ AT_TYPE_UNK1000        = (1 << 12),
    /* 0x00002000 */ AT_TYPE_UNK2000        = (1 << 13),
    /* 0x00004000 */ AT_TYPE_NORMAL_ARROW   = (1 << 14),
    /* 0x00008000 */ AT_TYPE_HOOKSHOT       = (1 << 15),
    /* 0x00010000 */ AT_TYPE_SKULL_HAMMER   = (1 << 16),
    /* 0x00020000 */ AT_TYPE_UNK20000       = (1 << 17),
    /* 0x00040000 */ AT_TYPE_FIRE_ARROW     = (1 << 18),
    /* 0x00080000 */ AT_TYPE_ICE_ARROW      = (1 << 19),
    /* 0x00100000 */ AT_TYPE_LIGHT_ARROW    = (1 << 20),
    /* 0x00200000 */ AT_TYPE_LEAF_WIND      = (1 << 21),
    /* 0x00400000 */ AT_TYPE_UNK400000      = (1 << 22),
    /* 0x00800000 */ AT_TYPE_LIGHT          = (1 << 23),
    /* 0x01000000 */ AT_TYPE_STALFOS_MACE   = (1 << 24),
    /* 0x02000000 */ AT_TYPE_UNK2000000     = (1 << 25),
    /* 0x04000000 */ AT_TYPE_DARKNUT_SWORD  = (1 << 26),
    /* 0x08000000 */ AT_TYPE_GRAPPLING_HOOK = (1 << 27),
    /* 0x10000000 */ AT_TYPE_MOBLIN_SPEAR   = (1 << 28),
    /* 0x20000000 */ AT_TYPE_PGANON_SWORD   = (1 << 29),
    /* 0xFFFFFFFF */ AT_TYPE_ALL            = ~0,
};

enum AtSPrm_e {
    AT_SPRM_SET = 1,
    AT_SPRM_NO_TG_HIT_INF_SET = 0x10,
};

enum TgSPrm_e {
    TG_SPRM_SET = 1,
    TG_SPRM_NO_AT_HIT_INF_SET = 0x10,
};

enum CoSPrm_e {
    CO_SPRM_SET = 1,
    CO_SPRM_NO_CRR = 0x100,
    CO_SPRM_NO_CO_HIT_INF_SET = 0x200,
};

class cCcD_ShapeAttr {
public:
    /* 0x00 */ cM3dGAab mAab;
    /* 0x1C */ void* vtable;
};
static_assert(0x20 == sizeof(cCcD_ShapeAttr));

class cCcD_CpsAttr {
public:
    cCcD_ShapeAttr shape_base;
    cM3dGCps cps;
};
static_assert(0x40 == sizeof(cCcD_CpsAttr));

class cCcD_SphAttr {
public:
    cCcD_ShapeAttr shape_base;
    cM3dGSph sph;
};
static_assert(0x34 == sizeof(cCcD_SphAttr));

class cCcD_CylAttr {
public:
    cCcD_ShapeAttr shape_base;
    cM3dGCyl cyl;
};
static_assert(0x38 == sizeof(cCcD_CylAttr));

class cCcD_TriAttr {};

class cCcD_DivideInfo {
public:
    /* 0x00 */ u32 mRangeBits;
    /* 0x04 */ void* vtable;
};

class cCcD_DivideArea : public cM3dGAab {
public:
    /* 0x1C */ bool mXDiffIsZero;
    /* 0x20 */ f32 mScaledXDiff;
    /* 0x24 */ f32 mInvScaledXDiff;
    /* 0x28 */ bool mYDiffIsZero;
    /* 0x2C */ f32 mScaledYDiff;
    /* 0x30 */ f32 mInvScaledYDiff;
    /* 0x34 */ bool mZDiffIsZero;
    /* 0x38 */ f32 mScaledZDiff;
    /* 0x3C */ f32 mInvScaledZDiff;
};  // Size = 0x40

static_assert(sizeof(cCcD_DivideArea) == 0x40);

struct cCcD_SrcObjCommonBase {
    /* 0x0 */ s32 mSPrm;
};

struct cCcD_SrcObjTg {
    /* 0x0 */ s32 mType;
    /* 0x4 */ cCcD_SrcObjCommonBase mBase;
};  // Size: 0x8

struct cCcD_SrcObjAt {
    /* 0x0 */ s32 mType;
    /* 0x4 */ u8 mAtp;
    /* 0x8 */ cCcD_SrcObjCommonBase mBase;
};  // Size: 0xC

struct cCcD_SrcObjCo {
    /* 0x0 */ cCcD_SrcObjCommonBase mBase;
};  // Size: 0x4

struct cCcD_SrcObjHitInf {
    /* 0x00 */ cCcD_SrcObjAt mObjAt;
    /* 0x0C */ cCcD_SrcObjTg mObjTg;
    /* 0x14 */ cCcD_SrcObjCo mObjCo;
};  // Size: 0x18

struct cCcD_SrcObj {
    /* 0x0 */ int mFlags;
    /* 0x4 */ cCcD_SrcObjHitInf mSrcObjHitInf;
};  // Size: 0x1C

class cCcD_GStts {
public:
    /* 0x00 */ void* vtable;
};  // Size = 0x4

class cCcD_Stts {
public:
    /* 0x00 */ cXyz m_cc_move;
    /* 0x0C */ fopAc_ac_c* mActor;
    /* 0x10 */ int mApid;
    /* 0x14 */ u8 mWeight;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 mDmg;
    /* 0x18 */ void* vtable;
};  // Size = 0x1C

class cCcD_Obj;
class cCcD_ObjCommonBase {
public:
    /* 0x00 */ u32 mSPrm;
    /* 0x04 */ u32 mRPrm;
    /* 0x08 */ cCcD_Obj* mHitObj;
    /* 0x0C */ void* vtable;
};

class cCcD_Obj;
class cCcD_ObjAt : public cCcD_ObjCommonBase {
public:
    /* 0x10 */ int mType;
    /* 0x14 */ u8 mAtp;
};

static_assert(0x18 == sizeof(cCcD_ObjAt));

class cCcD_ObjTg : public cCcD_ObjCommonBase {
public:
    /* 0x10 */ int mType;
};

class cCcD_ObjCo : public cCcD_ObjCommonBase {
public:
};

struct cCcD_GObjInf__vtbl_t {
    /* 0x00 */ void* RTTI;
    /* 0x04 */ void* pad;
    /* 0x08 */ void* dtor;
    /* 0x0C */ void* GetGObjInf_const;
    /* 0x10 */ void* GetGObjInf;
    /* 0x14 */ void* GetShapeAttr_const;
    /* 0x18 */ void* GetShapeAttr;
    /* 0x20 */ void* ClrAtHit;
    /* 0x24 */ void* ClrTgHit;
    /* 0x28 */ void* ClrCoHit;
};

class cCcD_ObjHitInf {
public:
    /* 0x000 */ cCcD_ObjAt mObjAt;
    /* 0x018 */ cCcD_ObjTg mObjTg;
    /* 0x02C */ cCcD_ObjCo mObjCo;
    /* 0x03C */ void* vtable;
};  // Size = 0x40

static_assert(0x40 == sizeof(cCcD_ObjHitInf));

class cCcD_Obj : public cCcD_ObjHitInf {
public:
    /* 0x040 */ int mFlags;
    /* 0x044 */ cCcD_Stts* mStts;
    /* 0x048 */ cCcD_DivideInfo mDivideInfo;
};  // Size = 0x50

static_assert(0x50 == sizeof(cCcD_Obj));

class cCcD_GObjInf : public cCcD_Obj {
public:
};

#endif /* C_CC_D_H */
