#ifndef M_DO_M_DO_MTX_H
#define M_DO_M_DO_MTX_H

#include "../dolphin/gctypes.h"
#include "../dolphin/mtx/mtx.h"
#include "../defines.h"

extern "C" Mtx now__14mDoMtx_stack_c;
#define mDoMtx_stack_c__now now__14mDoMtx_stack_c

LIBTWW_DEFINE_FUNC(mDoMtx_XYZrotM__FPA4_fsss,
                  void, mDoMtx_XYZrotM, (Mtx, short, short, short))

LIBTWW_DEFINE_FUNC(scaleM__14mDoMtx_stack_cFfff,
                  void, mDoMtx_stack_c__scaleM, (f32, f32, f32))

LIBTWW_DEFINE_FUNC(transM__14mDoMtx_stack_cFfff,
                  void, mDoMtx_stack_c__transM, (f32, f32, f32))

LIBTWW_DEFINE_FUNC(mDoMtx_inverseTranspose__FPA4_CfPA4_f,
                  bool, mDoMtx_inverseTranspose, (const Mtx, Mtx))

LIBTWW_DEFINE_FUNC(mDoMtx_XrotM__FPA4_fs,
                  void, mDoMtx_XrotM, (Mtx, s16))

LIBTWW_DEFINE_FUNC(mDoMtx_XrotS__FPA4_fs,
                  void, mDoMtx_XrotS, (Mtx, s16))

LIBTWW_DEFINE_FUNC(mDoMtx_YrotS__FPA4_fs,
                  void, mDoMtx_YrotS, (Mtx, s16))

LIBTWW_DEFINE_FUNC(mDoMtx_YrotM__FPA4_fs,
                  void, mDoMtx_YrotM, (Mtx, s16))

LIBTWW_DEFINE_FUNC(mDoMtx_ZrotM__FPA4_fs,
                  void, mDoMtx_ZrotM, (Mtx, s16))

inline void mDoMtx_trans(Mtx m, f32 x, f32 y, f32 z) {
    PSMTXTrans(m, x, y, z);
}

inline void mDoMtx_concat(const Mtx a, const Mtx b, Mtx c) {
    PSMTXConcat(a, b, c);
}

inline void mDoMtx_scale(Mtx m, f32 x, f32 y, f32 z) {
    PSMTXScale(m, x, y, z);
}

inline void mDoMtx_inverse(const Mtx a, Mtx b) {
    PSMTXInverse(a, b);
}

inline void mDoMtx_multVecArray(Mtx m, const Vec* src, Vec* dst, u32 count) {
    PSMTXMultVecArray(m, src, dst, count);
}

class mDoMtx_stack_c {
public:
    static MtxP get() { return mDoMtx_stack_c__now; }
    static void transS(f32 x, f32 y, f32 z) { PSMTXTrans(mDoMtx_stack_c__now, x, y, z); }
    static void scaleS(f32 x, f32 y, f32 z) { PSMTXScale(mDoMtx_stack_c__now, x, y, z); }
    static void XYZrotM(short x, short y, short z) { mDoMtx_XYZrotM(mDoMtx_stack_c__now, x, y, z); }
    static void revConcat(MtxP mtx) { PSMTXConcat(mtx, mDoMtx_stack_c__now, mDoMtx_stack_c__now); }
    static void scaleM(f32 x, f32 y, f32 z) { mDoMtx_stack_c__scaleM(x, y, z); }
    static void copy(const Mtx m) { PSMTXCopy(m, mDoMtx_stack_c__now); }
    static void transM(f32 x, f32 y, f32 z) { mDoMtx_stack_c__transM(x, y, z); }
    static void inverseTranspose() { mDoMtx_inverseTranspose(mDoMtx_stack_c__now, mDoMtx_stack_c__now); }
    static void XrotM(s16 x) { mDoMtx_XrotM(mDoMtx_stack_c__now, x); }
    static void YrotM(s16 y) { mDoMtx_YrotM(mDoMtx_stack_c__now, y); }
    static void ZrotM(s16 z) { mDoMtx_ZrotM(mDoMtx_stack_c__now, z); }
    static void YrotS(s16 y) { mDoMtx_YrotS(mDoMtx_stack_c__now, y); }
    static void multVec(const Vec* a, Vec* b) { PSMTXMultVec(mDoMtx_stack_c__now, a, b); }
};

#endif /* M_DO_M_DO_MTX_H */
