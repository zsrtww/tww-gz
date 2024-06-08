#ifndef C_XYZ_H
#define C_XYZ_H

#include "../../dolphin/gctypes.h"
#include "../../dolphin/mtx/vec.h"
#include "../../addrs.h"

class cXyz;

typedef cXyz (*cXyz__operator_pl_t)(const cXyz* thisx, const Vec& vec);
#define cXyz__operator_pl ((cXyz__operator_pl_t)cXyz__operator_pl_addr)

typedef cXyz (*cXyz__operator_mi_t)(const cXyz* thisx, const Vec& vec);
#define cXyz__operator_mi ((cXyz__operator_mi_t)cXyz__operator_mi_addr)

typedef cXyz (*cXyz__operator_ml_t)(const cXyz* thisx, f32 scale);
#define cXyz__operator_ml ((cXyz__operator_ml_t)cXyz__operator_ml_addr)

typedef cXyz (*cXyz__operator_ml2_t)(const cXyz* thisx, const Vec& vec);
#define cXyz__operator_ml2 ((cXyz__operator_ml2_t)cXyz__operator_ml2_addr)

typedef cXyz (*cXyz__operator_dv_t)(const cXyz* thisx, f32 scale);
#define cXyz__operator_dv ((cXyz__operator_dv_t)cXyz__operator_dv_addr)

class cXyz : public Vec {
public:
    ~cXyz() {}
    cXyz() {}
    cXyz(f32 x, f32 y, f32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    cXyz(const cXyz& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }

    cXyz(const Vec& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }

    void operator=(const Vec& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }

    cXyz operator+(const Vec& vec) const {
        return cXyz__operator_pl(this, vec);
    }

    cXyz operator-(const Vec& vec) const {
        return cXyz__operator_mi(this, vec);
    }

    cXyz operator*(f32 scale) const {
        return cXyz__operator_ml(this, scale);
    }

    cXyz operator*(const Vec& vec) const {
        return cXyz__operator_ml2(this, vec);
    }

    cXyz operator/(f32 scale) const {
        return cXyz__operator_dv(this, scale);
    }

    void operator+=(f32 f) {
        x += f;
        y += f;
        z += f;
    }

    void operator-=(f32 f) {
        x -= f;
        y -= f;
        z -= f;
    }

    void operator+=(const Vec& vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;
    }

    void setAll(f32 f) {
        z = f;
        y = f;
        x = f;
    }

    void set(f32 pX, f32 pY, f32 pZ) {
        x = pX;
        y = pY;
        z = pZ;
    }

    void setMin(const cXyz& other) {
        if (x > other.x) {
            x = other.x;
        }
        if (y > other.y) {
            y = other.y;
        }
        if (z > other.z) {
            z = other.z;
        }
    }

    void setMax(const cXyz& other) {
        if (x < other.x) {
            x = other.x;
        }
        if (y < other.y) {
            y = other.y;
        }
        if (z < other.z) {
            z = other.z;
        }
    }
};

class cXy {
public:
    f32 x, y;
};

#endif