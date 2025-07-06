#include <main.h>
#include "bomb_push_clip_tool.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"

namespace twwgz::modules {
void main() {
    g_drawListener->addListener(BombPushClipTool::GZ_BombPushClipTool);
}
void exit() {
    g_drawListener->removeListener(BombPushClipTool::GZ_BombPushClipTool);
}

}  // namespace twwgz::modules
