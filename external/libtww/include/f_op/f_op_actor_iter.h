#ifndef F_OP_ACTOR_ITER_H_
#define F_OP_ACTOR_ITER_H_

#include "f_op_actor.h"
#include "../defines.h"

typedef void* (*fopAcIt_JudgeFunc)(void*, void*);

LIBTWW_DEFINE_FUNC(fopAcIt_Judge__FPFPvPv_PvPv, void*, fopAcIt_Judge, (fopAcIt_JudgeFunc, void*))

#endif