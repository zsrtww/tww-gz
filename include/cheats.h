#ifndef LIB_TWW_CHEATS
#define LIB_TWW_CHEATS

#define CHEAT_AMNT 7

enum CheatId {
    InfiniteAir,
    InfiniteArrows,
    InfiniteBombs,
    InfiniteHearts,
    InfiniteMagic,
    InfiniteRupees,
    MoonJump
};

struct Cheat {
    enum CheatId id;
    bool active;
};

void GZ_applyCheats();

extern Cheat g_cheats[CHEAT_AMNT];

#endif