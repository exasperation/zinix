#include <stdint.h>
#include <stdio.h>

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

void disk_setbuffer(char *buf) {
	__asm
		ld hl, #2
		add hl, sp
		ld c, (hl)
		inc hl
		ld b, (hl)
		ld h, b
		ld l, c
		ld b, #0x19
		rst 08
	__endasm;
}

uint16_t disk_getbuffer() {
	__asm
		ld b, #0x18
		rst 08
	__endasm;
}

void disk_read(char dev, long lba) {
	__asm
		ld b, #0x10
		ld hl, #2
		add hl, sp
		ld c, (hl)
		inc hl
		ld d, (hl)
		inc hl
		ld e, (hl)
		ld hl, #0
		rst 08
	__endasm;
}

void main() {
	int x;
	disk_setbuffer(buf);
	disk_read(0x80, 0);
	
	for (x = 0; x < 512; x++) 
		printf("%02x ", buf[x]);
}
