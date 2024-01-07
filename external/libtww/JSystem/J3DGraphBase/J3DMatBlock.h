#ifndef J3DMATBLOCK_H
#define J3DMATBLOCK_H

#include "J3DStruct.h"
#include "J3DTexture.h"

struct J3DGXColorS10 {
    J3DGXColorS10() {}
    J3DGXColorS10(J3DGXColorS10& other) { mColor = other.mColor; }
    J3DGXColorS10& operator=(const J3DGXColorS10& other) {
        mColor = other.mColor;
        return *this;
    }
    J3DGXColorS10& operator=(const GXColorS10& color) {
        mColor = color;
        return *this;
    }

    GXColorS10 mColor;
};

struct J3DGXColor {
    J3DGXColor() {}
    J3DGXColor(J3DGXColor& other) { mColor = other.mColor; }
    J3DGXColor& operator=(const J3DGXColor& other) {
        mColor = other.mColor;
        return *this;
    }
    J3DGXColor& operator=(const GXColor& color) {
        mColor = color;
        return *this;
    }

    GXColor mColor;
};

struct J3DZMode {
    /* 0x0 */ u16 mZModeID;
};

struct J3DBlend : public J3DBlendInfo {
    void setType(u8 i_type) {
        mBlendMode = i_type;
    }

    void setSrcFactor(u8 i_src) {
        mSrcFactor = i_src;
    }

    void setDstFactor(u8 i_dst) {
        mDstFactor = i_dst;
    }
};


struct J3DFog : public J3DFogInfo {
};

struct J3DAlphaCompInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 mRef0;
    /* 0x3 */ u8 mRef1;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
};

struct J3DAlphaComp {
    /* 0x00 */ u16 mAlphaCmpID;
    /* 0x02 */ u8 mRef0;
    /* 0x03 */ u8 mRef1;
};  // Size: 0x4

struct J3DIndTexCoordScale : public J3DIndTexCoordScaleInfo {
    u8 getScaleS() { return mScaleS; }
    u8 getScaleT() { return mScaleT; }
};

struct J3DIndTexMtx : public J3DIndTexMtxInfo {
    Mtx3P getOffsetMtx() {
        return mOffsetMtx;
    }

    void setScaleExp(s8 i_scaleExp) {
        mScaleExp = i_scaleExp;
    }
};  // Size: 0x1C

struct J3DIndTexOrder : public J3DIndTexOrderInfo {
    u8 getCoord() const { return mCoord; }
    u8 getMap() const { return mMap; }
};

struct J3DColorChan {
    /* 0x0 */ u16 mChanCtrl;
};

#endif /* J3DMATBLOCK_H */