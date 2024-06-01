#include "utils/hook.h"
#include <cstdio>
#include "boot.h"
#include "controller.h"
#include "libtww/include/addrs.h"
#include "rels/include/patch.h"
#include "rels/include/cxx.h"
#include "rels/include/defines.h"

#define HOOK_DEF(rettype, name, params)                                                            \
    typedef rettype(*tp_##name##_t) params;                                                        \
    tp_##name##_t name##Trampoline;

HOOK_DEF(void, fapGm_Execute, (void));
HOOK_DEF(void, ExceptionCallback, (void));
HOOK_DEF(void, draw, (void*));
HOOK_DEF(uint32_t, PADRead, (uint16_t*));

namespace Hook {
void gameLoopHook(void) {
    game_loop();
    fapGm_ExecuteTrampoline();
    post_game_loop();
}

void drawHook(void* p1) {
    drawTrampoline(p1);
    draw();
}

#ifdef PR_TEST
void myExceptionCallbackHook(void) {
    ExceptionCallbackTrampoline();
    *reinterpret_cast<uint32_t*>(CRASH_ADDRESS) = 1;
    DCFlushRange((void*)(CRASH_ADDRESS), sizeof(uint32_t));
    ICInvalidateRange((void*)(CRASH_ADDRESS), sizeof(uint32_t));
}
#endif  // PR_TEST

uint32_t readControllerHook(uint16_t* p1) {
    auto returnValue = PADReadTrampoline(p1);
    GZ_readController();
    return returnValue;
}

#define draw_console draw__17JUTConsoleManagerCFv
#define f_fapGm_Execute fapGm_Execute__Fv

extern "C" {
uint32_t PADRead(uint16_t*);
void draw_console(void*);
void f_fapGm_Execute();
}

KEEP_FUNC void applyHooks() {
#define APPLY_HOOK(name, addr, func) name##Trampoline = hookFunction((tp_##name##_t)(addr), func)
    APPLY_HOOK(fapGm_Execute, &f_fapGm_Execute, gameLoopHook);
    APPLY_HOOK(draw, &draw_console, drawHook);
    APPLY_HOOK(PADRead, &PADRead, readControllerHook);

#undef APPLY_HOOK
}
}  // namespace Hook