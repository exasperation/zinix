// main.c

#include <stdint.h>
#include "kernel/debug.h"
#include "kernel/trap.h"
#include "kernel/dev.h"
#include "kernel/mm.h"
#include <string.h>
#include <stdio.h>
#include "msg.h"

void main()
{
    printf("starting...\n\r");
    bankcpy(RAM_0, 0x100, ROM_2, 0, 0x6000);
    enable_intr();

    __asm
        jp 0x100
        __endasm;


    panic("end of main!");
}
