#ifndef D_CC_D_CC_S_H
#define D_CC_D_CC_S_H

#include "../../SSystem/SComponent/c_cc_s.h"
#include "d_cc_d.h"
#include "d_cc_mass_s.h"

struct dCcS__vtable_t {
  /* 0x00 */ void* rtti;
  /* 0x04 */ void* pad;
  /* 0x08 */ void* CalcTgPlusDmg;
  /* 0x0C */ void* SetPosCorrect;
  /* 0x10 */ void* SetCoGObjInf;
  /* 0x14 */ void* SetAtTgGObjInf;
  /* 0x18 */ void* ChkNoHitGAtTg;
  /* 0x1C */ void* ChkAtTgHitAfterCross;
  /* 0x20 */ void* ChkNoHitGCo;
  /* 0x24 */ void* dtor;
  /* 0x28 */ void* MoveAfterCheck;
  /* 0x2C */ void* SetCoGCorrectProc;
  /* 0x30 */ void* CalcParticleAngle;
};

extern "C" dCcS__vtable_t __vt__4dCcS;

LIBTWW_DEFINE_FUNC(__ct__4cCcSFv,
                  void, cCcS__ctor, (cCcS*))

LIBTWW_DEFINE_FUNC(__ct__12dCcMassS_MngFv,
                  void, dCcMassS_Mng__ctor, (dCcMassS_Mng*))

class dCcS : public cCcS {
public:
    dCcS() {
        cCcS__ctor(this);
        vtable = &__vt__4dCcS;
        dCcMassS_Mng__ctor(&mMass_Mng);
    }

    /* 0x284C */ dCcMassS_Mng mMass_Mng;
};  // Size = 0x29f4


LIBTWW_DEFINE_FUNC(__dt__4dCcSFv,
                  void, dCcS__dtor, (dCcS*))
                  
static_assert(sizeof(dCcS) == 0x29f4);

#endif /* D_CC_D_CC_S_H */
