#include "menus/tools_menu.h"
#include "menus/settings_menu.h"
#include "menus/main_menu.h"
#include "menu.h"
#include "utils/card.h"
#include "libtww/MSL_C/string.h"
#include "lib.h"
#include "font.h"
#include "utils/draw.h"
#include "utils/hook.h"

#define LINE_NUM 3
Cursor ToolsMenu::cursor;

bool g_debugInfo = false;
bool g_areaReload;
bool g_teleport;
bool g_inputViewer;

Line lines[LINE_NUM] = {
    {"Link Debug Info", DEBUG_INDEX, "Display position and angle data for Link.", true, &g_debugInfo},
    {"Teleport", TELEPORT_INDEX, "Set and load saved positions. Set with R + D-pad up and load with R + D-pad down.", true, &g_teleport},
    {"Area Reload", AREA_RELOAD_INDEX, "Reloads the current room by pressing L + R + A + Start", true,
     &g_areaReload},
};

void ToolsMenu::draw(){
 cursor.setMode(Cursor::MODE_LIST);
 cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(GZPad::B)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    if (GZ_getButtonTrig(GZPad::A)) {
        switch (cursor.y){
            case DEBUG_INDEX:
                g_debugInfo =! g_debugInfo;
                return;

            case TELEPORT_INDEX:
                g_teleport =! g_teleport;
                if (g_teleport == true){
                    if (tww_mPadStatus.button == (CButton::R | CButton::DPAD_DOWN) && l_fopScnRq_IsUsingOfOverlap != 1) {
                    //store position info;
                    }
                    if (tww_mPadStatus.button == (CButton::R | CButton::DPAD_UP) && l_fopScnRq_IsUsingOfOverlap != 1) {
                    //load position info
                    }
                }                
                return;

            case AREA_RELOAD_INDEX:
                g_areaReload =! g_areaReload;
                if (g_areaReload == true && tww_mPadStatus.button == (CButton :: L | CButton::R | CButton::A | CButton::START) && l_fopScnRq_IsUsingOfOverlap != 1){
                    //reload the room
                }
                return;
        }
    }

 GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}



