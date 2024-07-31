#ifndef C_M3D_G_LIN_H
#define C_M3D_G_LIN_H

#include "c_xyz.h"
#include "../../dolphin/mtx/vec.h"

// Line
class cM3dGLin {
    // private:
public:
    /* 0x00 */ cXyz mStart;
    /* 0x0C */ cXyz mEnd;
    /* 0x18 */ void* vtable;

    void CalcVec(Vec* pOut) const { PSVECSubtract(&this->mEnd, &this->mStart, pOut); }
    f32 GetLen() const { return PSVECDistance(&mStart, &mEnd); }

    const cXyz* GetStartP() const { return &mStart; }
    cXyz* GetStartP() { return &mStart; }
    cXyz& GetStart() { return mStart; }
    const cXyz* GetEndP() const { return &mEnd; }
    cXyz* GetEndP() { return &mEnd; }
    cXyz& GetEnd() { return mEnd; }
};

static_assert(0x1C == sizeof(cM3dGLin));

#endif /* C_M3D_G_LIN_H */
