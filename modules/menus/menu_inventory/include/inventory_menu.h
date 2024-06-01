#include "menu.h"

enum InventoryMenuIndex {
    AMOUNT_INDEX,
    ITEM_INVENTORY_INDEX,
    QUEST_STATUS_INDEX,
    DELIVERY_BAG_INDEX,
    SPOILS_INDEX,
    BAIT_INDEX,
    CHART_INDEX,

    INVENTORY_MENU_MAX,
};

class InventoryMenu : public Menu {
public:
    InventoryMenu(Cursor&);
    virtual ~InventoryMenu();
    virtual void draw();

private:
    Line lines[INVENTORY_MENU_MAX];
};