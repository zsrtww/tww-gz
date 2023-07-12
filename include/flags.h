#ifndef LIB_TWW_FLAGS
#define LIB_TWW_FLAGS

#include "libtww/dolphin/gctypes.h"

#define FLAG_AMNT 12
#define CUTSCENE_FLAG_OFFSET 3
#define KORL_FLAG_OFFSET 6
#define SAVEWARP_FLAG_OFFSET 7

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

    /*Savewarp Flags*/
    LEAVING_OUTSET_CUTSCENE,
    TETRA_SPOILS_BAG_TEXT,
    BARREL_LAUNCH_CUTSCENE,
    POST_FF1_KORL_CUTSCENE,
    ENTER_KORL_FIRST_TIME,

};

void setEventFlag(uint16_t flag);
void updateFlags();

extern bool g_flags[FLAG_AMNT];

#endif
