#ifndef C_BG_S_CHK_H
#define C_BG_S_CHK_H

#include "../../dolphin/gctypes.h"

class cBgS_PolyPassChk;

class cBgS_GrpPassChk {
public:
    void* vtable;
};

class cBgS_Chk {
public:
    /* 0x00 */ cBgS_PolyPassChk* mPolyPassChk;
    /* 0x04 */ cBgS_GrpPassChk* mGrpPassChk;
    /* 0x08 */ u32 mActorPid;
    /* 0x0C */ u8 unk_0x0C;
    /* 0x10 */ void* vtable;

    void SetActorPid(u32 pid) { mActorPid = pid; }
    u32 GetActorPid() const { return mActorPid; }
    void SetPolyPassChk(cBgS_PolyPassChk* p_chk) { mPolyPassChk = p_chk; }
    void SetGrpPassChk(cBgS_GrpPassChk* p_chk) { mGrpPassChk = p_chk; }
    cBgS_PolyPassChk* GetPolyPassChk() const { return mPolyPassChk; }
    cBgS_GrpPassChk* GetGrpPassChk() const { return mGrpPassChk; }
};

#endif /* C_BG_S_CHK_H */
