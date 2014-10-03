#include <string.h>
#include <stdio.h>
#include "debug.h"
#include "mm.h"
#include "mesg.h"

extern zpage;
long ticks;

mesg_t msg;

void syscall(mesg_t *m)
{
    memcpy(&msg, m, sizeof(msg));
    printf("mesg type: %x, mp1: %x\n\r",  msg.m_target, msg.mp1);
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
