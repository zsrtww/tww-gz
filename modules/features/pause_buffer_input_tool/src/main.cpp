#include <main.h>
#include "pause_buffer_input.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"

namespace twwgz::modules {
void main() {
    g_drawListener->addListener(PauseBufferInputTool::GZ_PauseBufferInputTool);
}
void exit() {
    g_drawListener->removeListener(PauseBufferInputTool::GZ_PauseBufferInputTool);
}

}  // namespace twwgz::modules
