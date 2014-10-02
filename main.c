// main.c

#include <stdint.h>
#include "debug.h"
#include "trap.h"
#include "dev.h"
#include "mm.h"
#include <string.h>
#include <stdio.h>
#include "mesg.h"

void main()
{
	printf("starting...\n\r");
    enable_intr();
    

    __asm
        ld hl,#0x1234
        rst 0x30
    __endasm;

    panic("end of main!");
}
