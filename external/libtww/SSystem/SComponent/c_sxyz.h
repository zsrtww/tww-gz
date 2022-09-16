#ifndef C_SXYZ_H
#define C_SXYZ_H

#include <stdint.h>

struct SVec {
    int16_t mX, mY, mZ;
};

class csXyz : public SVec {
public:
    ~csXyz() {}
    csXyz() {}
    csXyz(const csXyz& other) : SVec(other) {};
    csXyz(int16_t x, int16_t y, int16_t z) {
        mX = x;
        mY = y;
        mZ = z;
    }
};

#endif /* C_SXYZ_H */
