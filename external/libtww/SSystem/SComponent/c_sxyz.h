#ifndef C_SXYZ_H
#define C_SXYZ_H

#include "../../dolphin/gctypes.h"

struct SVec {
    s16 sx, sy, sz;
};

class csXyz : public SVec {
public:
    ~csXyz() {}
    csXyz() {}
    csXyz(const csXyz& other) : SVec(other) {};
    csXyz(s16 x, s16 y, s16 z) {
        sx = x;
        sy = y;
        sz = z;
    }

    void operator=(const SVec& other) {
        sx = other.sx;
        sy = other.sy;
        sz = other.sz;
    }
};

#endif /* C_SXYZ_H */
