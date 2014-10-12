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

void main()
{
    Queue *mq;
    printf("starting...\n\r");
    enable_intr();
    mm_init();
    _sdcc_heap_init();

    panic("end of main!");
}
