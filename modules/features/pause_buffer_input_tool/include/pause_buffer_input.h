#pragma once

#include "libtww/include/dolphin/gctypes.h"

enum Buffer_Input_Result {
    WRONG,
    SUCCESS,
    LATE,
    EARLY
};

namespace PauseBufferInputTool {
void GZ_PauseBufferInputTool();
void setResultStr(int result, u8 inputFrame = 0);
}  // namespace PauseBufferInputTool