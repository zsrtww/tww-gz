#ifndef LIB_TWW_FLAGS
#define LIB_TWW_FLAGS

#include "libtww/dolphin/gctypes.h"

#define FLAG_AMNT 7
#define CUTSCENE_FLAG_OFFSET 3
#define KORL_FLAG_OFFSET 6

enum FlagId {
    /*Important Flags*/
    WATCHED_FF2_HELMAROC_CUTSCENE,
    HAVE_HURRICANE_SPIN,
    ENDLESS_NIGHT,

    /*Cutscene Flags */
    ORCA_INTRO_CUTSCENE,
    PUPPET_GANON_CUTSCENE,
    COURTYARD_CUTSCENE,

    /*Korl Flags*/
    MEETING_KORL_CUTSCENE,

};

void setEventFlag(uint16_t flag);
void updateFlags();

extern bool g_flags[FLAG_AMNT];

#endif