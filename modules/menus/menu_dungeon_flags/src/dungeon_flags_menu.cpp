#include "menus/menu_dungeon_flags/include/dungeon_flags_menu.h"
#include "libtww/include/d/kankyo/d_kankyo.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "flags.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "commands.h"

#define LINE_NUM 7

u8 l_selDun = 0;
u8 l_keyNum;
bool l_mapFlag;
bool l_compassFlag;
bool l_bosskeyFlag;
bool l_medli;
bool l_makar;
bool l_partner;
bool l_partner_room;

KEEP_FUNC DungeonFlagsMenu::DungeonFlagsMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"dungeon", PICK_DUNGEON_INDEX, "Change the dungeon being modified"},
                        {"keys", MODIFY_KEYS_INDEX, "modify the number of small keys"},
                        {"boss key", BOSS_KEY_INDEX, "get the boss key", true, &l_bosskeyFlag},
                        {"map", MAP_INDEX, "get the map", true, &l_mapFlag},
                        {"compass", COMPASS_INDEX, "get the compass", true, &l_compassFlag},
                        {"partner", PARTNER_INDEX, "Medli/Makar in ET/WT", true, &l_partner},
                        {"partner room", PARTNER_ROOM_INDEX, "Spawn Medli/Makar in current room in ET/WT", true,
                         &l_partner_room},
                    } {}

DungeonFlagsMenu::~DungeonFlagsMenu() {}

inline bool isStageDungeonItem(int stage, int flag) {
    return isDungeonItem__12dSv_memBit_cFi(&g_dComIfG_gameInfo.info.mSavedata.mSave[stage].mBit, flag);
}

inline void onStageDungeonItem(int stage, int flag) {
    onDungeonItem__12dSv_memBit_cFi(&g_dComIfG_gameInfo.info.mSavedata.mSave[stage].mBit, flag);
}

inline void offStageDungeonItem(int stage, int flag) {
    g_dComIfG_gameInfo.info.mSavedata.mSave[stage].mBit.offDungeonItem(flag);
}

void dungeonItemSwitch(int stage, int flag) {
    if (isStageDungeonItem(stage, flag)) {
        offStageDungeonItem(stage, flag);
    } else {
        onStageDungeonItem(stage, flag);
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
    u8 amount = dComIfGs_getSaveKeyNum(stage_id);
    Cursor::moveListSimple(amount);
    if (amount == 0xFF) {
        amount = 99;
    }
    if (amount > 99) {
        amount = 0;
    }
    dComIfGs_setSaveKeyNum(stage_id, amount);
}

void DungeonFlagsMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
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

    l_mapFlag = isStageDungeonItem(area_id, dSv_memBit_c::MAP);
    l_compassFlag = isStageDungeonItem(area_id, dSv_memBit_c::COMPASS);
    l_bosskeyFlag = isStageDungeonItem(area_id, dSv_memBit_c::BOSS_KEY);
    l_medli = (dComIfGs_isEventBit(0x1620) && dComIfGs_isEventBit(0x1608) && dComIfGs_isEventBit(0x2920) &&
               dComIfGs_isEventBit(0x2E04));
    l_makar = (dComIfGs_isEventBit(0x1610) && dComIfGs_isEventBit(0x1604) && dComIfGs_isEventBit(0x2910));

    if (area_id == 6) {
        l_partner = l_medli;
        l_partner_room = g_medli_room;
    }

    if (area_id == 7) {
        l_partner = l_makar;
        l_partner_room = g_makar_room;
    }

    int MAX_MOVE;
    if ((area_id == 6) || (area_id == 7)) {
        MAX_MOVE = LINE_NUM;
    } else {
        MAX_MOVE = LINE_NUM - 2;
    }

    switch (cursor.y) {
    case PICK_DUNGEON_INDEX:
        cursor.x = l_selDun;
        cursor.move(5, MAX_MOVE);

        if (cursor.y == PICK_DUNGEON_INDEX) {
            l_selDun = cursor.x;
        }
        l_keyNum = dComIfGs_getSaveKeyNum(area_id);
        selectDungeon();
        break;
    case MODIFY_KEYS_INDEX:
        cursor.move(0, MAX_MOVE);
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
            case PARTNER_ROOM_INDEX:
                if (area_id == 6) {
                    g_medli_room = !g_medli_room;
                }
                if (area_id == 7) {
                    g_makar_room = !g_makar_room;
                }
            }
        }
    }

    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
    lines[PICK_DUNGEON_INDEX].printf(" <%s>", get_dun_name(area_id));
    lines[MODIFY_KEYS_INDEX].printf(" <%d>", dComIfGs_getSaveKeyNum(area_id));

    if ((area_id != 6) && (area_id != 7)) {
        GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM - 2);
    } else {
        GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
    }
}
