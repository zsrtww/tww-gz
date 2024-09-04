#pragma once
#include "menu.h"

enum DungeonMenuIndex {
    PICK_DUNGEON_INDEX,
    MODIFY_KEYS_INDEX,
    BOSS_KEY_INDEX,
    MAP_INDEX,
    COMPASS_INDEX,
    PARTNER_INDEX,

    DUNGEON_FLAGS_MAX
};

class DungeonFlagsMenu : public Menu {
public:
    DungeonFlagsMenu(Cursor&);
    virtual ~DungeonFlagsMenu();
    virtual void draw();

private:
    Line lines[DUNGEON_FLAGS_MAX];
};
