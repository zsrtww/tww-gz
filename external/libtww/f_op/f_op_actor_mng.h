#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "f_op_actor.h"

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

inline s32 fopAcM_GetRoomNo(const fopAc_ac_c* pActor) {
    return (s8)pActor->mCurrent.mRoomNo;
}

inline u32 fopAcM_checkStatus(fopAc_ac_c* pActor, u32 status) {
    return pActor->mStatus & status;
}

inline u32 fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->mStatus & 0x2000;
}

inline u32 fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_checkStatus(pActor, 0x100000);
}

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus &= ~flag;
}

inline csXyz& fopAcM_GetAngle_p(fopAc_ac_c* pActor) {
    return pActor->mCurrent.mAngle;
}

#endif
