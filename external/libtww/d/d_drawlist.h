#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include <stdint.h>

class dDlst_window_c {
public:
    /* 0x00 */ float mXOrig;
    /* 0x04 */ float mYOrig;
    /* 0x08 */ float mWidth;
    /* 0x0C */ float mHeight;
    /* 0x10 */ float mNearZ;
    /* 0x14 */ float mFarZ;
    /* 0x18 */ float mScissorXOrig;
    /* 0x1C */ float mScissorYOrig;
    /* 0x20 */ float mScissorWidth;
    /* 0x24 */ float mScissorHeight;
};

#endif /* D_D_DRAWLIST_H */
