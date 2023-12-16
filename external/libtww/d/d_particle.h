#ifndef D_PARTICLE
#define D_PARTICLE

#include "../dolphin/gctypes.h"
#include "../dolphin/gx/gx.h"

class JPABaseEmitter;
class dKy_tevstr_c;

class dPa_levelEcallBack /* : public JPACallBackBase<JPABaseEmitter*> */ {
public:
    void* vtable;
};  // Size: 0x04

class dPa_followEcallBack : public dPa_levelEcallBack {
public:
    JPABaseEmitter* getEmitter() { return mpEmitter; }
    void setRateOff(u8 param_0) { mRateOff = param_0; }
    bool isEnd() { return mFlag & 1; }

    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ u8 field_0x08[0x10 - 0x08];
    /* 0x10 */ u8 mFlag;
    /* 0x11 */ u8 mRateOff;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
};  // Size: 0x14

static_assert(sizeof(dPa_followEcallBack) == 0x14);

class dPa_smokeEcallBack : public dPa_followEcallBack {
public:
    /* 0x14 */ s8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ GXColor field_0x16;
    /* 0x1A */ u8 field_0x1A[0x1C - 0x1A];
    /* 0x1C */ dKy_tevstr_c* mTevstr;
};  // Size: 0x20

static_assert(sizeof(dPa_smokeEcallBack) == 0x20);

class dPa_cutTurnEcallBack_c : public dPa_levelEcallBack {
public:
    /* 0x04 */ u8 field_0x04[0x0C];
};  // Size: 0x10

static_assert(sizeof(dPa_cutTurnEcallBack_c) == 0x10);

class dPa_rippleEcallBack : public dPa_levelEcallBack {
public:
    JPABaseEmitter* getEmitter() { return mpBaseEmitter; }
    void setRate(f32 rate) { mRate = rate; }

    /* 0x04 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x08 */ cXyz* mPos;
    /* 0x0C */ u32 mFlags;
    /* 0x10 */ f32 mRate;
};

#endif /* D_PARTICLE */