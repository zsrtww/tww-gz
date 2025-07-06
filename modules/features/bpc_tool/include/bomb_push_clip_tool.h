#pragma once

#include "libtww/include/dolphin/gctypes.h"

enum BPC_Result {
    WRONG,
    SUCCESS,
    LATE,
    EARLY
};

namespace BombPushClipTool {
void GZ_BombPushClipTool();
void setBombPushStr(int result, u8 inputFrame = 0);
}  // namespace BombPushClipTool