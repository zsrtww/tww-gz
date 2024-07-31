#ifndef JAIBASIC_H
#define JAIBASIC_H

#include "JAISound.h"
#include "../../dolphin/mtx/vec.h"

class JKRSolidHeap;

namespace JAInter {
    class Actor;
    class Camera;
}

namespace JASystem {
    class TTrack;
}

class JAIBasic {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ JAInter::Camera* mAudioCamera;
    /* 0x08 */ JKRSolidHeap* field_0x8;
    /* 0x0C */ u8 initLoadFileSw;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ struct {
        u8 flag1 : 1;
        u8 flag2 : 1;
        u8 flag3 : 1;
        u8 flag4 : 1;
        u8 flag5 : 1;
        u8 flag6 : 1;
        u8 flag7 : 1;
        u8 flag8 : 1;
    } field_0xe;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ int field_0x14;
    /* 0x18 */ void* field_0x18;
    /* 0x1C */ u8** field_0x1c;
};

#endif /* JAIBASIC_H */
