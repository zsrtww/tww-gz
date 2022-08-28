#ifndef C_COUNTER_H
#define C_COUNTER_H

#include <stdint.h>
#include "../../addrs.h"

struct cCounter {
    uint32_t game_counter;
    uint32_t game_counter2;
    uint32_t non_menu_counter;
};

#define g_Counter (*(cCounter*)(g_Counter_addr))

uint32_t cCt_getFrameCount() {
    return g_Counter.game_counter;
}

#endif /* C_COUNTER_H */