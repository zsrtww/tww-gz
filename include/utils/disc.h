#include "gcn_c/include/dvd.h"
#include "libtww/dolphin/gctypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Like DVDReadPrio, but allows for arbitrary sizes and offsets.
 */
s32 dvd_read(DVDFileInfo* file_info, void* data, s32 size, s32 offset);

#ifdef __cplusplus
}
#endif