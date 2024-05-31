/**	@file cxx.h
 *	@brief Custom override of (de)allocation onto specific heaps.
 *
 *	@author Zephiles
 *	@author kipcode66
 *	@bug No known bugs.
 */
#ifndef LIBTWW_CXX_H
#define LIBTWW_CXX_H

#include <cstdint>
#include <new>

enum HeapID : int32_t {
    HEAP_GAME = 0,
    HEAP_ZELDA,
    HEAP_ARCHIVE,
};

void* operator new(std::size_t size);
void* operator new[](std::size_t size);
void* operator new(std::size_t size, int32_t alignment);
void* operator new[](std::size_t size, int32_t alignment);
void* operator new(std::size_t size, int32_t alignment, int32_t heapId);
void* operator new[](std::size_t size, int32_t alignment, int32_t heapId);
void operator delete(void* ptr);
void operator delete[](void* ptr);
void operator delete(void* ptr, std::size_t size);
void operator delete[](void* ptr, std::size_t size);

#endif  // LIBTWW_CXX_H