#include "addrs.h"
#include "utils/draw.h"
#include "utils/texture.h"
#include "gcn_c/include/gfx.h"

#define DEFAULT_WIDTH 0x06

Texture blankTex;

namespace Draw {
void init() {
    load_texture("twwgz/tex/blank.tex", &blankTex);
    if (blankTex.loadCode != TexCode::TEX_OK) {
        //tp_osReport("Could not load blank texture (Code: %d)", blankTex.loadCode);
    }
}

void begin(uint16_t n) {
    begin(n, GX_TRIANGLESTRIP);
}

void begin(uint16_t n, uint8_t primitive) {
    begin(n, primitive, &blankTex._texObj);
}

void begin(uint16_t n, GXTexObj* tex) {
    begin(n, GX_TRIANGLESTRIP, tex);
}

void begin(uint16_t n, uint8_t primitive, GXTexObj* tex) {
    GX_LoadTexObj(tex, (uint8_t)GX_TEXMAP0);
    GX_Begin(primitive, GX_VTXFMT0, n);
}

void begin_outline(uint16_t n) {
    begin_outline(n, DEFAULT_WIDTH);
}

void begin_outline(uint16_t n, uint8_t width) {
    GX_LoadTexObj(&blankTex._texObj, (uint8_t)GX_TEXMAP0);
    GX_SetLineWidth(width, GX_TO_ZERO);
    GX_Begin(GX_LINESTRIP, GX_VTXFMT0, n);
}

void add_vertex(uint32_t color, Vec2 point, Vec2 tex) {
    GX_Position2f32(point.x, point.y);
    GX_Color1u32(color);
    GX_TexCoord2f32(tex.x, tex.y);
}

void add_vertex(uint32_t color, Vec2 point) {
    add_vertex(color, point, {0.0f, 0.0f});
}

void end() {
    GX_End();
}

void drawQuad(uint32_t color, Vec2 p[4]) {
    drawQuad(color, p, &blankTex._texObj);
}

void drawQuad(uint32_t color, Vec2 p[4], Vec2 tex[4]) {
    drawQuad(color, p, tex, &blankTex._texObj);
}

void drawQuad(uint32_t color, Vec2 p[4], GXTexObj* texture) {
    Vec2 tex[4] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0},
    };
    drawQuad(color, p, tex, texture);
}

void drawQuad(uint32_t color, Vec2 p[4], Vec2 tex[4], GXTexObj* texture) {
    begin(4, texture);
    add_vertex(color, p[0], tex[0]);
    add_vertex(color, p[1], tex[1]);
    add_vertex(color, p[3], tex[3]);
    add_vertex(color, p[2], tex[2]);
    end();
}

void drawQuadOutline(uint32_t color, Vec2 p[4]) {
    drawQuadOutline(color, p, DEFAULT_WIDTH);
}

void drawQuadOutline(uint32_t color, Vec2 p[4], uint8_t width) {
    begin_outline(5, width);
    add_vertex(color, p[0], {0.0, 0.0});
    add_vertex(color, p[1], {1.0, 0.0});
    add_vertex(color, p[2], {1.0, 1.0});
    add_vertex(color, p[3], {0.0, 1.0});
    add_vertex(color, p[0], {0.0, 0.0});
    end();
}

void drawRect(uint32_t color, Vec2 pos, Vec2 dim) {
    drawRect(color, pos, dim, &blankTex._texObj);
}

void drawRect(uint32_t color, Vec2 pos, Vec2 dim, GXTexObj* texture) {
    Vec2 tex[4] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0},
    };
    drawRect(color, pos, dim, tex, texture);
}

void drawRect(uint32_t color, Vec2 pos, Vec2 dim, Vec2 tex[4]) {
    drawRect(color, pos, dim, tex, &blankTex._texObj);
}

void drawRect(uint32_t color, Vec2 pos, Vec2 dim, Vec2 tex[4], GXTexObj* texture) {
    Vec2 vertices[4] = {{pos.x, pos.y},
                        {pos.x + dim.x, pos.y},
                        {pos.x + dim.x, pos.y + dim.y},
                        {pos.x, pos.y + dim.y}};
    drawQuad(color, vertices, tex, texture);
}

void drawRectOutline(uint32_t color, Vec2 pos, Vec2 dim) {
    drawRectOutline(color, pos, dim, DEFAULT_WIDTH);
}

void drawRectOutline(uint32_t color, Vec2 pos, Vec2 dim, uint8_t width) {
    Vec2 vertices[4] = {{pos.x, pos.y},
                        {pos.x + dim.x, pos.y},
                        {pos.x + dim.x, pos.y + dim.y},
                        {pos.x, pos.y + dim.y}};
    drawQuadOutline(color, vertices, width);
}

};  // namespace Draw