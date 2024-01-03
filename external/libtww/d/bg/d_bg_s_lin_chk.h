#ifndef D_BG_D_BG_S_LIN_CHK_H
#define D_BG_D_BG_S_LIN_CHK_H

#include "../../SSystem/SComponent/c_bg_s_lin_chk.h"
#include "d_bg_s_chk.h"

class fopAc_ac_c;

class dBgS_LinChk : public cBgS_LinChk, public dBgS_Chk {
public:
    /* 0x00 cBgS_LinChk */;
    /* 0x58 dBgS_Chk */;
};

class dBgS_LinkLinChk : public dBgS_LinChk {
public:
};

class dBgS_RopeLinChk : public dBgS_LinChk {
public:
};

class dBgS_BoomerangLinChk : public dBgS_LinChk {
public:
};

class dBgS_ArrowLinChk : public dBgS_LinChk {
public:
};

class dBgS_ObjLinChk : public dBgS_LinChk {
public:
};

class dBgS_BombLinChk : public dBgS_LinChk {
public:
};

class dBgS_CamLinChk : public dBgS_LinChk {
public:
};

class dBgS_CamLinChk_NorWtr : public dBgS_CamLinChk {
public:
};

class dBgS_MirLightLinChk : public dBgS_LinChk {
public:
};

#endif /* D_BG_D_BG_S_LIN_CHK_H */