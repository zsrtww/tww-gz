#include "lib.h"
#include "font.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "menu.h"
#include "controller.h"

extern "C" {

// Use the supplied string from the Makefile
#define MAKESTRING(S) MAKESTRING_(S)
#define MAKESTRING_(S) #S

#define main_trampoline ((void (*)(void))0x80336068)

void apply_lib_hooks() {
    Hook::applyHooks();
    main_trampoline();
}

void init() {
    *reinterpret_cast<u8*>(0x803f60e0) = 1;  // Enable debug crash screen
    Font::loadFont("twwgz/fonts/consola.fnt");
    Draw::init();
    g_cursorColorType = 0;
}

void game_loop() {
    if (tww_mPadStatus.button == (CButton::L | CButton::R | CButton::DPAD_DOWN) && l_fopScnRq_IsUsingOfOverlap != 1) {
        GZ_setMenu(GZ_MAIN_MENU);
    }

    if (l_fopScnRq_IsUsingOfOverlap) {
        GZ_clearMenu();
    }

    GZ_setCursorColor();
}

void draw() {

    // Setup rendering so we can display things on screen
    setupRendering();
    
    // Create and render a splash screen once the game has launched using the supplied address
    extern uint32_t *mDoExt_font0;
    static int splash_time = 256;
    
    if (mDoExt_font0 == 0x0) {
        return;
    } else {
        if (splash_time > 0) {
            // Set up the splash properties
            const char *name = MAKESTRING(PACKAGE_NAME);
            const char *url = MAKESTRING(PACKAGE_URL);
            float splash_x = 96.0f;
            float splash_y = 440.0f;

            // Finally draw the string
            Font::GZ_drawStr(name, splash_x, splash_y, 0xFFFFFFFF, true, 18.0f);
            Font::GZ_drawStr(url, splash_x, splash_y + 24.0f, 0xFFFFFFFF, true, 18.0f);

            // Then when splash_time hits < 1, it won't display the string anymore
            splash_time--;
        }
    }

    GZ_drawMenu();
}
}
