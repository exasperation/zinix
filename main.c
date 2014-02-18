#include <stdint.h>
#include "debug.h"
#include "bio.h"
#include "bcache.h"


// main.c

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
	bcache_init();

	panic("end of main!");
}
