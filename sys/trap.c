#include <string.h>
#include <stdio.h>
#include "sys/debug.h"
#include "sys/mm.h"
#include "sys/message.h"
#include "sys/trap.h"
#include "sys/proc.h"
#include <stdint.h>

#define SYS_SEND        1

#define ENOSYS          2
#define EACCES          3
#define EINVAL          4

/* temporary registers
 *
 * these hold the value of the registers of a process *or the kernel*
 * at the time of an interrupt or syscall
 */

regs_t tr;

char inkernel;


extern zpage;
long ticks;

msg_t msg;

char *p;

void dump_regs()
{
    printf("AF: %4x  BC: %4x  DE: %4x  HL: %4x  IX: %4x  IY: %4x\n\rPC: %4x  SP: %4x  AF': %4x  BC': %4x  DE': %4x  HL': %4x\n\r", tr.r_af, tr.r_bc, tr.r_de, tr.r_hl, tr.r_ix, tr.r_iy, tr.r_pc, tr.r_sp, tr.r_af_, tr.r_bc_, tr.r_de_, tr.r_hl_);
}

int insys;

uint8_t u_call;
msg_t  *u_msg;

handle_msg()
{
    //printf("message @ %04x -- src: %02x, dst: %02x, op, %02x, i1: %04x, b1: %02x\n\r", 
    //    u_msg, u_msg->src, u_msg->dst, u_msg->op, u_msg->mi1, u_msg->mb1);
    if (u_msg->op == KERNEL_PUTCHAR)
        putchar(u_msg->mb1);
}

void syscall()
{
    inkernel = 1;
    u_call = (tr.r_af >> 8) & 0xff;
    u_msg = tr.r_hl;
    //dump_regs();
    handle_msg();
    inkernel = 0;
}

void isr()
{
    if(!inkernel)
        schedule();
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
