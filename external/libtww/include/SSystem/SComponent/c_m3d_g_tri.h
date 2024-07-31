#ifndef C_M3D_G_TRI_H_
#define C_M3D_G_TRI_H_

#include "c_m3d_g_pla.h"
#include "c_xyz.h"

struct cM3dGTriS {
    Vec a;
    Vec b;
    Vec c;
};

class cM3dGTri : public cM3dGPla {
public:
    /* 0x00 */ /* cM3dGPla */
    /* 0x14 */ Vec mA;
    /* 0x20 */ Vec mB;
    /* 0x2C */ Vec mC;
};

#endif