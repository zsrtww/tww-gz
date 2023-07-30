#pragma once

#include "font.h"
#include "gcn_c/include/storage.h"
#include "menu.h"
#include "menus/tools_menu.h"
#include "menus/cheat_menu.h"
#include "menus/watches_menu.h"
#include "commands.h"
#include "cheats.h"

s32 GZ_storageWrite(Storage* info, void* data, s32 size, s32 offset,
                        s32 sector_size);
s32 GZ_storageRead(Storage* info, void* data, s32 size, s32 offset,
                       s32 sector_size);
void GZ_storeMemCard(Storage& card);
void GZ_storeMemfile(Storage& card);
void GZ_deleteMemCard(Storage& card);
void GZ_deleteMemfile(Storage& card);
void GZ_loadMemCard(Storage& card);
void GZ_loadMemfile(Storage& card);
void GZ_loadGZSave(bool& card_load);

//#define GZ_SAVE_VERSION_NUMBER 0
//#define GZ_SAVE_ENTRIES_AMNT 7