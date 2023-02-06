#pragma once

#include "libtww/addrs.h"
#include "libtww/dolphin/mtx/vec.h"
#include "utils/texture.h"
#include "gcn_c/include/gfx.h"

extern Texture blankTex;

namespace Draw {
void init();

// Basic functions
void begin(u16 n);
void begin(u16 n, u8 primitive);
void begin(u16 n, GXTexObj* tex);
void begin(u16 n, u8 primitive, GXTexObj* tex);
void begin_outline(u16 n);
void begin_outline(u16 n, u8 width);
void add_vertex(u32 color, Vec2 point);
void add_vertex(u32 color, Vec2 point, Vec2 tex);
void end();

void drawQuad(u32 color, Vec2 p[4]);
void drawQuad(u32 color, Vec2 p[4], GXTexObj* texture);
void drawQuad(u32 color, Vec2 p[4], Vec2 tex[4]);
void drawQuad(u32 color, Vec2 p[4], Vec2 tex[4], GXTexObj* texture);
void drawQuadOutline(u32 color, Vec2 p[4]);
void drawQuadOutline(u32 color, Vec2 p[4], u8 width);
void drawRect(u32 color, Vec2 pos, Vec2 dim);
void drawRect(u32 color, Vec2 pos, Vec2 dim, GXTexObj* texture);
void drawRect(u32 color, Vec2 pos, Vec2 dim, Vec2 tex[4]);
void drawRect(u32 color, Vec2 pos, Vec2 dim, Vec2 tex[4], GXTexObj* texture);
void drawRectOutline(u32 color, Vec2 pos, Vec2 dim);
void drawRectOutline(u32 color, Vec2 pos, Vec2 dim, u8 width);
};  // namespace Draw