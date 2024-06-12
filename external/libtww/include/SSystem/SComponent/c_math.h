#ifndef C_MATH_H
#define C_MATH_H

#include "../../dolphin/gctypes.h"
#include "../../defines.h"

LIBTWW_DEFINE_FUNC(cM_atan2s__Fff,
                  s16, cM_atan2s, (f32, f32))

inline s16 cM_deg2s(f32 deg) {
    return deg * 182.04445f;
}

inline f32 cM_sht2d(f32 v) {
    return v * 0.005493164f;
}

inline f32 cM_s2rad(s16 x) {
    return x * 9.58738e-05f;
}

#endif /* C_MATH_H */
