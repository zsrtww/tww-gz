#ifndef M_DO_EXT_H
#define M_DO_EXT_H

#include "../JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "../JSystem/J3DGraphBase/J3DTransform.h"
#include "../JSystem/J3DGraphBase/J3DTexture.h"
#include "../JSystem/J3DGraphBase/J3DJoint.h"
#include "../JSystem/J3DGraphBase/J3DMatBlock.h"
#include "../SSystem/SComponent/c_xyz.h"
#include "../JAZelAudio/JAIZelAnime.h"

class J3DTexMtxAnm;
class J3DMtxCalcMayaAnm;
class J3DMatColorAnm;
class J3DVisibilityManager;
class J3DModel;
class J3DTexNoAnm;
class mDoExt_zelAnime;
class dKy_tevstr_c;

class mDoExt_baseAnm {
public:
    mDoExt_baseAnm() { mFrameCtrl = NULL; }

    J3DFrameCtrl* getFrameCtrl() { return mFrameCtrl; }
    f32 getPlaySpeed() { return mFrameCtrl->getRate(); }
    void setPlaySpeed(f32 speed) { mFrameCtrl->setRate(speed); }
    f32 getFrame() { return mFrameCtrl->getFrame(); }
    f32 getEndFrame() { return mFrameCtrl->getEnd(); }
    void setFrame(f32 frame) { mFrameCtrl->setFrame(frame); }
    void setPlayMode(int i_mode) { mFrameCtrl->setAttribute(i_mode); }
    void setLoopFrame(f32 i_frame) { mFrameCtrl->setLoop(i_frame); }
    BOOL isStop() {
        bool stopped = true;
        if (!mFrameCtrl->checkState(J3DFrameCtrl::STATE_STOP_E) && mFrameCtrl->getRate() != 0.0f) {
            stopped = false;
        }
        return stopped;
    }
    BOOL isLoop() { return mFrameCtrl->checkState(J3DFrameCtrl::STATE_LOOP_E); }

    /* 0x0 */ void* vtable;
    /* 0x4 */ J3DFrameCtrl* mFrameCtrl;
};  // Size: 0x08

class mDoExt_btkAnm : public mDoExt_baseAnm {
public:
    mDoExt_btkAnm() { mpTexMtxAnm = NULL; }

    void entryFrame() { entryFrame(getFrame()); }
    void entryFrame(f32 frame) { mpAnm->setFrame(frame); }

    J3DAnmTextureSRTKey* getBtkAnm() const { return mpAnm; }

    /* 0x08 */ J3DAnmTextureSRTKey* mpAnm;
    /* 0x0C */ J3DTexMtxAnm* mpTexMtxAnm;
    /* 0x10 */ u16 mUpdateMaterialNum;
};  // Size: 0x14

static_assert(sizeof(mDoExt_btkAnm) == 0x14);

class J3DTevColorAnm;
class J3DTevKColorAnm;
class mDoExt_brkAnm : public mDoExt_baseAnm {
public:
    mDoExt_brkAnm() {
        mpCRegAnm = NULL;
        mpKRegAnm = NULL;
    }

    void entryFrame() { entryFrame(getFrame()); }
    void entryFrame(f32 frame) { mpAnm->setFrame(frame); }

    J3DAnmTevRegKey* getBrkAnm() const { return mpAnm; }

    /* 0x08 */ J3DAnmTevRegKey* mpAnm;
    /* 0x0C */ J3DTevColorAnm* mpCRegAnm;
    /* 0x10 */ J3DTevKColorAnm* mpKRegAnm;
    /* 0x14 */ u16 mCRegUpdateMaterialNum;
    /* 0x16 */ u16 mKRegUpdateMaterialNum;
};  // Size: 0x18

static_assert(sizeof(mDoExt_brkAnm) == 0x18);

class mDoExt_bckAnm : public mDoExt_baseAnm {
public:
    mDoExt_bckAnm() { mAnm = NULL; }

    J3DAnmTransform* getBckAnm() { return mAnmTransform; }

    /* 0x08 */ J3DAnmTransform* mAnmTransform;
    /* 0x0C */ J3DMtxCalcMayaAnm* mAnm;
};  // Size: 0x10

static_assert(sizeof(mDoExt_bckAnm) == 0x10);

class mDoExt_btpAnm : public mDoExt_baseAnm {
public:
    mDoExt_btpAnm() { field_0xc = NULL; }

    /* 0x08 */ J3DAnmTexPattern* mpAnm;
    /* 0x0C */ J3DTexNoAnm* field_0xc;
    /* 0x10 */ u16 mUpdateMaterialNum;
};

class mDoExt_blkAnm : public mDoExt_baseAnm {
public:
    J3DAnmCluster* getBlkAnm() { return mpAnm; }

    /* 0x14 */ J3DAnmCluster* mpAnm;
};

