// main.c

#include <stdint.h>
#include "debug.h"
#include "trap.h"
#include "dev.h"
#include "mm.h"
#include <string.h>
#include <stdio.h>
#include "mesg.h"
#include "queue.h"

void main()
{
    printf("starting...\n\r");
//    enable_intr();

    swapbank(ROM_2);
    hexdump(0, 0x200);
    panic("end of main!");
}
