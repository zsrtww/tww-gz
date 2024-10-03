#include "menu.h"

enum AnyPercentSaves {
    MSS,
    POST_MSS,
    FF1O,
    BOMBS_ANY,
    ROPES_2_ANY,
    FH_SWIM_ANY,
    DTCS_ANY,
    LEAF_HOVER,
    QUIVER_FF2,
    FF2_SWIM_ANY,
    HELM_SKIP,
    BARRIER_SKIP_ANY,
    TRIALS_SKIP_ANY,
    PG_FIGHT_ANY,
    MORTH_HOVER_ANY,
    GANONDORF_ANY,

    ANY_SAVES_COUNT
};

class AnySavesMenu : public Menu {
public:
    AnySavesMenu(Cursor& cursor);
    virtual ~AnySavesMenu();
    virtual void draw();

private:
    Line lines[ANY_SAVES_COUNT];
};