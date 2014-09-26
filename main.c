// main.c

#include <stdint.h>
#include "debug.h"
#include "sm.h"
#include "trap.h"
#include "sr.h"
#include "fs.h"
#include <string.h>
#include <stdio.h>

char buf[512];

void main() {
    int i;
	printf("starting...\n\r");
	enable_intr();
	simh_hdsk_reset();
    fs_init();
	panic("end of main!");
}
