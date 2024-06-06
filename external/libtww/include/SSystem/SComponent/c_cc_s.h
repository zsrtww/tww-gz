#ifndef C_CC_S_H
#define C_CC_S_H

#include "c_cc_d.h"

class cCcS {
public:
    /* 0x0000 */ cCcD_Obj* mpObjAt[0x100];
    /* 0x0400 */ cCcD_Obj* mpObjTg[0x300];
    /* 0x1000 */ cCcD_Obj* mpObjCo[0x100];
    /* 0x1400 */ cCcD_Obj* mpObj[0x500];
    /* 0x2800 */ int mObjAtCount;
    /* 0x2804 */ int mObjTgCount;
    /* 0x2808 */ int mObjCoCount;
    /* 0x280C */ int mObjCount;
    /* 0x2810 */ cCcD_DivideArea mDivideArea;
    /* 0x2850 */ void* vtable;
};  // Size = 0x2854

static_assert(sizeof(cCcS) == 0x2854);

#endif /* C_CC_S_H */
