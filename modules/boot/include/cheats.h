#ifndef LIB_TWW_CHEATS
#define LIB_TWW_CHEATS

#define CHEAT_AMNT 16

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
};

struct Cheat {
    enum CheatId id;
    bool active;
};

void GZ_applyCheats();

extern Cheat g_cheats[CHEAT_AMNT];

#endif