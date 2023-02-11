#include "color.h"
#include "libtww/SSystem/SComponent/c_counter.h"

#define NUM_RAINBOW_COLORS 6

int rainbow() {
	switch(cCt_getFrameCount() % NUM_RAINBOW_COLORS) {
		case 0: return ColorPalette::RED;
		case 1: return ColorPalette::ORANGE;
		case 2: return ColorPalette::YELLOW;
		case 3: return ColorPalette::GREEN;
		case 4: return ColorPalette::BLUE;
		default: return ColorPalette::PURPLE;
	}
}