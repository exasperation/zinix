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
	int x;


	ticks = 0;
	printf("%x\n\r", &zpage);

	__asm
		im 1
	__endasm;

	memcpy(0x0, &zpage, 128);

	hexdump(&zpage, 128);
	hexdump(0, 128);

	__asm
		ei
	__endasm;

	printf("ticks: %d", ticks);

	for (;;);

	panic("end of main!");
}
