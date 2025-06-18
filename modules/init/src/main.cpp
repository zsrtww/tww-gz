#include <main.h>
#include "boot.h"
#include "fifo_queue.h"
#include "font.h"
#include "menu.h"
#include "pos_settings.h"
#include "geometry_draw.h"
#include "modules.h"
#include "menus/utils/menu_mgr.h"
#include "libtww/include/m_Do/m_Do_ext.h"

#include "utils/memory.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "utils/link.h"
#include "gz_flags.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"
#include "events/pre_loop_listener.h"
#include "events/post_loop_listener.h"

#define NOP_INSTRUCTION(addr)                                                                                          \
    *reinterpret_cast<u32*>(addr) = 0x60000000;                                                                        \
    DCFlushRange((void*)addr, sizeof(u32));                                                                            \
    ICInvalidateRange((void*)addr, sizeof(u32));

namespace twwgz::modules {
void main() {
    // Utilities initialization
    Hook::applyHooks();
    Font::loadFont("/twwgz/fonts/consola.fnt");
    Draw::init();
    GZ_PosSettings_initDefaults();

    g_menuMgr = new MenuMgr();
    g_fifoVisible = true;
    // Init the draw listener
    g_drawListener = new DrawListener();
    // Setup the render order
    g_drawListener->addListener(GZ_renderMenuTitle);
    g_drawListener->addListener(GZ_renderFifoQueue);
    g_drawListener->addListener(GZ_displayLinkInfo);
    g_drawListener->addListener(GZ_displayTimeInfo);
    g_drawListener->addListener(GZ_frameCounter);
    g_drawListener->addListener(GZ_rollClipInfo);
    g_drawListener->addListener(GZ_displayStageInfo);
    g_drawListener->addListener(GZ_displayZombieHoverInfo);
    g_drawListener->addListener(GZ_displaySplash);
    g_drawListener->addListener(GZ_drawWatches);

    // Init the pre-loop listener
    g_PreLoopListener = new PreLoopListener();
    g_PreLoopListener->addListener(GZ_handleMenu);
    g_PreLoopListener->addListener(GZ_handleFlags_PreLoop);
    g_PreLoopListener->addListener(GZ_frameAdvance);
    g_PreLoopListener->addListener(GZ_setCursorColor);
    g_PreLoopListener->addListener(GZ_drawPolygons);
    g_PreLoopListener->addListener(GZ_handleModules);

    // Init the post-loop listener
    g_PostLoopListener = new PostLoopListener();
    g_PostLoopListener->addListener(GZ_handleFlags_PostLoop);
    g_PostLoopListener->addListener(GZ_setCursorColor);
    g_PostLoopListener->addListener(GZ_processActorModRequests);

    // Init the module list
    g_modules.push_back(new Module{inputViewer_active, "/twwgz/rels/features/input_viewer.rel"});
    g_modules.push_back(new Module{actorView_active, "/twwgz/rels/features/actor_view.rel"});

    // Manually nop calls to JUTReport in Map Select, so we can replace them later.
    // This sucks, especially because of multiversion. But it works.

#ifdef NTSCJ
    NOP_INSTRUCTION(0x8022c19c);
    NOP_INSTRUCTION(0x8022c1c8);
    NOP_INSTRUCTION(0x8022c2e4);
    NOP_INSTRUCTION(0x8022c37c);
    NOP_INSTRUCTION(0x8022c3a8);
    NOP_INSTRUCTION(0x8022c3c4);
    NOP_INSTRUCTION(0x8022c3f0);
    NOP_INSTRUCTION(0x8022c428);
    NOP_INSTRUCTION(0x8022c448);
    NOP_INSTRUCTION(0x8022c470);
#endif
#ifdef NTSCU
    NOP_INSTRUCTION(0x8022ea24);
    NOP_INSTRUCTION(0x8022ea50);
    NOP_INSTRUCTION(0x8022eb6c);
    NOP_INSTRUCTION(0x8022ec04);
    NOP_INSTRUCTION(0x8022ec30);
    NOP_INSTRUCTION(0x8022ec4c);
    NOP_INSTRUCTION(0x8022ec78);
    NOP_INSTRUCTION(0x8022ecb0);
    NOP_INSTRUCTION(0x8022ece8);
    NOP_INSTRUCTION(0x8022ed08);
    NOP_INSTRUCTION(0x8022ed30);
#endif
#ifdef PAL
    NOP_INSTRUCTION(0x80232dfc);
    NOP_INSTRUCTION(0x80232e28);
    NOP_INSTRUCTION(0x80232f44);
    NOP_INSTRUCTION(0x80232fdc);
    NOP_INSTRUCTION(0x80233008);
    NOP_INSTRUCTION(0x80233024);
    NOP_INSTRUCTION(0x80233050);
    NOP_INSTRUCTION(0x80233088);
    NOP_INSTRUCTION(0x802330c0);
    NOP_INSTRUCTION(0x802330e0);
    NOP_INSTRUCTION(0x80233108);
#endif
}
void exit() {}

}  // namespace twwgz::modules