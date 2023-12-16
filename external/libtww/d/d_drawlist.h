#ifndef D_D_DRAWLIST_H
#define D_D_DRAWLIST_H

#include "../f_op/f_op_view.h"

class dDlst_window_c {
public:
    /* 0x00 */ view_port_class mViewport;
    /* 0x28 */ s8 mCameraID;
    /* 0x29 */ s8 mMode;
};

static_assert(sizeof(dDlst_window_c) == 0x2C);

#endif /* D_D_DRAWLIST_H */
