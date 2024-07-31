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

    MAIN_MENU_MAX,
};

class MainMenu : public Menu {
public:
    MainMenu(Cursor&);
    virtual ~MainMenu();
    virtual void draw();

private:
    Line lines[MAIN_MENU_MAX];
};