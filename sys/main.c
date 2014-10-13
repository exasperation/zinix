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
#include "sys/queue.h"
#include <stdlib.h>
#include "sys/conf.h"

void main()
{
    queue_t *q;
    int j;
    int i;
    int x;
    printf("\n\rZINIX v%d.%d for the N8VEM\n\r\n", 
            MAJOR_VERSION, MINOR_VERSION);
    mm_init();
    _sdcc_heap_init();
    initProcQueues();

    bankcpy(RAM_0, 0x100, ROM_2, 0x0, 0x4000);
    bankcpy(RAM_1, 0x100, ROM_2, 0x0, 0x4000);
    enable_intr();


    __asm
        jp 0x100
        __endasm;

    panic("end of main!");
}
