// main.c

#include <stdint.h>
#include "debug.h"
#include "bio.h"
#include <string.h>
#include <stdio.h>

char buf[512];

void main() {
	printf("starting...\n\r");
	enable_intr();
	simh_hdsk_reset();

	panic("end of main!");
}
