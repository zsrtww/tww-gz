#include <cstdio>
#include "menus/menu_actor_list/include/actor_list_menu.h"
#include "memory_editor.h"
#include "settings.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/f_op/f_op_actor_mng.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "libtww/include/d/d_procname.h"

#define CONTROLLER_RIGHT GZPad::DPAD_RIGHT
#define CONTROLLER_LEFT GZPad::DPAD_LEFT
#define MEM_SWITCH_BTN GZPad::Y
#define CONTROL_TEXT "Y"


 KEEP_VAR const char *objectNames[] = {
    "kusax1",  "kusax7",  "kusax21", "flower",  "flwr7",   "flwr17",  "pflower",
    "pflwrx7", "swood",   "swood3",  "swood5",  "woodb",   "woodbx",  "door10",
    "door11",  "door20",  "door21",  "Zenshut", "keyshut", "K_Zshut", "ATdoor",
    "Mori1",   "doorKD",  "ZenshKD", "K_ZshKD", "doorSH",  "doorSZ",  "KNOB00",
    "KNOB01",  "KNOB02",  "KNOB03",  "KNOB00D", "KNOB01D", "KNOB02D", "KNOB03D",
    "door12",  "door12M", "door12B", "door13",  "door13M", "door13B", "keyS12",
    "ZenS12",  "bonbori", "SW_C00",  "takara",  "takara2", "takara3", "takara4",
    "takara5", "takara6", "takara7", "takara8", "takaraK", "takaraI", "takaraM",
    "tkrASw",  "tkrAGc",  "tkrAKd",  "tkrAIk",  "tkrBMs",  "tkrCTf",  "tkrAOc",
    "tkrAOs",  "tkrSlv",  "agbA",    "agbAT",   "agbA2",   "agbF",    "agbF2",
    "agbMARK", "agbMW",   "agbCSW",  "agbTBOX", "agbR",    "agbB",    "agbD",
    "agbFA",   "NoneCam", "NormCam", "Link",    "kotubo",  "ootubo1", "Kmtub",
    "Ktaru",   "Ostool",  "Odokuro", "Okioke",  "Kmi02",   "Ptubo",   "KkibaB",
    "Kmi00",   "Hbox2S",  "SW_HIT0", "koisi1",  "koisi2",  "Aygr",    "Salvage",
    "SwSlvg",  "Salvag2", "SalvagN", "SalvagE", "SalvFM",  "osiBLK0", "osiBLK1",
    "Kkiba",   "Hseki2",  "Hseki7",  "Mmrr",    "MkieBB",  "Ecube",   "Hjump1",
    "Hbox1",   "MpwrB",   "DBLK0",   "DBLK1",   "DKkiba",  "Hbox2",   "BLK_CR",
    "CrTrS3",  "CrTrS4",  "CrTrS5",  "CrTrM1",  "CrTrM2",  "CrTrGr",  "CrTrBl",
    "Kbota_A", "Kbota_B", "KbotaC",  "Hhbot1",  "Hhbot1N", "MhmrSW0", "TagSo",
    "TagMSo",  "PScnChg", "ALLdie",  "TagEv",   "TagHt",   "TagHt2",  "TagMsg",
    "TagMsg2", "TagIsl",  "TagMd",   "TagKf1",  "TagKk1",  "TagKb",   "TagMk",
    "TagWp",   "TagDM",   "TagTy",   "TagMd1",  "TagCb1",  "TagMd11", "TagMd12",
    "TagMd13", "TagMd14", "TagMd15", "TagMd16", "TagCb11", "TagCb12", "TagCb13",
    "TagCb14", "TagBa1",  "Evsw",    "Search",  "Otble",   "OtbleL",  "Warpt",
    "Warpnt",  "Warpts1", "Warpts2", "Warpts3", "Seatag",  "Warpf",   "Hys",
    "Hys2",    "Hsen1",   "Hsen2",   "Hsen3",   "Olift",   "Ylsic",   "Yllic",
    "Ylkic",   "Hpbot1",  "Vpbot",   "Hami1",   "HamiY",   "LTag0",   "LTag1",
    "LTagR0",  "AttTag",  "AttTagB", "Ikori",   "MsuSW",   "MsuSWB",  "SWat00",
    "ITat00",  "SWtact",  "SWtactB", "Hhyu1",   "Oyashi",  "Kanban",  "kt",
    "ho",      "mo2",     "moZOU",   "hotest",  "Kui",     "Kamome",  "item",
    "itemFLY", "itemDek", "Ship",    "AND_SW0", "AND_SW2", "Bb",      "Ebrock",
    "Ekao",    "Ebrock2", "ky_tag0", "kytag00", "ky00you", "ky_tag1", "ky_tag2",
    "ky_tag3", "kytag4",  "kytag5",  "kytag6",  "kytag7",  "sea",     "nezumi",
    "nezuana", "kani",    "Demo_Dk", "DmKmm",   "DmKmm2",  "amos",    "amos2",
    "gmos",    "gmos_g",  "gmos_f",  "kuro_s",  "kuro_t",  "c_green", "c_red",
    "c_blue",  "c_black", "c_kiiro", "bable",   "bable_r", "wiz_r",   "wiz_s",
    "wiz_m",   "wiz_o",   "p_hat",   "p_zelda", "big_pow", "pow",     "sea_hat",
    "jbaba",   "bbaba",   "bridge",  "dragon",  "Nh",      "NpcSo",   "NpcNz",
    "Os",      "Os1",     "Os2",     "Ym1",     "Ym2",     "Yw1",     "Ji1",
    "Ko1",     "Ko2",     "Ls1",     "Bm1",     "Bm2",     "Bm3",     "Bm4",
    "Bm5",     "Bmcon1",  "Bmcon2",  "Bmsw",    "Btsw",    "Btsw2",   "Zk1",
    "Zl1",     "Ob1",     "Aj1",     "Km1",     "Cb1",     "Ba1",     "Bj1",
    "Bj2",     "Bj3",     "Bj4",     "Bj5",     "Bj6",     "Bj7",     "Bj8",
    "Bj9",     "Bs1",     "Bs2",     "Bms1",    "Bms2",    "Ds1",     "Rsh1",
    "Kk1",     "Pm1",     "Kp1",     "Pf1",     "Gp1",     "Jb1",     "Kf1",
    "De1",     "Sfairy",  "Md1",     "Uo1",     "Uo2",     "Uo3",     "Ub1",
    "Ub2",     "Ub3",     "Ub4",     "Uw1",     "Uw2",     "Um1",     "Um2",
    "Um3",     "Sa1",     "Sa2",     "Sa3",     "Sa4",     "Sa5",     "Ug1",
    "Ug2",     "Gk1",     "Ac1",     "Hi1",     "Pirates", "keeth",   "Fkeeth",
    "yg_awa",  "magtail", "RopeR",   "Ktarur",  "Ktarux",  "Magrock", "Quake",
    "Yfire00", "Turu",    "Turu2",   "Turu3",   "Kanat",   "s_turu",  "spotbox",
    "Ksaku",   "spotbx1", "Mswing",  "Pig",     "Rdead1",  "Rdead2",  "Fmaster",
    "Fmastr1", "Fmastr2", "Daiocta", "Daioeye", "Oq",      "Oqw",     "Gy",
    "GyCtrl",  "GyCtrlB", "Bk",      "Ypit00",  "Pitfall", "Nzfall",  "ScnChg",
    "Oship",   "Ayush",   "Tpost",   "Ocanon",  "Ikada",   "ikada_h", "ikadaS",
    "ikada_u", "Svsp",    "Sv0",     "Sv1",     "Sv2",     "Sv3",     "MjDoor",
    "Ikari",   "MjFlag",  "MtFlag",  "HcFlag",  "TrFlag",  "SieFlag", "lwood",
    "Ktaruo",  "Touseki", "frock",   "fallrck", "Dr2",     "Mkdan1",  "Btd",
    "Dk",      "Ystm0",   "Ystm1",   "Gflag",   "Branch",  "P1a",     "P1b",
    "P1c",     "P2a",     "P2b",     "P2c",     "Tc",      "Throck",  "magma",
    "Bita",    "YkgrON",  "YkgrOFF", "Dsaku",   "Otana",   "OtanaG",  "Bdk",
    "Bdkobj",  "SWTdoor", "Canon",   "GBoard",  "Hlift",   "Hliftb",  "Hami2",
    "Hami3",   "Hami4",   "Hbrf1",   "Mflft",   "ObjTime", "Klft",    "Kita",
    "Humi0z",  "Humi4z",  "Humi5z",  "Tide3",   "Humi2z",  "Humi3z",  "WLvTag",
    "Fire",    "Zenfire", "Kokiie",  "Paper",   "Ppos",    "Piwa",    "Ss",
    "WindTag", "Kryu00",  "Mcube",   "Mcyln",   "Mcube10", "Mcyln10", "MwtrSB",
    "MygnSB",  "Owater",  "Astop",   "Ojtree",  "Ospbox",  "Hmlif",   "Ywarp00",
    "Ysdls00", "Yswtr00", "Gbrg00",  "Mhsg6",   "Mhsg9",   "Mhsg12",  "Mhsg15",
    "Mhsg4h",  "Sss",     "Wall",    "Blift",   "MtoriSU", "Lamp",    "Sitem",
    "Hmos1",   "Hmos2",   "Hmos3",   "Ylesr00", "Hseki1",  "Hseki6",  "Hseki3",
    "Hseki4",  "Hseki5",  "Hmon1",   "Hmon1d",  "Hmon2",   "Hmon2d",  "Hseki31",
    "Hseki41", "Hseki51", "Hseki32", "Hseki42", "Hseki52", "Com_A",   "WBird",
    "SMtoge",  "SMBdor",  "KGBdor",  "BFlower", "VbakH",   "VigaH",   "Stal",
    "MkieBA",  "MkieBAB", "MkieK",   "MknjD",   "Msdan",   "MsdanSb", "Msdan2",
    "MsdanS2", "Htobi1",  "Htobi2",  "Htobi3",  "Hfbot1A", "Hfbot1B", "Hfbot1C",
    "Ykzyg",   "GiceL",   "Qdghd",   "dmgroom", "Doguu",   "MegamiD", "MegamiF",
    "MegamiN", "DoguuD",  "ReTag0",  "VolTag",  "Auc7",    "Auc1",    "Auc2",
    "Auc3",    "Auc4",    "Auc5",    "Auc6",    "Auc0",    "RotenA",  "RotenB",
    "RotenC",  "Tn",      "Fdai",    "Ytrnd00", "Plant",   "Rflw",    "Table",
    "Gtaki",   "Tenmado", "X_tower", "Eskban",  "Ekskz",   "Pbka",    "Yboil00",
    "Cafelmp", "MKanoke", "MKanok2", "Kg1",     "Kg2",     "Tt",      "Hr",
    "Hr2",     "BigElf",  "Ho",      "Gkai00",  "Mk",      "UkB",     "UkC",
    "UkD",     "Mk2",     "UkB2",    "UkC2",    "UkD2",    "Co1",     "Mt",
    "Mn",      "Ah",      "Hyuf1",   "Hyuf2",   "Hdai1",   "Hdai2",   "Hdai3",
    "Auction", "Auzu",    "Hpu1",    "Hpu2",    "Hkikai1", "Ybgaf00", "LOD01",
    "LOD02",   "LOD03",   "LOD04",   "LOD05",   "LOD06",   "LOD07",   "LOD08",
    "LOD09",   "LOD10",   "LOD11",   "LOD12",   "LOD13",   "LOD14",   "LOD15",
    "LOD16",   "LOD17",   "LOD18",   "LOD19",   "LOD20",   "LOD21",   "LOD22",
    "LOD23",   "LOD24",   "LOD25",   "LOD26",   "LOD27",   "LOD28",   "LOD29",
    "LOD30",   "LOD31",   "LOD32",   "LOD33",   "LOD34",   "LOD35",   "LOD36",
    "LOD37",   "LOD38",   "LOD39",   "LOD40",   "LOD41",   "LOD42",   "LOD43",
    "LOD44",   "LOD45",   "LOD46",   "LOD47",   "LOD48",   "LOD49",   "MtryB",
    "MtryBCr", "Vdora",   "Roten2",  "Roten3",  "Roten4",  "Qtkhd",   "Akabe",
    "Akabe10", "NBOX",    "NBOX10",  "Ashut",   "Mcrtn",   "VmcBS",   "Usovmc",
    "Vfan",    "Apzl",    "Adnno",   "Ycage00", "Yswdr00", "TnTrap",  "FgTrap",
    "CmTrap",  "Hjump2",  "Esekh",   "Esekh2",  "Po",      "TagPo",   "Htoge1",
    "Skanran", "Ajav",    "Trap",    "Hha",     "Htetu1",  "Tpota",   "Stoudai",
    "Pbco",    "Ebomzo",  "Psail",   "Homen1",  "Homen2",  "Xfuta",   "Vochi",
    "Hfuck1",  "YLzou",   "Gbed",    "Vteng",   "Ohatch",  "Rcloud",  "Ocloud",
    "MPot",    "MOsara",  "MKoppu",  "Ptco",    "Ptcu",    "Kmon",    "Sarace",
    "Hsh",     "Hsh2",    "Mmusic",  "Gryw00",  "AjavW",   "Omensmk", "Itnak",
    "Yfrlt00", "FTree",   "Vyasi",   "Vds",     "Rforce",  "zouK",    "zouK1",
    "zouK2",   "zouK3",   "zouK4",   "Gaship1", "Gaship2", "Ghrwp",   "Gdemo20",
    "Warpgn",  "Warpmj",  "Warpfo",  "Ygush00", "Ygush01", "Ygstp00", "Ygush02",
    "Hcbh",    "Com_B",   "Com_C",   "SPitem",  "HyoiKam", "Shmrgrd", "Vtil1",
    "Vtil2",   "Vtil3",   "Vtil4",   "Vtil5",   "Eayogn",  "VmsMS",   "VmsDZ",
    "VgnFD",   "Ygcwp",   "Figure",  "RoHat",   "Gntakis", "Gntakie", "Gnbtaki",
    "Bkm",     "Bst",     "Bitem",   "Fganon",  "Bwd",     "Bwds",    "Bgn",
    "Gnd",     "Puti",    "d_act0",  "d_act1",  "d_act2",  "d_act3",  "d_act4",
    "d_act5",  "d_act6",  "d_act7",  "d_act8",  "d_act9",  "d_act10", "d_act11",
    "d_act12", "d_act13", "d_act14", "d_act15", "d_act16", "d_act17", "d_act18",
    "d_act19", "d_act20", "d_act21", "d_act22", "d_act23", "d_act24", "d_act25",
    "d_act26", "d_act27", "d_act28", "d_act29", "d_act30", "d_act31", "SYAN",
    "TagD1",   "TagD2",   "TagD3",   "TagD4",   "mp",      "STBox",   "Fobj00",
    "Tama",    "Agb",     "Bg",      "Himo2",   "Esa",     "Boko",    "Kantera",
    "HShot",   "Boom",    "Bomb",    "Bomb2",   "Boko",    "Arrow",   "Arrow_i",
    "Arrow_l", "Grid",    "Kaji",    "HFloor",  "Buoyr",   "Ritem",   "Sitem",
    "Ditem",   "Iball",   "Grass",   "Vrbox",   "Vrbox2",  "EndCode"};

