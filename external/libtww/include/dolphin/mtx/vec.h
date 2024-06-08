#ifndef VEC_H
#define VEC_H

#include "../gctypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vec {
    f32 x, y, z;
} Vec;

typedef struct Vec2 {
    f32 x, y;
} Vec2;

typedef Vec* VecPtr;
typedef Vec Point3d;
typedef Vec* Point3dPtr;

typedef struct SVec {
    s16 x, y, z;
} SVec;

typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

#ifdef __cplusplus
};
#endif

extern "C" {
f32 PSVECSquareMag(const Vec* v);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void PSVECNormalize(const Vec* src, Vec* unit);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 PSVECMag(const Vec* v);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
f32 PSVECDistance(const Vec* a, const Vec* b);
}

#endif /* VEC_H */
