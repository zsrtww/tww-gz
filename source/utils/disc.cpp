#include "utils/disc.h"
#include "math.h"
#include "libtww/SSystem/SComponent/c_malloc.h"
#include "libtww/MSL_C/string.h"

#ifdef __cplusplus
extern "C" {
#endif

s32 dvd_read(DVDFileInfo* file_info, void* data, s32 size, s32 offset) {
    constexpr const u32 buf_size = 0x20;
    u8* buf = (u8*)tww_memalign(-32, buf_size);
    s32 read_bytes = 0;

    while (size > 0) {
        s32 result = DVDReadPrio(file_info, buf, buf_size, (offset & ~(buf_size - 1)), 2);
        if (result <= 0) {
            break;
        }
        s32 rem_size = buf_size - (offset & (buf_size - 1));
        tww_memcpy((void*)((u32)data + read_bytes), buf + (offset & (buf_size - 1)),
                  MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tww_free(buf);
    return read_bytes;
}

#ifdef __cplusplus
}
#endif