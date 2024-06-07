#include <main.h>
#include "boot.h"
#include "fifo_queue.h"
#include "font.h"
#include "menu.h"
#include "pos_settings.h"
#include "menus/utils/menu_mgr.h"
#include "libtww/include/m_Do/m_Do_ext.h"

#include "utils/memory.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "utils/link.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"
#include "events/pre_loop_listener.h"
#include "events/post_loop_listener.h"

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
    g_drawListener->addListener(GZ_displayZombieHoverInfo);
    g_drawListener->addListener(GZ_displaySplash);
    g_drawListener->addListener(GZ_drawWatches);
    
    // Init the pre-loop listener
    g_PreLoopListener = new PreLoopListener();
    g_PreLoopListener->addListener(GZ_handleCardLoad);
    g_PreLoopListener->addListener(GZ_handleMenu);
    g_PreLoopListener->addListener(GZ_handleFlags_PreLoop);
    g_PreLoopListener->addListener(GZ_setCursorColor);
    g_PreLoopListener->addListener(GZ_handleRelTools);
    
    // Init the post-loop listener
    g_PostLoopListener = new PostLoopListener();
    g_PostLoopListener->addListener(GZ_handleFlags_PostLoop);
    g_PostLoopListener->addListener(GZ_setCursorColor);
}
void exit() {}

}  // namespace twwgz::modules