class mDoExt_bpkAnm : public mDoExt_baseAnm {
public:
    /* 0x08 */ J3DAnmColor* mpAnm;
    /* 0x0C */ J3DMatColorAnm* field_0xc;
    /* 0x10 */ u16 mUpdateMaterialNum;
};

class mDoExt_bvaAnm : public mDoExt_baseAnm {
public:
    /* 0x08 */ J3DAnmVisibilityFull* mpAnm;
    /* 0x0C */ J3DVisibilityManager* field_0xc;
};

class mDoExt_AnmRatioPack {
public:
    ~mDoExt_AnmRatioPack() {}
    mDoExt_AnmRatioPack() {
        mRatio = 0.0f;
        mAnmTransform = NULL;
    }

    void setRatio(f32 ratio) { mRatio = ratio; }
    f32 getRatio() { return mRatio; }
    J3DAnmTransform* getAnmTransform() { return mAnmTransform; }
    void setAnmTransform(J3DAnmTransform* anm) { mAnmTransform = anm; }

    /* 0x0 */ f32 mRatio;
    /* 0x4 */ J3DAnmTransform* mAnmTransform;
};  // Size: 0x8

class mDoExt_MtxCalcOldFrame {
public:
    mDoExt_MtxCalcOldFrame(J3DTransformInfo* param_1, Quaternion* param_2) {
        mOldFrameTransInfo = param_1;
        mOldFrameQuaternion = param_2;
        mOldFrameRate = 0.0f;
        mOldFrameFlg = false;
        field_0x1 = true;
        mOldFrameStartJoint = 0;
        mOldFrameEndJoint = 0;
        mOldFrameMorfCounter = 0.0f;
        field_0x8 = 0.0f;
        field_0x10 = 0.0f;
        field_0x14 = 0.0f;
    }

    bool getOldFrameFlg() { return mOldFrameFlg; }
    void onOldFrameFlg() { mOldFrameFlg = true; }
    f32 getOldFrameRate() { return mOldFrameRate; }
    J3DTransformInfo* getOldFrameTransInfo(int i) { return &mOldFrameTransInfo[i]; }
    u16 getOldFrameStartJoint() { return mOldFrameStartJoint; }
    u16 getOldFrameEndJoint() { return mOldFrameEndJoint; }
    Quaternion* getOldFrameQuaternion(int i_no) { return &mOldFrameQuaternion[i_no]; }

    /* 0x00 */ bool mOldFrameFlg;
    /* 0x01 */ bool field_0x1;
    /* 0x04 */ f32 mOldFrameMorfCounter;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 mOldFrameRate;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ u16 mOldFrameStartJoint;
    /* 0x1A */ u16 mOldFrameEndJoint;
    /* 0x1C */ J3DTransformInfo* mOldFrameTransInfo;
    /* 0x20 */ Quaternion* mOldFrameQuaternion;
};  // Size: 0x24

class mDoExt_McaMorfCallBack1_c {
public:
    void* vtable;
};

class mDoExt_McaMorfCallBack2_c {
public:
    void* vtable;
};

class mDoExt_McaMorf : public J3DMtxCalcMaya {
public:
    J3DModel* getModel() { return mpModel; }
    u8 getPlayMode() { return mFrameCtrl.getAttribute(); }
    void setPlayMode(int mode) { mFrameCtrl.setAttribute(mode); }
    f32 getStartFrame() { return mFrameCtrl.getStart(); }
    void setStartFrame(f32 frame) { mFrameCtrl.setStart(frame); }
    f32 getEndFrame() { return mFrameCtrl.getEnd(); }
    void setEndFrame(f32 frame) { mFrameCtrl.setEnd(frame); }
    f32 getLoopFrame() { return mFrameCtrl.getLoop(); }
    void setLoopFrame(f32 frame) { mFrameCtrl.setLoop(frame); }
    f32 getPlaySpeed() { return mFrameCtrl.getRate(); }
    void setPlaySpeed(f32 speed) { mFrameCtrl.setRate(speed); }
    f32 getFrame() { return mFrameCtrl.getFrame(); }
    void setFrame(f32 frame) { mFrameCtrl.setFrame((s16)frame); }
    BOOL isStop() { //regswap somewhere here
        bool stopped = true;
        if (!mFrameCtrl.checkState(J3DFrameCtrl::STATE_STOP_E) && mFrameCtrl.getRate() != 0.0f) {
            stopped = false;
        }
        return stopped;
    }

    /* 0x50 */ J3DModel* mpModel;
    /* 0x54 */ J3DAnmTransform* mpAnm;
    /* 0x58 */ J3DFrameCtrl mFrameCtrl;
    /* 0x6C */ J3DTransformInfo* mpTransformInfo;
    /* 0x70 */ Quaternion* mpQuat;
    /* 0x74 */ f32 mCurMorf;
    /* 0x78 */ f32 mPrevMorf;
    /* 0x7C */ f32 mMorfStep;
    /* 0x80 */ mDoExt_zelAnime* mpSound;
    /* 0x84 */ mDoExt_McaMorfCallBack1_c * mpCallback1;
    /* 0x88 */ mDoExt_McaMorfCallBack2_c * mpCallback2;
};

