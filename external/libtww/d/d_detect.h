#ifndef D_D_DETECT_H
#define D_D_DETECT_H

#include "../SSystem/SComponent/c_xyz.h"

class dDetectPlace_c {
public:
    cXyz mPos;
    u16 mEnable;
};

class dDetect_c {
public:
    /* 0x00 */ dDetectPlace_c mPlace[1];
    /* 0x10 */ s16 mTimer;
};  // Size: 0x14

#endif /* D_D_DETECT_H */
