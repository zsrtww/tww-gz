#include <main.h>
#include "features/moveactor/include/moveactor.h"
#include "rels/include/cxx.h"
#include "events/post_loop_listener.h"

namespace twwgz::modules {
void main() {
    g_PostLoopListener->addListener(MoveActor::execute);
}
void exit() {
    g_PostLoopListener->removeListener(MoveActor::execute);
}

}  // namespace twwgz::modules