KEEP_FUNC ActorListMenu::ActorListMenu(Cursor& cursor, ActorListData& data)
    : Menu(cursor),
      l_index(data.l_index), lines{
                                 {"index:", ACTOR_ID_INDEX,
                                  "List Index (Dpad to scroll / " CONTROL_TEXT " to view memory)",
                                  false},
                             } {}

ActorListMenu::~ActorListMenu() {}

void ActorListMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    switch (cursor.y) {
    case ACTOR_ID_INDEX:
        if (GZ_getButtonRepeat(CONTROLLER_RIGHT) && l_index < g_fopAcTg_Queue.mSize) {
            l_index++;
        } else if (GZ_getButtonRepeat(CONTROLLER_LEFT) && l_index > 0) {
            l_index--;
        }
        break;
    }

    if (l_index > g_fopAcTg_Queue.mSize - 1) {
        l_index = g_fopAcTg_Queue.mSize - 1;
    }

    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = NULL;
    for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
        if (i == l_index && node != NULL) {
            create_tag_class* tag = (create_tag_class*)node;
            actorData = (fopAc_ac_c*)tag->mpTagData;
            break;
        }
        node = node->mpNextNode;
    }

    if (actorData != NULL) {
        char addressBuf[18];
        snprintf(addressBuf, sizeof(addressBuf), "Address: %08X", (uint32_t)actorData);
        GZ_drawText(addressBuf, 25.0f, 100.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char idBuf[16];
        snprintf(idBuf, sizeof(idBuf), "Proc ID: %d",  actorData->mBase.mProcName);
        GZ_drawText(idBuf, 25.0f, 120.f, 0xFFFFFFFF, GZ_checkDropShadows());
        char nameBuf[18];
         snprintf(nameBuf, sizeof(nameBuf), "Proc Name: %s",objectNames[actorData->mBase.mProcName]);
        GZ_drawText(nameBuf, 25.0f, 140.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char paramBuf[17];
        snprintf(paramBuf, sizeof(paramBuf), "Params: %08X", actorData->mBase.mParameters);
        GZ_drawText(paramBuf, 25.0f, 160.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char angleBuf[14];
        snprintf(angleBuf, sizeof(angleBuf), "Angle: %d", actorData->shape_angle.y);
        GZ_drawText(angleBuf, 25.0f, 180.f, 0xFFFFFFFF, GZ_checkDropShadows());

        char posBuf[50];
        snprintf(posBuf, sizeof(posBuf), "Position: %.1f %.1f %.1f",
                 actorData->current.pos.x, actorData->current.pos.y,
                 actorData->current.pos.z);
        GZ_drawText(posBuf, 25.0f, 200.f, 0xFFFFFFFF, GZ_checkDropShadows());

        lines[ACTOR_ID_INDEX].printf(" <%d / %d>", l_index, g_fopAcTg_Queue.mSize - 1);

        if (GZ_getButtonTrig(MEM_SWITCH_BTN)) {
            switch (cursor.y) {
            case ACTOR_ID_INDEX:
                g_memoryEditor_addressIndex = (uint32_t)actorData;
                g_menuMgr->push(MN_MEMORY_EDITOR_INDEX);
                return;
            }
        }
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
