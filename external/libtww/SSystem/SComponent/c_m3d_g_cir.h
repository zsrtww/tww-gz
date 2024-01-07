#ifndef C_M3D_G_CIR_H
#define C_M3D_G_CIR_H

#include "../../dolphin/gctypes.h"

class cM2dGCir {
public:
    f32 mPosX;
    f32 mPosY;
    f32 mRadius;
    void* vtable;
    
    f32 GetCx() const { return mPosX; }
    f32 GetCy() const { return mPosY; }
    f32 GetR() const { return mRadius; }
    void Set(f32 x, f32 y, f32 r) {
        mPosX = x;
        mPosY = y;
        mRadius = r;
    }
};

class cM3dGCir : public cM2dGCir {
    f32 mPosZ;

public:
    void Set(f32 x, f32 y, f32 z, f32 r) {
        cM2dGCir::Set(x, y, r);
        mPosZ = z;
    }
};

#endif /* C_M3D_G_CIR_H */
