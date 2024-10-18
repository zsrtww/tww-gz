#include "modules.h"
#include "libtww/include/defines.h"

#include "commands.h"
#include "global_data.h"
#include "settings.h"
#include "tools.h"

KEEP_VAR twwgz::containers::deque<Module*> g_modules;

/**
 * @brief   Handles when to load or unload REL modules.
 *          Registered to run before the main loop.
 */
KEEP_FUNC void GZ_handleModules() {
    for (auto mod : g_modules) {
        if (mod->active() && !mod->rel.isLoaded()) {
            mod->rel.load(true);
        }
        if (!mod->active() && mod->rel.isLoaded()) {
            mod->rel.close();
        }
    }
}

KEEP_FUNC bool inputViewer_active() {
    return GZStng_getData(STNG_TOOLS_INPUT_VIEWER, false);
}

KEEP_FUNC bool actorView_active() {
    return g_actorViewEnabled;
}