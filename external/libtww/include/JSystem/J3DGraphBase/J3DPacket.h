#ifndef J3DPACKET_H
#define J3DPACKET_H

#include "../../dolphin/gctypes.h"
#include "../../defines.h"

class J3DDrawBuffer;
class J3DPacket;
class J3DMatPacket;

class J3DDrawBuffer {
public:
    /* 0x00 */ J3DPacket** mpBuf;
    /* 0x04 */ u32 mBufSize;
    /* 0x08 */ u32 mDrawType;
    /* 0x0C */ u32 mSortType;
    /* 0x10 */ f32 mZNear;
    /* 0x14 */ f32 mZFar;
    /* 0x18 */ f32 mZRatio;
    /* 0x1C */ MtxP mpZMtx;
    /* 0x20 */ J3DPacket* mpCallBackPacket;
};

LIBTWW_DEFINE_FUNC(entryImm__13J3DDrawBufferFP9J3DPacketUs,
                  bool, J3DDrawBuffer__entryImm, (J3DDrawBuffer*, J3DPacket* packet, u16))

extern "C" int entry__9J3DPacketFP13J3DDrawBuffer(J3DPacket*, J3DDrawBuffer*);
#define J3DPacket__entry entry__9J3DPacketFP13J3DDrawBuffer

extern "C" int isSame__9J3DPacketCFP12J3DMatPacket(J3DPacket*, J3DMatPacket*);
#define J3DPacket__isSame isSame__9J3DPacketCFP12J3DMatPacket

struct J3DPacket__vtable_t {
    void* rtti;
    void* padding;
    void* isSame;
    void* entry;
    void* draw;
    void* dtor;
};

extern "C" J3DPacket__vtable_t __vt__9J3DPacket;
#define J3DPacket__vtable __vt__9J3DPacket

class J3DPacket {
public:
    J3DPacket() {
        vtable = &J3DPacket__vtable;
        mpNextPacket = NULL;
        mpFirstChild = NULL;
        mpUserData = NULL;
    }
    
    J3DPacket* getNextPacket() const { return mpNextPacket; }
    void setNextPacket(J3DPacket* i_packet) { mpNextPacket = i_packet; }

    void drawClear() {
        mpNextPacket = NULL;
        mpFirstChild = NULL;
    }

    void setUserArea(u32 area) { mpUserData = (void*)area; }
    u32 getUserArea() const { return (u32)mpUserData; }

public:
    /* 0x00 */ J3DPacket__vtable_t* vtable;
    /* 0x04 */ J3DPacket* mpNextPacket;
    /* 0x08 */ J3DPacket* mpFirstChild;
    /* 0x0C */ void* mpUserData;
};  // Size: 0x10

#endif