
#ifndef F_PC_CREATE_TAG_H_
#define F_PC_CREATE_TAG_H_

#include "../SSystem/SComponent/c_list.h"
#include "../SSystem/SComponent/c_tag.h"

typedef struct create_tag {
    create_tag_class mBase;
} create_tag;

extern "C" node_list_class g_fpcCtTg_Queue;

#endif