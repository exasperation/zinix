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

int insys;


uint8_t u_call;
msg_t  *u_msg;

handle_msg()
{
    if (u_msg->op == KERNEL_PUTCHAR)
        putchar(u_msg->mb1);
}

void syscall()
{
    if (insys)
        panic("syscall in kernel");
    u_call = (tr_af >> 8 & 0xff);     // syscall is in A
    u_msg = tr_hl;         // pointer to message in userspace
    
    /* no imposters allowed */
/*    if (u_msg->src != cp->p_pid)
    {
        u_msg->op = -1;
        u_msg->errno = EINVAL;
        printf("pid: %d: EINVAL syscall");
        return;
    } */
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
