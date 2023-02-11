#include "lib.h"
#include "font.h"
#include "color.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "utils/card.h"
#include "menu.h"
#include "controller.h"
#include "menus/settings_menu.h"
#include "menus/watches_menu.h"
#include "libtww/d/kankyo/d_kankyo.h"
#include "libtww/d/com/d_com_inf_game.h"
#include "libtww/f_op/f_op_scene_req.h"
#include "libtww/m_Do/m_Do_main.h"
#include "menus/tools_menu.h"
#include "input_viewer.h"

bool l_loadCard = true;
Texture l_twwgzIconTex;

extern "C" {

// Use the supplied string from the Makefile
#define MAKESTRING(S) MAKESTRING_(S)
#define MAKESTRING_(S) #S

#define INTERNAL_GZ_VERSION MAKESTRING(GZ_VERSION)

#if (NTSCJ)
#define main_trampoline ((void (*)(void))0x80336068)
#endif

#if (NTSCU)
#define main_trampoline ((void (*)(void))0x80338668)
#endif

void apply_lib_hooks() {
    Hook::applyHooks();
    main_trampoline();
}

void init() {
    Font::loadFont("twwgz/fonts/consola.fnt");
    Draw::init();
    if (l_twwgzIconTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("twwgz/tex/twwgz.tex", &l_twwgzIconTex);
    }
}

void game_loop() {
    // check and load gz settings card if found
    GZ_loadGZSave(l_loadCard);

    // Make title screen / file select endless night
    // disabled until new file crash fix is implemented
    /* if (!tww_strcmp(g_dComIfG_gameInfo.play.mStartStage.mStage, "Name") ||
    !tww_strcmp(g_dComIfG_gameInfo.play.mStartStage.mStage, "sea_T")) {
        g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().mTime = 1.0f;
        g_env_light.mCurTime = 1.0f;
        g_env_light.mColPatCurr = 1;
        g_env_light.mbThunderActive = 1;
        g_env_light.mRainCount = 250;
    } */

    if (tww_mPadStatus.button == (CButton::L | CButton::R | CButton::DPAD_DOWN) &&
        l_fopScnRq_IsUsingOfOverlap != 1) {
        GZ_setMenu(GZ_MAIN_MENU);
    }

    if (l_fopScnRq_IsUsingOfOverlap) {
        GZ_clearMenu();
    }

    GZ_setCursorColor();
}

void displaySplash() {
    // Create and render a splash screen once the game has launched using the supplied address
    extern u32* mDoExt_font0;
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

        Vec2 icon_pos = {splash_x - 48.0f, splash_y - 8.0f};
        Vec2 icon_scale = {32, 32};

        // Draw the string
        Font::GZ_drawStr(name, splash_x, splash_y, ColorPalette::WHITE, true, 18.0f);
        Font::GZ_drawStr(url, splash_x, splash_y + 25.0f, ColorPalette::WHITE, true, 18.0f);

        // Draw twwgz's logo
        if (l_twwgzIconTex.loadCode == TexCode::TEX_OK) {
            Draw::drawRect(ColorPalette::WHITE, icon_pos, icon_scale, &l_twwgzIconTex._texObj);
        }

        // Then when splash_time hits < 1, it won't display the string or logo anymore
        splash_time--;
        if (splash_time == 0 && l_twwgzIconTex.loadCode == TexCode::TEX_OK) {
            free_texture(&l_twwgzIconTex);
        }
    }
}

void draw() {
    // Setup rendering so we can display things on screen
    setupRendering();
    displaySplash();

    if (GZ_checkMenuOpen()) {
        Font::GZ_drawStr("twwgz v" INTERNAL_GZ_VERSION, 10.0f, 25.0f, g_cursorColor, g_dropShadows);
    }

    if (g_tools[ZH_INDEX].active) {
        ToolsMenu::displayZombieHoverInfo();
    }

    if (g_tools[DEBUG_INDEX].active) {
        ToolsMenu::displayLinkInfo();
    }

    if (g_tools[INPUT_VIEWER_INDEX].active) {
        InputViewer::draw();
    }

    GZ_drawMenu();
    WatchesMenu::drawWatches();
}
}

void GZ_drawString(const char* string, f32 x_pos, f32 y_pos, u32 color) {
    Font::GZ_drawStr(string, x_pos, y_pos, color, g_dropShadows);
}
