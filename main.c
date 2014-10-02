// main.c

#include <stdint.h>
#include "debug.h"
#include "trap.h"
#include "dev.h"
#include "mm.h"
#include <string.h>
#include <stdio.h>

char b2[512];

void main()
{
    int i;
	printf("starting...\n\r");
    enable_intr();
    __asm__("di");

    swapbank(RAM_A);
    hexdump(0, 0x100);
    bankcpy(RAM_A, 10, ROM_2, 0, 0x4000);
    hexdump(0, 0x100);

    panic("end of main!");
}
