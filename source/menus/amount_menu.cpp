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

    u16 g_healthNum = dComIfGs_getLife();
    u8 g_bombNum = dComIfGs_getBombNum();
    u8 g_arrowNum = dComIfGs_getArrowNum();
    u16 g_rupeeNum = dComIfGs_getRupee();
    u8 g_magicNum = dComIfGs_getMagic();
    u16 g_heartNum = dComIfGs_getMaxLife();

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
            g_healthNum = g_heartNum; //Maximum available health
        }
        if (g_healthNum < 1) {
            g_healthNum = 1; //Don't allow the player to go under 1 quarter heart
        }
        dComIfGs_setLife(g_healthNum);
        break;
    case BOMB_INDEX:
        Cursor::moveList(g_bombNum);
        if (g_bombNum > 99) {
            g_bombNum = 0;
        }
        dComIfGs_setBombNum(g_bombNum);
        break;
    case ARROW_INDEX:
        Cursor::moveList(g_arrowNum);
        if (g_arrowNum > 99) {
            g_arrowNum = 0;
        }
        dComIfGs_setArrowNum(g_arrowNum);
        break;
    case RUPEE_INDEX:
        Cursor::moveList(g_rupeeNum);
        if (g_rupeeNum == 0xFFFF) {
            g_rupeeNum = 5000;
        }
        if (g_rupeeNum > 5000) {
            g_rupeeNum = 0;
        }
        dComIfGs_setRupee(g_rupeeNum);
        break;
    case MAGIC_INDEX:
        Cursor::moveList(g_magicNum);
        if (g_magicNum == 0xFF) {
            g_magicNum = 32;
        }
        if (g_magicNum > 32) {
            g_magicNum = 0;
        }
        dComIfGs_setMagic(g_magicNum);
        break;
    case HEART_PIECE_INDEX:
        Cursor::moveList(g_heartNum);
        dComIfGs_setMaxLife(g_heartNum);
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
