// Taken from https://github.com/zsrtp/GC-Randomizer/blob/stable/source/patch.cpp
#include "utils/patch.h"
#include "libtww/dolphin/os/OSCache.h"


void writeBranch(void* ptr, void* destination) {
    u32 branch = 0x48000000;  // b
    writeBranchMain(ptr, destination, branch);
}

void writeBranchLR(void* ptr, void* destination) {
    u32 branch = 0x48000001;  // bl
    writeBranchMain(ptr, destination, branch);
}

void writeBranchMain(void* ptr, void* destination, u32 branch) {
    u32 delta = reinterpret_cast<u32>(destination) - reinterpret_cast<u32>(ptr);

    branch |= (delta & 0x03FFFFFC);

    u32* p = reinterpret_cast<u32*>(ptr);
    *p = branch;

    DCFlushRange(ptr, sizeof(u32));
    ICInvalidateRange(ptr, sizeof(u32));
}
