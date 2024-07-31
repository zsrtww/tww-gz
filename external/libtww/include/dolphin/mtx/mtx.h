#ifndef MTX_H
#define MTX_H

#include "../gctypes.h"

struct Vec;

typedef float Mtx[3][4];
typedef float Mtx44[4][4];
typedef float Mtx33[3][3];
typedef float Mtx23[2][3];
typedef float (*MtxP)[4];
typedef float (*Mtx3P)[3];

extern "C" {
void PSMTXIdentity(Mtx m);
void PSMTXTrans(Mtx m, f32 x, f32 y, f32 z);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXScale(Mtx m, f32 x, f32 y, f32 z);
void PSMTXCopy(const Mtx src, Mtx dst);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecArray(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void PSMTXConcat(const Mtx, const Mtx, Mtx);
void PSMTXScale(Mtx, f32, f32, f32);
void PSMTXTrans(Mtx matrix, f32 x_trans, f32 y_trans, f32 z_trans);
void PSMTXCopy(const Mtx src, Mtx dst);
}

#endif /* MTX_H */
