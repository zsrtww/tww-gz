#include "controller.h"
#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "menus/quest_status_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"

#define NUM_QUEST_ITEMS 28

Cursor QuestStatusMenu::cursor;

Line lines[NUM_QUEST_ITEMS] = {
    {"Sword:", MENU_ITEM_SWORD, "Add/remove/upgrade sword"},
    {"Shield:", MENU_ITEM_SHIELD, "Add/remove/upgrade shield"},
    {"Magic:", MENU_ITEM_MAGIC, "Add/remove/upgrade magic"},
    {"Wallet:", MENU_ITEM_WALLET, "Upgrade/downgrade wallet"},
    {"Quiver:", MENU_ITEM_QUIVER, "Add/remove/upgrade quiver"},
    {"Hurricane Spin:", MENU_ITEM_HURRICANE_SPIN, "Add/remove hurricane spin"},
    {"Heroes Clothes:", MENU_ITEM_HEROES_CLOTHES, "Add/remove heroes clothes (takes effect upon reload)"},
    {"Bomb Bag:", MENU_ITEM_BOMBAG, "Add/remove/upgrade bomb bag"},
    {"Power Bracelets:", MENU_ITEM_POWER_BRACELETS, "Add/remove power bracelets from inventory"},
    {"Pirate\'s Charm:", MENU_ITEM_PIRATES_CHARM, "Add/remove pirate\'s charm from inventory"},
    {"Hero\'s Charm:", MENU_ITEM_HEROS_CHARM, "Add/remove hero\'s charm from inventory"},
    {"Wind\'s Requiem:", MENU_ITEM_WINDS_REQUIEM, "Add/remove wind\'s requiem from songs list"},
    {"Ballad of Gales:", MENU_ITEM_BALLAD_OF_GALES, "Add/remove ballad of gales from songs list"},
    {"Command Melody:", MENU_ITEM_COMMAND_MELODY, "Add/remove command melody from songs list"},
    {"Earth God\'s Lyric:", MENU_ITEM_EARTH_GODS_LYRIC,"Add/remove earth god's lyric from songs list"},
    {"Wind God\'s Aria:", MENU_ITEM_WIND_GODS_ARIA, "Add/remove wind god\'s aria from songs list"},
    {"Song of Passing:", MENU_ITEM_SONG_OF_PASSING, "Add/remove song of passing from songs list"},
    {"Din\'s Pearl:", MENU_ITEM_DINS_PEARL, "Add/remove din\'s pearl from inventory"},
    {"Farore\'s Pearl:", MENU_ITEM_FARORES_PEARL, "Add/remove farore\'s pearl from inventory"},
    {"Nayru\'s Pearl:", MENU_ITEM_NAYRUS_PEARL, "Add/remove nayru\'s pearl from inventory"},
    {"Triforce Piece 1:", MENU_ITEM_TRIFORCE_PIECE_1, "Add/remove triforce piece 1 from inventory"},
    {"Triforce Piece 2:", MENU_ITEM_TRIFORCE_PIECE_2, "Add/remove triforce piece 2 from inventory"},
    {"Triforce Piece 3:", MENU_ITEM_TRIFORCE_PIECE_3, "Add/remove triforce piece 3 from inventory"},
    {"Triforce Piece 4:", MENU_ITEM_TRIFORCE_PIECE_4, "Add/remove triforce piece 4 from inventory"},
    {"Triforce Piece 5:", MENU_ITEM_TRIFORCE_PIECE_5, "Add/remove triforce piece 5 from inventory"},
    {"Triforce Piece 6:", MENU_ITEM_TRIFORCE_PIECE_6, "Add/remove triforce piece 6 from inventory"},
    {"Triforce Piece 7:", MENU_ITEM_TRIFORCE_PIECE_7, "Add/remove triforce piece 7 from inventory"},
    {"Triforce Piece 8:", MENU_ITEM_TRIFORCE_PIECE_8, "Add/remove triforce piece 8 from inventory"}};

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

