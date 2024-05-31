#ifndef C_M3D_G_AAB_H
#define C_M3D_G_AAB_H

#include "c_xyz.h"

// Axis aligned bounding box
class cM3dGAab {
private:
public:
    /* 0x00 */ cXyz mMin;
    /* 0x0C */ cXyz mMax;
    /* 0x18 */ void* vtable;

    const cXyz* GetMaxP() const { return &mMax; }
    const cXyz* GetMinP() const { return &mMin; }
    const f32 GetMaxX() const { return mMax.x; }
    const f32 GetMaxY() const { return mMax.y; }
    const f32 GetMaxZ() const { return mMax.z; }
    const f32 GetMinX() const { return mMin.x; }
    const f32 GetMinY() const { return mMin.y; }
    const f32 GetMinZ() const { return mMin.z; }
};  // Size = 0x1C

static_assert(0x1C == sizeof(cM3dGAab));

#endif /* C_M3D_G_AAB_H */
