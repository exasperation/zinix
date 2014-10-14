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

void _sdcc_heap_init();

void main()
{
    printf("\n\rZINIX v%d.%d for the N8VEM\n\r\n", 
            MAJOR_VERSION, MINOR_VERSION);

    mm_init();
    _sdcc_heap_init();
    ptable_init();

    initproc(1, ROM_2, 0, 0x1000);
    initproc(2, ROM_3, 0, 0x1000);
    enable_intr();

    panic("end of main!");
}
