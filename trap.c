#include <string.h>
#include "debug.h"

long ticks;

void isr() {
	ticks++;
}

void reset() {
	panic("reset");
}

extern zpage;

void enable_intr() {
	ticks = 0;
	memcpy(0x0, &zpage, 128);
	__asm
		im 1
		ei
	__endasm;
}

