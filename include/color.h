#pragma once

#define NUM_COLORS 8

enum ColorPalette {
	RED    = 0xCC0000FF,
	ORANGE = 0xEE8000FF,
	YELLOW = 0xFFCC00FF,
	GREEN  = 0x00CC00FF,
	BLUE   = 0x0080FFFF,
	PURPLE = 0x6600CCFF,
	WHITE  = 0xFFFFFFFF,
	BLACK  = 0x00000000
};

int rainbow();