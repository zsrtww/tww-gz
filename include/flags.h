#ifndef LIB_TWW_FLAGS
#define LIB_TWW_FLAGS

#include "libtww/dolphin/gctypes.h"

#define FLAG_AMNT 19
#define SAVEWARP_FLAG_OFFSET 9
#define TUNER_FLAG_OFFSET 14

enum FlagId {
    /*General Flags*/
    WATCHED_FF2_HELMAROC_CUTSCENE,
    GOSSIP_STONE_TRIGGER,
    GENERAL_POST_FF1_KORL_CUTSCENE,
    ENDLESS_NIGHT,
    RAISE_TOTG,
    LOAD_TOTG_AFTER_T2Z,
    OPEN_HYRULE3_WARP,
    DESTROY_HYRULE_BARRIER,
    OPEN_DARK_PORTAL,
    GET_SEA_CHART,

    /*Savewarp Flags*/
    LEAVING_OUTSET_CUTSCENE,
    TETRA_SPOILS_BAG_TEXT,
    BARREL_LAUNCH_CUTSCENE,
    POST_FF1_KORL_CUTSCENE,
    ENTER_KORL_FIRST_TIME,

    /*Tuner Flags */
    KOOLOO_LIMPAH,
    BALLOON_DISCOUNT,
    TINGS_DISCOUNT,
    HAND_ME_DOWN_TUNER,

};

void setEventFlag(uint16_t flag);
void updateFlags();

extern bool g_flags[FLAG_AMNT];

#endif
