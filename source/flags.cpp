#include "flags.h"

GZFlag g_flags[FLAG_AMNT] = {
    {WATCHED_FF2_HELMAROC_CUTSCENE, false, 0x803B8759, 0},
    {HAVE_HURRICANE_SPIN,false,0x803B8737,5},
    {ENDLESS_NIGHT,false,0x803B8736,1},
    {ORCA_INTRO_CUTSCENE,false,0x803B8732,6},
    {PUPPET_GANON_CUTSCENE,false,0x803B8767,1}
};

void GZ_activate(FlagId flag_index) {
    *(u8*)(g_flags[flag_index].address) |= 1 << g_flags[flag_index].bit_position;
}

void GZ_deactivate(FlagId flag_index) {
    *(u8*)(g_flags[flag_index].address) &= 0xFF ^ (1 << g_flags[flag_index].bit_position);
}

bool GZ_isActive(FlagId flag_index) {
    return ((*(u8*)(g_flags[flag_index].address)) & (1 << g_flags[flag_index].bit_position)) != 0;
}

void GZ_updateFlags() {
    for (int i = 0; i < FLAG_AMNT; i++) {
        g_flags[i].active = GZ_isActive((FlagId) i);
    }
}
