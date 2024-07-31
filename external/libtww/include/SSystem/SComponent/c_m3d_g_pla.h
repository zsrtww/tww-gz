#ifndef C_M3C_G_PLA_H_
#define C_M3C_G_PLA_H_

#include "c_xyz.h"

// Plane with a normal
class cM3dGPla {
public:
    /* 0x00 */ cXyz mNormal;
    /* 0x0C */ f32 mD;
    /* 0x10 */ void* vtable;

    cXyz* GetNP() { return &mNormal; }
    const cXyz* GetNP() const { return &mNormal; }
};

#endif