class mDoExt_McaMorf2 : public J3DMtxCalcMaya {
public:
    J3DModel* getModel() { return mpModel; }
    u8 getPlayMode() { return mFrameCtrl.getAttribute(); }
    void setPlayMode(int mode) { mFrameCtrl.setAttribute(mode); }
    f32 getStartFrame() { return mFrameCtrl.getStart(); }
    void setStartFrame(f32 frame) { mFrameCtrl.setStart(frame); }
    f32 getEndFrame() { return mFrameCtrl.getEnd(); }
    void setEndFrame(f32 frame) { mFrameCtrl.setEnd(frame); }
    f32 getLoopFrame() { return mFrameCtrl.getLoop(); }
    void setLoopFrame(f32 frame) { mFrameCtrl.setLoop(frame); }
    f32 getPlaySpeed() { return mFrameCtrl.getRate(); }
    void setPlaySpeed(f32 speed) { mFrameCtrl.setRate(speed); }
    f32 getFrame() { return mFrameCtrl.getFrame(); }
    void setFrame(f32 frame) { mFrameCtrl.setFrame((s16)frame); }
    BOOL isStop() { //regswap somewhere here
        bool stopped = true;
        if (!mFrameCtrl.checkState(J3DFrameCtrl::STATE_STOP_E) && mFrameCtrl.getRate() != 0.0f) {
            stopped = false;
        }
        return stopped;
    }

    BOOL isMorf() { return field_0x78 < 1.0f; }

    /* 0x50 */ J3DModel* mpModel;
    /* 0x54 */ J3DAnmTransform* field_0x54;
    /* 0x58 */ J3DAnmTransform* field_0x58;
    /* 0x5C */ int field_0x5c;
    /* 0x60 */ int field_0x60;
    /* 0x64 */ J3DFrameCtrl mFrameCtrl;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7c;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ mDoExt_zelAnime* mpSound;
    /* 0x8C */ mDoExt_McaMorfCallBack1_c * mpCallback1;
    /* 0x90 */ mDoExt_McaMorfCallBack2_c * mpCallback2;
};

class mDoExt_3DlineMat_c {
public:
    /* 0x0 */ void* field_0x0;
    /* 0x4 */ mDoExt_3DlineMat_c* field_0x4;
};

class mDoExt_3DlineMatSortPacket : public J3DPacket {
public:
    mDoExt_3DlineMatSortPacket() { mp3DlineMat = NULL; }

    void reset() { mp3DlineMat = NULL; }

    void setMat(mDoExt_3DlineMat_c* pMat) { mp3DlineMat = pMat; }

private:
    /* 0x10 */ mDoExt_3DlineMat_c* mp3DlineMat;
};

class mDoExt_invJntPacket : public J3DPacket {
public:
    void setJoint(J3DModel* i_model, u16 param_1) {
        mModel = i_model;
        field_0x14 = param_1;
    }

    J3DModel* mModel;
    u16 field_0x14;
};

class mDoExt_invisibleModel {
public:

    J3DModel* mModel;
    mDoExt_invJntPacket* mpPackets;
};

class mDoExt_offCupOnAupPacket : public J3DPacket {
public:
};

class mDoExt_onCupOffAupPacket : public J3DPacket {
public:
};

class mDoExt_3Dline_c {
public:
    /* 0x00 */ cXyz* mpSegments;
    /* 0x04 */ u8* mpSize;
    /* 0x08 */ cXyz* mPosArr[2];
    /* 0x10 */ f32* mTexArr[2][2];
};

class mDoExt_3DlineMat0_c {
public:
};

class mDoExt_3DlineMat1_c {
public:
    /* 0x00 */ mDoExt_3DlineMat_c parent;
    /* 0x08 */ GXTexObj mTexObj;
    /* 0x28 */ GXColor mColor;
    /* 0x2C */ dKy_tevstr_c* mpTevStr;
    /* 0x30 */ u16 mNumLines;
    /* 0x32 */ u16 m32;
    /* 0x34 */ u16 m34;
    /* 0x36 */ u8 mCurArr;
    /* 0x37 */ u8 m37[0x38 - 0x37];
    /* 0x38 */ mDoExt_3Dline_c* mpLines;
};

namespace m_Do_ext {
extern "C" {
extern JKRHeap* gameHeap;
extern JKRHeap* zeldaHeap;
extern JKRHeap* commandHeap;
extern JKRHeap* archiveHeap;  // Archive heap pointer
}
}  // namespace m_Do_ext

#endif