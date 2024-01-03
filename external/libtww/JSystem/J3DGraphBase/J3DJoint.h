#ifndef J3DJOINT_H
#define J3DJOINT_H

#include "../../dolphin/mtx/mtx.h"
#include "../../dolphin/mtx/vec.h"
#include "J3DTransform.h"
#include "J3DNode.h"

class J3DAnmTransform;
class J3DJoint;
class J3DMaterial;
class J3DMtxBuffer;

class J3DMtxCalc {
public:
    void initAnm() {
        for (int i = 0; i < 4; i++) {
            mOne[i] = 0;
            mTwo[i] = 0.0f;
        }
    }
    void setAnmTransform(J3DAnmTransform* mAnmTransform) { mOne[0] = mAnmTransform; }

public:
    void* vtable;
    J3DAnmTransform* mOne[4];
    f32 mTwo[4];
};

class J3DMtxCalcAnm : public J3DMtxCalc {
public:
};

class J3DMtxCalcBasic : public J3DMtxCalc {
private:
    Mtx mBackupMtx;
    Vec mBackupS;
    Vec mBackupParentS;

public:
    Mtx& getBackupMtx() { return mBackupMtx; }
    Vec& getBackupS() { return mBackupS; }
    Vec& getBackupParentS() { return mBackupParentS; }

    void setBackupS(const Vec& vec) { mBackupS = vec; }
    void setBackupParentS(const Vec& vec) { mBackupParentS = vec; }
};

class J3DMtxCalcSoftimage : public J3DMtxCalcBasic {
public:
};

class J3DMtxCalcMaya : public J3DMtxCalcBasic {
public:
};

class J3DMtxCalcMayaAnm : public J3DMtxCalcMaya, public J3DMtxCalcAnm {
public:
};

enum J3DJointMtxType {
    J3DJntMtxType_Normal,
    J3DJntMtxType_BBoard,
    J3DJntMtxType_YBBoard,
    J3DJntMtxType_Multi,
};

class J3DJoint : public J3DNode {
public:
    J3DMaterial* getMesh() { return mMesh; }
    u16 getJntNo() const { return mJntNo; }
    u8 getKind() const { return mKind & 0x0F; }
    u8 getMtxType() const { return (mKind >> 4) & 0x0F; }
    u8 getScaleCompensate() const { return mScaleCompensate; }
    J3DTransformInfo& getTransformInfo() { return mTransformInfo; }
    Vec* getMax() { return &mMax; }
    Vec* getMin() { return &mMin; }
    void setMtxCalc(J3DMtxCalc* i_mtxCalc) { mMtxCalc = i_mtxCalc; }
    J3DMtxCalc* getMtxCalc() { return mMtxCalc; }
    void setOldMtxCalc(J3DMtxCalc* i_mtxCalc) { mOldMtxCalc = i_mtxCalc; }
    J3DMtxCalc* getOldMtxCalc() { return mOldMtxCalc; }

private:
    friend struct J3DJointFactory;
    friend class J3DJointTree;

    /* 0x18 */ u16 mJntNo;
    /* 0x1A */ u8 mKind;
    /* 0x1B */ u8 mScaleCompensate;
    /* 0x1C */ J3DTransformInfo mTransformInfo;
    /* 0x3C */ f32 mRadius;
    /* 0x40 */ Vec mMin;
    /* 0x4C */ Vec mMax;
    /* 0x58 */ J3DMtxCalc* mMtxCalc;
    /* 0x5C */ J3DMtxCalc* mOldMtxCalc;
    /* 0x60 */ J3DMaterial* mMesh;
};  // Size: 0x64

#endif /* J3DJOINT_H */