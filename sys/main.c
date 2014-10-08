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
    printf("starting...\n\r");

    enable_intr();
    mm_init();
    init_ptable();

    acquire_page(RAM_0);
    acquire_page(RAM_0);

    panic("end of main!");
}
