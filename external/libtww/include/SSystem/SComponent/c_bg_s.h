#ifndef C_BG_S_H
#define C_BG_S_H

#include "c_bg_s_poly_info.h"
#include "../../dolphin/gctypes.h"

class fopAc_ac_c;
class cBgS_ShdwDraw;
class cBgS_LinChk;
class cBgS_GndChk;
class cM3dGPla;
class cXyz;

class cBgS_ChkElm {
public:
    /* 0x00 */ cBgW* m_bgw_base_ptr;
    /* 0x04 */ u32 m_flags;
    /* 0x08 */ u32 m_actor_id;
    /* 0x0C */ fopAc_ac_c* m_actor_ptr;
    /* 0x10 */ void* vtable;

    bool ChkUsed() const { return (m_flags & 1); }
};  // Size: 0x14

static_assert(sizeof(cBgS_ChkElm) == 0x14);

class cBgW;
class cBgS {
public:
    /* 0x0000 */ cBgS_ChkElm m_chk_element[256];
    /* 0x1400 */ void* vtable;
};  // Size: 0x1404

static_assert(sizeof(cBgS) == 0x1404);

#endif /* C_BG_S_H */