#include "controller.h"
#include "menus/main_menu.h"
#include "menus/amount_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"

#define LINE_NUM 6

Cursor AmountMenu::cursor;

Line lines[LINE_NUM] = {
    {"health:", HEALTH_INDEX, "Modifies the current health by quarter"},
    {"bombs:", BOMB_INDEX, "Current bomb count"},
    {"arrows:", ARROW_INDEX, "Current arrow count"},
    {"rupee:", RUPEE_INDEX, "Current rupee count"},
    {"magic:", MAGIC_INDEX, "Modifies current magic amount"},
    {"heart piece:", HEART_PIECE_INDEX, "Current heart pieces collected"},
};

void AmountMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    u8 g_healthNum = g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().getLife();
    u8 g_bombNum = g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemRecord().getBombNum();
    u8 g_arrowNum = g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemRecord().getArrowNum();
    u16 g_rupeeNum = g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().getRupee();
    u8 g_magicNum = g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().getMagic();
    u8 g_heartNum = g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().getMaxLife();

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
            g_healthNum = 1; //Quarter heart health
        }
        if (GZ_getButtonTrig(GZPad::R)) {
            g_healthNum = (g_heartNum / 4) * 4; //Maximum available health
        }
        if (g_healthNum < 1) {
            g_healthNum = 1; //Don't allow the player to go under 1 quarter heart
        }
        g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().setLife(g_healthNum);
        break;
    case BOMB_INDEX:
        Cursor::moveList(g_bombNum);
        if (g_bombNum > 99) {
            g_bombNum = 0;
        }
        g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemRecord().setBombNum(g_bombNum);
        break;
    case ARROW_INDEX:
        Cursor::moveList(g_arrowNum);
        if (g_arrowNum > 99) {
            g_arrowNum = 0;
        }
        g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemRecord().setArrowNum(g_arrowNum);
        break;
    case RUPEE_INDEX:
        Cursor::moveList(g_rupeeNum);
        if (g_rupeeNum == 0xFFFF) {
            g_rupeeNum = 5000;
        }
        if (g_rupeeNum > 5000) {
            g_rupeeNum = 0;
        }
        g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().setRupee(g_rupeeNum);
        break;
    case MAGIC_INDEX:
        Cursor::moveList(g_magicNum);
        if (g_magicNum == 0xFF) {
            g_magicNum = 32;
        }
        if (g_magicNum > 32) {
            g_magicNum = 0;
        }
        g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().setMagic(g_magicNum);
        break;
    case HEART_PIECE_INDEX:
        Cursor::moveList(g_heartNum);
        g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().setMaxLife(g_heartNum);
        break;
    }

    tww_sprintf(lines[HEALTH_INDEX].value, " <%d>", g_healthNum);
    tww_sprintf(lines[BOMB_INDEX].value, " <%d>", g_bombNum);
    tww_sprintf(lines[ARROW_INDEX].value, " <%d>", g_arrowNum);
    tww_sprintf(lines[RUPEE_INDEX].value, " <%d>", g_rupeeNum);
    tww_sprintf(lines[MAGIC_INDEX].value, " <%d>", g_magicNum);
    tww_sprintf(lines[HEART_PIECE_INDEX].value, " <%d>", g_heartNum);

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
