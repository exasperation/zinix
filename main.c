// main.c

#include <stdint.h>
#include "debug.h"
#include "bio.h"
#include "bcache.h"
#include <string.h>
#include <stdio.h>

long ticks;

void isr() {
	ticks++;
}

void reset() {
	panic("reset");
}

extern zpage;

void main() {
	ticks = 0;

	__asm
		im 1
		ei
	__endasm;

	memcpy(0x0, &zpage, 128);

	panic("end of main!");
}
