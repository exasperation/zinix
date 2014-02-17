#include <stdint.h>
#include <stdio.h>
#include "debug.h"

// main.c

uint8_t buf[512];

void putchar(char c) {
	__asm
		ld hl, #2
		add hl, sp
		ld e, (hl)
		ld b, #01
		ld c, #0
		rst 08
	__endasm;
}

char getchar() {
	__asm
		ld b, #0
		ld c, #0
		rst 08
		ld l, e
	__endasm;
}

void main() {
	hexdump(buf, sizeof(buf));
}
