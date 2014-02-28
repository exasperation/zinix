/* bio.c - block IO hardware */

#include "types.h"
#include "bio.h"
#include <string.h>
#include "bcache.h"
#include "debug.h"
#include <stdio.h>

#define SEC_PER_TRACK 256

__sfr __at 0xfd HDSK;

void simh_hdsk_reset() {
	char x;
	for(x = 0; x < 32; x++)
		HDSK = 0x1; // reset
}

void bio_rw(char op, char *buf, dev_t d, long block) {
	uint16_t track;
	uint8_t sector;

	track = block / SEC_PER_TRACK;
	sector = block % SEC_PER_TRACK;

	switch (op) {
		case BIO_READ:	HDSK = 0x2; break;
		case BIO_WRITE:	HDSK = 0x3; break;
		default:	panic("bio - invalid op");
	}

	HDSK = 0x0;		// hdsk 0
	HDSK = sector;	// sector 
	HDSK = (uint8_t) track; 
	HDSK = (uint8_t) (track >> 8);		// track 
	HDSK = (uint8_t) buf;
	HDSK = (uint8_t)((uint16_t)buf >> 8);	// dma
	sector = HDSK;
}
