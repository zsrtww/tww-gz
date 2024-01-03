#include "menu.h"
#include "libtww/d/kankyo/d_kankyo.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/f_op/f_op_scene_req.h"
#include "libtww/m_Do/m_Do_main.h"
#include "controller.h"

enum SceneMenuIndex {
    MODIFY_WIND_INDEX,
    MODIFY_CHART_SET_INDEX,
    TIME_HOURS_INDEX,
    TIME_MINUTES_INDEX,
    MODIFY_DATE_INDEX,
};

struct GZScene {
    int index;
    bool active;
};

extern GZScene g_scene[5];

class SceneMenu : public Menu {
public:
    SceneMenu() : Menu() {}
    static void draw();
    

    static Cursor cursor;
};

