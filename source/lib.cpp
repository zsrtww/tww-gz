#include "lib.h"
#include "font.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "utils/card.h"
#include "menu.h"
#include "controller.h"
#include "menus/settings_menu.h"

bool l_loadCard = true;

extern "C" {

// Use the supplied string from the Makefile
#define MAKESTRING(S) MAKESTRING_(S)
#define MAKESTRING_(S) #S

#define INTERNAL_GZ_VERSION MAKESTRING(GZ_VERSION)

#define main_trampoline ((void (*)(void))0x80336068)

void apply_lib_hooks() {
    Hook::applyHooks();
    main_trampoline();
}

void init() {
    *reinterpret_cast<u8*>(0x803f60e0) = 1;  // Enable debug crash screen
    Font::loadFont("twwgz/fonts/consola.fnt");
    Draw::init();
}

void game_loop() {
    // check and load gz settings card if found
    GZ_loadGZSave(l_loadCard);

    if (tww_mPadStatus.button == (CButton::L | CButton::R | CButton::DPAD_DOWN) && l_fopScnRq_IsUsingOfOverlap != 1) {
        GZ_setMenu(GZ_MAIN_MENU);
    }

    if (l_fopScnRq_IsUsingOfOverlap) {
        GZ_clearMenu();
    }

    GZ_setCursorColor();
}

void displaySplash() {
    // Create and render a splash screen once the game has launched using the supplied address
    extern uint32_t* mDoExt_font0;
    static int splash_time = 256;

    if (splash_time > 0) {
        if (mDoExt_font0 == nullptr) {
            return;
        }

        // Set up the splash properties
        const char* name = MAKESTRING(PACKAGE_NAME);
        const char* url = MAKESTRING(PACKAGE_URL);
        float splash_x = 200.0f;
        float splash_y = 440.0f;

        // Finally draw the string
        Font::GZ_drawStr(name, splash_x, splash_y, 0xFFFFFFFF, true, 18.0f);
        Font::GZ_drawStr(url, splash_x, splash_y + 25.0f, 0xFFFFFFFF, true, 18.0f);

        // Then when splash_time hits < 1, it won't display the string anymore
        splash_time--;
    }
}

void draw() {
    // Setup rendering so we can display things on screen
    setupRendering();
    displaySplash();

    if (GZ_checkMenuOpen()) {
        Font::GZ_drawStr("twwgz v" INTERNAL_GZ_VERSION, 10.0f, 25.0f, g_cursorColor, g_dropShadows);
    }

    GZ_drawMenu();
}
}
