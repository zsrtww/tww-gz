#ifndef C_XYZ_H
#define C_XYZ_H

#include "../../dolphin/gctypes.h"
#include "../../dolphin/mtx/vec.h"

class cXyz : public Vec {
public:
    void operator=(Vec& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
};

#endif