#include <boot.h>
#include "controller.h"
#include "fifo_queue.h"
#include "font.h"
#include "gz_flags.h"
#include "libtww/include/m_Do/m_Do_printf.h"
#include "menu.h"
#include "settings.h"
#include "fifo_queue.h"
#include "menus/utils/menu_mgr.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/memory.h"
#include "utils/texture.h"
#include "libtww/include/d/com/d_com_inf_game.h"
#include "libtww/include/f_op/f_op_scene_req.h"
#include "rels/include/cxx.h"
#include "utils/rels.h"
#include "rels/include/defines.h"
#include "events/draw_listener.h"
#include "events/pre_loop_listener.h"
#include "events/post_loop_listener.h"

#define isWidescreen (false)

_FIFOQueue Queue;
bool l_loadCard = true;
Texture l_gzIconTex;
bool last_frame_was_loading = false;

#define Q(x) #x
#define QUOTE(x) Q(x)

#ifdef GZ_VERSION
#define INTERNAL_GZ_VERSION QUOTE(GZ_VERSION)
#else
#warning GZ_VERSION is not defined
#define INTERNAL_GZ_VERSION "<unk>"
#endif

#define BUTTONS (GZ_getButtonStatus())
#define CANCEL_LOAD_BUTTONS (CButton::L | CButton::R | CButton::B)
#define SHOW_MENU_BUTTONS (CButton::L | CButton::R | CButton::DPAD_DOWN)

namespace twwgz::modules {
void main() {
    OSReportEnable();
    OSReport("TWWGZ is starting...\n");
    // Run the initialization module.
    twwgz::dyn::GZModule* initRel = new twwgz::dyn::GZModule("/twwgz/rels/init.rel");
    initRel->loadFixed(true);
    // The initialization module doesn't need to be kept in memory once ran.
    // initRel->close(); // This code is implicitly ran in the destructor.
    delete initRel;

    if (l_gzIconTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("/twwgz/tex/twwgz.tex", &l_gzIconTex);
    }
}
void exit() {}

}  // namespace twwgz::modules

// Game hooks
extern "C" {

/**
 * @brief Hooked to run right before the next main loop starts.
 */
KEEP_FUNC void game_loop() {
    // Call all the functions registered to be run before the main loop.
    g_PreLoopListener->dispatchAll();
}

/**
 * @brief Hooked to run right after the current main loop finishes.
 */
KEEP_FUNC void post_game_loop() {
    // Call all the functions registered to be run after the main loop.
    g_PostLoopListener->dispatchAll();
}

/**
 * @brief Hooked to run in the render thread.
 */
KEEP_FUNC void draw() {
    // Setup the graphic library for our drawing utility API.
    setupRendering();
    // Call all the functions registered to be run in the render thread.
    g_drawListener->dispatchAll();
}
}

/**
 * @brief Handles when to show/hid the menus.
 */
KEEP_FUNC void GZ_handleMenu() {
    if (BUTTONS == SHOW_MENU_BUTTONS && l_fopScnRq_IsUsingOfOverlap != 1) {
        if (!g_menuMgr->isOpen()) {
            if (!g_menuMgr->isEmpty()) {
                g_menuMgr->open();
            } else {
                g_menuMgr->push(MN_MAIN_MENU_INDEX);
            }
        }

        g_fifoVisible = false;
    }

    if (l_fopScnRq_IsUsingOfOverlap) {
        g_menuMgr->hide();
        last_frame_was_loading = true;
    }

    g_menuMgr->handleCommands();
}

KEEP_FUNC void GZ_handleCardLoad() {
    // Button combo to bypass the automatic loading of the save file
    // in case of crash caused by the load.
    if (BUTTONS == CANCEL_LOAD_BUTTONS && l_loadCard) {
        l_loadCard = false;
    }

    // check and load gz settings card if found
    // GZ_loadGZSave(l_loadCard);
}

KEEP_FUNC void GZ_renderMenuTitle() {
    if (g_menuMgr->isOpen()) {
        Font::GZ_drawStr("twwgz v" INTERNAL_GZ_VERSION, 25.0f + 35.0f, 25.0f,
                         g_cursorColor, g_dropShadows);
        if (l_gzIconTex.loadCode == TexCode::TEX_OK) {
            Draw::drawRect(0xFFFFFFFF, {25.0f, 5.0f},
                           {30 * (isWidescreen ? 0.75f : 1.0f), 30}, &l_gzIconTex._texObj);
        }
    }
}
