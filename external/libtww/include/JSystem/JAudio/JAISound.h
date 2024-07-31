#ifndef JAISOUND_H
#define JAISOUND_H

#include "../../dolphin/gctypes.h"

class JAISound;
LIBTWW_DEFINE_FUNC(setVolume__8JAISoundFfUlUc,
                  void, JAISound__setVolume, (JAISound*, f32, u32, u8))


namespace JAInter {
    class Actor;
    class SeParameter;
    class SeqParameter;
    class StreamParameter;
}

class JAISound {
public:
    void setVolume(f32 param_0, u32 param_1, u8 param_2) {
        JAISound__setVolume(this, param_0, param_1, param_2);
    }

    struct PositionInfo_t {
        f32 field_0x0;
        u8 field_0x4[0x8 - 0x4];
        f32 field_0x8;
        u8 field_0xc[0x18 - 0xc];
        f32 field_0x18;
    };

    /* 0x00 */ void* vtable;
    /* 0x04 */ u8 field_0x4;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0a */ short field_0xa;
    /* 0x0c */ int field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ int field_0x18;
    /* 0x1c */ int field_0x1c;
    /* 0x20 */ PositionInfo_t* mPositionInfo;
    /* 0x24 */ void* field_0x24;
    /* 0x28 */ int field_0x28;
    /* 0x2C */ int field_0x2c;
    /* 0x30 */ JAISound* field_0x30;
    /* 0x34 */ JAISound* field_0x34;
    /* 0x38 */ JAISound** field_0x38;
    /* 0x3C */ void* field_0x3c;
    /* 0x40 */ void* field_0x40;
};

#endif /* JAISOUND_H */
