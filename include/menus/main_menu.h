#include "menu.h"

enum MainMenuIndex {
    CHEAT_INDEX,
    FLAGS_INDEX,
    INVENTORY_INDEX,
    MEMORY_INDEX,
    PRACTICE_INDEX,
    SCENE_INDEX,
    SETTINGS_INDEX,
    TOOLS_INDEX,
};

class MainMenu : public Menu {
public:
    MainMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};