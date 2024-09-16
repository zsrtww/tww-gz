#ifndef F_PC_STDCREATE_H_
#define F_PC_STDCREATE_H_

#include "f_pc_create_req.h"

typedef struct layer_class layer_class;

typedef int (*stdCreateFunc)(void*, void*);

typedef struct standard_create_request_class {
    /* 0x00 */ create_request mBase;
    /* 0x48 */ request_of_phase_process_class unk_0x48;
    /* 0x50 */ s16 mLoadID;
    /* 0x54 */ void* unk_0x54;
    /* 0x58 */ stdCreateFunc unk_0x58;
    /* 0x5C */ void* unk_0x5C;
} standard_create_request_class;

LIBTWW_DEFINE_FUNC(fpcSCtRq_Request__FP11layer_classsPFPvPv_iPvPv, fpc_ProcID, fpcSCtRq_Request, (layer_class*, s16, stdCreateFunc, void*, void*))

#endif
