#ifndef C_BG_S_POLY_INFO_H
#define C_BG_S_POLY_INFO_H

#include "../../dolphin/gctypes.h"

class cBgW;
class cBgS_PolyInfo {
public:
    /* 0x00 */ u16 mPolyIndex;
    /* 0x02 */ u16 mBgIndex;
    /* 0x04 */ cBgW* mpBgW;
    /* 0x08 */ unsigned int mActorId;
    /* 0x0C */ void* vtable;
};

#endif /* C_BG_S_POLY_INFO_H */
