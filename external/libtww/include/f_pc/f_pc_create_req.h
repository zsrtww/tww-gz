
#ifndef F_PC_CREATE_REQ_H_
#define F_PC_CREATE_REQ_H_

#include "../SSystem/SComponent/c_phase.h"
#include "../defines.h"
#include "f_pc_create_tag.h"
#include "f_pc_method.h"
#include "f_pc_method_tag.h"
#include "f_pc_base.h"


typedef struct base_process_class base_process_class;
typedef struct layer_class layer_class;

typedef struct create_request_method_class {
    cPhs__Handler mpHandler;
    process_method_func mpCancel;
    process_method_func mpDelete;
} create_request_method_class;

typedef struct create_request {
    create_tag mBase;
    s8 mbIsCreating;
    s8 mbIsCancelling;
    process_method_tag_class mMtdTg;
    create_request_method_class* mpCtRqMtd;
    void* mpUnk1;
    s32 mBsPcId;
    struct base_process_class* mpRes;
    layer_class* mpLayer;
} create_request;  // Size: 0x48

#endif