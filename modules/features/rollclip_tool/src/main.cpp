#include <main.h>
#include "rollclip_tool.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"

namespace twwgz::modules {
void main() {
    g_drawListener->addListener(RollClip::GZ_rollClipInfo);
}
void exit() {
    g_drawListener->removeListener(RollClip::GZ_rollClipInfo);
}

}  // namespace twwgz::modules