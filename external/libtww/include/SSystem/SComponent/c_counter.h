#ifndef C_COUNTER_H
#define C_COUNTER_H

#include "../../dolphin/gctypes.h"
#include "../../addrs.h"

struct counter_class {
    u32 mCounter0;
    s32 mCounter1;
    u32 mTimer;
};

#define g_Counter (*(counter_class*)(g_Counter_addr))

inline u32 cCt_getFrameCount() {
    return g_Counter.mCounter0;
}

#endif /* C_COUNTER_H */