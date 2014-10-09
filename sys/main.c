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
    int i;
    int *p;
    printf("starting...\n\r");

    enable_intr();
    mm_init();
    init_ptable();

    for (i = 0; i < 16; i++)
        printf("%x\n\r", acquire_page(FREE_PAGE));

    panic("end of main!");
}
