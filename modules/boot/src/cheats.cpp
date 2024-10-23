#include "cheats.h"
#include "commands.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "rels/include/patch.h"
#include "libtww/include/defines.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

void GZ_applyCheats() {
    if (GZ_checkCheat(STNG_CHEATS_MOON_JUMP)) {
        GZCmd_enable(CMD_MOON_JUMP);
    } else {
        GZCmd_disable(CMD_MOON_JUMP);
    }

    if (GZ_checkCheat(STNG_CHEATS_STORAGE)) {
        GZCmd_enable(CMD_STORAGE);
    } else {
        GZCmd_disable(CMD_STORAGE);
    }

    if (GZ_checkCheat(STNG_CHEATS_NORMAL_COLLISION)) {
        GZCmd_enable(CMD_NORMAL_COLLISION);
    } else {
        GZCmd_disable(CMD_NORMAL_COLLISION);
    }

    if (GZ_checkCheat(STNG_CHEATS_CHEST_STORAGE)) {
        GZCmd_enable(CMD_CHEST_STORAGE);
    } else {
        GZCmd_disable(CMD_CHEST_STORAGE);
    }

    if (GZ_checkCheat(STNG_CHEATS_DOOR_CANCEL)) {
        GZCmd_enable(CMD_DOOR_CANCEL);
    } else {
        GZCmd_disable(CMD_DOOR_CANCEL);
    }

    if (GZ_checkCheat(STNG_CHEATS_QUARTER_HEART)) {
        GZCmd_enable(CMD_QUARTER_HEART);
    } else {
        GZCmd_disable(CMD_QUARTER_HEART);
    }

    if (GZ_checkCheat(STNG_CHEATS_FAST_MOVEMENT)) {
        GZCmd_enable(CMD_FAST_MOVEMENT);
    } else {
        GZCmd_disable(CMD_FAST_MOVEMENT);
    }

    if (GZ_checkCheat(STNG_CHEATS_UPCHARGE)) {
        GZCmd_enable(CMD_UPCHARGE);
    } else {
        GZCmd_disable(CMD_UPCHARGE);
    }

    if (GZ_checkCheat(STNG_CHEATS_INFINITE_HEARTS)) {
        uint16_t max_life = dComIfGs_getMaxLife();
        uint16_t life = max_life - dComIfGs_getLife();
        dComIfGs_setLife(max_life);
        dComIfGp_setItemLifeCount(static_cast<f32>(life));
    }

    if (GZ_checkCheat(STNG_CHEATS_INFINITE_MAGIC)) {
        uint8_t max_magic = dComIfGs_getMaxMagic();
        if (max_magic == 0)
            max_magic = 2;
        dComIfGs_setMagic(max_magic);
    }

    if (GZ_checkCheat(STNG_CHEATS_INFINITE_AIR)) {
        dComIfGp_setItemTimeCount(900);
    }

    if (GZ_checkCheat(STNG_CHEATS_INFINITE_BOMBS)) {
        dComIfGs_setBombNum(99);
    }

    if (GZ_checkCheat(STNG_CHEATS_INFINITE_RUPEES)) {
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

    if (GZ_checkCheat(STNG_CHEATS_INFINITE_ARROWS)) {
        dComIfGs_setArrowNum(99);
    }

    if (GZ_checkCheat(STNG_CHEATS_REFILL_HEALTH)) {
        GZCmd_enable(CMD_REFILL_HEALTH);
    } else {
        GZCmd_disable(CMD_REFILL_HEALTH);
    }

    if (GZ_checkCheat(STNG_CHEATS_REFILL_MAGIC)) {
        GZCmd_enable(CMD_REFILL_MAGIC);
    } else {
        GZCmd_disable(CMD_REFILL_MAGIC);
    }
}
