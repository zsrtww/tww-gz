#ifndef LIB_TWW_FLAGS
#define LIB_TWW_FLAGS

#include "libtww/dolphin/gctypes.h"

#define FLAG_AMNT 1

enum FlagId {
    WATCHED_FF2_HELMAROC_CUTSCENE
};

void setEventFlag(uint16_t flag);
void updateFlags();

extern bool g_flags[FLAG_AMNT];

#endif