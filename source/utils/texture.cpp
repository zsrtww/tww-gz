#include "libtww/SSystem/SComponent/c_malloc.h"
#include "libtww/SSystem/SComponent/c_lib.h"
#include "utils/texture.h"
#include "utils/disc.h"
#include "gcn_c/include/dvd.h"
#include "gcn_c/include/gfx.h"

enum TexFmt {
    RGB8 = 0,
    CMPR = 1,
    I8 = 2,
};

#ifdef __cplusplus
extern "C" {
#endif

u32 get_size(u32 format, u32 width, u32 height) {
    switch (format) {
    case TexFmt::CMPR: {
        return width * height / 2;
    }
    case TexFmt::I8: {
        return width * height;
    }
    case TexFmt::RGB8:
    default: {
        return 4 * width * height;
    }
    }
}

TexCode load_texture(const char* path, Texture* tex) {
    return load_texture_offset(path, tex, 0);
}

TexCode load_texture_offset(const char* path, Texture* tex, u32 offset) {
    DVDFileInfo fileInfo;
    s32 readsize;
    if (tex->loadCode == TexCode::TEX_OK) {
        free_texture(tex);
    }

    if (!DVDOpen(path, &fileInfo)) {
        tex->loadCode = TexCode::TEX_ERR_FILE;
        return tex->loadCode;
    }
    readsize = dvd_read(&fileInfo, &tex->header, sizeof(TexHeader), offset);
    if (readsize < (s32)sizeof(TexHeader)) {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_READ;
        return tex->loadCode;
    }

    u8 fmt = GX_TF_I8;
    switch (tex->header.format) {
    case TexFmt::RGB8: {
        fmt = GX_TF_RGBA8;
        break;
    }
    case TexFmt::CMPR: {
        fmt = GX_TF_CMPR;
        break;
    }
    case TexFmt::I8: {
        fmt = GX_TF_I8;
        break;
    }
    default: {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_INVALID_FORMAT;
        return tex->loadCode;
    }
    }

    u32 size = get_size(tex->header.format, tex->header.width, tex->header.height);
    tex->data = (u8*)tww_memalign(-32, size);
    if (tex->data == nullptr) {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_MEM;
        return tex->loadCode;
    }

    if (DVDReadPrio(&fileInfo, tex->data, size, offset + sizeof(tex->header), 2) < (s32)size) {
        tww_free(tex->data);
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_READ;
        return tex->loadCode;
    }
    DVDClose(&fileInfo);

    tww_memset(&tex->_texObj, 0, sizeof(GXTexObj));
    GX_InitTexObj(&tex->_texObj, tex->data, tex->header.width, tex->header.height, fmt, GX_CLAMP,
                  GX_CLAMP, GX_FALSE);
    tex->loadCode = TexCode::TEX_OK;
    return tex->loadCode;
}

void free_texture(Texture* tex) {
    if (tex->data != nullptr) {
        tww_free(tex->data);
        tex->data = 0;
    }
    tww_memset(tex, 0, sizeof(Texture));
    // The next line is redundant, but is still there for good measure
    tex->loadCode = TexCode::TEX_UNLOADED;
}

void setupRendering() {
    GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);

    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GX_SetNumTexGens(1);
    GX_SetTexCoordGen2((u16)GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE,
                       GX_DTTIDENTITY);

    GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GX_SetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GX_SetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GX_SetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
}

#ifdef __cplusplus
}
#endif