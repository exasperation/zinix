// main.c

#include <stdint.h>
#include "debug.h"
#include "bio.h"
#include "bcache.h"
#include <string.h>
#include <stdio.h>

char buf[512];

void main() {
	int i;
	struct buf *b;
	
	printf("starting...\n\r");
	enable_intr();
	bcache_init();
	simh_hdsk_reset();

	b = bcache_read(0, 4);
	memcpy(buf, b->data, 512);
	bcache_relse(b);

	for (i = 5; i < 1000; i++) {
		b = bcache_read(0, i);
		memcpy(b->data, buf, 512);
		bcache_write(b);
		bcache_relse(b);
	}
	panic("end of main!");
}