const char* get_heros_charm_string(u8 has_heros_charm) {
    switch (has_heros_charm) {
    case NO_HEROS_CHARM:
        return "Empty";
    case HEROS_CHARM_DISABLED:
        return "Hero\'s Charm (Disabled)";
    case HEROS_CHARM_ENABLED:
        return "Hero\'s Charm (Enabled)";
    default:
        return "Empty";
    };
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

u8 swordIdToSwordOwned(u8 sword_item_id) {
    switch (sword_item_id) {
    case NO_ITEM:
        return NO_SWORD_OWNED;
    case HEROS_SWORD:
        return HEROS_SWORD_OWNED;
    case UNCHARGED_MASTER_SWORD:
        return UNCHARGED_MASTER_SWORD_OWNED;
    case HALF_CHARGED_MASTER_SWORD:
        return HALF_CHARGED_MASTER_SWORD_OWNED;
    case FULLY_CHARGED_MASTER_SWORD:
        return FULLY_CHARGED_MASTER_SWORD_OWNED;
    default:
        return NO_SWORD_OWNED;
    };
}

u8 shieldIdToShieldOwned(u8 shield_item_id) {
    switch (shield_item_id) {
    case NO_ITEM:
        return NO_SHIELD_OWNED;
    case HEROS_SHIELD:
        return HEROS_SHIELD_OWNED;
    case MIRROR_SHIELD:
        return MIRROR_SHIELD_OWNED;
    default:
        return NO_SHIELD_OWNED;
    };
}

u8 powerBraceletsIdToPowerBraceletsOwned(u8 power_bracelets_item_id) {
    switch (power_bracelets_item_id) {
    case NO_ITEM:
        return 0;
    case POWER_BRACELETS:
        return 1;
    default:
        return 0;
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

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
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
        dComIfGs_setSelectEquip(SWORD_INDEX, new_sword_item_id);
        dComIfGs_onCollect(SWORD_INDEX, swordIdToSwordOwned(new_sword_item_id));
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
        dComIfGs_setSelectEquip(SHIELD_INDEX, new_shield_item_id);
        dComIfGs_onCollect(SHIELD_OWNED_INDEX, shieldIdToShieldOwned(new_shield_item_id));
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
            new_wallet_size = g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();
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
        dComIfGs_setSelectEquip(POWER_BRACELETS_INDEX, new_power_bracelets_item_id);
        dComIfGs_onCollect(POWER_BRACELETS_OWNED_INDEX, powerBraceletsIdToPowerBraceletsOwned(new_power_bracelets_item_id));
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

        if (is_pirates_charm_owned > 0) {
            is_pirates_charm_owned = 1;
        } else {
            is_pirates_charm_owned = 0;
        }
        dComIfGs_onCollect(PIRATES_CHARM_OWNED_INDEX, is_pirates_charm_owned);
        break;
    case MENU_ITEM_HEROS_CHARM:
        heros_charm_flag = dComIfGs_isCollect(HEROS_CHARM_OWNED_INDEX, 0);
        Cursor::moveListSimple(heros_charm_flag);

        if (heros_charm_flag > 0) {
            heros_charm_flag = 1;
        } else {
            heros_charm_flag = 0;
        }
        dComIfGs_onCollect(HEROS_CHARM_OWNED_INDEX, heros_charm_flag);
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

    tww_sprintf(lines[MENU_ITEM_SWORD].value, " <%s>", item_id_to_str(dComIfGs_getSelectEquip(SWORD_INDEX)));
    tww_sprintf(lines[MENU_ITEM_SHIELD].value, " <%s>", item_id_to_str(dComIfGs_getSelectEquip(SHIELD_INDEX)));
    tww_sprintf(lines[MENU_ITEM_MAGIC].value, " <%s>", get_magic_string(dComIfGs_getMaxMagic()));
    tww_sprintf(lines[MENU_ITEM_WALLET].value, " <%s>",
                get_wallet_string(g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize()));
    tww_sprintf(lines[MENU_ITEM_QUIVER].value, " <%s>", get_quiver_string(dComIfGs_getArrowMax()));
    tww_sprintf(lines[MENU_ITEM_HURRICANE_SPIN].value, " <%s>", get_hurricane_spin_string());
    tww_sprintf(lines[MENU_ITEM_HEROES_CLOTHES].value, " <%s>", get_heroes_clothes_string());
    tww_sprintf(lines[MENU_ITEM_BOMBAG].value, " <%s>", get_bombags_string(dComIfGs_getBombMax()));
    tww_sprintf(lines[MENU_ITEM_POWER_BRACELETS].value, " <%s>",
                item_id_to_str(dComIfGs_getSelectEquip(POWER_BRACELETS_INDEX)));
    tww_sprintf(lines[MENU_ITEM_PIRATES_CHARM].value, " <%s>",
                get_pirates_charm_string(dComIfGs_isCollect(PIRATES_CHARM_OWNED_INDEX, 0)));
    tww_sprintf(lines[MENU_ITEM_HEROS_CHARM].value, " <%s>",
                get_heros_charm_string(dComIfGs_isCollect(HEROS_CHARM_OWNED_INDEX, 0)));
    tww_sprintf(lines[MENU_ITEM_WINDS_REQUIEM].value, " <%s>",
                get_song_string(dComIfGs_isTact(WINDS_REQUIEM_VALUE), WINDS_REQUIEM_VALUE));
    tww_sprintf(lines[MENU_ITEM_BALLAD_OF_GALES].value, " <%s>",
                get_song_string(dComIfGs_isTact(BALLAD_OF_GALES_VALUE), BALLAD_OF_GALES_VALUE));
    tww_sprintf(lines[MENU_ITEM_COMMAND_MELODY].value, " <%s>",
                get_song_string(dComIfGs_isTact(COMMAND_MELODY_VALUE), COMMAND_MELODY_VALUE));
    tww_sprintf(lines[MENU_ITEM_EARTH_GODS_LYRIC].value, " <%s>",
                get_song_string(dComIfGs_isTact(EARTH_GODS_LYRIC_VALUE), EARTH_GODS_LYRIC_VALUE));
    tww_sprintf(lines[MENU_ITEM_WIND_GODS_ARIA].value, " <%s>",
                get_song_string(dComIfGs_isTact(WIND_GODS_ARIA_VALUE), WIND_GODS_ARIA_VALUE));
    tww_sprintf(lines[MENU_ITEM_SONG_OF_PASSING].value, " <%s>",
                get_song_string(dComIfGs_isTact(SONG_OF_PASSING_VALUE), SONG_OF_PASSING_VALUE));
    tww_sprintf(lines[MENU_ITEM_DINS_PEARL].value, " <%s>",
                get_pearl_string(dComIfGs_isSymbol(DINS_PEARL_VALUE), DINS_PEARL_VALUE));
    tww_sprintf(lines[MENU_ITEM_FARORES_PEARL].value, " <%s>",
                get_pearl_string(dComIfGs_isSymbol(FARORES_PEARL_VALUE), FARORES_PEARL_VALUE));
    tww_sprintf(lines[MENU_ITEM_NAYRUS_PEARL].value, " <%s>",
                get_pearl_string(dComIfGs_isSymbol(NAYRUS_PEARL_VALUE), NAYRUS_PEARL_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_1].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_1_VALUE), TRIFORCE_PIECE_1_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_2].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_2_VALUE), TRIFORCE_PIECE_2_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_3].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_3_VALUE), TRIFORCE_PIECE_3_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_4].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_4_VALUE), TRIFORCE_PIECE_4_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_5].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_5_VALUE), TRIFORCE_PIECE_5_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_6].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_6_VALUE), TRIFORCE_PIECE_6_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_7].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_7_VALUE), TRIFORCE_PIECE_7_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_8].value, " <%s>",
                get_triforce_string(dComIfGs_isTriforce(TRIFORCE_PIECE_8_VALUE), TRIFORCE_PIECE_8_VALUE));

    cursor.move(0, NUM_QUEST_ITEMS);
    GZ_drawMenuLines(lines, cursor.y, NUM_QUEST_ITEMS);
}