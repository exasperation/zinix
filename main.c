// main.c

#include <stdint.h>
#include "debug.h"
#include "bio.h"
#include "trap.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>

char buf[512];

void main() {
    int i;
	printf("starting...\n\r");
	enable_intr();
	simh_hdsk_reset();

	panic("end of main!");
}
