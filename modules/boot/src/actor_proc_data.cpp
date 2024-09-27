#include "actor_proc_data.h"
#include "fs.h"
#include "global_data.h"

KEEP_FUNC void loadActorName(s16& i_procName) {
    if (i_procName < 0) {
        i_procName = 501;
    }

    if (i_procName > 501) {
        i_procName = 0;
    }

    int offset = i_procName * 32;
    loadFile("twwgz/procs.bin", &g_procData, sizeof(g_procData), offset);
}

KEEP_FUNC void loadActorName() {
    if (g_currentActor) {
        int offset = (g_currentActor->mBase.mProcName * 32);
        loadFile("twwgz/procs.bin", &g_procData, sizeof(g_procData), offset);
    }
}

KEEP_FUNC void loadPlayerProc(int& i_procName) {
    int offset = i_procName * 32;
    loadFile("twwgz/procsInit.bin", &g_procInit, sizeof(g_procInit), offset);
}