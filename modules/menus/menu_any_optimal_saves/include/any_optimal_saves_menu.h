#include "menu.h"

enum AnyPercentOptimalSaves {
    MSS,
    POST_MSS,
    FF1O,
    DC_LEAF,
    FH_CLIMB,
    DTCS,
    DC_FF2,
    HELM_SKIP,
    BARRIER_SKIP,
    TRIAL_SKIP,
    LA_SKIP,
    PGCS,
    PGS,
    GANON,

    ANY_OPTIMAL_SAVES_COUNT
};

class AnyOptimalSavesMenu : public Menu {
public:
    AnyOptimalSavesMenu(Cursor& cursor);
    virtual ~AnyOptimalSavesMenu();
    virtual void draw();

private:
    Line lines[ANY_OPTIMAL_SAVES_COUNT];
};