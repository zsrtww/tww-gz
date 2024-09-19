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
           &g_tools[DEBUG_INDEX].active},
          {"display time info", TIME_DISP_INDEX, "Display current day, time and moon phase", true,
           &g_tools[TIME_DISP_INDEX].active},
          {"stage info", STAGE_INFO_INDEX, "show Link's current stage info", true, &g_tools[STAGE_INFO_INDEX].active},
          {"teleport", TELEPORT_INDEX, "R+D-pad up to save position. R+D-pad down to load", true,
           &g_tools[TELEPORT_INDEX].active},
          {"area reload", AREA_RELOAD_INDEX, "Reload stage with L + R + A + Start, may crash/softlock after a void",
           true, &g_tools[AREA_RELOAD_INDEX].active},
          {"map select", MAP_SELECT_INDEX, "Load map select by holding D-pad down + Y + Z", true,
           &g_tools[MAP_SELECT_INDEX].active},
          {"zombie hover info", ZH_INDEX, "Display A and B button presses per second", true, &g_tools[ZH_INDEX].active},
          {"input viewer", INPUT_VIEWER_INDEX, "Show current inputs", true, &g_tools[INPUT_VIEWER_INDEX].active},
          {"timers", FRAME_COUNT_INDEX, "Toggle timers with L+R+D-pad Right, reset with L+R+D-pad Left", true,
           &g_tools[FRAME_COUNT_INDEX].active},
          {"frame advance", FRAME_ADVANCE_INDEX, "D-pad Down to pause/unpause, D-pad Up to advance frames", true,
           &g_tools[FRAME_ADVANCE_INDEX].active},
          {"ess checker", ESS_CHECKER_INDEX, "Change input stick color based on distance from ideal ESS", true,
           &g_tools[ESS_CHECKER_INDEX].active},
          {"deadzone checker", DEADZONE_CHECKER_INDEX, "Change input viewer stick color if stick is in deadzone", true,
           &g_tools[DEADZONE_CHECKER_INDEX].active},
          {"disable save checks", DISABLE_SVCHECK_INDEX, "Disables save location checks, set used spawn ID in settings",
           true, &g_tools[DISABLE_SVCHECK_INDEX].active},
          {"intro skip", INTRO_SKIP_INDEX, "Skips the intro cutscenes when starting a new file", true,
           &g_tools[INTRO_SKIP_INDEX].active},
          {"room reload/void out", VOID_INDEX, "Reload room by void out by pressing L + R + B + Start", true,
           &g_tools[VOID_INDEX].active}} {}

ToolsMenu::~ToolsMenu() {}

void ToolsMenu::draw() {
    cursor.move(0, MENU_LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_tools[cursor.y].active = !g_tools[cursor.y].active;

        if (g_tools[cursor.y].active) {
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
