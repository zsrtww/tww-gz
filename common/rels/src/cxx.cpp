/**	@file cxx.h
 *	@brief Custom override of (de)allocation onto specific heaps.
 *
 *  @author Zephiles
 *	@bug No known bugs.
 */
#include "rels/include/cxx.h"

#include <cstdint>
#include <cstring>

#include "libtww/include/dolphin/os/OSCache.h"
#include "libtww/include/m_Do/m_Do_ext.h"
#include "libtww/include/JSystem/JKernel/JKRHeap.h"

void* getHeapPtr(int32_t id) {
    static JKRHeap** heapPtrArray[] = {
        &m_Do_ext::gameHeap,
        &m_Do_ext::zeldaHeap,
        &m_Do_ext::archiveHeap,
    };

    // Make sure the id is valid
    constexpr uint32_t heapPtrArraySize = sizeof(heapPtrArray) / sizeof(heapPtrArray[0]);
    if ((id < 0) || (static_cast<uint32_t>(id) >= heapPtrArraySize)) {
        // The id is invalid, so use the archive heap by default
        id = HEAP_ARCHIVE;
    }

    return *heapPtrArray[id];
}

void* allocateMemory(std::size_t size, void* heap, int32_t alignment) {
    // Make sure the heap exists
    if (!heap) {
        return nullptr;
    }

    void* ptr = __nw_JKRHeap(size, heap, alignment);
    ptr = memset(ptr, 0, size);
    DCFlushRange(ptr, size);
    return ptr;
}

void* allocateMemoryFromMainHeap(std::size_t size, int32_t alignment) {
    void* heapPtr = m_Do_ext::archiveHeap;
    return allocateMemory(size, heapPtr, alignment);
}

void* allocateMemoryFromHeapId(std::size_t size, int32_t alignment, int32_t id) {
    void* heapPtr = getHeapPtr(id);
    return allocateMemory(size, heapPtr, alignment);
}

void* operator new(std::size_t size) {
    return allocateMemoryFromMainHeap(size, 0x20);
}

void* operator new[](std::size_t size) {
    return allocateMemoryFromMainHeap(size, 0x20);
}

void* operator new(std::size_t size, int32_t alignment) {
    return allocateMemoryFromMainHeap(size, alignment);
}

void* operator new[](std::size_t size, int32_t alignment) {
    return allocateMemoryFromMainHeap(size, alignment);
}

void* operator new(size_t size, int32_t alignment, int32_t id) {
    return allocateMemoryFromHeapId(size, alignment, id);
}

void* operator new[](size_t size, int32_t alignment, int32_t id) {
    return allocateMemoryFromHeapId(size, alignment, id);
}

void* operator new(unsigned int size, std::align_val_t alignment) {
    return allocateMemoryFromMainHeap(size, (int)alignment);
}

void operator delete(void* ptr) {
    return __dl_JKRHeap(ptr);
}

void operator delete[](void* ptr) {
    return __dl_JKRHeap(ptr);
}

void operator delete(void* ptr, std::size_t size) {
    (void)size;

    return __dl_JKRHeap(ptr);
}

void operator delete[](void* ptr, std::size_t size) {
    (void)size;

    return __dl_JKRHeap(ptr);
}
