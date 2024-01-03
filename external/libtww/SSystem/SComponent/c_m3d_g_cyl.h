#ifndef C_M3D_G_CYL_H
#define C_M3D_G_CYL_H

#include "c_xyz.h"

// Cylinder
struct cM3dGCylS {
    /* 0x00 */ Vec mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
};  // Size = 0x14
class cM3dGSph;

class cM3dGCyl {
public:
    /* 0x00 */ cXyz mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
    /* 0x14 */ void* vtable;

    const cXyz* GetCP() const { return &mCenter; }
    f32 GetR() const { return mRadius; }
    f32 GetH() const { return mHeight; }
    cXyz& GetC() { return mCenter; }
};

static_assert(0x18 == sizeof(cM3dGCyl));

#endif /* C_M3D_G_CYL_H */
