#include "font.h"
#include "libtww/SSystem/SComponent/c_malloc.h"
#include "libtww/SSystem/SComponent/c_lib.h"
#include "libtww/MSL_C/string.h"
#include "utils/disc.h"
#include "utils/draw.h"
#include "menus/settings_menu.h"

_Font Font::font;

FontCode Font::loadFont(const char* path) {
    DVDFileInfo fileInfo;
    s32 readsize;
    if (font.loadCode == FontCode::FNT_OK) {
        free_font();
    }

    if (!DVDOpen(path, &fileInfo)) {
        font.loadCode = FontCode::FNT_ERR_FILE;
        return font.loadCode;
    }
    readsize = dvd_read(&fileInfo, &font.header, sizeof(_FontHeader), 0);
    if (readsize < (s32)sizeof(_FontHeader)) {
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_READ;
        return font.loadCode;
    }

    u32 size = font.header.glyph_count * sizeof(_Glyph);
    font.glyphs = (_Glyph*)tww_memalign(-32, size);
    if (font.glyphs == nullptr) {
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_MEM;
        return font.loadCode;
    }

    if (DVDReadPrio(&fileInfo, font.glyphs, size, sizeof(font.header), 2) < (s32)size) {
        tww_free(font.glyphs);
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_READ;
        return font.loadCode;
    }

    if (load_texture_offset(path, &font.texture, sizeof(font.header) + size) != TexCode::TEX_OK) {
        tww_free(font.glyphs);
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_TEXTURE;
        return font.loadCode;
    }
    DVDClose(&fileInfo);

    font.loadCode = FontCode::FNT_OK;
    return font.loadCode;
}

void Font::free_font() {
    if (font.glyphs != nullptr) {
        tww_free(font.glyphs);
        font.glyphs = 0;
    }
    free_texture(&font.texture);
    tww_memset(&font, 0, sizeof(_Font));
    // The next line is redundant, but is still there for good measure
    font.loadCode = FontCode::FNT_UNLOADED;
}

void PositionedGlyph::render(u32 color, Texture* texture) {
    Draw::drawQuad(color, vertices, tex_coords, &texture->_texObj);
}

PositionedGlyph DecodedGlyph::position(float _x, float _y, float factor) {
    float vty = _y - metrics.ascender * factor;
    float vby = _y + metrics.descender * factor;
    float vrx = _x + (width + offset) * factor;
    float vlx = _x + offset * factor;

    float tty = glyph->minY;
    float tby = glyph->maxY;
    float trx = glyph->maxX;
    float tlx = glyph->minX;

    return {{{vlx, vty}, {vrx, vty}, {vrx, vby}, {vlx, vby}},
            {{tlx, tty}, {trx, tty}, {trx, tby}, {tlx, tby}},
            (_x + width * factor)};
}

bool Font::lookupGlyph(char c, DecodedGlyph& glyph) {
    u8 idx = c;
    if (idx < 0 || idx >= font.header.glyph_count) {
        return false;
    }
    glyph.glyph = &font.glyphs[idx];
    glyph.width = font.glyphs[idx].width;
    glyph.offset = font.glyphs[idx].offset;
    glyph.metrics = font.header.metrics;
    return true;
}

float Font::renderChar(char c, float x, float y, u32 color, float size) {
    DecodedGlyph glyph;
    if (lookupGlyph(c, glyph)) {
        auto positioned = glyph.position(x, y, size / font.header.base_size);
        positioned.render(color, &font.texture);
        return positioned.next_x;
    } else {
        return x + font.glyphs[' '].width * size / font.header.base_size;
    }
}

void Font::renderChars(const char* str, float x, float y, u32 color, float size) {
    int len = tww_strlen(str);
    for (int i = 0; i < len; i++) {
        x = renderChar(str[i], x, y, color, size);
    }
}

void Font::GZ_drawChar(char c, float x, float y, u32 color, bool drop_shadows, float size) {
    if (drop_shadows) {
        renderChar(c, x + 1.0f, y + 1.0f, DROP_SHADOWS_RGBA, size);
    }
    renderChar(c, x, y, color, size);
}

void Font::GZ_drawStr(const char* str, float x, float y, u32 color, bool drop_shadows,
                      float size) {
    if (drop_shadows) {
        renderChars(str, x + 1.0f, y + 1.0f, DROP_SHADOWS_RGBA, size);
    }
    renderChars(str, x, y, color, size);
}

float Font::getCharWidth(char c, float size) {
    DecodedGlyph glyph;
    if (lookupGlyph(c, glyph)) {
        return glyph.width * size / font.header.base_size;
    } else {
        return font.glyphs[' '].width * size / font.header.base_size;
    }
}

float Font::getStrWidth(const char* str, float size) {
    int len = tww_strlen(str);
    float str_size = 0.f;
    for (int i = 0; i < len; i++) {
        str_size += getCharWidth(str[i], size);
    }
    return str_size;
}

// returns the width of the rendered string
float GZ_drawSelectChar(const char* str, float x, float y, size_t char_idx, size_t max_char,
                        u32 color) {
    float pos = 0.0f;
    for (size_t i = 0; i <= max_char; ++i) {
        Font::GZ_drawChar(str[i], x + pos, y, char_idx == i ? CURSOR_RGBA : color,
                          g_dropShadows);
        pos += Font::getCharWidth(str[i]);
    }
    return pos;
}