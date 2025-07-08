#include "settings.h"
#include "rels/include/defines.h"
#include <cstdio>

KEEP_VAR ListMember g_font_opt[] = {"consola",   "calamity-bold",  "lib-sans",      "lib-sans-bold",
                                    "lib-serif", "lib-serif-bold", "press-start-2p"};

KEEP_VAR bool g_dropShadows = true;
KEEP_VAR bool g_angleValuesInDecimal = false;
KEEP_VAR bool g_customSaveSpawns = true;
KEEP_VAR uint32_t g_fontType = 0;
KEEP_VAR uint32_t g_cursorColorType;
KEEP_VAR int g_buffer_input = 1;

void GZ_initFont() {
    if (g_fontType >= 0 && g_fontType < FONT_OPTIONS_COUNT) {
        char buf[40] = {0};
        snprintf(buf, sizeof(buf), "twwgz/fonts/%s.fnt", g_font_opt[g_fontType].member);
        Font::loadFont(buf);
    }
}
