/* bio.c - block IO hardware */

#include "types.h"
#include <string.h>
#include "debug.h"

#define SEC_PER_TRACK 256

#define BIO_READ    0
#define BIO_WRITE   1

__sfr __at 0xfd HDSK;

int sm_open() {
	char x;
	for(x = 0; x < 32; x++)
		HDSK = 0x1; // reset
    return 0;
}

int sm_read(dev_t d, char *b, long off, int n) {

}

int sm_write(dev_t d, char *b, long off, int n) {
}

void simh_bio_rw(char *buf, dev_t d, char op, long block) {
	uint16_t track;
	uint8_t sector;

	track = block / SEC_PER_TRACK;
	sector = block % SEC_PER_TRACK;

	switch (op) {
		case BIO_READ:	HDSK = 0x2; break;
		case BIO_WRITE:	HDSK = 0x3; break;
	} // potential to fall through here, bool?

	HDSK = 0x0;		// hdsk 0
	HDSK = sector;	// sector 
	HDSK = (uint8_t) track; 
	HDSK = (uint8_t) (track >> 8);		// track 
	HDSK = (uint8_t) buf;
	HDSK = (uint8_t)((uint16_t)buf >> 8);	// dma
	sector = HDSK;
}
