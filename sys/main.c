// main.c

#include "sys/kernel.h"

void _sdcc_heap_init();

void main()
{
    printf("\n\rZINIX v%d.%d for the N8VEM\n\r\n", 
            MAJOR_VERSION, MINOR_VERSION);
    mm_init();
    ptable_init();

    initproc(1, ROM_2, 0, 0x1000);

    intr = 1;
    enable_intr();
    swtch(1);

    for (;;);

    panic("end of main!");
}
