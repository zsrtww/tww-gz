#ifndef J3DTRANSFORM_H
#define J3DTRANSFORM_H

#include "../../dolphin/mtx/vec.h"

// I doubt this is right but it seems like the only way to prevent an empty ctor being added on array construction
struct J3DTransformInfo {
    /* 0x00 */ Vec mScale;
    /* 0x0C */ SVec mRotation;
    /* 0x14 */ Vec mTranslate;
    inline J3DTransformInfo& operator=(const J3DTransformInfo& b) {
        mScale = b.mScale;
        mRotation = b.mRotation;
        mTranslate = b.mTranslate;
        return *this;
    }
};  // Size: 0x20

#endif