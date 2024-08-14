#include <main.h>
#include "features/actor_view/include/actor_view.h"
#include "rels/include/cxx.h"
#include "events/pre_loop_listener.h"

namespace twwgz::modules {
void main() {
    g_PreLoopListener->addListener(ActorViewer::execute);
}
void exit() {
    g_PreLoopListener->removeListener(ActorViewer::execute);
}

}  // namespace twwgz::modules