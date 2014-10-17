// main.c

#include "sys/kernel.h"

void _sdcc_heap_init();

void main(void)
{
    printf("\n\rZINIX v%d.%d for the N8VEM\n\r\n", 
            MAJOR_VERSION, MINOR_VERSION);
    mm_init();
    ptable_init();
    intr = 1;
    enable_intr();

    swapbank(KMOD_FS);
    bankcpy(KMOD_FS, 0x100, ROM_2, 0, 0x4000); 

    kmod_init();

    panic("end of main!");
}
