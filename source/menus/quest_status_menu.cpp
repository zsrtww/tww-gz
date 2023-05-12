#include "controller.h"
#include "menus/main_menu.h"
#include "menus/inventory_menu.h"
#include "menus/quest_status_menu.h"
#include "libtww/MSL_C/string.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/d/save/d_save.h"

#define NUM_QUEST_ITEMS 25

Cursor QuestStatusMenu::cursor;

Line lines[NUM_QUEST_ITEMS] = {
    {"Sword:", MENU_ITEM_SWORD, "Add/remove/upgrade sword"},
    {"Shield:", MENU_ITEM_SHIELD, "Add/remove/upgrade shield"},
    {"Magic:", MENU_ITEM_MAGIC, "Add/remove/upgrade magic"},
    {"Quiver:", MENU_ITEM_QUIVER, "Add/remove/upgrade Quiver"},
    {"Bombs Bags :", MENU_ITEM_BOMBAG, "Add/remove/upgrade Quiver"},
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
    {"Triforce Piece 8:", MENU_ITEM_TRIFORCE_PIECE_8,"Add/remove triforce piece 8 from inventory"}};

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

const char* get_song_string(u8 songs_owned, u8 song) {
    if ((songs_owned & song) == 0) {
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
    if ((pearls_owned & pearl) == 0) {
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
    if ((triforce_owned & triforce_piece) == 0) {
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

void updateSongs(u8 song_value) {
    u8 songs_owned = dComIfGs_getSongsOwned();
    u8 has_song = songs_owned & song_value;
    if (has_song == 0)
        has_song = 0xFE;
    Cursor::moveListSimple(has_song);
    if (has_song == 0xFF) {
        dComIfGs_setSongsOwned(songs_owned + song_value);
    } else if (has_song == song_value - 1) {
        dComIfGs_setSongsOwned(songs_owned - song_value);
    }
}

void updatePearls(u8 pearl_value) {
    u8 pearls_owned = dComIfGs_getPearlsOwned();
    u8 has_pearl = pearls_owned & pearl_value;
    if (has_pearl == 0)
        has_pearl = 0xFE;
    Cursor::moveListSimple(has_pearl);
    if (has_pearl == 0xFF) {
        dComIfGs_setPearlsOwned(pearls_owned + pearl_value);
    } else if (has_pearl == pearl_value - 1) {
        dComIfGs_setPearlsOwned(pearls_owned - pearl_value);
    }
}

void updateTriforce(u8 triforce_value) {
    u8 triforce_owned = dComIfGs_getTriforceOwned();
    u8 has_triforce_piece = triforce_owned & triforce_value;
    s8 position = 0;
    Cursor::moveListSimple(position);
    if (position == 1 && has_triforce_piece == 0) {
        dComIfGs_setTriforceOwned(triforce_owned + triforce_value);
    } else if (position == -1 && has_triforce_piece > 0) {
        dComIfGs_setTriforceOwned(triforce_owned - triforce_value);
    }
}

void QuestStatusMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
        return;
    }

    u8 new_sword_item_id, new_shield_item_id, new_max_magic_value, new_arrows_capacity,new_bombs_capacity,new_power_bracelets_item_id,
is_pirates_charm_owned, heros_charm_flag;

    switch (cursor.y) {
    case MENU_ITEM_SWORD:
        new_sword_item_id = dComIfGs_getSword();
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
            new_sword_item_id = dComIfGs_getSword();
        }
        dComIfGs_setSword(new_sword_item_id);
        dComIfGs_setSwordOwned(swordIdToSwordOwned(new_sword_item_id));
        break;
    case MENU_ITEM_SHIELD:
        new_shield_item_id = dComIfGs_getShield();
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
            new_shield_item_id = dComIfGs_getShield();
        }
        dComIfGs_setShield(new_shield_item_id);
        dComIfGs_setShieldOwned(shieldIdToShieldOwned(new_shield_item_id));
        break;
    case MENU_ITEM_MAGIC:
        new_max_magic_value = dComIfGs_getMaxMagic();
        Cursor::moveListSimple(new_max_magic_value);
        if (new_max_magic_value == NO_MAGIC - 1) {
            new_max_magic_value = NO_MAGIC;
        } else if (new_max_magic_value == NO_MAGIC) {
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
    case MENU_ITEM_POWER_BRACELETS:
        new_power_bracelets_item_id = dComIfGs_getPowerBracelets();
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
            new_power_bracelets_item_id = dComIfGs_getPowerBracelets();
        }
        dComIfGs_setPowerBracelets(new_power_bracelets_item_id);
        dComIfGs_setPowerBraceletsOwned(powerBraceletsIdToPowerBraceletsOwned(new_power_bracelets_item_id));
        break;
    case MENU_ITEM_QUIVER:
        new_arrows_capacity = dComIfGs_getArrowCapacity();
        Cursor::moveListSimple(new_arrows_capacity);
         if (new_arrows_capacity == NO_QUIVER - 1) {
            new_arrows_capacity = NO_QUIVER;
        } else if (new_arrows_capacity == NO_QUIVER + 1) {
              new_arrows_capacity = ARROWS_30;
        } else if (new_arrows_capacity == NO_QUIVER) {
            new_arrows_capacity = NO_QUIVER;
             } else if (new_arrows_capacity == ARROWS_30 - 1) {
            new_arrows_capacity = NO_BOMBBAG;
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
            new_arrows_capacity = dComIfGs_getArrowCapacity();
        }
        dComIfGs_setArrowNum(new_arrows_capacity);
        dComIfGs_setArrowCapacity(new_arrows_capacity);
        break;
    case MENU_ITEM_BOMBAG:
        new_bombs_capacity = dComIfGs_getBombCapacity();
        Cursor::moveListSimple(new_bombs_capacity);
         if (new_bombs_capacity == NO_BOMBBAG - 1) {
            new_bombs_capacity = NO_BOMBBAG;
        } else if (new_bombs_capacity == NO_BOMBBAG + 1) {
              new_arrows_capacity = BOMBS_30;
        } else if (new_bombs_capacity == NO_BOMBBAG) {
            new_bombs_capacity = NO_BOMBBAG;
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
            new_bombs_capacity = dComIfGs_getBombCapacity();
        }
        dComIfGs_setBombNum(new_bombs_capacity);
        dComIfGs_setBombCapacity(new_bombs_capacity);
        break;
    case MENU_ITEM_PIRATES_CHARM:
        is_pirates_charm_owned = dComIfGs_getPiratesCharmOwned();
        Cursor::moveListSimple(is_pirates_charm_owned);
        if (is_pirates_charm_owned == 0xFF) {
            is_pirates_charm_owned = 0;
        } else if (is_pirates_charm_owned == 2) {
            is_pirates_charm_owned = 1;
        }
        dComIfGs_setPiratesCharmOwned(is_pirates_charm_owned);
        break;
    case MENU_ITEM_HEROS_CHARM:
        heros_charm_flag = dComIfGs_getHerosCharmOwned();
        Cursor::moveListSimple(heros_charm_flag);
        if (heros_charm_flag == 0xFF) {
            heros_charm_flag = 0;
        } else if (heros_charm_flag == 3) {
            heros_charm_flag = HEROS_CHARM_ENABLED;
        }
        dComIfGs_setHerosCharmOwned(heros_charm_flag);
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

    tww_sprintf(lines[MENU_ITEM_SWORD].value, " <%s>", item_id_to_str(dComIfGs_getSword()));
    tww_sprintf(lines[MENU_ITEM_SHIELD].value, " <%s>", item_id_to_str(dComIfGs_getShield()));
    tww_sprintf(lines[MENU_ITEM_MAGIC].value, " <%s>", get_magic_string(dComIfGs_getMaxMagic()));
    tww_sprintf(lines[MENU_ITEM_QUIVER].value, " <%s>", get_quiver_string(dComIfGs_getArrowCapacity()));
    tww_sprintf(lines[MENU_ITEM_BOMBAG].value, " <%s>", get_bombags_string(dComIfGs_getBombCapacity()));
    tww_sprintf(lines[MENU_ITEM_POWER_BRACELETS].value, " <%s>",
                item_id_to_str(dComIfGs_getPowerBracelets()));
    tww_sprintf(lines[MENU_ITEM_PIRATES_CHARM].value, " <%s>",
                get_pirates_charm_string(dComIfGs_getPiratesCharmOwned()));
    tww_sprintf(lines[MENU_ITEM_HEROS_CHARM].value, " <%s>",
                get_heros_charm_string(dComIfGs_getHerosCharmOwned()));
    tww_sprintf(lines[MENU_ITEM_WINDS_REQUIEM].value, " <%s>",
                get_song_string(dComIfGs_getSongsOwned(), WINDS_REQUIEM_VALUE));
    tww_sprintf(lines[MENU_ITEM_BALLAD_OF_GALES].value, " <%s>",
                get_song_string(dComIfGs_getSongsOwned(), BALLAD_OF_GALES_VALUE));
    tww_sprintf(lines[MENU_ITEM_COMMAND_MELODY].value, " <%s>",
                get_song_string(dComIfGs_getSongsOwned(), COMMAND_MELODY_VALUE));
    tww_sprintf(lines[MENU_ITEM_EARTH_GODS_LYRIC].value, " <%s>",
                get_song_string(dComIfGs_getSongsOwned(), EARTH_GODS_LYRIC_VALUE));
    tww_sprintf(lines[MENU_ITEM_WIND_GODS_ARIA].value, " <%s>",
                get_song_string(dComIfGs_getSongsOwned(), WIND_GODS_ARIA_VALUE));
    tww_sprintf(lines[MENU_ITEM_SONG_OF_PASSING].value, " <%s>",
                get_song_string(dComIfGs_getSongsOwned(), SONG_OF_PASSING_VALUE));
    tww_sprintf(lines[MENU_ITEM_DINS_PEARL].value, " <%s>",
                get_pearl_string(dComIfGs_getPearlsOwned(), DINS_PEARL_VALUE));
    tww_sprintf(lines[MENU_ITEM_FARORES_PEARL].value, " <%s>",
                get_pearl_string(dComIfGs_getPearlsOwned(), FARORES_PEARL_VALUE));
    tww_sprintf(lines[MENU_ITEM_NAYRUS_PEARL].value, " <%s>",
                get_pearl_string(dComIfGs_getPearlsOwned(), NAYRUS_PEARL_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_1].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_1_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_2].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_2_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_3].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_3_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_4].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_4_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_5].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_5_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_6].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_6_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_7].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_7_VALUE));
    tww_sprintf(lines[MENU_ITEM_TRIFORCE_PIECE_8].value, " <%s>",
                get_triforce_string(dComIfGs_getTriforceOwned(), TRIFORCE_PIECE_8_VALUE));

    cursor.move(0, NUM_QUEST_ITEMS);
    GZ_drawMenuLines(lines, cursor.y, NUM_QUEST_ITEMS);
}