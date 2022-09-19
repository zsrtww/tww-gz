#ifndef C_ANGLE_H
#define C_ANGLE_H

#include "c_xyz.h"
#include "../../dolphin/gctypes.h"

class cSAngle {
public:
    s16 mAngle;

    s16 Val() const { return this->mAngle; }
    bool operator<(const cSAngle& other) const { return mAngle < other.mAngle; }
    bool operator>(const cSAngle& other) const { return mAngle > other.mAngle; }
    operator s16(void) const { return mAngle; }
    void operator=(const cSAngle& other) { mAngle = other.mAngle; }
};

class cDegree {
public:
    float mDegree;
};

class cSPolar {
public:
    float mRadial;
    cSAngle mAngle1;
    cSAngle mAngle2;
};

class cSGlobe {
public:
    float mRadius;
    cSAngle mAzimuth;      // original: V
    cSAngle mInclination;  // original: U

    float R(void) const { return mRadius; }
    const cSAngle& V(void) const { return mAzimuth; }
    const cSAngle& U(void) const { return mInclination; }
};

#endif /* C_ANGLE_H */
