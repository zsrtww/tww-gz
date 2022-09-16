#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "f_op_actor.h"

struct fopAcM_prmBase_class {
    /* 0x00 */ uint32_t field_0x00;
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ csXyz field_0x10;
    /* 0x16 */ uint16_t field_0x16;
};  // Size = 0x18

struct fopAcM_prm_class {
    /* 0x00 */ uint32_t mParameter;  // single uint32_t Parameter
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ csXyz mAngle;  // rotation
    /* 0x16 */ uint16_t mEnemyNo;
    /* 0x18 */ uint8_t mScale[3];
    /* 0x1B */ uint8_t mGbaName;
    /* 0x1C */ int32_t mParentPId;  // parent process ID
    /* 0x20 */ int8_t mSubtype;
    /* 0x21 */ int8_t mRoomNo;
};

typedef int (*heapCallbackFunc)(fopAc_ac_c*);
typedef int (*createFunc)(void*);

inline int32_t fopAcM_GetRoomNo(const fopAc_ac_c* pActor) {
    return (int8_t)pActor->mCurrent.mRoomNo;
}

inline uint32_t fopAcM_checkStatus(fopAc_ac_c* pActor, uint32_t status) {
    return pActor->mStatus & status;
}

inline uint32_t fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->mStatus & 0x2000;
}

inline uint32_t fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_checkStatus(pActor, 0x100000);
}

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, uint32_t flag) {
    pActor->mStatus |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, uint32_t flag) {
    pActor->mStatus &= ~flag;
}

inline csXyz& fopAcM_GetAngle_p(fopAc_ac_c* pActor) {
    return pActor->mCurrent.mAngle;
}

#endif
