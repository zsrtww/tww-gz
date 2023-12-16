#include "controller.h"
#include "menus/main_menu.h"
#include "menus/quest_status_menu.h"
#include "menus/amount_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"

#define LINE_NUM 14

Cursor AmountMenu::cursor;

Line lines[LINE_NUM] = {
    {"health:", HEALTH_INDEX, "Modify the current health by quarter"},
    {"bombs:", BOMB_INDEX, "Modify the current bomb count"},
    {"arrows:", ARROW_INDEX, "Modify the current arrow count"},
    {"rupees:", RUPEE_INDEX, "Modify the current rupee count"},
    {"magic:", MAGIC_INDEX, "Modify the current magic amount"},
    {"heart pieces:", HEART_PIECE_INDEX, "Modify the current heart pieces collected"},
    {"joy pendants:", JOY_PENDANT_INDEX, "Modify the current joy pendant count"},
    {"skull necklaces:", SKULL_NECKLACE_INDEX, "Modify the current skull necklace count"},
    {"boko baba seeds:", BOKO_BABA_SEED_INDEX, "Modify the current boko baba seed count"},
    {"golden feathers:", GOLDEN_FEATHER_INDEX, "Modify the current golden feather count"},
    {"knights crests:", KNIGHTS_CREST_INDEX, "Modify the current knights crest count"},
    {"red chu jelly:", RED_CHU_JELLY_INDEX, "Modify the current red chu jelly count"},
    {"green chu jelly:", GREEN_CHU_JELLY_INDEX, "Modify the current green chu jelly count"},
    {"blue chu jelly:", BLUE_CHU_JELLY_INDEX, "Modify the current blue chu jelly count"},

};

void updateSpoilsBagAmount(u8 index) {
    u8 amount = dComIfGs_getBeastNum(index);
    Cursor::moveListSimple(amount);
    if (amount == 0xFF) {
        amount = 99;
    }
    if (amount > 99) {
        amount = 0;    
    }
    dComIfGs_setBeastNum(index, amount);
}

void AmountMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    u16 g_healthNum = dComIfGs_getLife();
    u8 g_bombNum = dComIfGs_getBombNum();
    u8 g_arrowNum = dComIfGs_getArrowNum();
    u16 g_rupeeNum = g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getRupee();
    u8 g_magicNum = dComIfGs_getMagic();
    u16 g_heartNum = dComIfGs_getMaxLife();
    u8 g_maxMagicNum = dComIfGs_getMaxMagic();
    u8 g_walletSize = g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();

    u16 max_rupees;
    switch (g_walletSize) {
    case WALLET_200:
        max_rupees = 200;
        break;
    case WALLET_1000:
        max_rupees = 1000;
        break;
    case WALLET_5000:
        max_rupees = 5000;
        break;
    default:
        max_rupees = 200;
        break;
    }

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
        return;
    }

    /*
     * Made it so if it's more than the maximum or if
     * the player sets it to less than 0, wrap to maximum
     * or back to 0 in some cases
     */
    switch (cursor.y) {
    case HEALTH_INDEX:
        Cursor::moveList(g_healthNum);
        if (GZ_getButtonTrig(GZPad::A)) {
            g_healthNum = 1;  // Quarter heart health
        }
        if (GZ_getButtonTrig(GZPad::R)) {
            g_healthNum = g_heartNum;  // Maximum available health
        }
        if (g_healthNum < 1) {
            g_healthNum = 1;  // Don't allow the player to go under 1 quarter heart
        }
        dComIfGs_setLife(g_healthNum);
        break;
    case BOMB_INDEX:
        Cursor::moveList(g_bombNum);
        if (g_bombNum == 0xFF) {
            g_bombNum = 99;
        }
        if (g_bombNum > 99) {
            g_bombNum = 0;
        }
        dComIfGs_setBombNum(g_bombNum);
        break;
    case ARROW_INDEX:
        Cursor::moveList(g_arrowNum);
        if (g_arrowNum == 0xFF) {
            g_arrowNum = 99;
        }
        if (g_arrowNum > 99) {
            g_arrowNum = 0;
        }
        dComIfGs_setArrowNum(g_arrowNum);
        break;
    case RUPEE_INDEX:
        Cursor::moveList(g_rupeeNum);
        if (g_rupeeNum == 0xFFFF) {
            g_rupeeNum = max_rupees;
        }
        if (g_rupeeNum > max_rupees) {
            g_rupeeNum = 0;
        }
        g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(g_rupeeNum);
        break;
    case MAGIC_INDEX:
        Cursor::moveList(g_magicNum);
        if (g_magicNum == 0xFF) {
            g_magicNum = g_maxMagicNum;
        }
        if (g_magicNum > g_maxMagicNum) {
            g_magicNum = 0;
        }
        dComIfGs_setMagic(g_magicNum);
        break;
    case HEART_PIECE_INDEX:
        Cursor::moveList(g_heartNum);
        if (g_heartNum < 12) {
            g_heartNum = 12;
        }
        dComIfGs_setMaxLife(g_heartNum);
        break;
    case JOY_PENDANT_INDEX:
        updateSpoilsBagAmount(7);
        break;
    case SKULL_NECKLACE_INDEX:
        updateSpoilsBagAmount(0);
        break;
    case BOKO_BABA_SEED_INDEX:
        updateSpoilsBagAmount(1);
        break;
    case GOLDEN_FEATHER_INDEX:
        updateSpoilsBagAmount(2);
        break;
    case KNIGHTS_CREST_INDEX:
        updateSpoilsBagAmount(3);
        break;
    case RED_CHU_JELLY_INDEX:
        updateSpoilsBagAmount(4);
        break;
    case GREEN_CHU_JELLY_INDEX:
        updateSpoilsBagAmount(5);
        break;
    case BLUE_CHU_JELLY_INDEX:
        updateSpoilsBagAmount(6);
        break;
    }

    tww_sprintf(lines[HEALTH_INDEX].value, " <%d>", g_healthNum);
    tww_sprintf(lines[BOMB_INDEX].value, " <%d>", g_bombNum);
    tww_sprintf(lines[ARROW_INDEX].value, " <%d>", g_arrowNum);
    tww_sprintf(lines[RUPEE_INDEX].value, " <%d>", g_rupeeNum);
    tww_sprintf(lines[MAGIC_INDEX].value, " <%d>", g_magicNum);
    tww_sprintf(lines[HEART_PIECE_INDEX].value, " <%d>", g_heartNum);
    tww_sprintf(lines[JOY_PENDANT_INDEX].value, " <%d>", dComIfGs_getBeastNum(7));
    tww_sprintf(lines[SKULL_NECKLACE_INDEX].value, " <%d>", dComIfGs_getBeastNum(0));
    tww_sprintf(lines[BOKO_BABA_SEED_INDEX].value, " <%d>", dComIfGs_getBeastNum(1));
    tww_sprintf(lines[GOLDEN_FEATHER_INDEX].value, " <%d>", dComIfGs_getBeastNum(2));
    tww_sprintf(lines[KNIGHTS_CREST_INDEX].value, " <%d>", dComIfGs_getBeastNum(3));
    tww_sprintf(lines[RED_CHU_JELLY_INDEX].value, " <%d>", dComIfGs_getBeastNum(4));
    tww_sprintf(lines[GREEN_CHU_JELLY_INDEX].value, " <%d>", dComIfGs_getBeastNum(5));
    tww_sprintf(lines[BLUE_CHU_JELLY_INDEX].value, " <%d>", dComIfGs_getBeastNum(6));

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
