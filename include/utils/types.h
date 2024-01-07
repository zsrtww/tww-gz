#pragma once

#include "libtww/dolphin/mtx/vec.h"

struct Vec2 {
    f32 x, y;
};

struct CameraMatrix {
    Vec target;
    Vec pos;
};