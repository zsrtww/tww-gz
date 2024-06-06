#ifndef C_SXYZ_H
#define C_SXYZ_H

#include "../../dolphin/gctypes.h"
#include "../../dolphin/mtx/vec.h"

class csXyz : public SVec {
public:
    ~csXyz() {}
    csXyz() {}
    csXyz(const csXyz& other) : SVec(other) {}
    csXyz(s16 x, s16 y, s16 z) {
        x = x;
        y = y;
        z = z;
    }

    void operator=(const SVec& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    csXyz operator+(csXyz& param_0) {
        return csXyz(x + param_0.x, y + param_0.y, z + param_0.z);
    }

    void operator+=(csXyz& param_0) {
        x += param_0.x;
        y += param_0.y;
        z += param_0.z;
    }

    csXyz operator*(f32 param_0) {
        return csXyz(x * param_0, y * param_0, z * param_0);
    }

    void set(s16 oX, s16 oY, s16 oZ) {
        x = oX;
        y = oY;
        z = oZ;
    }

    void setall(s16 val) {
        x = val;
        y = val;
        z = val;
    }
};

#endif /* C_SXYZ_H */
