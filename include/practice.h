#pragma once

#include "save_manager.h"

enum SpeedrunCategories {
    ANY_NO_MSS,
};

#define REQ_POS 1
#define REQ_CAM 2

extern int last_save_index;
extern char last_category[5];
extern special* last_special_ptr;
extern int last_special_size;