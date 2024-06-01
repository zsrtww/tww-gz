#pragma once
#include "menu.h"

enum DeliveryBagMenuIndex {
    SLOT1_INDEX,
    SLOT2_INDEX,
    SLOT3_INDEX,
    SLOT4_INDEX,
    SLOT5_INDEX,
    SLOT6_INDEX,
    SLOT7_INDEX,
    SLOT8_INDEX,

    DELIVERY_BAG_MAX,
};

class DeliveryBagMenu : public Menu {
public:
    DeliveryBagMenu(Cursor&);
    virtual ~DeliveryBagMenu();
    virtual void draw();

private:
    Line lines[DELIVERY_BAG_MAX];
};
