#include "menus/menu_quest_status/include/quest_status_menu.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "font.h"
#include "gz_flags.h"
#include "utils/item.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define NUM_QUEST_ITEMS 28

KEEP_FUNC QuestStatusMenu::QuestStatusMenu(Cursor& cursor)
    : Menu(cursor),
      lines{{"Sword:", MENU_ITEM_SWORD, "Add/remove/upgrade sword"},
            {"Shield:", MENU_ITEM_SHIELD, "Add/remove/upgrade shield"},
            {"Magic:", MENU_ITEM_MAGIC, "Add/remove/upgrade magic"},
            {"Wallet:", MENU_ITEM_WALLET, "Upgrade/downgrade wallet"},
            {"Quiver:", MENU_ITEM_QUIVER, "Add/remove/upgrade quiver"},
            {"Hurricane Spin:", MENU_ITEM_HURRICANE_SPIN, "Add/remove hurricane spin"},
            {"Heroes Clothes:", MENU_ITEM_HEROES_CLOTHES,
             "Add/remove heroes clothes (takes effect upon reload)"},
            {"Bomb Bag:", MENU_ITEM_BOMBAG, "Add/remove/upgrade bomb bag"},
            {"Power Bracelets:", MENU_ITEM_POWER_BRACELETS,
             "Add/remove power bracelets from inventory"},
            {"Pirate\'s Charm:", MENU_ITEM_PIRATES_CHARM,
             "Add/remove pirate\'s charm from inventory"},
            {"Hero\'s Charm:", MENU_ITEM_HEROS_CHARM, "Add/remove hero\'s charm from inventory"},
            {"Wind\'s Requiem:", MENU_ITEM_WINDS_REQUIEM,
             "Add/remove wind\'s requiem from songs list"},
            {"Ballad of Gales:", MENU_ITEM_BALLAD_OF_GALES,
             "Add/remove ballad of gales from songs list"},
            {"Command Melody:", MENU_ITEM_COMMAND_MELODY,
             "Add/remove command melody from songs list"},
            {"Earth God\'s Lyric:", MENU_ITEM_EARTH_GODS_LYRIC,
             "Add/remove earth god's lyric from songs list"},
            {"Wind God\'s Aria:", MENU_ITEM_WIND_GODS_ARIA,
             "Add/remove wind god\'s aria from songs list"},
            {"Song of Passing:", MENU_ITEM_SONG_OF_PASSING,
             "Add/remove song of passing from songs list"},
            {"Din\'s Pearl:", MENU_ITEM_DINS_PEARL, "Add/remove din\'s pearl from inventory"},
            {"Farore\'s Pearl:", MENU_ITEM_FARORES_PEARL,
             "Add/remove farore\'s pearl from inventory"},
            {"Nayru\'s Pearl:", MENU_ITEM_NAYRUS_PEARL, "Add/remove nayru\'s pearl from inventory"},
            {"Triforce Piece 1:", MENU_ITEM_TRIFORCE_PIECE_1,
             "Add/remove triforce piece 1 from inventory"},
            {"Triforce Piece 2:", MENU_ITEM_TRIFORCE_PIECE_2,
             "Add/remove triforce piece 2 from inventory"},
            {"Triforce Piece 3:", MENU_ITEM_TRIFORCE_PIECE_3,
             "Add/remove triforce piece 3 from inventory"},
            {"Triforce Piece 4:", MENU_ITEM_TRIFORCE_PIECE_4,
             "Add/remove triforce piece 4 from inventory"},
            {"Triforce Piece 5:", MENU_ITEM_TRIFORCE_PIECE_5,
             "Add/remove triforce piece 5 from inventory"},
            {"Triforce Piece 6:", MENU_ITEM_TRIFORCE_PIECE_6,
             "Add/remove triforce piece 6 from inventory"},
            {"Triforce Piece 7:", MENU_ITEM_TRIFORCE_PIECE_7,
             "Add/remove triforce piece 7 from inventory"},
            {"Triforce Piece 8:", MENU_ITEM_TRIFORCE_PIECE_8,
             "Add/remove triforce piece 8 from inventory"}} {}

QuestStatusMenu::~QuestStatusMenu() {}

