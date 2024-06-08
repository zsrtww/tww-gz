#include "global_data.h"
#include "geometry_draw.h"
#include "rels/include/defines.h"

KEEP_VAR u8 g_geometryOpacity = 0x80;

KEEP_VAR CollisionItem g_collisionFlags[VIEW_COLLISION_MAX] = {
    {VIEW_AT_CC, false},
    {VIEW_TG_CC, false},
    {VIEW_CO_CC, false},
};