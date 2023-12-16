#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include "../f_op/f_op_view.h"
#include "../JSystem/J3DGraphBase/J3DPacket.h"

class dDlst_shadowTri_c {
public:
    /* 0x0 */ cXyz mPos[3];
};

class dDlst_shadowPoly_c {
public:
    /* 0x0 */ void* vtable;
    /* 0x4 */ u16 mCount;
    /* 0x6 */ u8 field_0x6[2];
};

class dDlst_shadowRealPoly_c : public dDlst_shadowPoly_c {
public:
    /* 0x8 */ dDlst_shadowTri_c mShadowTri[256];
};

class dDlst_mirrorPacket : public J3DPacket {
public:
    /* 0x0010 */ u8 field_0x0010[0x0040 - 0x0010];
    /* 0x0040 */ Mtx mPosMtx;
    /* 0x0070 */ u8 field_0x0070[0x0080 - 0x0070];
    /* 0x0080 */ Mtx mTexMtx;
    /* 0x00B0 */ dDlst_shadowRealPoly_c mShadowPoly;
    /* 0x24B8 */ GXTexObj mTexObj;
    /* 0x24D8 */ u8 mAlpha;
};

class dDlst_window_c {
public:
    /* 0x00 */ view_port_class mViewport;
    /* 0x28 */ s8 mCameraID;
    /* 0x29 */ s8 mMode;
};

static_assert(sizeof(dDlst_window_c) == 0x2C);

#endif /* D_D_DRAWLIST_H */
