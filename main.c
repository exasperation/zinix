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
    enable_intr();

    brk();
	panic("end of main!");
}
