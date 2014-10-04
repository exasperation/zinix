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
    bankcpy(RAM_0, 0x100, ROM_2, 0, 0x6000);
    enable_intr();

    __asm
        jp 0x100
        __endasm;


    panic("end of main!");
}
