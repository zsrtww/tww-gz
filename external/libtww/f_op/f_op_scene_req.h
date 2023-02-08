#ifndef F_F_OP_SCENE_REQ_H_
#define F_F_OP_SCENE_REQ_H_

#include "../dolphin/gctypes.h"
#include "../addrs.h"

#define l_fopScnRq_IsUsingOfOverlap (*(int*)l_fopScnRq_IsUsingOfOverlap_addr)

typedef int (*fopScnM_ChangeReq_t)(void* _this, s16, s16, u16);
#define fopScnM_ChangeReq ((fopScnM_ChangeReq_t)fopScnM_ChangeReq_addr)

#endif