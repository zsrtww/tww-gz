#include "lib.h"
#include "font.h"
#include "utils/draw.h"
#include "utils/hook.h"

void init() {
    cdyl_init_async();  // call to original function first
    *reinterpret_cast<u8*>(0x803f60e0) = 1;  // Enable debug crash screen
    Draw::init();
}

void game_loop() {

}


void draw() {
    
}