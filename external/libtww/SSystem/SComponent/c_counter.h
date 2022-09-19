#ifndef C_COUNTER_H
#define C_COUNTER_H

#include "../../dolphin/gctypes.h"
#include "../../addrs.h"

struct cCounter {
    u32 game_counter;
    u32 game_counter2;
    u32 non_menu_counter;
};

#define g_Counter (*(cCounter*)(g_Counter_addr))

u32 cCt_getFrameCount() {
    return g_Counter.game_counter;
}

#endif /* C_COUNTER_H */