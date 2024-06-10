#ifndef D_BG_D_BG_S_CHK_H
#define D_BG_D_BG_S_CHK_H

#include "d_bg_s_grp_pass_chk.h"
#include "d_bg_s_poly_pass_chk.h"

class dBgS_Chk {
public:
    dBgS_Chk() {}
    dBgS_PolyPassChk* GetPolyPassChkInfo() { return (dBgS_PolyPassChk*)this; }
    dBgS_GrpPassChk* GetGrpPassChkInfo() { return (dBgS_GrpPassChk*)this; }

    /* 0x000 */ dBgS_PolyPassChk mPolyPassChkInfo;
    /* 0x010 */ dBgS_GrpPassChk mGrpPassChkInfo;
};  // Size: 0x14

static_assert(sizeof(dBgS_Chk) == 0x14);

#endif /* D_BG_D_BG_S_CHK_H */