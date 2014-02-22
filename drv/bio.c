/* bio.c - block IO hardware */

#include "types.h"
#include "bio.h"
#include <string.h>
#include "bcache.h"
#include "debug.h"
#include <stdio.h>

// prototypes

void hbios_setbuffer(char *buf);
uint16_t hbios_getbuffer();

// globals

char disk_buf[512];

// public interface

/* copy 512 bytes from dev d to buf */
void bio_read(char *buf, dev_t d, long block) {
	hbios_setbuffer(disk_buf);
	hbios_diskread(0x80, block);
	printf("%x -> %x\n\r", &disk_buf, buf);
	memcpy(buf, disk_buf, 512);
}

void bio_write(char *buf, dev_t d, long block) {
}

/* HBIOS functions
 *
 * See http://n8vem-sbc.pbworks.com/w/file/fetch/55667257/RomWBW%20Architecture.pdf
 * for more details about HBIOS.
 *
 * HBIOS requires the disk buffer be in high mem (above 0x8000) */

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

/* Disk Read – DIORD ($10) 

Input 
B=$10 (function)	Read a single 512 byte sector into the buffer previously 
C=Device/Unit 		specified buffer area (see DIOSBA). 
HL=Track			For a hard disk device, only LBA addressing is supported. 
D=Head				In this case, HL will contain the high 16 bits of 
E=Sector			the LBA block number and DE will contain the low 16 bits 
					of the LBA block number. 	

Output		A=Status (0=OK, 1=Error)   */

// DE = LBA_low, HL = LBA_high, B = 0x10, C = dev

// currently only works on the first 16 bits, limiting size to 32 MB

void hbios_diskread(char dev, uint32_t block) {
	__asm
	ld hl, #2
	add hl, sp
	ld c, (hl)
	inc hl	
	ld e, (hl)
	inc hl 
	ld d, (hl)
	ld hl, #0
	ld b, #0x10
	rst 08
	__endasm;
}
