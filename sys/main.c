// main.c

#include "sys/kernel.h"

void _sdcc_heap_init();

void (*fsmain)( void (*)(char) );

void main()
{
    printf("\n\rZINIX v%d.%d for the N8VEM\n\r\n", 
            MAJOR_VERSION, MINOR_VERSION);
    mm_init();
    ptable_init();
    intr = 1;
    enable_intr();

    bankcpy(RAM_0, 0x100, ROM_2, 0, 0x4000); 

    printf("%p\n\r", &putchar);

    fsmain = (void*) 0x100;

    fsmain(&putchar);

    panic("end of main!");
}
