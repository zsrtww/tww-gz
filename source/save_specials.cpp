#include "flags.h"
#include "save_manager.h"
#include "save_specials.h"

void SaveMngSpecial_ForestOfFairies() {
    gSaveManager.injectDefault_during();
    //GZ_activate(HAS_SEEN_HELMAROC_ARRIVING_AT_OUTSET);
}

void SaveMngSpecial_TrialsSkip() {
    gSaveManager.injectDefault_during();
    //GZ_activate(WATCHED_FF2_HELMAROC_CUTSCENE);
}