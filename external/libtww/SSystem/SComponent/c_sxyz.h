#ifndef C_SXYZ_H
#define C_SXYZ_H

#include "../../dolphin/gctypes.h"

struct SVec {
    s16 mX, mY, mZ;
};

class csXyz : public SVec {
public:
    ~csXyz() {}
    csXyz() {}
    csXyz(const csXyz& other) : SVec(other) {};
    csXyz(s16 x, s16 y, s16 z) {
        mX = x;
        mY = y;
        mZ = z;
    }
};

#endif /* C_SXYZ_H */
