#include "menus/menu_tools/include/tools_menu.h"
#include <cstdio>
#include "commands.h"
#include "global_data.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/dolphin/os/OSCache.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#ifdef NTSCJ
#define INTRO_SKIP_INST0_ADDR 0x8023031c
#define INTRO_SKIP_INST1_ADDR 0x8023032c
#define INTRO_SKIP_ORIG_INST0 0x48000EB9
#define INTRO_SKIP_ORIG_INST1 0x4082000C
#endif

#ifdef NTSCU
#define INTRO_SKIP_INST0_ADDR 0x80232c78
#define INTRO_SKIP_INST1_ADDR 0x80232c88
#define INTRO_SKIP_ORIG_INST0 0x48000F6D
#define INTRO_SKIP_ORIG_INST1 0x4082000C
#endif

#ifdef PAL
#define INTRO_SKIP_INST0_ADDR 0x80237d00
#define INTRO_SKIP_INST1_ADDR 0x80237d10
#define INTRO_SKIP_ORIG_INST0 0x48000F6D
#define INTRO_SKIP_ORIG_INST1 0x4082000C
#endif

KEEP_FUNC ToolsMenu::ToolsMenu(Cursor& cursor)
    : Menu(cursor),
      lines{
          {"link debug info", DEBUG_INDEX, "Display position and angle data for Link", true,
           [](){return GZStng_getData(STNG_TOOLS_DEBUG, false);}},
          {"display time info", TIME_DISP_INDEX, "Display current day, time and moon phase", true,
           [](){return GZStng_getData(STNG_TOOLS_TIME_DISP, false);}},
          {"stage info", STAGE_INFO_INDEX, "show Link's current stage info", true, [](){return GZStng_getData(STNG_TOOLS_STAGE_INFO, false);}},
          {"teleport", TELEPORT_INDEX, "R+D-pad up to save position. R+D-pad down to load", true,
           [](){return GZStng_getData(STNG_TOOLS_TELEPORT, false);}},
          {"area reload", AREA_RELOAD_INDEX, "Reload stage with L + R + A + Start", true,
           [](){return GZStng_getData(STNG_TOOLS_AREA_RELOAD, false);}},
          {"map select", MAP_SELECT_INDEX, "Load map select by holding D-pad down + Y + Z", true,
           [](){return GZStng_getData(STNG_TOOLS_MAP_SELECT, false);}},
          {"zombie hover info", ZH_INDEX, "Display A and B button presses per second", true, [](){return GZStng_getData(STNG_TOOLS_ZH, false);}},
          {"input viewer", INPUT_VIEWER_INDEX, "Show current inputs", true, [](){return GZStng_getData(STNG_TOOLS_INPUT_VIEWER, false);}},
          {"timers", FRAME_COUNT_INDEX, "Toggle timers with L+R+D-pad Right, reset with L+R+D-pad Left", true,
           [](){return GZStng_getData(STNG_TOOLS_FRAME_COUNT, false);}},
          {"frame advance", FRAME_ADVANCE_INDEX, "D-pad Down to pause/unpause, D-pad Up to advance frames", true,
           [](){return GZStng_getData(STNG_TOOLS_FRAME_ADVANCE, false);}},
          {"ess checker", ESS_CHECKER_INDEX, "Change input stick color based on distance from ideal ESS", true,
           [](){return GZStng_getData(STNG_TOOLS_ESS_CHECKER, false);}},
          {"deadzone checker", DEADZONE_CHECKER_INDEX, "Change input viewer stick color if stick is in deadzone", true,
           [](){return GZStng_getData(STNG_TOOLS_DEADZONE_CHECKER, false);}},
          {"disable save checks", DISABLE_SVCHECK_INDEX, "Disables save location checks, set used spawn ID in settings",
           true, [](){return GZStng_getData(STNG_TOOLS_DISABLE_SVCHECK, false);}},
          {"intro skip", INTRO_SKIP_INDEX, "Skips the intro cutscenes when starting a new file", true,
           [](){return GZStng_getData(STNG_TOOLS_INTRO_SKIP, false);}},
          {"room reload/void out", VOID_INDEX, "Reload room by void out by pressing L + R + B + Start", true,
           [](){return GZStng_getData(STNG_TOOLS_VOID, false);}}} {}

ToolsMenu::~ToolsMenu() {}

GZSettingID l_mapping[] = {
    STNG_TOOLS_DEBUG,
    STNG_TOOLS_TIME_DISP,
    STNG_TOOLS_STAGE_INFO,
    STNG_TOOLS_TELEPORT,
    STNG_TOOLS_AREA_RELOAD,
    STNG_TOOLS_MAP_SELECT,
    STNG_TOOLS_ZH,
    STNG_TOOLS_INPUT_VIEWER,
    STNG_TOOLS_FRAME_COUNT,
    STNG_TOOLS_FRAME_ADVANCE,
    STNG_TOOLS_ESS_CHECKER,
    STNG_TOOLS_DEADZONE_CHECKER,
    STNG_TOOLS_DISABLE_SVCHECK,
    STNG_TOOLS_INTRO_SKIP,
    STNG_TOOLS_VOID,
};

void ToolsMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        auto stng = GZStng_get(l_mapping[cursor.y]);
        if (!stng) {
            stng = new GZSettingEntry{l_mapping[cursor.y], sizeof(bool), new bool{false}};
            g_settings.push_back(stng);
        }
        *static_cast<bool*>(stng->data) = !*static_cast<bool*>(stng->data);

        if (*static_cast<bool*>(stng->data)) {
            switch (cursor.y) {
            case TELEPORT_INDEX:
                GZCmd_enable(Commands::CMD_STORE_POSITION);
                GZCmd_enable(Commands::CMD_LOAD_POSITION);
                break;
            case FRAME_COUNT_INDEX:
                GZCmd_enable(Commands::CMD_TOGGLE_TIMER);
                GZCmd_enable(Commands::CMD_RESET_TIMER);
                break;
            case AREA_RELOAD_INDEX:
                GZCmd_enable(Commands::CMD_AREA_RELOAD);
                break;
            case VOID_INDEX:
                GZCmd_enable(Commands::CMD_VOID);
                break;
            case INTRO_SKIP_INDEX:
                *reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR) = 0x60000000;  // nop
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));

                *reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR) = 0x60000000;  // nop
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                break;
            }
        } else {
            switch (cursor.y) {
            case TELEPORT_INDEX:
                GZCmd_disable(Commands::CMD_STORE_POSITION);
                GZCmd_disable(Commands::CMD_LOAD_POSITION);
                break;
            case FRAME_COUNT_INDEX:
                GZCmd_disable(Commands::CMD_TOGGLE_TIMER);
                GZCmd_disable(Commands::CMD_RESET_TIMER);
                break;
            case AREA_RELOAD_INDEX:
                GZCmd_disable(Commands::CMD_AREA_RELOAD);
                break;
            case VOID_INDEX:
                GZCmd_disable(Commands::CMD_VOID);
                break;
            case INTRO_SKIP_INDEX:
                *reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR) =
                    INTRO_SKIP_ORIG_INST0;  // bl dScnOpen_proc_c::proc_execute
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST0_ADDR), sizeof(u32));

                *reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR) = INTRO_SKIP_ORIG_INST1;  // bne ret
                DCFlushRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                ICInvalidateRange(reinterpret_cast<u32*>(INTRO_SKIP_INST1_ADDR), sizeof(u32));
                break;
            }
        }
    }

    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
