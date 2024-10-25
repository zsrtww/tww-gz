#ifndef LIB_TWW_CHEATS
#define LIB_TWW_CHEATS

#include "settings.h"

#define CHEAT_AMNT 17

enum CheatId {
    InfiniteAir,
    InfiniteArrows,
    InfiniteBombs,
    InfiniteHearts,
    RefillHealth,
    InfiniteMagic,
    RefillMagic,
    InfiniteRupees,
    MoonJump,
    StorageCheat,
    NormalCollision,
    ChestStorage,
    DoorCancel,
    QuarterHeart,
    FastMovement,
    Upcharge,
    Hoverboots,
};

struct Cheat {
    enum CheatId id;
    bool active;
};

void GZ_applyCheats();

inline bool GZ_checkCheat(GZSettingID cheatIdx) {
    return GZStng_getData(cheatIdx, false);
}

#endif