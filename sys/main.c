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

int i;

struct p_entry *fpe;

void main()
{
    printf("starting...\n\r");
    enable_intr();
    mm_init();
    for(i = 0; i < 1000; i++)
        printf("%d - %x\r\n", i, kmalloc(sizeof(int)));

    panic("end of main!");
}
