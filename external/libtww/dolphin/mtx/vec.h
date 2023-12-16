#ifndef VEC_H
#define VEC_H

#include "../gctypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vec {
    f32 x, y, z;
} Vec;

typedef Vec* VecPtr;
typedef Vec Point3d;
typedef Vec* Point3dPtr;

typedef struct SVec {
    s16 x, y, z;
} SVec;

#ifdef __cplusplus
};
#endif

#endif /* VEC_H */
