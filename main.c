// main.c

#include <stdint.h>
#include "debug.h"
#include "trap.h"
#include "dev.h"
#include "mm.h"
#include <string.h>
#include <stdio.h>

char buf[512];

void main()
{
	printf("starting...\n\r");
    swapbank(RAMBANK, 15);
    hexdump(0x1000, 0x100);

	panic("end of main!");
}
