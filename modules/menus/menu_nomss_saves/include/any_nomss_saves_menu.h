#include "menu.h"

enum AnyNoMssSaves {
    AFTER_INTRO,
    ORCA,
    FOREST_OF_FAIRIES,
    ROPES_1,
    EARLY_LIGHTS,
    FF1,
    FF1_INTERIOR,
    WINDFALL,
    FH_SWIM,
    EARLY_LEAF,
    DTCS,
    HOLE_IN_ONE,
    FF2_SWIM,
    HELMAROC_SKIP,
    BARRIER_SKIP,
    TRIALS_SKIP,
    PG_FIGHT,
    TUNER_HOVER,
    GANONDORF,

    ANY_NOMSS_SAVES_COUNT,
};

class AnyNoMssSavesMenu : public Menu {
public:
    AnyNoMssSavesMenu(Cursor& cursor);
    virtual ~AnyNoMssSavesMenu();
    virtual void draw();

private:
    Line lines[ANY_NOMSS_SAVES_COUNT];
};