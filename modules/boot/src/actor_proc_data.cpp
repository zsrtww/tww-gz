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

#define PLAYER_PROC_DATA_SIZE 0x1B60  // size of res/proc_info/procsInit.bin

u8* g_playerProcDataBuf = nullptr;  // pointer to buffer of size PLAYER_PROC_DATA_SIZE

KEEP_FUNC void loadPlayerProcData() {
    if (g_playerProcDataBuf == nullptr) {
        g_playerProcDataBuf = new u8[PLAYER_PROC_DATA_SIZE];
        loadFile("twwgz/procsInit.bin", g_playerProcDataBuf, PLAYER_PROC_DATA_SIZE, 0);
    }
}

KEEP_FUNC procBinData* getPlayerProcName(int& i_procName) {
    int offset = i_procName * 32;
    return (procBinData*)(g_playerProcDataBuf + offset);
}

KEEP_FUNC void freePlayerProcData() {
    if (g_playerProcDataBuf != nullptr) {
        delete g_playerProcDataBuf;
        g_playerProcDataBuf = nullptr;
    }
}
