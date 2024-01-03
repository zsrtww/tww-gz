#ifndef C_M3D_G_SPH_H_
#define C_M3D_G_SPH_H_

#include "c_m3d_g_cyl.h"
#include "c_xyz.h"

struct cM3dGSphS {
    /* 0x0 */ Vec mCenter;
    /* 0xC */ f32 mRadius;
};  // Size: 0x10

class cM3dGSph {
private:
public:
    /* 0x00 */ cXyz mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ void* vtable;

    const cXyz& GetC() const { return mCenter; }
    const cXyz* GetCP() const { return &mCenter; }
    const f32 GetR() const { return mRadius; }
    f32 GetCX() const { return mCenter.x; }
    f32 GetCY() const { return mCenter.y; }
    f32 GetCZ() const { return mCenter.z; }
};

static_assert(0x14 == sizeof(cM3dGSph));

#endif