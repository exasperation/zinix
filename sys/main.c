// main.c

#include "sys/kernel.h"

void _sdcc_heap_init();

void main()
{
    printf("\n\rZINIX v%d.%d for the N8VEM\n\r\n", 
            MAJOR_VERSION, MINOR_VERSION);
    mm_init();
    ptable_init();
    intr = 1;
    enable_intr();

    initproc(1, ROM_2, 0, 0x7500);

    __asm__("jp 0x100");

    panic("end of main!");
}