const char* get_pirates_charm_string(u8 has_pirates_charm) {
    switch (has_pirates_charm) {
    case 0:
        return "Empty";
    case 1:
        return "Pirate\'s Charm";
    default:
        return "Empty";
    };
}

const char* get_heros_charm_string() {
    if (dComIfGs_isCollect(HEROS_CHARM_OWNED_INDEX, 0)) {
        if (dComIfGs_isCollect(HEROS_CHARM_OWNED_INDEX, 1)) {
            return "Hero\'s Charm (Enabled)";
        }

        return "Hero\'s Charm (Disabled)";
    }

    return "Empty";
}

const char* get_hurricane_spin_string() {
    if (dComIfGs_isEventBit(0x0B20)) {
        return "Hurricane Spin";
    } else {
        return "Empty";
    };
}

const char* get_heroes_clothes_string() {
    if (dComIfGs_isEventBit(0x2A80)) {
        return "Heroes Clothes";
    } else {
        return "Pajamas";
    };
}

const char* get_song_string(u8 songs_owned, u8 song) {
    if (!songs_owned) {
        return "Empty";
    } else {
        switch (song) {
        case WINDS_REQUIEM_VALUE:
            return "Wind\'s Requiem";
        case BALLAD_OF_GALES_VALUE:
            return "Ballad of Gales";
        case COMMAND_MELODY_VALUE:
            return "Command Melody";
        case EARTH_GODS_LYRIC_VALUE:
            return "Earth God\'s Lyric";
        case WIND_GODS_ARIA_VALUE:
            return "Wind God\'s Aria";
        case SONG_OF_PASSING_VALUE:
            return "Song of Passing";
        default:
            return "Empty";
        };
    }
}

const char* get_pearl_string(u8 pearls_owned, u8 pearl) {
    if (!pearls_owned) {
        return "Empty";
    } else {
        switch (pearl) {
        case NAYRUS_PEARL_VALUE:
            return "Nayru\'s Pearl";
        case DINS_PEARL_VALUE:
            return "Din\'s Pearl";
        case FARORES_PEARL_VALUE:
            return "Farore\'s Pearl";
        default:
            return "Empty";
        };
    }
}

const char* get_magic_string(u8 magic_value) {
    if (magic_value == 0) {
        return "Empty";
    } else if (magic_value > SINGLE_MAGIC) {
        return "Double Magic";
    } else
        return "Single Magic";
}

const char* get_wallet_string(u8 wallet_size) {
    switch (wallet_size) {
    case WALLET_200:
        return "Wallet 200";
    case WALLET_1000:
        return "Wallet 1000";
    case WALLET_5000:
        return "Wallet 5000";
    default:
        return "ERROR";
    }
}

const char* get_quiver_string(u8 arrows_capacity) {
    if (arrows_capacity == 0) {
        return "No Quiver";
    } else {
        switch (arrows_capacity) {
        case ARROWS_30:
            return "Quiver 30";
        case ARROWS_60:
            return "Quiver 60";
        case ARROWS_99:
            return "Quiver 99";
        default:
            return "Empty";
        };
    }
}

const char* get_bombags_string(u8 max_bombs_owned) {
    if (max_bombs_owned == 0) {
        return "No Bomb Bag";
    } else {
        switch (max_bombs_owned) {
        case BOMBS_30:
            return "Bomb Bag 30";
        case BOMBS_60:
            return "Bomb Bag 60";
        case BOMBS_99:
            return "Bomb Bag 99";
        default:
            return "Empty";
        };
    }
}

const char* get_triforce_string(u8 triforce_owned, u8 triforce_piece) {
    if (!triforce_owned) {
        return "Empty";
    } else {
        switch (triforce_piece) {
        case TRIFORCE_PIECE_1_VALUE:
            return "Triforce Piece 1";
        case TRIFORCE_PIECE_2_VALUE:
            return "Triforce Piece 2";
        case TRIFORCE_PIECE_3_VALUE:
            return "Triforce Piece 3";
        case TRIFORCE_PIECE_4_VALUE:
            return "Triforce Piece 4";
        case TRIFORCE_PIECE_5_VALUE:
            return "Triforce Piece 5";
        case TRIFORCE_PIECE_6_VALUE:
            return "Triforce Piece 6";
        case TRIFORCE_PIECE_7_VALUE:
            return "Triforce Piece 7";
        case TRIFORCE_PIECE_8_VALUE:
            return "Triforce Piece 8";
        default:
            return "Empty";
        };
    }
}

