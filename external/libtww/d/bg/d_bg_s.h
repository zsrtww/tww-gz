#ifndef D_BG_D_BG_S_H
#define D_BG_D_BG_S_H

#include <stdint.h>

class dBgW;
class fopAc_ac_c;

class cBgS_ChkElm {
    /* 0x00 */ dBgW* mpBgW;
    /* 0x04 */ uint32_t mFlags;
    /* 0x08 */ uint32_t mProcID;
    /* 0x0C */ fopAc_ac_c* mpActorPtr;
    /* 0x10 */ void* vtable;
};  // Size = 0x14

static_assert(sizeof(cBgS_ChkElm) == 0x14);

class cBgS {
    /* 0x0000 */ cBgS_ChkElm cbgs_elements[256];
    /* 0x1400 */ void* vtable;
};  // Size = 0x1404

static_assert(sizeof(cBgS) == 0x1404);

class dBgS_Acch;
class dBgS : public cBgS {};

#endif /* D_BG_D_BG_S_H */