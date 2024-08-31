#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "f_op_actor.h"
#include "../f_pc/f_pc_manager.h"
#include "../defines.h"

struct fopAcM_prmBase_class {
    /* 0x00 */ u32 field_0x00;
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ csXyz field_0x10;
    /* 0x16 */ u16 field_0x16;
};  // Size = 0x18

struct fopAcM_prm_class {
    /* 0x00 */ u32 mParameter;  // single u32 Parameter
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ csXyz mAngle;  // rotation
    /* 0x16 */ u16 mEnemyNo;
    /* 0x18 */ u8 mScale[3];
    /* 0x1B */ u8 mGbaName;
    /* 0x1C */ s32 mParentPId;  // parent process ID
    /* 0x20 */ s8 mSubtype;
    /* 0x21 */ s8 mRoomNo;
};

typedef int (*heapCallbackFunc)(fopAc_ac_c*);
typedef int (*createFunc)(void*);

inline s8 fopAcM_GetRoomNo(fopAc_ac_c* pActor) {
    return pActor->current.roomNo;
}

inline bool fopAcM_checkStatus(fopAc_ac_c* pActor, u32 status) {
    return pActor->mStatus & status;
}

inline u32 fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->mStatus & fopAcStts_CARRY_e;
}

inline u32 fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_checkStatus(pActor, fopAcStts_HOOK_CARRY_e);
}

inline u32 fopAcM_GetParam(void* pActor) {
    return fpcM_GetParam(pActor);
}

inline u32 fopAcM_GetParamBit(u32 param, u8 shift, u8 bit) {
    return (param >> shift) & ((1 << bit) - 1);
}

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus &= ~flag;
}

inline csXyz* fopAcM_GetAngle_p(fopAc_ac_c* i_actor) {
    return &i_actor->current.angle;
}

LIBTWW_DEFINE_FUNC(fopAcM_delete__FP10fopAc_ac_c, void, fopAcM_delete, (fopAc_ac_c*))

LIBTWW_DEFINE_FUNC(fopAcM_SearchByName__FsPP10fopAc_ac_c, s32, fopAcM_SearchByName, (u32, fopAc_ac_c**))

LIBTWW_DEFINE_FUNC(fopAcM_getProcNameString__FP10fopAc_ac_c, const char*, fopAcM_getProcNameString, (fopAc_ac_c*))

LIBTWW_DEFINE_FUNC(fopAcM_create__FsUlP4cXyziP5csXyzP4cXyzScPFPv_i, void, fopAcM_create, (s16, u32, const cXyz*, int, const csXyz*, const cXyz*, s8, createFunc))

extern "C" {
extern node_list_class g_fopAcTg_Queue;
}

#endif
