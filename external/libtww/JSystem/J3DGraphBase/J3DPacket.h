#ifndef J3DPACKET_H
#define J3DPACKET_H

#include "../../dolphin/gctypes.h"

class J3DPacket {
public:
    J3DPacket() {
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
    /* 0x00 */ void* vtable;
    /* 0x04 */ J3DPacket* mpNextPacket;
    /* 0x08 */ J3DPacket* mpFirstChild;
    /* 0x0C */ void* mpUserData;
};  // Size: 0x10

#endif