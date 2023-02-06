// Taken from https://github.com/zsrtp/GC-Randomizer/blob/stable/include/patch.h
#pragma once


#include "libtww/dolphin/os/OSCache.h"

void writeBranch(void* ptr, void* destination);
void writeBranchLR(void* ptr, void* destination);
void writeBranchMain(void* ptr, void* destination, u32 branch);

/**
 * @brief Hooks a function to execute the provided one instead.
 *
 * The trampoline is a callable structure that allows to execute the original function.
 *
 * @param function 		The original function to hook.
 * @param _trampoline 	A u32 array of size 2 that will contain the trampoline code.
 * 						(Must be preallocated).
 * @param destination 	The function to replace the hooked function.
 * @return 	A reference to the trampoline.
 */
template <typename Func, typename Dest>
Func hookFunction(Func function, u32* trampoline, Dest destination) {
    u32* instructions = reinterpret_cast<u32*>(function);

    // Original instruction
    trampoline[0] = instructions[0];
    DCFlushRange(&trampoline[0], sizeof(u32));
    ICInvalidateRange(&trampoline[0], sizeof(u32));

    // Branch to original function past hook
    writeBranch(&trampoline[1], &instructions[1]);

    // Write actual hook
    writeBranch(&instructions[0], reinterpret_cast<void*>(static_cast<Func>(destination)));

    return reinterpret_cast<Func>(trampoline);
}