void updateHurricaneSpin() {
    u8 has_hurricane_spin = dComIfGs_isEventBit(0x0B20);
    s8 position = 0;
    Cursor::moveListSimple(position);
    if ((position == 1) && (has_hurricane_spin == 0)) {
        dComIfGs_onEventBit(0x0B20);
    } else if ((position == -1) && (has_hurricane_spin == 1)) {
        dComIfGs_offEventBit(0x0B20);
    }
}

void updateHeroesClothes() {
    u8 has_heroesclothes = dComIfGs_isEventBit(0x2A80);
    s8 position = 0;
    Cursor::moveListSimple(position);
    if ((position == 1) && (has_heroesclothes == 0)) {
        dComIfGs_onEventBit(0x2A80);
    } else if ((position == -1) && (has_heroesclothes == 1)) {
        dComIfGs_offEventBit(0x2A80);
    }
}

void updateSongs(u8 song_value) {
    u8 has_song = dComIfGs_isTact(song_value);
    Cursor::moveListSimple(has_song);

    if (has_song > 0) {
        has_song = 1;
    } else {
        has_song = 0;
    }

    if (has_song) {
        dComIfGs_onTact(song_value);
    } else {
        dComIfGs_offTact(song_value);
    }
}

void updatePearls(u8 pearl_value) {
    u8 has_pearl = dComIfGs_isSymbol(pearl_value);
    Cursor::moveListSimple(has_pearl);

    if (has_pearl > 0) {
        has_pearl = 1;
    } else {
        has_pearl = 0;
    }

    if (has_pearl) {
        dComIfGs_onSymbol(pearl_value);
    } else {
        dComIfGs_offSymbol(pearl_value);
    }
}

void updateTriforce(u8 triforce_value) {
    u8 has_triforce = dComIfGs_isTriforce(triforce_value);
    Cursor::moveListSimple(has_triforce);

    if (has_triforce > 0) {
        has_triforce = 1;
    } else {
        has_triforce = 0;
    }

    if (has_triforce) {
        dComIfGs_onTriforce(triforce_value);
    } else {
        dComIfGs_offTriforce(triforce_value);
    }
}

void QuestStatusMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    u8 new_sword_item_id, new_shield_item_id, new_max_magic_value, new_wallet_size,
        new_arrows_capacity, new_bombs_capacity, new_power_bracelets_item_id,
        is_pirates_charm_owned, heros_charm_flag;

    switch (cursor.y) {
    case MENU_ITEM_SWORD:
        new_sword_item_id = dComIfGs_getSelectEquip(SWORD_INDEX);
        Cursor::moveListSimple(new_sword_item_id);
        if (new_sword_item_id == NO_ITEM - 1) {
            new_sword_item_id = NO_ITEM;
        } else if (new_sword_item_id == 0) {
            new_sword_item_id = HEROS_SWORD;
        } else if (new_sword_item_id == HEROS_SWORD - 1) {
            new_sword_item_id = NO_ITEM;
        } else if (new_sword_item_id == HEROS_SWORD + 1) {
            new_sword_item_id = UNCHARGED_MASTER_SWORD;
        } else if (new_sword_item_id == UNCHARGED_MASTER_SWORD - 1) {
            new_sword_item_id = HEROS_SWORD;
        } else if (new_sword_item_id == UNCHARGED_MASTER_SWORD + 1) {
            new_sword_item_id = HALF_CHARGED_MASTER_SWORD;
        } else if (new_sword_item_id == HALF_CHARGED_MASTER_SWORD - 1) {
            new_sword_item_id = UNCHARGED_MASTER_SWORD;
        } else if (new_sword_item_id == HALF_CHARGED_MASTER_SWORD + 1) {
            new_sword_item_id = FULLY_CHARGED_MASTER_SWORD;
        } else if (new_sword_item_id == FULLY_CHARGED_MASTER_SWORD - 1) {
            new_sword_item_id = HALF_CHARGED_MASTER_SWORD;
        } else if (new_sword_item_id == FULLY_CHARGED_MASTER_SWORD + 1) {
            new_sword_item_id = FULLY_CHARGED_MASTER_SWORD;
        } else {
            new_sword_item_id = dComIfGs_getSelectEquip(SWORD_INDEX);
        }

        switch (new_sword_item_id) {
        case NO_ITEM:
            dComIfGs_offCollect(SWORD_INDEX, 0);
            dComIfGs_offCollect(SWORD_INDEX, 1);
            dComIfGs_offCollect(SWORD_INDEX, 2);
            dComIfGs_offCollect(SWORD_INDEX, 3);
            break;
        case HEROS_SWORD:
            dComIfGs_onCollect(SWORD_INDEX, 0);
            dComIfGs_offCollect(SWORD_INDEX, 1);
            break;
        case UNCHARGED_MASTER_SWORD:
            dComIfGs_onCollect(SWORD_INDEX, 1);
            dComIfGs_offCollect(SWORD_INDEX, 2);
            break;
        case HALF_CHARGED_MASTER_SWORD:
            dComIfGs_onCollect(SWORD_INDEX, 2);
            dComIfGs_offCollect(SWORD_INDEX, 3);
            break;
        case FULLY_CHARGED_MASTER_SWORD:
            dComIfGs_onCollect(SWORD_INDEX, 3);
            break;
        }

        dComIfGs_setSelectEquip(SWORD_INDEX, new_sword_item_id);
        break;
    case MENU_ITEM_SHIELD:
        new_shield_item_id = dComIfGs_getSelectEquip(SHIELD_INDEX);
        Cursor::moveListSimple(new_shield_item_id);
        if (new_shield_item_id == NO_ITEM - 1) {
            new_shield_item_id = NO_ITEM;
        } else if (new_shield_item_id == 0) {
            new_shield_item_id = HEROS_SHIELD;
        } else if (new_shield_item_id == HEROS_SHIELD - 1) {
            new_shield_item_id = NO_ITEM;
        } else if (new_shield_item_id == HEROS_SHIELD + 1) {
            new_shield_item_id = MIRROR_SHIELD;
        } else if (new_shield_item_id == MIRROR_SHIELD - 1) {
            new_shield_item_id = HEROS_SHIELD;
        } else if (new_shield_item_id == MIRROR_SHIELD + 1) {
            new_shield_item_id = MIRROR_SHIELD;
        } else {
            new_shield_item_id = dComIfGs_getSelectEquip(SHIELD_INDEX);
        }

        switch (new_shield_item_id) {
        case NO_ITEM:
            dComIfGs_offCollect(SHIELD_INDEX, 0);
            dComIfGs_offCollect(SHIELD_INDEX, 1);
            break;
        case HEROS_SHIELD:
            dComIfGs_onCollect(SHIELD_INDEX, 0);
            dComIfGs_offCollect(SHIELD_INDEX, 1);
            break;
        case MIRROR_SHIELD:
            dComIfGs_onCollect(SHIELD_INDEX, 1);
            break;
        }

        dComIfGs_setSelectEquip(SHIELD_INDEX, new_shield_item_id);
        break;
    case MENU_ITEM_MAGIC:
        new_max_magic_value = dComIfGs_getMaxMagic();
        Cursor::moveListSimple(new_max_magic_value);
        if (new_max_magic_value == NO_MAGIC - 1) {
            new_max_magic_value = NO_MAGIC;
        } else if (new_max_magic_value == NO_MAGIC + 1) {
            new_max_magic_value = SINGLE_MAGIC;
        } else if (new_max_magic_value == SINGLE_MAGIC - 1) {
            new_max_magic_value = NO_MAGIC;
        } else if (new_max_magic_value == SINGLE_MAGIC + 1) {
            new_max_magic_value = DOUBLE_MAGIC;
        } else if (new_max_magic_value == DOUBLE_MAGIC - 1) {
            new_max_magic_value = SINGLE_MAGIC;
        } else if (new_max_magic_value == DOUBLE_MAGIC + 1) {
            new_max_magic_value = DOUBLE_MAGIC;
        } else {
            new_max_magic_value = dComIfGs_getMaxMagic();
        }
        dComIfGs_setMagic(new_max_magic_value);
        dComIfGs_setMaxMagic(new_max_magic_value);
        break;
    case MENU_ITEM_WALLET:
        new_wallet_size = g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();
        Cursor::moveListSimple(new_wallet_size);
        if (new_wallet_size == WALLET_200 - 1) {
            new_wallet_size = WALLET_200;
        } else if (new_wallet_size == WALLET_200 + 1) {
            new_wallet_size = WALLET_1000;
        } else if (new_wallet_size == WALLET_1000 - 1) {
            new_wallet_size = WALLET_200;
        } else if (new_wallet_size == WALLET_1000 + 1) {
            new_wallet_size = WALLET_5000;
        } else if (new_wallet_size == WALLET_5000 - 1) {
            new_wallet_size = WALLET_1000;
        } else if (new_wallet_size == WALLET_5000 + 1) {
            new_wallet_size = WALLET_5000;
        } else {
            new_wallet_size =
                g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();
        }
        g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setWalletSize(new_wallet_size);
        break;
    case MENU_ITEM_POWER_BRACELETS:
        new_power_bracelets_item_id = dComIfGs_getSelectEquip(POWER_BRACELETS_INDEX);
        Cursor::moveListSimple(new_power_bracelets_item_id);
        if (new_power_bracelets_item_id == NO_ITEM - 1) {
            new_power_bracelets_item_id = NO_ITEM;
        } else if (new_power_bracelets_item_id == 0) {
            new_power_bracelets_item_id = POWER_BRACELETS;
        } else if (new_power_bracelets_item_id == POWER_BRACELETS - 1) {
            new_power_bracelets_item_id = NO_ITEM;
        } else if (new_power_bracelets_item_id == POWER_BRACELETS + 1) {
            new_power_bracelets_item_id = POWER_BRACELETS;
        } else {
            new_power_bracelets_item_id = dComIfGs_getSelectEquip(POWER_BRACELETS_INDEX);
        }

        switch (new_power_bracelets_item_id) {
        case NO_ITEM:
            dComIfGs_offCollect(POWER_BRACELETS_INDEX, 0);
            break;
        case POWER_BRACELETS:
            dComIfGs_onCollect(POWER_BRACELETS_INDEX, 0);
            break;
        }

        dComIfGs_setSelectEquip(POWER_BRACELETS_INDEX, new_power_bracelets_item_id);
        break;
    case MENU_ITEM_QUIVER:
        new_arrows_capacity = dComIfGs_getArrowMax();
        Cursor::moveListSimple(new_arrows_capacity);
        if (new_arrows_capacity == NO_QUIVER - 1) {
            new_arrows_capacity = NO_QUIVER;
        } else if (new_arrows_capacity == NO_QUIVER + 1) {
            new_arrows_capacity = ARROWS_30;
        } else if (new_arrows_capacity == ARROWS_30 - 1) {
            new_arrows_capacity = NO_QUIVER;
        } else if (new_arrows_capacity == ARROWS_30 + 1) {
            new_arrows_capacity = ARROWS_60;
        } else if (new_arrows_capacity == ARROWS_60 - 1) {
            new_arrows_capacity = ARROWS_30;
        } else if (new_arrows_capacity == ARROWS_60 + 1) {
            new_arrows_capacity = ARROWS_99;
        } else if (new_arrows_capacity == ARROWS_99 - 1) {
            new_arrows_capacity = ARROWS_60;
        } else if (new_arrows_capacity == ARROWS_99 + 1) {
            new_arrows_capacity = ARROWS_99;

        } else {
            new_arrows_capacity = dComIfGs_getArrowMax();
        }
        dComIfGs_setArrowNum(new_arrows_capacity);
        dComIfGs_setArrowMax(new_arrows_capacity);
        break;
    case MENU_ITEM_HURRICANE_SPIN:
        updateHurricaneSpin();
        break;
    case MENU_ITEM_HEROES_CLOTHES:
        updateHeroesClothes();
        break;
    case MENU_ITEM_BOMBAG:
        new_bombs_capacity = dComIfGs_getBombMax();
        Cursor::moveListSimple(new_bombs_capacity);
        if (new_bombs_capacity == NO_BOMBBAG - 1) {
            new_bombs_capacity = NO_BOMBBAG;
        } else if (new_bombs_capacity == NO_BOMBBAG + 1) {
            new_bombs_capacity = BOMBS_30;
        } else if (new_bombs_capacity == BOMBS_30 - 1) {
            new_bombs_capacity = NO_BOMBBAG;
        } else if (new_bombs_capacity == BOMBS_30 + 1) {
            new_bombs_capacity = BOMBS_60;
        } else if (new_bombs_capacity == BOMBS_60 - 1) {
            new_bombs_capacity = BOMBS_30;
        } else if (new_bombs_capacity == BOMBS_60 + 1) {
            new_bombs_capacity = BOMBS_99;
        } else if (new_bombs_capacity == BOMBS_99 - 1) {
            new_bombs_capacity = BOMBS_60;
        } else if (new_bombs_capacity == BOMBS_99 + 1) {
            new_bombs_capacity = BOMBS_99;

        } else {
            new_bombs_capacity = dComIfGs_getBombMax();
        }
        dComIfGs_setBombNum(new_bombs_capacity);
        dComIfGs_setBombMax(new_bombs_capacity);
        break;
    case MENU_ITEM_PIRATES_CHARM:
        is_pirates_charm_owned = dComIfGs_isCollect(PIRATES_CHARM_OWNED_INDEX, 0);
        Cursor::moveListSimple(is_pirates_charm_owned);

        if (is_pirates_charm_owned) {
            dComIfGs_onCollect(PIRATES_CHARM_OWNED_INDEX, 0);
        } else {
            dComIfGs_offCollect(PIRATES_CHARM_OWNED_INDEX, 0);
        }
        break;
    case MENU_ITEM_HEROS_CHARM:
        heros_charm_flag = dComIfGs_isCollect(HEROS_CHARM_OWNED_INDEX, 0);
        if (dComIfGs_isCollect(HEROS_CHARM_OWNED_INDEX, 1)) {
            heros_charm_flag = 2;
        }

        Cursor::moveListSimple(heros_charm_flag);

        if (heros_charm_flag == 1) {
            dComIfGs_onCollect(HEROS_CHARM_OWNED_INDEX, 0);
            dComIfGs_offCollect(HEROS_CHARM_OWNED_INDEX, 1);
        } else if (heros_charm_flag == 2) {
            dComIfGs_onCollect(HEROS_CHARM_OWNED_INDEX, 1);
        } else {
            dComIfGs_offCollect(HEROS_CHARM_OWNED_INDEX, 0);
            dComIfGs_offCollect(HEROS_CHARM_OWNED_INDEX, 1);
        }
        break;
    case MENU_ITEM_WINDS_REQUIEM:
        updateSongs(WINDS_REQUIEM_VALUE);
        break;
    case MENU_ITEM_BALLAD_OF_GALES:
        updateSongs(BALLAD_OF_GALES_VALUE);
        break;
    case MENU_ITEM_COMMAND_MELODY:
        updateSongs(COMMAND_MELODY_VALUE);
        break;
    case MENU_ITEM_EARTH_GODS_LYRIC:
        updateSongs(EARTH_GODS_LYRIC_VALUE);
        break;
    case MENU_ITEM_WIND_GODS_ARIA:
        updateSongs(WIND_GODS_ARIA_VALUE);
        break;
    case MENU_ITEM_SONG_OF_PASSING:
        updateSongs(SONG_OF_PASSING_VALUE);
        break;
    case MENU_ITEM_DINS_PEARL:
        updatePearls(DINS_PEARL_VALUE);
        break;
    case MENU_ITEM_FARORES_PEARL:
        updatePearls(FARORES_PEARL_VALUE);
        break;
    case MENU_ITEM_NAYRUS_PEARL:
        updatePearls(NAYRUS_PEARL_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_1:
        updateTriforce(TRIFORCE_PIECE_1_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_2:
        updateTriforce(TRIFORCE_PIECE_2_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_3:
        updateTriforce(TRIFORCE_PIECE_3_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_4:
        updateTriforce(TRIFORCE_PIECE_4_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_5:
        updateTriforce(TRIFORCE_PIECE_5_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_6:
        updateTriforce(TRIFORCE_PIECE_6_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_7:
        updateTriforce(TRIFORCE_PIECE_7_VALUE);
        break;
    case MENU_ITEM_TRIFORCE_PIECE_8:
        updateTriforce(TRIFORCE_PIECE_8_VALUE);
        break;
    };

    lines[MENU_ITEM_SWORD].printf(" <%s>", item_id_to_str(dComIfGs_getSelectEquip(SWORD_INDEX)));
    lines[MENU_ITEM_SHIELD].printf(" <%s>", item_id_to_str(dComIfGs_getSelectEquip(SHIELD_INDEX)));
    lines[MENU_ITEM_MAGIC].printf(" <%s>", get_magic_string(dComIfGs_getMaxMagic()));
    lines[MENU_ITEM_WALLET].printf(
        " <%s>",
        get_wallet_string(g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize()));
    lines[MENU_ITEM_QUIVER].printf(" <%s>", get_quiver_string(dComIfGs_getArrowMax()));
    lines[MENU_ITEM_HURRICANE_SPIN].printf(" <%s>", get_hurricane_spin_string());
    lines[MENU_ITEM_HEROES_CLOTHES].printf(" <%s>", get_heroes_clothes_string());
    lines[MENU_ITEM_BOMBAG].printf(" <%s>", get_bombags_string(dComIfGs_getBombMax()));
    lines[MENU_ITEM_POWER_BRACELETS].printf(
        " <%s>", item_id_to_str(dComIfGs_getSelectEquip(POWER_BRACELETS_INDEX)));
    lines[MENU_ITEM_PIRATES_CHARM].printf(
        " <%s>", get_pirates_charm_string(dComIfGs_isCollect(PIRATES_CHARM_OWNED_INDEX, 0)));
    lines[MENU_ITEM_HEROS_CHARM].printf(" <%s>", get_heros_charm_string());
    lines[MENU_ITEM_WINDS_REQUIEM].printf(
        " <%s>", get_song_string(dComIfGs_isTact(WINDS_REQUIEM_VALUE), WINDS_REQUIEM_VALUE));
    lines[MENU_ITEM_BALLAD_OF_GALES].printf(
        " <%s>", get_song_string(dComIfGs_isTact(BALLAD_OF_GALES_VALUE), BALLAD_OF_GALES_VALUE));
    lines[MENU_ITEM_COMMAND_MELODY].printf(
        " <%s>", get_song_string(dComIfGs_isTact(COMMAND_MELODY_VALUE), COMMAND_MELODY_VALUE));
    lines[MENU_ITEM_EARTH_GODS_LYRIC].printf(
        " <%s>", get_song_string(dComIfGs_isTact(EARTH_GODS_LYRIC_VALUE), EARTH_GODS_LYRIC_VALUE));
    lines[MENU_ITEM_WIND_GODS_ARIA].printf(
        " <%s>", get_song_string(dComIfGs_isTact(WIND_GODS_ARIA_VALUE), WIND_GODS_ARIA_VALUE));
    lines[MENU_ITEM_SONG_OF_PASSING].printf(
        " <%s>", get_song_string(dComIfGs_isTact(SONG_OF_PASSING_VALUE), SONG_OF_PASSING_VALUE));
    lines[MENU_ITEM_DINS_PEARL].printf(
        " <%s>", get_pearl_string(dComIfGs_isSymbol(DINS_PEARL_VALUE), DINS_PEARL_VALUE));
    lines[MENU_ITEM_FARORES_PEARL].printf(
        " <%s>", get_pearl_string(dComIfGs_isSymbol(FARORES_PEARL_VALUE), FARORES_PEARL_VALUE));
    lines[MENU_ITEM_NAYRUS_PEARL].printf(
        " <%s>", get_pearl_string(dComIfGs_isSymbol(NAYRUS_PEARL_VALUE), NAYRUS_PEARL_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_1].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_1_VALUE), TRIFORCE_PIECE_1_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_2].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_2_VALUE), TRIFORCE_PIECE_2_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_3].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_3_VALUE), TRIFORCE_PIECE_3_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_4].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_4_VALUE), TRIFORCE_PIECE_4_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_5].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_5_VALUE), TRIFORCE_PIECE_5_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_6].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_6_VALUE), TRIFORCE_PIECE_6_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_7].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_7_VALUE), TRIFORCE_PIECE_7_VALUE));
    lines[MENU_ITEM_TRIFORCE_PIECE_8].printf(
        " <%s>",
        get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_8_VALUE), TRIFORCE_PIECE_8_VALUE));

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}