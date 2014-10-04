#include <string.h>
#include <stdio.h>
#include "debug.h"
#include "mm.h"
#include "mesg.h"
#include "trap.h"

int tr_af;
int tr_bc;
int tr_de;
int tr_hl;
int tr_ix;
int tr_iy;
int tr_af_;
int tr_bc_;
int tr_de_;
int tr_hl_;
int tr_sp;
int tr_pc;

extern zpage;
long ticks;

mesg_t msg;

char *p;

void syscall()
{
//    printf("AF: %4x  BC: %4x  DE: %4x  HL: %4x  IX: %4x  IY: %4x\n\rPC: %4x  SP: %4x\n\r", tr_af, tr_bc, tr_de, tr_hl, tr_ix, tr_iy, tr_pc, tr_sp);
    p = tr_hl;
    
    putchar(*p);
}

void isr()
{
}

void enable_intr()
{
    char i;
    ticks = 0;

    for (i = RAM_0; i < RAM_E; i++)
    {
        swapbank(i);
        memcpy(0x0, &zpage, 64);
    }

    swapbank(RAM_0);
    __asm
    im 1
    ei
    __endasm;
}
