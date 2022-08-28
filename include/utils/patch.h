// Taken from https://github.com/zsrtp/GC-Randomizer/blob/stable/include/patch.h
#pragma once

#include <stdint.h>
#include "libtww/dolphin/os/OSCache.h"

void writeBranch(void* ptr, void* destination);
void writeBranchLR(void* ptr, void* destination);
void writeBranchMain(void* ptr, void* destination, uint32_t branch);

/**
 * @brief Hooks a function to execute the provided one instead.
 *
 * The trampoline is a callable structure that allows to execute the original function.
 *
 * @param function 		The original function to hook.
 * @param _trampoline 	A uint32_t array of size 2 that will contain the trampoline code.
 * 						(Must be preallocated).
 * @param destination 	The function to replace the hooked function.
 * @return 	A reference to the trampoline.
 */
template <typename Func, typename Dest>
Func hookFunction(Func function, uint32_t* trampoline, Dest destination) {
    uint32_t* instructions = reinterpret_cast<uint32_t*>(function);

    // Original instruction
    trampoline[0] = instructions[0];
    DCFlushRange(&trampoline[0], sizeof(uint32_t));
    ICInvalidateRange(&trampoline[0], sizeof(uint32_t));

    // Branch to original function past hook
    writeBranch(&trampoline[1], &instructions[1]);

    // Write actual hook
    writeBranch(&instructions[0], reinterpret_cast<void*>(static_cast<Func>(destination)));

    return reinterpret_cast<Func>(trampoline);
}
