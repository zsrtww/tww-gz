#ifndef D_BG_D_BG_S_GND_CHK_H
#define D_BG_D_BG_S_GND_CHK_H

#include "../../SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "d_bg_s_chk.h"

class dBgS_GndChk : public cBgS_GndChk, public dBgS_Chk {
public:
};  // Size: 0x54

static_assert(sizeof(dBgS_GndChk) == 0x54);

class dBgS_LinkGndChk : public dBgS_GndChk {
public:
};  // Size: 0x54

class dBgS_ObjGndChk : public dBgS_GndChk {
public:
}; // Size: 0x54

class dBgS_ObjGndChk_Yogan : public dBgS_ObjGndChk {
public:
}; // Size: 0x54

class dBgS_ObjGndChk_Wtr : public dBgS_ObjGndChk {
public:
};

class dBgS_ObjGndChk_Spl : public dBgS_ObjGndChk {
public:
};

class dBgS_ObjGndChk_All : public dBgS_ObjGndChk {
public:
};

class dBgS_CamGndChk : public dBgS_GndChk {
public:
};

class dBgS_CamGndChk_Wtr : public dBgS_CamGndChk {
public:
};

#endif /* D_BG_D_BG_S_GND_CHK_H */