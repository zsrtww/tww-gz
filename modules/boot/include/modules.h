#pragma once

#include "utils/rels.h"
#include "utils/containers/deque.h"

struct Module {
    bool (*active)();
    twwgz::dyn::GZModule rel;
};

extern twwgz::containers::deque<Module*> g_modules;

void GZ_handleModules();

bool inputViewer_active();
bool actorView_active();
bool rollClipTool_active();