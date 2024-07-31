#ifndef C_M3D_G_CPS_H
#define C_M3D_G_CPS_H

#include "c_m3d_g_lin.h"
#include "c_xyz.h"

struct cM3dGCpsS {
    /* 0x00 */ Vec mStart;
    /* 0x0C */ Vec mEnd;
    /* 0x18 */ f32 mRadius;
};  // Size: 0x1C

class cM3dGCps : public cM3dGLin {
public:
    /* 0x1C */ f32 mRadius;

    f32 GetR() const { return mRadius; }
};

static_assert(0x20 == sizeof(cM3dGCps));

#endif /* C_M3D_G_CPS_H */
