/* bio.c - block IO hardware */

#include "types.h"
#include "bio.h"

// prototypes

void hbios_setbuffer(char *buf);
uint16_t hbios_getbuffer();
void hbios_diskread(char dev, long lba);

// public interface

void read_block(char *buf, dev_t d, long block) {
	hbios_setbuffer(buf);
	hbios_diskread(0x80, block);
}

void bwrite(char *buf, long block) {
}

/* HBIOS functions
 *
 * See http://n8vem-sbc.pbworks.com/w/file/fetch/55667257/RomWBW%20Architecture.pdf
 * for more details about HBIOS.
 *
 * HBIOS requires the disk buffer be in high mem (above 0x8000) */

char disk_buf[512];

void hbios_setbuffer(char *buf) {
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

uint16_t hbios_getbuffer() {
	__asm
		ld b, #0x18
		rst 08
	__endasm;
}

void hbios_diskread(char dev, long lba) {
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
