#include "cheats.h"
#include "commands.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/patch.h"
#include "libtww/include/defines.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

Cheat g_cheats[CHEAT_AMNT] = {
    {InfiniteAir, false},  {InfiniteArrows, false}, {InfiniteBombs, false},   {InfiniteHearts, false},
    {RefillHealth, false}, {InfiniteMagic, false},  {RefillMagic, false},     {InfiniteRupees, false},
    {MoonJump, false},     {StorageCheat, false},   {NormalCollision, false}, {ChestStorage, false},
    {DoorCancel, false},   {QuarterHeart, false},   {FastMovement, false},    {Upcharge, false},
};

inline bool GZ_checkCheat(int cheatIdx) {
    return g_cheats[cheatIdx].active;
}

void GZ_applyCheats() {
    if (GZ_checkCheat(MoonJump)) {
        GZCmd_enable(CMD_MOON_JUMP);
    } else {
        GZCmd_disable(CMD_MOON_JUMP);
    }

    if (GZ_checkCheat(StorageCheat)) {
        GZCmd_enable(CMD_STORAGE);
    } else {
        GZCmd_disable(CMD_STORAGE);
    }

    if (GZ_checkCheat(NormalCollision)) {
        GZCmd_enable(CMD_NORMAL_COLLISION);
    } else {
        GZCmd_disable(CMD_NORMAL_COLLISION);
    }

    if (GZ_checkCheat(ChestStorage)) {
        GZCmd_enable(CMD_CHEST_STORAGE);
    } else {
        GZCmd_disable(CMD_CHEST_STORAGE);
    }

    if (GZ_checkCheat(DoorCancel)) {
        GZCmd_enable(CMD_DOOR_CANCEL);
    } else {
        GZCmd_disable(CMD_DOOR_CANCEL);
    }

    if (GZ_checkCheat(QuarterHeart)) {
        GZCmd_enable(CMD_QUARTER_HEART);
    } else {
        GZCmd_disable(CMD_QUARTER_HEART);
    }

    if (GZ_checkCheat(FastMovement)) {
        GZCmd_enable(CMD_FAST_MOVEMENT);
    } else {
        GZCmd_disable(CMD_FAST_MOVEMENT);
    }

    if (GZ_checkCheat(Upcharge)) {
        GZCmd_enable(CMD_UPCHARGE);
    } else {
        GZCmd_disable(CMD_UPCHARGE);
    }

    if (GZ_checkCheat(InfiniteHearts)) {
        uint16_t max_life = dComIfGs_getMaxLife();
        uint16_t life = max_life - dComIfGs_getLife();
        dComIfGs_setLife(max_life);
        dComIfGp_setItemLifeCount(static_cast<f32>(life));
    }

    if (GZ_checkCheat(InfiniteMagic)) {
        uint8_t max_magic = dComIfGs_getMaxMagic();
        if (max_magic == 0)
            max_magic = 2;
        dComIfGs_setMagic(max_magic);
    }

    if (GZ_checkCheat(InfiniteAir)) {
        dComIfGp_setItemTimeCount(900);
    }

    if (GZ_checkCheat(InfiniteBombs)) {
        dComIfGs_setBombNum(99);
    }

    if (GZ_checkCheat(InfiniteRupees)) {
        u8 wallet_size = g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();

        switch (wallet_size) {
        case 0:
            g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(200);
            break;
        case 1:
            g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(1000);
            break;
        case 2:
            g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(5000);
            break;
        }
    }

    if (GZ_checkCheat(InfiniteArrows)) {
        dComIfGs_setArrowNum(99);
    }

    if (GZ_checkCheat(RefillHealth)) {
        GZCmd_enable(CMD_REFILL_HEALTH);
    } else {
        GZCmd_disable(CMD_REFILL_HEALTH);
    }

    if (GZ_checkCheat(RefillMagic)) {
        GZCmd_enable(CMD_REFILL_MAGIC);
    } else {
        GZCmd_disable(CMD_REFILL_MAGIC);
    }
}
