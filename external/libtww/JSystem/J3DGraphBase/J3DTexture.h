#ifndef J3DTEXTURE_H
#define J3DTEXTURE_H

#include "../../dolphin/gctypes.h"
#include "../../dolphin/mtx/mtx.h"
#include "../JUtility/JUTTexture.h"
#include "J3DStruct.h"

class J3DTexture {
private:
    /* 0x0 */ u16 mNum;
    /* 0x4 */ ResTIMG* mpRes;
    /* 0x8 */ void* vtable;

public:
    u16 getNum() const { return mNum; }
    ResTIMG* getResTIMG(u16 entry) const { return &mpRes[entry]; }
    void setResTIMG(u16 entry, const ResTIMG& timg) {
        mpRes[entry] = timg;
        mpRes[entry].imageOffset = ((mpRes[entry].imageOffset + (u32)&timg - (u32)(mpRes + entry)));
        mpRes[entry].paletteOffset = ((mpRes[entry].paletteOffset + (u32)&timg - (u32)(mpRes + entry)));
    }
};

class J3DTexMtx {
public:
    J3DTexMtxInfo& getTexMtxInfo() { return mTexMtxInfo; }
    Mtx& getMtx() { return mMtx; }
    Mtx& getViewMtx() { return mViewMtx; }

private:
    /* 0x00 */ J3DTexMtxInfo mTexMtxInfo;
    /* 0x64 */ Mtx mMtx;
    /* 0x94 */ Mtx mViewMtx;
};  // Size: 0xc4

struct J3DTexCoord : public J3DTexCoordInfo {
    u8 getTexGenType() { return mTexGenType; }
    u8 getTexGenSrc() { return mTexGenSrc; }
    u32 getTexGenMtx() { return mTexGenMtx & 0xFF; }
    void setTexGenMtx(u8 v) { mTexGenMtx = v; }
};  // Size: 0x4

#endif /* J3DTEXTURE_H */