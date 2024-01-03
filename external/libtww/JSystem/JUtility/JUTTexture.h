#ifndef JUTTEXTURE_H
#define JUTTEXTURE_H

#include "../../dolphin/gctypes.h"

class JUTPalette;

/*
 * Acts as the header to image data. Usually texture data immediately follows it,
 * so any pointer arithmetic to go past the end of this structure is so that a
 * variable sized allocated buffer can be accessed.
 */
struct ResTIMG {
    /* 0x00 */ u8 format;
    /* 0x01 */ u8 alphaEnabled;
    /* 0x02 */ u16 width;
    /* 0x04 */ u16 height;
    /* 0x06 */ u8 wrapS;
    /* 0x07 */ u8 wrapT;
    /* 0x08 */ u8 indexTexture;
    /* 0x09 */ u8 colorFormat;
    /* 0x0A */ u16 numColors;
    /* 0x0C */ u32 paletteOffset;
    /* 0x10 */ u8 mipmapEnabled;
    /* 0x11 */ u8 doEdgeLOD;
    /* 0x12 */ u8 biasClamp;
    /* 0x13 */ u8 maxAnisotropy;
    /* 0x14 */ u8 minFilter;
    /* 0x15 */ u8 magFilter;
    /* 0x16 */ s8 minLOD;
    /* 0x17 */ s8 maxLOD;
    /* 0x18 */ u8 mipmapCount;
    /* 0x19 */ u8 unknown;
    /* 0x1A */ s16 LODBias;
    /* 0x1C */ u32 imageOffset;
};  // Size: 0x20

#endif /* JUTTEXTURE_H */