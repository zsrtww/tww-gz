#ifndef JUTNAMETAB_H
#define JUTNAMETAB_H

#include "../../dolphin/gctypes.h"

struct ResNTAB {
    u16 mEntryNum;
    u16 mPad0;
    struct Entry {
        u16 mKeyCode;
        u16 mOffs;
    } mEntries[1];

    inline const char* getName(u32 index) const {
        return ((const char*)mEntries) + mEntries[index].mOffs - 4;
    }
};

class JUTNameTab {
public:
    const ResNTAB* getResNameTable() const { return mNameTable; }

private:
    /* 0x0 */ void* vtable;
    /* 0x4 */ const ResNTAB* mNameTable;
    /* 0x8 */ const char* mpStrData;
    /* 0xC */ u16 mNameNum;
};

#endif /* JUTNAMETAB_H */