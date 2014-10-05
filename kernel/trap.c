#include <string.h>
#include <stdio.h>
#include "kernel/debug.h"
#include "kernel/mm.h"
#include "msg.h"
#include "kernel/trap.h"
#include <stdint.h>

#define SYS_SEND        1

/* temporary registers
 *
 * these hold the value of the registers of a process *or the kernel*
 * at the time of an interrupt or syscall
 */

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

msg_t msg;

char *p;

void dump_regs()
{
    printf("AF: %4x  BC: %4x  DE: %4x  HL: %4x  IX: %4x  IY: %4x\n\rPC: %4x  SP: %4x  AF': %4x  BC': %4x  DE': %4x  HL': %4x\n\r", tr_af, tr_bc, tr_de, tr_hl, tr_ix, tr_iy, tr_pc, tr_sp, tr_af_, tr_bc_, tr_de_, tr_hl_);
}

int inkernel;


uint8_t u_call;
msg_t  *u_msg;

handle_msg()
{
    switch (u_msg->op)
    {
        case KERNEL_PUTCHAR:
            putchar(u_msg->mb1);
            break;
    }
}

void syscall()
{
    if (inkernel)
        panic("syscall in kernel");
    u_call = (tr_af >> 8 & 0xff);     // syscall is in A
    u_msg = tr_hl;         // pointer to message in userspace
    // do some verification that the message is valid, etc.
    handle_msg();
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
