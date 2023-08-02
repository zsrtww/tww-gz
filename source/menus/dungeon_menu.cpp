#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/main_menu.h"
#include "menus/dungeon_menu.h"
#include "flags.h"
#include "menu.h"
#include "utils/card.h"
#include "libtww/MSL_C/string.h"
#include "lib.h"
#include "font.h"
#include "color.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "commands.h"
#include "libtww/d/kankyo/d_kankyo.h"

#define LINE_NUM 6
Cursor DungeonMenu::cursor;
u8 l_selDun = 0;
u8 l_keyNum;
bool l_mapFlag;
bool l_compassFlag;
bool l_bosskeyFlag;
bool l_medli;
bool l_makar;
bool l_partner;


Line lines[LINE_NUM] = {
    {"dungeon", PICK_DUNGEON_INDEX, "Change the dungeon being modified"},
    {"keys", MODIFY_KEYS_INDEX, "modify the number of small keys"},
    {"boss key", BOSS_KEY_INDEX, "get the boss key",true, &l_bosskeyFlag},
    {"map", MAP_INDEX, "get the map", true, &l_mapFlag},
    {"compass", COMPASS_INDEX, "get the compass",true, &l_compassFlag},
    {"partner", PARTNER_INDEX, "Medli/Makar in ET/WT",true, &l_partner},
};

void dungeonItemSwitch(int stage, int flag) {
    if (dComIfGs_isDungeonItem(stage, flag)) {
        dComIfGs_offDungeonItem(stage, flag);
    }
    else {
        dComIfGs_onDungeonItem(stage, flag);
    }
}

const char* get_dun_name(u8 area_id) {
    switch (area_id) {
        case 3:
            return "DRC";
            break;
        case 4:
            return "FW";
            break;
        case 5:
            return "TOTG";
            break;
        case 6:
            return "ET";
            break;
        case 7:
            return "WT";
            break;
        default:
            return "DRC";
    }
}

u8 selectDungeon() {
    u8 stage = 3;
    Cursor::moveListSimple(stage);
    if (stage == 2) {
        stage = 7;
    }
    if (stage > 7) {
        stage = 3;
    }
    return stage;
}

void modifyKeys(int stage_id) {
    u8 amount = dComIfGs_getKeyNum(stage_id);
    Cursor::moveListSimple(amount);
    if (amount == 0xFF) {
        amount = 99;
    }
    if (amount > 99) {
        amount = 0;
    }
    dComIfGs_setKeyNum(stage_id, amount);
}


void DungeonMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_FLAGS_MENU);
        return;
    }

    u8 area_id = 3;
    switch (l_selDun) {
    case 0:
        area_id = 3;
        break;
    case 1:
        area_id = 4;
        break;
    case 2:
        area_id = 5;
        break;
    case 3:
        area_id = 6;
        break;
    case 4:
        area_id = 7;
        break;
    }

    l_mapFlag = dComIfGs_isDungeonItem(area_id, 0);
    l_compassFlag = dComIfGs_isDungeonItem(area_id, 1);
    l_bosskeyFlag = dComIfGs_isDungeonItem(area_id, 2);
    l_medli = (dComIfGs_isEventBit(0x1620) && dComIfGs_isEventBit(0x1608) &&
               dComIfGs_isEventBit(0x2920) && dComIfGs_isEventBit(0x2E04));
    l_makar = (dComIfGs_isEventBit(0x1610) && dComIfGs_isEventBit(0x1604) && dComIfGs_isEventBit(0x2910));
    if (area_id == 6) { l_partner = l_medli; }
    if (area_id == 7) { l_partner = l_makar; }
    int MAX_MOVE;
    if ((area_id == 6) || (area_id == 7)) {
        MAX_MOVE = LINE_NUM;
    } else {
        MAX_MOVE = LINE_NUM - 1;
    }
    switch (cursor.y) {
    case PICK_DUNGEON_INDEX:
        cursor.x = l_selDun;
        cursor.move(5, MAX_MOVE);

        if (cursor.y == PICK_DUNGEON_INDEX) {
            l_selDun = cursor.x;
        }
        l_keyNum = dComIfGs_getKeyNum(area_id);
        selectDungeon();
        break;
    case MODIFY_KEYS_INDEX:
        cursor.move(0, LINE_NUM);
        modifyKeys(area_id);
        break;
    default:
        cursor.move(0, MAX_MOVE);
        break;
    }
    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y) {
        case BOSS_KEY_INDEX:
            dungeonItemSwitch(area_id, 2);
            break;
        case MAP_INDEX:
            dungeonItemSwitch(area_id, 0);
            break;
        case COMPASS_INDEX:
            dungeonItemSwitch(area_id, 1);
            break;
            if ((area_id == 6) || (area_id == 7)) {
            case PARTNER_INDEX:
                if (area_id == 6) {
                    setEventFlag(0x1620);
                    setEventFlag(0x1608);
                    setEventFlag(0x2920);
                    setEventFlag(0x2E04);
                }
                if (area_id == 7) {
                    setEventFlag(0x1610);
                    setEventFlag(0x1604);
                    setEventFlag(0x2910);
                }
            }
        }
    }
    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
    tww_sprintf(lines[PICK_DUNGEON_INDEX].value, " <%s>", get_dun_name(area_id));
    tww_sprintf(lines[MODIFY_KEYS_INDEX].value, " <%d>", dComIfGs_getKeyNum(area_id));

    if ((area_id != 6) && (area_id != 7)) {
        GZ_drawMenuLines(lines, cursor.y, LINE_NUM - 1);
        if (cursor.y != PICK_DUNGEON_INDEX) {
        }
    } else {
        GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
        if (cursor.y != PICK_DUNGEON_INDEX) {
        }
    }

}
