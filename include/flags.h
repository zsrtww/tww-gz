#ifndef LIB_TWW_FLAGS
#define LIB_TWW_FLAGS

#include "libtww/dolphin/gctypes.h"

#define FLAG_AMNT 1

enum FlagId {
    WATCHED_FF2_HELMAROC_CUTSCENE
};

struct GZFlag {
    int index;
    bool active;
    u32 flag;
};

void setEventFlag(uint16_t flag);
void updateFlags();

extern GZFlag g_flags[FLAG_AMNT];

#endif