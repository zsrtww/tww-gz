#include "utils/hook.h"
#include "lib.h"
#include "addrs.h"
#include "utils/patch.h"

#define HOOK_DEF(rettype, name, params)                                                            \
    typedef rettype(*tww_##name##_t) params;                                                        \
    tww_##name##_t name##Trampoline;

HOOK_DEF(void, draw, (void*));

struct {
    uint32_t a[2];
} trampolines[HOOK_AMNT];

namespace Hook {
void drawHook(void* p1) {
    drawTrampoline(p1);
    draw();
}

void applyHooks() {
#define APPLY_HOOK(name, addr, idx, func)                                                          \
    name##Trampoline = hookFunction((tww_##name##_t)addr, trampolines[idx].a, func)
    APPLY_HOOK(draw, tww_draw_console_addr, 0, drawHook);

#undef APPLY_HOOK
}
}  // namespace Hook