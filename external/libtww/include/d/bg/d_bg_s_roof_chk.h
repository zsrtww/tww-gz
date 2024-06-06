#ifndef D_BG_D_BG_S_ROOF_CHK_H
#define D_BG_D_BG_S_ROOF_CHK_H

#include "../../SSystem/SComponent/c_bg_s_poly_info.h"
#include "../../SSystem/SComponent/c_xyz.h"
#include "d_bg_s_chk.h"

class dBgS_RoofChk : public cBgS_PolyInfo, public cBgS_Chk, public dBgS_Chk {
public:
    void SetPos(cXyz& pos) { m_pos = pos; }
    cXyz* GetPosP() { return &m_pos; }
    f32 GetNowY() { return m_now_y; }
    void SetNowY(f32 y) { m_now_y = y; }

private:
    /* 0x38 */ cXyz m_pos;
    /* 0x44 */ void* field_0x44;
    /* 0x48 */ f32 m_now_y;
};  // Size: 0x4C

static_assert(sizeof(dBgS_RoofChk) == 0x4C);

class dBgS_LinkRoofChk : public dBgS_RoofChk {
public:
};  // Size: 0x4C

#endif /* D_BG_D_BG_S_ROOF_CHK_H */