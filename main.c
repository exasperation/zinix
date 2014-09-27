// main.c

#include <stdint.h>
#include "debug.h"
#include "trap.h"
#include "dev.h"
#include <string.h>
#include <stdio.h>

char buf[512];

void main() {
    int i;
	printf("starting...\n\r");
	enable_intr();
	//simh_hdsk_reset();
    for(;;);
	panic("end of main!");
}
