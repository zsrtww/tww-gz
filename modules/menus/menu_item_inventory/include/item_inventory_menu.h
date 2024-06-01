#include "menu.h"

class ItemInventoryMenu : public Menu {
public:
    ItemInventoryMenu(Cursor&);
    virtual ~ItemInventoryMenu();
    virtual void draw();

private:
    Line lines[21];
};