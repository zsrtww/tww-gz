#ifndef D_EVENT_D_EVENT_MANAGER_H
#define D_EVENT_D_EVENT_MANAGER_H

#include "d_event_data.h"

class dEvent_exception_c {
public:
    u32 mEventInfoIdx;
    u8 field_0x4;
    u8 field_0x5;
    u8 field_0x6;
    u8 field_0x7;
    u32 mState;
};
static_assert(sizeof(dEvent_exception_c) == 0xC);

class dEvent_manager_c {
public:
    /* 0x00 */ dEvDtBase_c mEventBase;
    /* 0x20 */ s32 mCameraPlay;
    /* 0x24 */ dEvent_exception_c mEventException;
    /* 0x30 */ cXyz mGoal;
    /* 0x3C */ dEvDtFlag_c mFlags;
};
static_assert(sizeof(dEvent_manager_c) == 0x53C);

#endif /* D_EVENT_D_EVENT_MANAGER_H */
