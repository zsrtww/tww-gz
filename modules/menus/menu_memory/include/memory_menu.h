#pragma once
#include "menu.h"
#include "settings.h"

enum SettingsIndex {
    WATCHES_INDEX,
    MEM_EDITOR_INDEX,
    FLAG_LOGGER_INDEX,

    MEMORY_COUNT
};

class MemoryMenu : public Menu {
public:
    MemoryMenu(Cursor&);
    virtual ~MemoryMenu();
    virtual void draw();

private:
    Line lines[MEMORY_COUNT];
};
