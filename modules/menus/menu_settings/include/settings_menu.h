#pragma once

#include "menu.h"
#include "settings.h"

enum SettingsIndex {
    CURSOR_COLOR_INDEX,
    FONT_INDEX,
    DROP_SHADOWS_INDEX,
    ITEM_EQUIP_PRIORITY_INDEX,
    SAVE_CARD_INDEX,
    LOAD_CARD_INDEX,
    DELETE_CARD_INDEX,
    POS_SETTINGS_MENU_INDEX,
    WATER_SPEED_INDEX,
    LAND_SPEED_INDEX,

    SETTINGS_COUNT
};

class SettingsMenu : public Menu {
public:
    SettingsMenu(Cursor&);
    virtual ~SettingsMenu();
    virtual void draw();

private:
    Line lines[SETTINGS_COUNT];
};