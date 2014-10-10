// main.c

#include <stdint.h>
#include "sys/debug.h"
#include "sys/trap.h"
#include "sys/dev.h"
#include "sys/mm.h"
#include "sys/proc.h"
#include <string.h>
#include <stdio.h>
#include "sys/message.h"

void main()
{
    int i;
    int *p;
    printf("starting...\n\r");

    enable_intr();
    mm_init();

    bankcpy(RAM_0, 0x100, ROM_2, 0, 0x6000);
    swapbank(RAM_0);

    hexdump(0x0, 0x200);
    brk();    
    __asm
        jp 0x100
    __endasm;

    panic("end of main!");
}
